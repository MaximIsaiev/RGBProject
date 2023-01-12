#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include <iostream>
/**
 * namespace Printing предполагает что в этойм пространстве имён кроме данного класса будет что-то ещё, касающееся принтеров,
 *  например, логика, связывающее каким-то образом взаимодействие принтеров
 */
namespace Printing {
/**
 * @brief The Printer class - класс, который предназначен для вывода в выходной поток подаваемых на вход строк.
 * вывод непосредственно реализует метод print()
 *
 * ТЗ:
 *    объекты класса, созданные через конктруктор по умолчанию должны выводить строки, поступающие в метод print() в консоль,
 *    вывод из консоли не должен быть перенаправлен
 *
 *    вывод следующей строки через метод print() должен начинаться с новой строки
 *
 *    так же, должна быть возможность в качестве выходного потока определить собственны, задаваемы пользователем
 *
 *    в программе количество принтеров должно быть точно известно в любой момент
 *
 *
 *    поведение при копировании и перемещении объектов этого класса считать undefined.
 */
	class Printer {
	public:
		/**
		 * @brief Printer конструктор по умолчанию
		 */
		Printer();
		/**
		 * @brief Printer конктруктор с параметром
		 * @param customStream поток вывода, задаваемый пользователем
		 */
		Printer(std::ostream& customStream);
		/**
		 * @brief print основной метод, печатьающий строкую
		 * @param stringForPrint - константная ссылка на строку для печати
		 */
		void print(const std::string& stringForPrint);
		/**
		 * @brief getCountCreatedPrinters метод, для получения созданных принтеров
		 * @return количество принетров находящийся в памяти
		 */
		static uint32_t getCountCreatedPrinters();

		~Printer();
	private:
		static uint32_t countCreaterPrinters;
		std::ostream& printStream;

		void incrementCreatedPrinters();
		void decrementCreatedPrinters();
	};
}

#endif
