#pragma once

#include <QObject>
#include <QUrl>
#include <QImage>

class RGBSimpleBackend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUrl simpleImage
               READ simpleImage
               WRITE setSimpleImage
               NOTIFY simpleImageChanged)
public:
    explicit RGBSimpleBackend(QObject *parent = nullptr);

    int start(int argc, char *argv[]);

    Q_INVOKABLE void hello_from_QML();

    Q_INVOKABLE void openByteArrayFile(QUrl filePath);

    const QUrl &simpleImage() const;
    void setSimpleImage(const QUrl &newSimpleImage);

signals:
    void simpleImageChanged();

private:
    QUrl m_simpleImage;
    QUrl imageToUrl(const QImage& image);
};

