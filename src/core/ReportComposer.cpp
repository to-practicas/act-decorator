#include "ReportComposer.h"
#include "AuthorDecorator.h"
#include "BasicReport.h"
#include "DateDecorator.h"
#include "SignatureDecorator.h"

std::unique_ptr<Report> composeReport(const ReportOptions& o) {
    std::unique_ptr<Report> report = std::make_unique<BasicReport>(o.title, o.body);

    // Cada decorador "envuelve" al anterior.
    if (o.withAuthor)    report = std::make_unique<AuthorDecorator>(std::move(report), o.author);
    if (o.withDate)      report = std::make_unique<DateDecorator>(std::move(report));
    if (o.withSignature) report = std::make_unique<SignatureDecorator>(std::move(report), o.signer);

    return report;
}
