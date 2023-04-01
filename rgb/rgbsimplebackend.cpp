#include "rgbsimplebackend.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QBuffer>
#include <QDebug>

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
    QFile file(filePath.toLocalFile());

    if (!file.open(QFile::ReadOnly)) {
        qDebug() << tr("Не удалось открыть файл");
        return;
    }

    QByteArray byteArray = file.readAll();

    // Где-то здесь будет происходить конвертация одномерного массива в двухмерный массив
    // и вообще вся магия
/*//File size
    fileRGB.seekg(0, std::ios::end);
    int size = fileRGB.tellg();
    std::cout << size << std::endl;
    fileRGB.seekg(0, std::ios::beg);

    std::vector<std::vector<uint8_t>> colorChannelsRGB(3);
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
    fileRGB.read((char*)&magicNumberRed, sizeof magicNumberRed); printf("%#x\n", magicNumberRed);
    while (position <= size - 4)
    {
        fileRGB.seekg(position, std::ios_base::beg);
        fileRGB.read((char*)&magicNumberRead, sizeof magicNumberRead);
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
        fileRGB.seekg(i, std::ios::beg);
        fileRGB.read((char*)&redPixel, sizeof(redPixel));
        redData.push_back(redPixel);
        //printf("%d\n", redPixel);
    }
    colorChannelsRGB[0].resize(lengthOfColorData);
    colorChannelsRGB[0].assign(redData.begin(), redData.end());

    //GreenChanel
    fileRGB.seekg(endRedChannel + 4, std::ios_base::beg);
    startGreenChannel = endRedChannel + 4;
    position = startGreenChannel + 4;
    fileRGB.read((char*)&magicNumberGreen, sizeof magicNumberGreen); printf("%#x\n", magicNumberGreen);
    while (position <= size - 4)
    {
        fileRGB.seekg(position, std::ios_base::beg);
        fileRGB.read((char*)&magicNumberRead, sizeof magicNumberRead);
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
        fileRGB.seekg(i, std::ios::beg);
        fileRGB.read((char*)&greenPixel, sizeof(greenPixel));
        greenData.push_back(greenPixel);
        //printf("%d\n", greenPixel);
    }
    colorChannelsRGB[1].resize(lengthOfColorData);
    colorChannelsRGB[1].assign(greenData.begin(), greenData.end());

    //BlueChanel
    fileRGB.seekg(endGreenChannel + 4, std::ios_base::beg);
    startBlueChannel = endGreenChannel + 4;
    position = startBlueChannel + 4;
    fileRGB.read((char*)&magicNumberBlue, sizeof magicNumberBlue); printf("%#x\n", magicNumberBlue);
    while (position <= size - 4)
    {
        fileRGB.seekg(position, std::ios_base::beg);
        fileRGB.read((char*)&magicNumberRead, sizeof magicNumberRead);
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
        fileRGB.seekg(i, std::ios::beg);
        fileRGB.read((char*)&bluePixel, sizeof(bluePixel));
        blueData.push_back(bluePixel);
        //printf("%d\n", bluePixel);
    }
    colorChannelsRGB[2].resize(lengthOfColorData);
    colorChannelsRGB[2].assign(blueData.begin(), blueData.end());*/

    QImage image;
    image.loadFromData(byteArray);
    setSimpleImage(imageToUrl(image));
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
