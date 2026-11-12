#pragma once
#include <memory>
#include <stdexcept>
#include "Report.h"

// ============================================================
//  DECORADOR BASE (abstracto)
//  - ES un Report (hereda de Report).
//  - TIENE un Report (el reporte que envuelve).
//  Por defecto delega todo en el reporte envuelto; los decoradores
//  concretos sobrescriben generate() para agregar su funcionalidad.
// ============================================================
class ReportDecorator : public Report {
public:
    explicit ReportDecorator(std::unique_ptr<Report> wrapped)
        : wrapped_(std::move(wrapped)) {
        if (!wrapped_) throw std::invalid_argument("ReportDecorator: el reporte envuelto es nulo");
    }

    std::string generate() const override { return wrapped_->generate(); }
    std::string description() const override { return wrapped_->description(); }

protected:
    // Acceso de solo lectura al reporte envuelto para las clases hijas
    const Report& inner() const { return *wrapped_; }

private:
    std::unique_ptr<Report> wrapped_;
};