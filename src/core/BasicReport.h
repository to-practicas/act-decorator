#pragma once
#include <string>
#include "Report.h"

// COMPONENTE CONCRETO: el reporte "simple", sin funcionalidades extra.
class BasicReport : public Report {
public:
    BasicReport(std::string title, std::string body);

    std::string generate() const override;
    std::string description() const override;

private:                       // ENCAPSULAMIENTO
    std::string title_;
    std::string body_;
};