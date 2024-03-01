# Práctica 1: [Cálculo de la eficiencia de algoritmos]

Este proyecto proporciona un conjunto de herramientas y scripts para compilar, ejecutar pruebas y generar gráficas a partir de archivos fuente en C++.

## Requisitos

- **G++**: Un compilador de C++ que soporte el estándar C++11.
- **Gnuplot**: Una herramienta para generar gráficas a partir de datos.

## Estructura del Proyecto

El proyecto tiene la siguiente estructura de carpetas:

- **src**: Contiene los archivos fuente en C++. **¡IMPORTANTE** El nombre de los archivos debe estar en inglés y en SnakeCase, con la primera letra mayúscula. De lo contrario, las gráficas no se generarán.
- **bin**: Aquí se almacenan los binarios ejecutables generados.
- **dat**: Carpeta donde se guardan los datos generados por las pruebas.
- **img**: Las gráficas generadas se almacenan en esta carpeta.

## Uso

### Compilación

Para compilar el proyecto, ejecuta el siguiente comando:

```bash
make
```

### Ejecución de pruebas
Para ejecutar las pruebas y generar datos y las gráficas:

```bash
make test
```

### Limpieza
Para eliminar todos los archivos generados:
```bash
make clean
```
### Ayuda
Para obtener una lista de todas las opciones disponibles, ejecuta:
```bash
make help
```
