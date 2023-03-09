#include "printer/printer.h"
#include "rgb/rgbsimplebackend.h"

int main(int argc, char *argv[])
{
    Printing::Printer printer;

    printer.print(" Hello Word! ");
    std::cerr << " принтеров создано: " << Printing::Printer::getCountCreatedPrinters() << std::endl;

    Printing::Printer* ptrToprinter = nullptr;

    ptrToprinter = new Printing::Printer();

    std::cerr << " принтеров создано: " << Printing::Printer::getCountCreatedPrinters() << std::endl;

    delete ptrToprinter;

    std::cerr << " принтеров создано: " << Printing::Printer::getCountCreatedPrinters() << std::endl;

    auto app = new RGBSimpleBackend();

    return app->start(argc, argv);
}
