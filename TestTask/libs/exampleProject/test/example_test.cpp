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

/**
 * @brief этот тест запускает gui-приложение
 */

