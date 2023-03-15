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
