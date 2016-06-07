#Errores y soluciones en valgrind

## testimagen

Se salía del vector de datos, al hacer i+100 e j+110, por eso le metemos filtros de módulos.

![foto](imagenes/pantallazos/pantallazo1.png)

```
destino.set(i, j, origen.get((i+110)%origen.filas(),(j+100)%origen.columnas()));
```

## testarteASCII

Problema de valores sin inicializar

![foto](imagenes/pantallazos/pantallazo2.png)
![foto](imagenes/pantallazos/pantallazo3.png)
![foto](imagenes/pantallazos/pantallazo4.png)

**solución:**

inicializar variables a 0
```
char arteASCII[4501]={0}; // 4500 + el \0
```

![foto](imagenes/pantallazos/pantallazo5.png)

## arteASCII

Errores
![foto](imagenes/pantallazos/arteASCII1.png)
![foto](imagenes/pantallazos/arteASCII2.png)
![foto](imagenes/pantallazos/arteASCII3.png)
![foto](imagenes/pantallazos/arteASCII4.png)

Nos dice que hay una variable sin inicializar en arteASCII en la línea 34:
Esa variable sin inicializar es el objeto datos, lo inicializamos a 0 e intentamos crear un espacio de memoria de 0 y se soluciona, no es lo mejor...
```
datos = new byte [0];
```

Es como si creásemos un vector de 0 elementos.

Solución:
![foto](imagenes/pantallazos/arteascii5.png)

## arteASCII2

Nos da varios errores:
![foto](imagenes/pantallazos/arteascii2.png)

Probamos a ejecutar con el max-stackframe para solucionar algunos problemas de memoria:
![foto](imagenes/pantallazos/pantallazo6.png)
