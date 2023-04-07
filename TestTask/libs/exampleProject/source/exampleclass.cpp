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

    QFile file(fileName);

    if (!file.open(QFile::ReadOnly)) {
        qDebug() << tr("Не удалось открыть файл");
        return;
    }

    QByteArray byteArray = file.readAll();

    // Где-то здесь будет происходить конвертация одномерного массива в двухмерный массив
    // и вообще вся магия


    QImage newImage;
    newImage.loadFromData(byteArray);

    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->adjustSize();
}
