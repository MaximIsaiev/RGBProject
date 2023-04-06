#ifndef EXAMPLECLASS_H
#define EXAMPLECLASS_H
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>

class ExampleClass : public QWidget
{
public:
    ExampleClass(QWidget *parent = nullptr);
private:
    QLabel *imageLabel;
    QImage image;
    QVBoxLayout *layout;

    void createActions();
    void open();
};

#endif // EXAMPLECLASS_H
