# Aduana Conculandia

Este proyecto es un simulador de la oficina de aduanas del país conculandia. Es el primer trabajo práctico de la materia 75.59 Técnicas de programación concurrente I de la FIUBA

Para mas información, puede revisar el [informe](https://docs.google.com/document/d/1Z-Cl7awIQP-KW8EVxxx5jXw9S37zjfRLdaCBrTa8dXo "Informe")

## Diagrama de procesos

El siguiente diagrama de procesos modela los diferentes procesos que se ejecutan dentro del sistema así como también las técnicas de comunicación y sincronización que utilizan entre ellos

![Diagrama de procesos](https://github.com/FedericoAmura/ConcurrentesI2018C1Conculandia/blob/master/diagramaProcesos.png "Diagrama de procesos")

## Instalación
Para la instalación de este proyecto debe contar con cmake y las herramientas de compilación para C++11

Primero debe copiar el repositorio en el directorio destino

````bash
$ git clone https://github.com/FedericoAmura/ConcurrentesI2018C1Conculandia.git
````

Luego debe ejecutar cmake y posteriormente make para compilar los archivos fuente
````bash
$ cmake
$ make
````

Una vez terminado, ya podrá pasar a la sección de ejecución

## Ejecución
Para correr el programa debe especificar los parámetros para indicar la cantidad de ventanillas y sellos
`-v <cantidad de ventanillas>`
`-s <cantidad de sellos>`

Opcionalmente, tambien puede especificar la opción `-d` para ejecutar el programa en modo debug e ir generando un archivo log

Por ejemplo:
```bash
$ ./aduanaconculandia -v 5 -s 3 -d
```

Una vez dentro del programa, un menú interactivo lo llevará por las diferentes opciones que desee ejecutar

