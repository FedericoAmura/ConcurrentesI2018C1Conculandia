# Aduana Conculandia

Este proyecto es un simulador de la oficina de aduanas del pais conculandia. Es el primer trabajo practico de la materia 75.59 Tecnicas de programacion concurrente I de la FIUBA

Para mas informacion, puede revisar el [informe](https://docs.google.com/document/d/1Z-Cl7awIQP-KW8EVxxx5jXw9S37zjfRLdaCBrTa8dXo "Informe")

## Diagrama de procesos

El siguiente diagrama de procesos modela los diferentes procesos que se ejecutan dentro del sistema asi como tambien las tecnicas de comunicacion y sincronizacion que utilizan entre ellos

![Diagrama de procesos](https://github.com/FedericoAmura/ConcurrentesI2018C1Conculandia/blob/master/diagramaProcesos.png "Diagrama de procesos")

## Ejecucion
Para correr el programa debe especificar los parametros para indicar la cantidad de ventanillas y sellos
`-v <cantidad de ventanillas>`
`-s <cantidad de sellos>`

Por ejemplo
```bash
./aduanaconculandia -v 5 -s 3
```

Una vez dentro del programa, un menu interactivo lo llevara por las diferentes opciones que desee ejecutar