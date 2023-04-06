#include "printer/printer.h"

int main()
{
    Printing::Printer printer;

    printer.print(" Hello Word! ");
    std::cerr << " принтеров создано: " << Printing::Printer::getCountCreatedPrinters() << std::endl;

    Printing::Printer* ptrToprinter = nullptr;

    ptrToprinter = new Printing::Printer();

    std::cerr << " принтеров создано: " << Printing::Printer::getCountCreatedPrinters() << std::endl;

    delete ptrToprinter;

    std::cerr << " принтеров создано: " << Printing::Printer::getCountCreatedPrinters() << std::endl;

	return 0;
}
