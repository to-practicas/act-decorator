#pragma once
#include <string>

// ============================================================
//  COMPONENTE (interfaz comun del patron Decorator)
//  Tanto el reporte basico como todos los decoradores
//  cumplen esta misma interfaz.
// ============================================================
class Report {
public:
    virtual ~Report() = default;

    // Devuelve el texto completo del reporte
    virtual std::string generate() const = 0;

    // Describe la cadena de decoradores aplicada (util para depurar/explicar)
    virtual std::string description() const = 0;
};