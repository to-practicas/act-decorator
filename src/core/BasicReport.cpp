#include "BasicReport.h"

BasicReport::BasicReport(std::string title, std::string body)
    : title_(std::move(title)), body_(std::move(body)) {}

std::string BasicReport::generate() const {
    return "=== " + title_ + " ===\n\n" + body_ + "\n";
}

std::string BasicReport::description() const {
    return "Reporte basico";
}