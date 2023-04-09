#ifndef EXAMPLECLASS_H
#define EXAMPLECLASS_H
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>

class ExampleClass : public QWidget
{
public:
    ExampleClass(QWidget *parent = nullptr);

    void readWidthAndHeight(QString &path);

    int getImageHeght() const;
    int getImageWidth() const;

private:
    QLabel *imageLabel {nullptr};
    QImage image {nullptr};
    QVBoxLayout *layout {nullptr};
    QString filePath;
    int imageHeight {0};
    int imageWidth {0};
    QLabel *fileSizeLabel;
    QLabel *MagicNumbers;

    void createActions();
    void open();
};

#endif // EXAMPLECLASS_H
