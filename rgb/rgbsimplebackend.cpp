#include "rgbsimplebackend.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QBuffer>
#include <QDebug>
#include <fstream>
#include <string>
#include <iostream>

RGBSimpleBackend::RGBSimpleBackend(QObject *parent)
    : QObject{parent}
{
    qmlRegisterType<RGBSimpleBackend>("tdd.project", 1, 0, "RGBSimpleBackend");
}

int RGBSimpleBackend::start(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

void RGBSimpleBackend::hello_from_QML()
{
    qDebug() << "hello from QML!";
}

void RGBSimpleBackend::openByteArrayFile(QUrl filePath)
{
    std::ifstream file;
    QString qPath = filePath.toLocalFile();
    std::string path = qPath.toStdString();
    file.open(path, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        qDebug() << tr("Не удалось открыть файл");
        return;
    }

    //QByteArray byteArray = file.readAll();

    // Где-то здесь будет происходить конвертация одномерного массива в двухмерный массив
    // и вообще вся магия
    //File size
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    //std::cout << size << std::endl;
    file.seekg(0, std::ios::beg);

    std::vector<QRgb> pixelsRGB;
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

    pixelsRGB.resize(lengthOfColorData);
    for (int i = 0; i < lengthOfColorData; i++)
    {
        pixelsRGB[i] = qRgb(redData[i] ,greenData[i] ,blueData[i] );
    }

    int width = 100, height = 100; // your valid values here

    // what you're interesting in
    auto image(QImage((uint8_t *)pixelsRGB.data(), width, height, QImage::Format_RGB888));

    //QImage image;
    //image.loadFromData(byteArray);
    setSimpleImage(imageToUrl(image));

    file.close();
}

const QUrl &RGBSimpleBackend::simpleImage() const
{
    return m_simpleImage;
}

void RGBSimpleBackend::setSimpleImage(const QUrl &newSimpleImage)
{
    if (m_simpleImage == newSimpleImage)
        return;
    m_simpleImage = newSimpleImage;
    emit simpleImageChanged();
}

QUrl RGBSimpleBackend::imageToUrl(const QImage& image)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "jpg");
    QString base64 = QString::fromUtf8(byteArray.toBase64());
    return QString("data:image/jpg;base64,") + base64;
}
