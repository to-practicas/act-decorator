#pragma once
#include <string>
#include "ReportDecorator.h"

// DECORADOR CONCRETO: agrega un bloque de firma al final del reporte.
class SignatureDecorator : public ReportDecorator {
public:
    SignatureDecorator(std::unique_ptr<Report> wrapped, std::string signer);

    std::string generate() const override;
    std::string description() const override;

private:
    std::string signer_;
};
