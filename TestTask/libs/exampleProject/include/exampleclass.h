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
    QLabel *imageLabel {nullptr};
    QImage image {nullptr};
    QVBoxLayout *layout {nullptr};
    QString filePath;
    int imageHeight {50};
    int imageWidth {50};
    QLabel *fileSizeLabel;
    QLabel *MagicNumbers;

    void createActions();
    void open();
    void readWidthAndHeight(QString &path);
};

#endif // EXAMPLECLASS_H
