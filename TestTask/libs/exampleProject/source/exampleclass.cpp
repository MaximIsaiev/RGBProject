#include "exampleclass.h"
#include <QApplication>
#include <QMainWindow>

const auto windowWidth = 1024;
const auto windowHeight = 720;

ExampleClass::ExampleClass()
{

}

int ExampleClass::initializeApplication(int &argc, char **argv)
{
    QApplication app(argc, argv);
    QMainWindow window;

    window.setFixedSize(windowWidth, windowHeight);
    window.show();

    return app.exec();
}
