# Lista de pruebas

| # | Prueba | Cómo hacerla | Resultado esperado |
|---|---|---|---|
| 1 | Pruebas automáticas | `./build/test_decorator` | Muestra "Todas las pruebas pasaron correctamente" |
| 2 | Reporte básico | Consola: desactivar opciones 5, 6 y 7, luego opción 8 | Solo aparecen título y contenido |
| 3 | Cada decorador por separado | Consola: dejar activo solo uno y pulsar opción 8 | Aparece únicamente su funcionalidad (fecha, autor o firma) |
| 4 | Apilar decoradores | Consola: opción 9 (demo paso a paso) | Cada paso agrega una funcionalidad sobre el anterior |
| 5 | Cadena de decoradores (Qt) | Marcar y desmarcar Fecha / Autor / Firma | La etiqueta "Cadena de decoradores" y el texto cambian al instante |
| 6 | Guardar (Qt) | Pulsar "Guardar como .txt" y abrir el archivo | El archivo contiene el mismo texto de la vista previa |

Responsable de las pruebas: Gerson.
