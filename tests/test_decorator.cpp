// Pruebas automaticas del patron Decorator (sin Qt).
#undef NDEBUG
#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include "AuthorDecorator.h"
#include "BasicReport.h"
#include "DateDecorator.h"
#include "ReportComposer.h"
#include "SignatureDecorator.h"

static bool contains(const std::string& s, const std::string& p) {
    return s.find(p) != std::string::npos;
}

int main() {
    // 1. Reporte basico: sin extras
    BasicReport basic("Titulo", "Cuerpo");
    assert(contains(basic.generate(), "Titulo"));
    assert(contains(basic.generate(), "Cuerpo"));
    assert(!contains(basic.generate(), "Fecha:"));
    assert(!contains(basic.generate(), "Autor:"));
    assert(!contains(basic.generate(), "Firma:"));
    assert(basic.description() == "Reporte basico");

    // 2. Cada decorador agrega SOLO lo suyo
    {
        DateDecorator d(std::make_unique<BasicReport>("T", "C"), "2026-01-01 10:00");
        assert(contains(d.generate(), "Fecha: 2026-01-01 10:00"));
        assert(contains(d.generate(), "C"));
        assert(!contains(d.generate(), "Autor:"));

        AuthorDecorator a(std::make_unique<BasicReport>("T", "C"), "Wilber");
        assert(contains(a.generate(), "Autor: Wilber"));
        assert(!contains(a.generate(), "Fecha:"));

        SignatureDecorator s(std::make_unique<BasicReport>("T", "C"), "Jhon");
        assert(contains(s.generate(), "Firma:"));
        assert(contains(s.generate(), "Jhon"));
    }

    // 3. Apilar decoradores: orden de las partes
    {
        std::unique_ptr<Report> r = std::make_unique<BasicReport>("TITULO", "CUERPO");
        r = std::make_unique<AuthorDecorator>(std::move(r), "Diego");
        r = std::make_unique<DateDecorator>(std::move(r), "2026-02-02 08:00");
        r = std::make_unique<SignatureDecorator>(std::move(r), "Gerson");

        const std::string out = r->generate();
        const auto posFecha  = out.find("Fecha:");
        const auto posAutor  = out.find("Autor:");
        const auto posCuerpo = out.find("CUERPO");
        const auto posFirma  = out.find("Firma:");
        assert(posFecha < posAutor);    // la fecha queda arriba del autor
        assert(posAutor < posCuerpo);   // los encabezados van antes del cuerpo
        assert(posCuerpo < posFirma);   // la firma va al final

        assert(r->description() == "Reporte basico + Autor + Fecha + Firma");
    }

    // 4. composeReport segun las opciones elegidas
    {
        ReportOptions o;
        o.withDate = false; o.withAuthor = true; o.withSignature = false;
        auto r = composeReport(o);
        assert(contains(r->generate(), "Autor:"));
        assert(!contains(r->generate(), "Fecha:"));
        assert(!contains(r->generate(), "Firma:"));
        assert(r->description() == "Reporte basico + Autor");

        o.withDate = o.withAuthor = o.withSignature = true;
        auto full = composeReport(o);
        assert(contains(full->generate(), "Fecha:"));
        assert(contains(full->generate(), "Autor:"));
        assert(contains(full->generate(), "Firma:"));
    }

    // 5. Un decorador no acepta un reporte nulo
    {
        bool threw = false;
        try { DateDecorator d(nullptr); } catch (const std::invalid_argument&) { threw = true; }
        assert(threw);
    }

    std::cout << "Todas las pruebas pasaron correctamente\n";
    return 0;
}
