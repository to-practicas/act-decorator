# Diagrama de clases

```mermaid
classDiagram
    class Report {
        <<interface>>
        +generate() string
        +description() string
    }
    class BasicReport {
        -title_ : string
        -body_ : string
    }
    class ReportDecorator {
        <<abstract>>
        -wrapped_ : Report
        #inner() Report
    }
    class DateDecorator {
        -fixedDate_ : string
    }
    class AuthorDecorator {
        -author_ : string
    }
    class SignatureDecorator {
        -signer_ : string
    }
    class ReportComposer {
        <<funcion>>
        +composeReport(options) Report
    }
    class MainWindow

    Report <|-- BasicReport
    Report <|-- ReportDecorator
    ReportDecorator <|-- DateDecorator
    ReportDecorator <|-- AuthorDecorator
    ReportDecorator <|-- SignatureDecorator
    ReportDecorator o-- Report : envuelve a otro
    ReportComposer ..> ReportDecorator : crea y apila
    MainWindow ..> ReportComposer : usa
```

## Lectura del diagrama
- **Report** es la interfaz común: todo lo que se puede "generar" es un `Report`.
- **BasicReport** es el objeto original, sin funcionalidades extra.
- **ReportDecorator** es a la vez un `Report` (herencia) y **tiene** un `Report` (el que envuelve). Por eso se pueden apilar.
- **DateDecorator**, **AuthorDecorator** y **SignatureDecorator** agregan cada uno una sola funcionalidad.
- **composeReport** arma la cadena según lo que elija el usuario: `BasicReport -> Autor -> Fecha -> Firma`.