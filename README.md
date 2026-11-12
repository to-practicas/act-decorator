# Grupo 5 - Patron Decorator: Reportes con fecha, autor y firma


Reportes con fecha, autor y firma usando el patrón Decorator (C++ / Qt).


**Integrantes:** 
- Wilber Jesus Guerra Pilco
- Jhon Deyvis Cuyo Ccapa
- Diego Sebastian Santa Cruz Villa
- Cristhian Matias Bravo Arredondo
- Jaime Daniel Igreda Alvarado
- Fernando Gerson Luque Guevara


## Explicacion breve
El patron **Decorator** permite agregar funcionalidades a un objeto **sin modificar su clase** y
sin crear una subclase por cada combinacion. Aqui partimos de un `BasicReport` (titulo + contenido)
y le "envolvemos" decoradores:


- `DateDecorator`: agrega la fecha al inicio.
- `AuthorDecorator`: agrega el autor al inicio.
- `SignatureDecorator`: agrega un bloque de firma al final.


Cada decorador **es un `Report`** (hereda de la misma interfaz) y **tiene un `Report`** (el que envuelve),
por eso se pueden apilar en cualquier combinacion:


```
SignatureDecorator( DateDecorator( AuthorDecorator( BasicReport ) ) )
```


Al llamar `generate()` sobre el decorador de afuera, cada capa pide el texto a la capa interior
y le agrega lo suyo.


## Roles del patron en el codigo
| Rol del patron | Clase |
|---|---|
| Componente (interfaz) | `Report` |
| Componente concreto | `BasicReport` |
| Decorador base (abstracto) | `ReportDecorator` |
| Decoradores concretos | `DateDecorator`, `AuthorDecorator`, `SignatureDecorator` |
| Cliente | `ReportComposer`, `main_console.cpp`, `MainWindow` |


## POO usada
- **Clases y encapsulamiento:** atributos privados (`title_`, `author_`, `signer_`, `wrapped_`).
- **Herencia y polimorfismo:** `Report` (abstracta) -> `BasicReport` y `ReportDecorator` -> decoradores concretos.
- **Composicion:** `ReportDecorator` guarda un `std::unique_ptr<Report>`.
- **Qt:** `MainWindow` hereda de `QMainWindow`.


## Estructura
```
src/core/     Patron Decorator (C++ puro, reutilizable)
src/console/  Demo por consola
src/qt/       Interfaz grafica Qt
tests/        Pruebas automaticas
docs/         Diagrama de clases y lista de pruebas
```


## Compilar
```
cmake -S . -B build
cmake --build build
./build/test_decorator
./build/decorator_console
./build/decorator_qt        # si Qt esta instalado
```
En Qt Creator: abrir `CMakeLists.txt` y ejecutar.


## Uso
- **Consola:** el menu permite editar los datos, activar o desactivar cada decorador, mostrar el reporte
  y ver la opcion 9, que muestra paso a paso como se apilan los decoradores.
- **Qt:** al marcar o desmarcar Fecha / Autor / Firma, el reporte y la "cadena de decoradores" se
  actualizan al instante. Tambien se puede guardar el resultado en un `.txt`.


## Responsables
| Integrante | Rama | Aporte |
|---|---|---|
| Wilber | `feature/wilber-estructura-build` | Estructura del repo, CMake, README, integración |
| Jhon | `feature/jhon-componente-base` | `Report`, `BasicReport` y `ReportDecorator` (base del patrón) |
| Diego | `feature/diego-decoradores-fecha-autor` | `DateDecorator` y `AuthorDecorator` |
| Cristhian | `feature/cristhian-composer-consola` | `ReportComposer` y demo por consola |
| Jaime | `feature/jaime-qt-ventana` | Ventana principal Qt y `main_qt.cpp` |
| Gerson | `feature/gerson-firma-tests-docs` | `SignatureDecorator`, pruebas y documentación |


Todas las ramas se integran en `main` mediante Pull Request.