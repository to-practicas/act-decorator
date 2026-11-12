#pragma once
#include <string>
#include "ReportDecorator.h"

// DECORADOR CONCRETO: agrega la fecha al inicio del reporte.
class DateDecorator : public ReportDecorator {
public:
    // Si fixedDate esta vacio, usa la fecha y hora actuales.
    explicit DateDecorator(std::unique_ptr<Report> wrapped, std::string fixedDate = "");

    std::string generate() const override;
    std::string description() const override;

private:
    static std::string currentDateTime();
    std::string fixedDate_;
};
