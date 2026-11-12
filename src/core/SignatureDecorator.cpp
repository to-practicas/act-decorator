#include "SignatureDecorator.h"

SignatureDecorator::SignatureDecorator(std::unique_ptr<Report> wrapped, std::string signer)
    : ReportDecorator(std::move(wrapped)), signer_(std::move(signer)) {}

std::string SignatureDecorator::generate() const {
    return inner().generate()
         + "\n------------------------------\n"
         + "Firma: ______________________\n"
         + "       " + signer_ + "\n";
}

std::string SignatureDecorator::description() const {
    return ReportDecorator::description() + " + Firma";
}
