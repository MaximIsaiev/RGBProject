#include "printer/printer.h"

Printing::Printer::Printer() : printStream(std::cerr)
{
	incrementCreatedPrinters();
}

Printing::Printer::Printer(std::ostream& customStream) : printStream(customStream)
{
	incrementCreatedPrinters();
}

void Printing::Printer::print(const std::string& stringForPrint)
{
	printStream << stringForPrint << "\n";
}

uint32_t Printing::Printer::getCountCreatedPrinters()
{
	return countCreaterPrinters;
}

void Printing::Printer::incrementCreatedPrinters()
{
	countCreaterPrinters++;
}

void Printing::Printer::decrementCreatedPrinters()
{
	countCreaterPrinters--;
}
Printing::Printer::~Printer()
{
	decrementCreatedPrinters();
}

uint32_t Printing::Printer::countCreaterPrinters = 0;
