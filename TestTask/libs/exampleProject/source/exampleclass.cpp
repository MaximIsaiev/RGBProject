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
#include <QPushButton>
#include <fstream>
#include <string>
#include <iostream>


const auto windowWidth = 1024;
const auto windowHeight = 720;

ExampleClass::ExampleClass(QWidget *parent) : QWidget(parent), imageLabel(new QLabel(this))
{
    setWindowTitle(tr("Analog Clock"));
    resize(windowWidth, windowHeight);
    layout = new QVBoxLayout(this);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    layout->addWidget(imageLabel);
    createActions();
}

void ExampleClass::createActions()
{
    auto button = new QPushButton("File",this);
    layout->addWidget(button);

    connect(button, &QPushButton::clicked, this, &ExampleClass::open);
}

void ExampleClass::open()
{
    QString fileName =  QFileDialog::getOpenFileName(
                this,
                "Open Document",
                QDir::currentPath(),
                "All files (*.*) ;; PNG files (*.png)");

    /*QFile file(fileName);

    if (!file.open(QFile::ReadOnly)) {
        qDebug() << tr("Не удалось открыть файл");
        return;
    }

    QByteArray byteArray = file.readAll();*/

    // Где-то здесь будет происходить конвертация одномерного массива в двухмерный массив
    // и вообще вся магия
    std::ifstream file;
    std::string path = fileName.toStdString();
    file.open(path, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        qDebug() << tr("Не удалось открыть файл");
        return;
    }

    //File size
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    //std::cout << size << std::endl;
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

    /*pixelsRGB.resize(lengthOfColorData);
    for (int i = 0; i < lengthOfColorData; i++)
    {
        pixelsRGB[i] = qRgb(redData[i] ,greenData[i] ,blueData[i] );
    }*/

    int width = 100, height = 100; // your valid values here


    //auto newImage(QImage((uchar *)pixelsRGB.data(), width, height, QImage::Format_RGB888));

    QImage newImage(width, height, QImage::Format_RGB888);
      newImage.fill(QColor(Qt::green).rgb());

      for (int x = 0; x < height; ++x)
      {
        for (int y = 0; y < width; ++y)
        {
          newImage.setPixel(x, y, qRgb(redData[x * width + y], greenData[x * width + y], blueData[x * width + y]));
        }
      }

    //QImage image;
    //image.loadFromData(byteArray);
    //setSimpleImage(imageToUrl(image));

    file.close();

    //QImage newImage;
    //newImage.loadFromData(byteArray);

    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->adjustSize();
}
