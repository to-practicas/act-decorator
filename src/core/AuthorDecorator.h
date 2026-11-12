#pragma once
#include <string>
#include "ReportDecorator.h"

// DECORADOR CONCRETO: agrega el autor al inicio del reporte.
class AuthorDecorator : public ReportDecorator {
public:
    AuthorDecorator(std::unique_ptr<Report> wrapped, std::string author);

    std::string generate() const override;
    std::string description() const override;

private:
    std::string author_;
};