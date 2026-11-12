#include "DateDecorator.h"
#include <ctime>

DateDecorator::DateDecorator(std::unique_ptr<Report> wrapped, std::string fixedDate)
    : ReportDecorator(std::move(wrapped)), fixedDate_(std::move(fixedDate)) {}

std::string DateDecorator::currentDateTime() {
    std::time_t now = std::time(nullptr);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", std::localtime(&now));
    return buf;
}

std::string DateDecorator::generate() const {
    const std::string date = fixedDate_.empty() ? currentDateTime() : fixedDate_;
    return "Fecha: " + date + "\n" + inner().generate();
}

std::string DateDecorator::description() const {
    return ReportDecorator::description() + " + Fecha";
}