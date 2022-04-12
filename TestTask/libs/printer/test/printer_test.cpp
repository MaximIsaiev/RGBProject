#include <gtest/gtest.h>
#include "printer.h"

/**
 * @brief этот тест ничего не тестирует. это стартовый тест, который был написан до написания кода свомого принтера.
 * если этот тест проходит успешно, то конструкторы этого класса реализованны и с созданием объекта всё ок.
 */
TEST(PrinterTests, Creating) {
	Printing::Printer testedObject;
	Printing::Printer testedObject1(std::cerr);
}
/**
 * @brief TEST в этом тесте не создаётся объектов. поэтому число созданных объектов равно нулю
 */
TEST(PrinterTests, CheckCountCreatedObjects_nothing) {
	ASSERT_EQ(Printing::Printer::getCountCreatedPrinters(), 0);
}
/**
 * @brief TEST создаём три подряд объекта. счётчик созданных объектов равен нулю
 */
TEST(PrinterTests, CheckCountCreatedObjects) {
	Printing::Printer testedObject;
	Printing::Printer testedObject1;
	Printing::Printer testedObject2;

	ASSERT_EQ(Printing::Printer::getCountCreatedPrinters(), 3);
}
/**
 * @brief TEST создаётся три подряд объекта в куче. далее по одному объекты начинают удаляться.
 * после каждого последующего удаления количество созданных принеторов декрементируется.
 * и достигает нуля, когда каждый из созданных обектов уничтожился.
 *
 */
TEST(PrinterTests, CheckCountCreatedObjectsWithDelete) {
	Printing::Printer* testedObject = new Printing::Printer();
	Printing::Printer* testedObject1 = new Printing::Printer();
	Printing::Printer* testedObject2 = new Printing::Printer();

	delete  testedObject;
	ASSERT_EQ(Printing::Printer::getCountCreatedPrinters(), 2);
	delete  testedObject1;
	ASSERT_EQ(Printing::Printer::getCountCreatedPrinters(), 1);
	delete  testedObject2;
	ASSERT_EQ(Printing::Printer::getCountCreatedPrinters(), 0);
}
/**
 * @brief этот тест проверяет печатает ли принтер вообще что-то, результат виден только в виде вывода в консоль
 */
TEST(PrinterTests, printing_stock) {
	Printing::Printer testedObject;
	testedObject.print(" Hello Word! ");
}
/**
 * @brief этот тест проверяет печатает ли принтер путём подстановки собственного потока вывода.
 * в данном случае это объект класса std::stringstream
 * результат печати должен находиться в объекте printString, и должен представлять из себя сторку для печати + escape последовательность '\n'
 * '\n' переводит каретку в начало следующей строки
 */
TEST(PrinterTests, printing_custom) {
	std::stringstream printString;

	Printing::Printer testedObject(printString);

	testedObject.print(" Hello Word! ");

	auto printerResult = printString.str();
	ASSERT_EQ(printerResult, (" Hello Word! \n"));
}
