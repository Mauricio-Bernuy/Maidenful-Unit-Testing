## Programa para verificar si un usuario es mayor de edad (c++)
```bash
g++ -O0 main.cpp -o program && ./program -t
```
## Tests unitarios
Valida el correcto comportamiento del:
* parser de fechas
* validación del formato de fecha
* validación de fecha de query mayor que fecha de nacimiento
* validación de mayor de edad

### codigo de validación:

![](https://i.imgur.com/I2RkbWD.png)

### output de consola original (18/18 tests passing)

![](https://i.imgur.com/imFriKc.png)

---
Pudiendo verificar el correcto funcionamiento de los métodos actuales, se procederá a hacer un refactor del método *CorrectDateFormat*, el cual es dificil de interpretar y propenso a errores al tratar de modificar alguna parte de la lógica.

### CorrectDateFormat previo a refactor
![](https://i.imgur.com/qQ29bmW.png)

Se realizó una implementación del código simplificada, más fácil de interpretar y con comentarios sobre las diferentes partes de la lógica.

### CorrectDateFormat luego del refactor
![](https://i.imgur.com/jLYgjev.png)

Corriendo nuevamente los tests, podemos ver que igualmente se consiguen los 18/18 tests de la función original, por lo que el refactor fue exitoso.
### output de consola refactored (18/18 tests passing)
![](https://i.imgur.com/Q12LaIN.png)
