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
    stepByStepDemo(opt); // menu interactivo: pendiente
    return 0;
}
