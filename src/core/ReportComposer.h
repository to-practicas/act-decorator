#pragma once
#include <memory>
#include <string>
#include "Report.h"

// Opciones que elige el usuario (las usan la consola y la interfaz Qt).
struct ReportOptions {
    std::string title  = "Informe mensual";
    std::string body   = "Este es el contenido del reporte.";
    std::string author = "Equipo Grupo 5";
    std::string signer = "Equipo Grupo 5";
    bool withDate      = true;
    bool withAuthor    = true;
    bool withSignature = true;
};

// Arma la cadena de decoradores segun las opciones elegidas:
// BasicReport -> Autor -> Fecha -> Firma
std::unique_ptr<Report> composeReport(const ReportOptions& options);
