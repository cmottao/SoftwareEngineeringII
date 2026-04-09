# Principios SOLID

A continuación se explican brevemente los principios SOLID, con un ejemplo sencillo en Java para cada uno, y una pequeña conclusión final.

---

## S – Single Responsibility Principle (SRP)

**Definición breve:**  
Una clase debe tener **una única razón para cambiar**, es decir, una única responsabilidad bien definida.

**Ejemplo (mal diseño):**

```java
class Reporte {
    public String generarContenido() {
        return "Contenido del reporte";
    }

    // También se encarga de guardarse en disco → 2 responsabilidades
    public void guardarEnArchivo(String ruta) {
        // código para escribir el archivo
    }
}
```

**Ejemplo (aplicando SRP):**

```java
class Reporte {
    public String generarContenido() {
        return "Contenido del reporte";
    }
}

class ReporteFileSaver {
    public void guardarEnArchivo(Reporte reporte, String ruta) {
        String contenido = reporte.generarContenido();
        // código para escribir "contenido" en "ruta"
    }
}
```

---

## O – Open/Closed Principle (OCP)

**Definición breve:**  
Las entidades de software (clases, módulos, funciones) deben estar **abiertas a la extensión, pero cerradas a la modificación**.

**Ejemplo (violando OCP):**

```java
class CalculadoraDescuento {
    public double calcular(double precio, String tipoCliente) {
        if (tipoCliente.equals("VIP")) {
            return precio * 0.8;
        } else if (tipoCliente.equals("NORMAL")) {
            return precio * 0.9;
        }
        return precio;
    }
}
```

Cada nuevo tipo de cliente obliga a **modificar** la clase.

**Ejemplo (aplicando OCP con polimorfismo):**

```java
interface ReglaDescuento {
    double aplicar(double precio);
}

class DescuentoVip implements ReglaDescuento {
    public double aplicar(double precio) {
        return precio * 0.8;
    }
}

class DescuentoNormal implements ReglaDescuento {
    public double aplicar(double precio) {
        return precio * 0.9;
    }
}

class CalculadoraDescuento {
    public double calcular(double precio, ReglaDescuento regla) {
        return regla.aplicar(precio);
    }
}
```

Para agregar un nuevo tipo de descuento se crea una nueva clase que implemente `ReglaDescuento`, sin modificar la calculadora.

---

## L – Liskov Substitution Principle (LSP)

**Definición breve:**  
Las clases hijas deben poder **reemplazar** sin problemas a sus clases padre, sin romper la lógica del programa.

**Ejemplo (violando LSP):**

```java
class Rectangulo {
    protected int ancho;
    protected int alto;

    public void setAncho(int ancho) { this.ancho = ancho; }
    public void setAlto(int alto) { this.alto = alto; }
    public int getArea() { return ancho * alto; }
}

class Cuadrado extends Rectangulo {
    @Override
    public void setAncho(int ancho) {
        this.ancho = ancho;
        this.alto = ancho; // fuerza a ser cuadrado
    }

    @Override
    public void setAlto(int alto) {
        this.alto = alto;
        this.ancho = alto;
    }
}
```

Código que espera un `Rectangulo` y usa `setAncho` y `setAlto` por separado se comportará de forma inesperada si le pasamos un `Cuadrado`.

**Ejemplo (aplicando LSP mejorando jerarquía):**

```java
interface Figura {
    int getArea();
}

class Rectangulo implements Figura {
    private int ancho, alto;

    public Rectangulo(int ancho, int alto) {
        this.ancho = ancho;
        this.alto = alto;
    }

    public int getArea() { return ancho * alto; }
}

class Cuadrado implements Figura {
    private int lado;

    public Cuadrado(int lado) {
        this.lado = lado;
    }

    public int getArea() { return lado * lado; }
}
```

Ambas clases implementan `Figura` sin romper expectativas.

---

## I – Interface Segregation Principle (ISP)

**Definición breve:**  
Es mejor tener **interfaces específicas y pequeñas** que una grande y general que obligue a implementar métodos que no se usan.

**Ejemplo (violando ISP):**

```java
interface Trabajador {
    void trabajar();
    void comer();
}

class Robot implements Trabajador {
    public void trabajar() {
        // trabaja
    }

    public void comer() {
        // el robot no come → método inútil
        throw new UnsupportedOperationException();
    }
}
```

**Ejemplo (aplicando ISP):**

```java
interface Trabajador {
    void trabajar();
}

interface Come {
    void comer();
}

class Empleado implements Trabajador, Come {
    public void trabajar() { /* ... */ }
    public void comer() { /* ... */ }
}

class Robot implements Trabajador {
    public void trabajar() { /* ... */ }
}
```

Cada clase implementa solo lo que realmente necesita.

---

## D – Dependency Inversion Principle (DIP)

**Definición breve:**  
Los módulos de alto nivel no deben depender de módulos de bajo nivel, ambos deben depender de **abstracciones** (interfaces).

**Ejemplo (sin DIP):**

```java
class MySqlRepositorio {
    public void guardar(String dato) {
        // guardar en MySQL
    }
}

class Servicio {
    private MySqlRepositorio repo = new MySqlRepositorio();

    public void procesar(String dato) {
        // lógica
        repo.guardar(dato); // depende de una implementación concreta
    }
}
```

**Ejemplo (aplicando DIP):**

```java
interface Repositorio {
    void guardar(String dato);
}

class MySqlRepositorio implements Repositorio {
    public void guardar(String dato) {
        // guardar en MySQL
    }
}

class Servicio {
    private Repositorio repo;

    public Servicio(Repositorio repo) {  // inyección de dependencia
        this.repo = repo;
    }

    public void procesar(String dato) {
        // lógica
        repo.guardar(dato);
    }
}
```

Ahora el servicio depende de la abstracción `Repositorio`, no de la implementación concreta.

---

## Conclusión

- Los principios SOLID ayudan a crear **código más mantenible, flexible y fácil de probar**.  
- Aplicarlos reduce el acoplamiento, mejora la cohesión y facilita la extensión de funcionalidades sin romper lo existente.  
- No son reglas absolutas, pero sí **buenas guías** para tomar mejores decisiones de diseño orientado a objetos.
