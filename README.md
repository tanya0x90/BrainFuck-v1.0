## BF-Compiler: Un Compilador de Brainfuck en C

Este proyecto es un compilador ligero y eficiente escrito en C para el lenguaje de programación esotérico Brainfuck. El compilador traduce el código Brainfuck directamente en instrucciones ejecutables o lo interpreta en tiempo de ejecución.

## Resumen del Lenguaje

Brainfuck opera sobre una cinta de memoria de celdas (usualmente 30,000) inicializadas en cero, y un puntero de datos que apunta a la celda actual. Solo utiliza 8 comandos simples:
Comando Descripción

>     Incrementa el puntero de datos (mueve a la derecha).
>
> < Decrementa el puntero de datos (mueve a la izquierda).

- Incrementa el valor en la celda actual.

* Decrementa el valor en la celda actual.
  . Imprime el carácter ASCII de la celda actual.
  , Lee un carácter de la entrada y lo guarda en la celda actual.
  [ Si la celda es 0, salta adelante hasta el ] correspondiente.
  ] Si la celda no es 0, salta atrás hasta el [ correspondiente.
