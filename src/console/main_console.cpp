// Demo por consola (sin Qt) del patron Decorator.
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include "AuthorDecorator.h"
#include "BasicReport.h"
#include "DateDecorator.h"
#include "ReportComposer.h"
#include "SignatureDecorator.h"

namespace {

void printReport(const std::string& label, const Report& r) {
    std::cout << "\n--- " << label << " ---\n"
              << "Cadena: " << r.description() << "\n\n"
              << r.generate() << "\n";
}

std::string ask(const std::string& prompt) {
    std::cout << prompt;
    std::string v;
    std::getline(std::cin, v);
    return v;
}

// Muestra como cada decorador va "envolviendo" al anterior.
void stepByStepDemo(const ReportOptions& o) {
    std::unique_ptr<Report> r = std::make_unique<BasicReport>(o.title, o.body);
    printReport("1) Reporte basico", *r);

    r = std::make_unique<AuthorDecorator>(std::move(r), o.author);
    printReport("2) + AuthorDecorator", *r);

    r = std::make_unique<DateDecorator>(std::move(r));
    printReport("3) + DateDecorator", *r);

    r = std::make_unique<SignatureDecorator>(std::move(r), o.signer);
    printReport("4) + SignatureDecorator", *r);
}

const char* onOff(bool b) { return b ? "SI" : "NO"; }

} // namespace


int main() {
    ReportOptions opt;
    int op = -1;

    while (op != 0) {
        std::cout << "\n=== Reportes con Decorator ===\n"
                  << "1. Cambiar titulo (" << opt.title << ")\n"
                  << "2. Cambiar contenido\n"
                  << "3. Cambiar autor (" << opt.author << ")\n"
                  << "4. Cambiar firmante (" << opt.signer << ")\n"
                  << "5. Activar/desactivar fecha [" << onOff(opt.withDate) << "]\n"
                  << "6. Activar/desactivar autor [" << onOff(opt.withAuthor) << "]\n"
                  << "7. Activar/desactivar firma [" << onOff(opt.withSignature) << "]\n"
                  << "8. Mostrar reporte\n"
                  << "9. Demo paso a paso (como se apilan los decoradores)\n"
                  << "0. Salir\nOpcion: ";
        if (!(std::cin >> op)) break;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (op) {
            case 1: opt.title  = ask("Titulo: "); break;
            case 2: opt.body   = ask("Contenido: "); break;
            case 3: opt.author = ask("Autor: "); break;
            case 4: opt.signer = ask("Firmante: "); break;
            case 5: opt.withDate      = !opt.withDate; break;
            case 6: opt.withAuthor    = !opt.withAuthor; break;
            case 7: opt.withSignature = !opt.withSignature; break;
            case 8: { auto r = composeReport(opt); printReport("Reporte final", *r); break; }
            case 9: stepByStepDemo(opt); break;
            default: break;
        }
    }
    return 0;
}
