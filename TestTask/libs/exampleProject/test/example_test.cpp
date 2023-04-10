#include <gtest/gtest.h>
#include "exampleclass.h"
#include <QApplication>

/**
 * @brief этот тест ничего не тестирует. это стартовый тест, который был написан до написания кода свомого принтера.
 * если этот тест проходит успешно, то конструкторы этого класса реализованны и с созданием объекта всё ок.
 */
TEST(ExampleTests, Creating) {
    int argc {0};
    QApplication app(argc, nullptr);
    ExampleClass testedObject;
    testedObject.show();
    app.exec();
}

TEST(ExampleTests, ReadWidthAndHeight) {
    int argc {0};
    QApplication app(argc, nullptr);
    ExampleClass testedObject;

    QString case1 ("/home/100x100.dat");
    testedObject.readWidthAndHeight(case1);
    ASSERT_EQ(100, testedObject.getImageHeght()) << "Неправильная высота изображения";
    ASSERT_EQ(100, testedObject.getImageWidth()) << "Неправильная ширина изображения";

    QString case2 ("/home/150x190.dat");
    testedObject.readWidthAndHeight(case2);
    ASSERT_EQ(190, testedObject.getImageHeght()) << "Неправильная высота изображения";
    ASSERT_EQ(150, testedObject.getImageWidth()) << "Неправильная ширина изображения";

    QString case3 ("");
    testedObject.readWidthAndHeight(case3);
    ASSERT_EQ(0, testedObject.getImageHeght()) << "Неправильная высота изображения";
    ASSERT_EQ(0, testedObject.getImageWidth()) << "Неправильная ширина изображения";
}

