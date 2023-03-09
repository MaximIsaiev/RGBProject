#pragma once

#include <QObject>

class RGBSimpleBackend : public QObject
{
    Q_OBJECT
public:
    explicit RGBSimpleBackend(QObject *parent = nullptr);

    int start(int argc, char *argv[]);

    Q_INVOKABLE void hello_from_QML();

signals:

};

