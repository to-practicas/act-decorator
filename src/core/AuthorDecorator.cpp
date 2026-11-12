#include "AuthorDecorator.h"

AuthorDecorator::AuthorDecorator(std::unique_ptr<Report> wrapped, std::string author)
    : ReportDecorator(std::move(wrapped)), author_(std::move(author)) {}

std::string AuthorDecorator::generate() const {
    return "Autor: " + author_ + "\n" + inner().generate();
}

std::string AuthorDecorator::description() const {
    return ReportDecorator::description() + " + Autor";
}