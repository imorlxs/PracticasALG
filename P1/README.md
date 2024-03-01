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

## Compilación y Ejecución

1. Asegúrate de tener **g++** instalado en tu sistema.
2. Ejecuta `make ` para compilar todos los binarios.
3. Para generar los datos, ejecuta `make data`.
4. Si deseas crear las gráficas, utiliza `make graphic`.

## Limpieza

- `make clean`: Elimina todos los archivos generados y binarios.
- `make clean-data`: Elimina solo las tablas de datos.
- `make clean-img`: Elimina solo las gráficas.
- `make clean`: Elimina todos los archivos generados y binarios.


