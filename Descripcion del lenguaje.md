## Declaracion de variables númericas
Para nuestro lenguaje hemos decidido tener las variables básicas como son float, int char y sus distintos arrays, la declaracion de los mismos sería de la forma

#### Declaracion
```
int nombre
float nombre
char nombre

int nombre[]
float nombre[]
char nombre[]
````

Para la asignacion de expresiones y variables usamos el operador básico '=' como podemos ver en el siguiente ejemplo

#### Ejemplo

```
float nombre = 1.5236
int nombre = 5131
```

## Operaciones numéricas básicas

Las operaciones que hemos visto necesarias dentro de un lenguja y vamos a implementar en este trabajo son:
suma, resta, multiplicacion, division y modulo.

#### Suma
```
float a = 1.56
float b = 2.12
int c = 5
int d = 10

float sumaFloatFloat = a + b       # 3.68
float sumaFloatInt = a + c         # 6.56
int sumaIntInt = c + d             # 15
int sumaFloatInt = b + d           # 12
```
#### Resta
```
float a = 1.56
float b = 2.12
int c = 5
int d = 10

float restaFloatFloat = a - b       # -0.56
float restaFloatInt = a - c         # -3.34
int restaIntInt = c - d             # -5
int restaFloatInt = b - d           # -7

```
#### Multiplicación
```
float a = 1.56
float b = 2.12
int c = 5
int d = 10

float mulFloatFloat = a * b         # 3.30
float mulFloatInt = a * c           # 7
int mulIntInt = c * d               # 50
int mulFloatInt = b * d             # 21
```
#### División
```
float a = 1.56
float b = 2.12
int c = 5
int d = 10

float divideFloatFloat = a / b      # 0.73
float divideFloatInt = a / c        # 0.312
int divideIntInt = c / d            # 0.5
int divideFloatInt = b / d          # 0.212
int divideBy0 = c / 0               # Error
float divideBy0 = a / 0             # Error

```
#### Módulo
```
float a = 1.56
float b = 2.12
int c = 5
int d = 10
int e = -1

float moduloFloatFloat = a % b       # Error
float moduloFloatInt = a % c         # Error
int moduloIntInt = c % d             # 5
int moduloFloatInt = b % d           # Error
int moduloIntIntNeg = d % e          # 0 
int moduloIntNegInt = e % d          # 1
```
Como hemos podido comprobar con los ejemplos anteriores el comportamiento que tendrían los operadores es el común que se mantiene en todos los lenguajes.

## Operadores lógicos básicos

Una vez repasado los operadores númericos básicos habría que definir los operadores lógicos para las estructuras de control de nuestro lenguaje. La salida de estos operadores sería 0 cuando se cumple y distinto de 0 cuando no

#### Igual que
```
float a = 1.56
float b = 2.12
float c = 1.56
int d = 1
int e = 2
int f = 1

a == b              # -1
a == c              # 0
a == d              # -1
d == e              # -1
d == f              # 0

```

#### Distinto
```
```

#### Menor que
```
float a = 1.56
float b = 2.12
float c = 1.56
int d = 1
int e = 2
int f = 1

a < b               # 0
a < c               # -1
a < d               # -1
d < e               # 0
d < f               # -1
d < a               # 0
```

#### Menor e Igual
```
float a = 1.56
float b = 2.12
float c = 1.56
int d = 1
int e = 2
int f = 1

a <= b              # 0
a <= c              # 0
a <= d              # -1
d <= e              # 0
d <= f              # 0
```

#### Mayor que
```
float a = 1.56
float b = 2.12
float c = 1.56
int d = 1
int e = 2
int f = 1

a > b               # -1
a > c               # -1
a > d               # 0
d > e               # -1
d > f               # -1
e > d               # 0

```

#### Mayor e Igual
```

float a = 1.56
float b = 2.12
float c = 1.56
int d = 1
int e = 2
int f = 1

a >= b              # -1
a >= c              # 0
a >= d              # 0
d >= e              # -1
d >= f              # 0
e >= d              # 0
```


## Estructuas de control

Las estructuras básicas para controlar el flujo de un programa sería la sentencia if, a esta además podemos añadirle un else por conveniencia. Podemos ver el uso en el siguiente ejemplo

```
if(a==b){
    int c = a+b
}else{
    int d = a-b
}

```

Así mismo necesutaremos una estructura que nos permita hacer bucles. Para ello usaremos la estructura básica de muchos lenguajes como es el while su uso sería el siguiente.

```
int cont = 0
while (cont<10){
    print("Contador = %d",cont)
    cont = cont +1
}
```

## Operaciones de salida para variables y ristras

Como operación básica de entrada usaremos print podemos ver su uso en este ejemplo

Uso básico:

```
print("Este es un ejemplo de mensaje de salida")
```

Uso con ristras y variables:

```
int a = 5
printf("Entero %d",a)

```

## Funciones

Necesitaremos usar funciones auxiliares, la declaracion de las mismas y las llamadas serían de la siguiente manera

#### Declaración:
```
int suma(int a, int b, int resultado){
    resultado[0] = a+b
}
```

#### Llamada:
```
int a = 2
int b = 3
int resultado[1]

suma(a,b,resultado)

print("El resultado de la suma es: %d", resultado[0])

```