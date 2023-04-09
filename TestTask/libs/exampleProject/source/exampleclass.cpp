#include "exampleclass.h"
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QMenuBar>
#include <QFileDialog>
#include <QImageReader>
#include <QDebug>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <fstream>
#include <string>
#include <iostream>


const auto windowWidth = 1024;
const auto windowHeight = 720;

ExampleClass::ExampleClass(QWidget *parent) : QWidget(parent),
    imageLabel(new QLabel(this)),
    MagicNumbers(new QLabel(this))
{
    setWindowTitle(tr("RGB Fixer"));
    resize(windowWidth, windowHeight);
    layout = new QVBoxLayout(this);
    imageLabel->setFixedSize(100, 100);
    setLayout(layout);
    layout->setAlignment(Qt::AlignTop);
    createActions();
}

void ExampleClass::createActions()
{
    auto formLayout = new QFormLayout(this);

    auto enterFileNameText = new QLabel(this);
    enterFileNameText->setText(tr("Введите путь к бинарному файлу:"));

    auto lineEdit = new QLineEdit(this);
    lineEdit->setAutoFillBackground(true);

    formLayout->addRow(enterFileNameText, lineEdit);
    formLayout->setSpacing(10);

    auto button = new QPushButton(tr("Открыть"), this);
    button->setFixedWidth(100);

    connect(button, &QPushButton::clicked, this, &ExampleClass::open);
    connect(lineEdit, &QLineEdit::textChanged, this, [this](QString path){
        filePath = path;
    });

    auto imageText = new QLabel(this);
    imageText->setText(tr("Преобразованная картинка:"));

    fileSizeLabel = new QLabel(this);


    layout->addItem(formLayout);
    layout->addWidget(button);
    layout->addWidget(imageText);
    layout->addWidget(imageLabel);
    layout->addWidget(fileSizeLabel);
    layout->addWidget(MagicNumbers);
}

void ExampleClass::open()
{
    QString fileName = filePath;
    fileName = QDir::toNativeSeparators(fileName);
    qDebug() << fileName;

    // Где-то здесь будет происходить конвертация одномерного массива в двухмерный массив
    // и вообще вся магия
    std::ifstream file;
    std::string path = fileName.toStdString();
    file.open(path, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        qDebug() << tr("Не удалось открыть файл");
        return;
    }

    readWidthAndHeight(fileName);
    imageLabel->setFixedSize(imageWidth, imageHeight);

    //File size
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    file.seekg(0, std::ios::beg);

    //std::vector<QRgb> pixelsRGB;
    uint32_t magicNumberRed = 0;
    uint32_t magicNumberGreen = 0;
    uint32_t magicNumberBlue = 0;
    uint32_t magicNumberRead = 0;
    int startRedChannel = 4;
    int endRedChannel = 0;
    int startGreenChannel = 0;
    int endGreenChannel = 0;
    int startBlueChannel = 0;
    int endBlueChannel = 0;
    int position = startRedChannel;
    std::vector<uint8_t> redData;
    std::vector<uint8_t> greenData;
    std::vector<uint8_t> blueData;

    //Red channel
    file.read((char*)&magicNumberRed, sizeof magicNumberRed); printf("%#x\n", magicNumberRed);
    while (position <= size - 4)
    {
        file.seekg(position, std::ios_base::beg);
        file.read((char*)&magicNumberRead, sizeof magicNumberRead);
        if (magicNumberRead == magicNumberRed)
        {
            endRedChannel = position;
            break;
        }
        position++;
    }
    int lengthOfColorData = endRedChannel - startRedChannel;

    uint8_t redPixel = 0;
    for (int i = startRedChannel; i < endRedChannel; i++)
    {
        file.seekg(i, std::ios::beg);
        file.read((char*)&redPixel, sizeof(redPixel));
        redData.push_back(redPixel);
        //printf("%d\n", redPixel);
    }

    //GreenChanel
    file.seekg(endRedChannel + 4, std::ios_base::beg);
    startGreenChannel = endRedChannel + 8;
    position = startGreenChannel + 8;
    file.read((char*)&magicNumberGreen, sizeof magicNumberGreen); printf("%#x\n", magicNumberGreen);
    while (position <= size - 4)
    {
        file.seekg(position, std::ios_base::beg);
        file.read((char*)&magicNumberRead, sizeof magicNumberRead);
        if (magicNumberRead == magicNumberGreen)
        {
            endGreenChannel = position;
            break;
        }
        position++;
    }

    uint8_t greenPixel = 0;
    for (int i = startGreenChannel; i < endGreenChannel; i++)
    {
        file.seekg(i, std::ios::beg);
        file.read((char*)&greenPixel, sizeof(greenPixel));
        greenData.push_back(greenPixel);
        //printf("%d\n", greenPixel);
    }

    //BlueChanel
    file.seekg(endGreenChannel + 4, std::ios_base::beg);
    startBlueChannel = endGreenChannel + 8;
    position = startBlueChannel + 8;
    file.read((char*)&magicNumberBlue, sizeof magicNumberBlue); printf("%#x\n", magicNumberBlue);
    while (position <= size - 4)
    {
        file.seekg(position, std::ios_base::beg);
        file.read((char*)&magicNumberRead, sizeof magicNumberRead);
        if (magicNumberRead == magicNumberBlue)
        {
            endBlueChannel = position;
            break;
        }
        position++;
    }

    uint8_t bluePixel = 0;
    for (int i = startBlueChannel; i < endBlueChannel; i++)
    {
        file.seekg(i, std::ios::beg);
        file.read((char*)&bluePixel, sizeof(bluePixel));
        blueData.push_back(bluePixel);
        //printf("%d\n", bluePixel);
    }

    int width = imageWidth, height = imageHeight; // your valid values here
    fileSizeLabel->setText(QString("Размер файла: %1 kB").arg(QString::number(size / 1024.0)));

    MagicNumbers->setText(QString("Первое магическое число: %1\nВторое магическое число: %2\nТретье магическое число: %3").arg(magicNumberRed, 0, 16).arg(magicNumberGreen, 0, 16).arg(magicNumberBlue, 0, 16));

    QImage newImage(width, height, QImage::Format_RGB888);
    newImage.fill(QColor(Qt::green).rgb());

    for (int x = 0; x < height; ++x)
    {
        for (int y = 0; y < width; ++y)
        {
            newImage.setPixel(x, y, qRgb(redData[x * width + y], greenData[x * width + y], blueData[x * width + y]));
        }
    }

    file.close();

    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->adjustSize();
}

void ExampleClass::readWidthAndHeight(QString &path)
{
    auto fileName = QDir(path).dirName();
    auto stringList = fileName.split('x');

    bool okWidth {false};
    bool okHeight {false};

    auto width = stringList.first().toInt(&okWidth);
    auto height = stringList.back().split('.').first().toInt(&okHeight);

    if (!okWidth || !okHeight) {
        qDebug() << tr("Файл имеет неверное наименование!");
        imageHeight = 0;
        imageWidth = 0;
        return;
    }

    imageHeight = height;
    imageWidth = width;

}

int ExampleClass::getImageHeght() const
{
    return imageHeight;
}

int ExampleClass::getImageWidth() const
{
    return imageWidth;
}
