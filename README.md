# Proyecto C++ — Entorno de Desarrollo

## 📌 Descripción

Este proyecto está desarrollado en C++ utilizando:

- Visual Studio Code  
- GNU g++  
- Git  

Compatible con:

- macOS  
- Windows  

---

# 1️⃣ Instalación del Compilador

## 🍎 macOS

### Verificar instalación

```bash
g++ --version
```

### Instalar (si no está disponible)

```bash
xcode-select --install
```

---

## 🪟 Windows

### Paso 1 — Instalar MinGW

Instalar MinGW y seleccionar durante la instalación:

```
mingw32-gcc-g++
```

### Paso 2 — Agregar al PATH

Agregar la carpeta `bin` al PATH del sistema.

Ejemplo:

```
C:\MinGW\bin
```

### Paso 3 — Verificar instalación

En CMD o PowerShell:

```bash
g++ --version
```

Si muestra la versión → está correctamente instalado.

---

# 2️⃣ Compilación y Ejecución

## 🍎 macOS

```bash
g++ main.cpp -o main
./main
```

Compilar y ejecutar en una línea:

```bash
g++ main.cpp -o main && ./main
```

---

## 🪟 Windows

```bash
g++ main.cpp -o main.exe
main.exe
```

Compilar y ejecutar en una línea:

```bash
g++ main.cpp -o main.exe && main.exe
```

⚠️ No usar `sudo` para compilar ni para usar git.

---

# 3️⃣ Extensión Necesaria en VS Code

Instalar:

## C/C++

Autor: Microsoft  
ID: `ms-vscode.cpptools`

Proporciona:

- Autocompletado  
- Detección de errores  
- IntelliSense  
- Formateo de código  

---

# 4️⃣ Configuración de Formateo Automático

Abrir:

- macOS → `Cmd + Shift + P`
- Windows → `Ctrl + Shift + P`

Ir a:

```
Preferences: Open Settings (JSON)
```

Agregar:

```json
{
  "editor.formatOnSave": true,
  "[cpp]": {
    "editor.defaultFormatter": "ms-vscode.cpptools"
  }
}
```

---

# 5️⃣ Estructura del Proyecto

```
Proyecto/
│
├── main.cpp
├── boolean.h
└── README.md
```

---

# 6️⃣ Protección de Headers

Todos los archivos `.h` deben protegerse contra doble inclusión:

```cpp
#ifndef BOOLEAN_H_INCLUDED
#define BOOLEAN_H_INCLUDED

// contenido del header

#endif
```

---

# 7️⃣ Flujo de Trabajo con Git

## 🔹 Rama Principal

La rama principal del repositorio es:

```
develop
```

Todo lo que esté en `develop` debe estar funcionando correctamente.  
No se sube código que no compile o esté incompleto.

---

## 🔹 Antes de comenzar a trabajar

Actualizar siempre:

```bash
git pull origin develop
```

---

## 🔹 Crear una Nueva Branch

```bash
git checkout -b feature/nombre-de-la-funcionalidad
```

Ejemplo:

```bash
git checkout -b feature/expresiones
```

---

# 8️⃣ Commits

## 🔹 Agregar archivos modificados

```bash
git add .
```

## 🔹 Crear commit

```bash
git commit -m "Descripción clara de la funcionalidad implementada"
```

Ejemplo:

```bash
git commit -m "Implementación del módulo de expresiones booleanas"
```

Buenas prácticas:

- Mensajes claros y descriptivos
- Un commit por cambio lógico
- No commitear código que no compile

---

# 9️⃣ Subir cambios al repositorio

```bash
git push origin feature/expresiones
```

Esto sube la branch al repositorio remoto.

---

# 🔟 Pull Request (PR)

Una vez subida la branch:

1. Ir al repositorio en la plataforma (GitHub).
2. Crear un **Pull Request** hacia la rama `develop`.
3. Verificar que:
   - El código compile
   - No haya errores
   - La descripción explique qué hace la feature

---

# 1️⃣1️⃣ Proceso de Review

- Compartir el link del Pull Request en el grupo de trabajo.
- El equipo revisa el código.
- Se comentan posibles mejoras o correcciones.
- Si es necesario, se realizan cambios adicionales en la misma branch.

---

# 1️⃣2️⃣ Coordinación de Reunión

Para features importantes:

- Coordinar una meet con el equipo.
- Explicar:
  - Qué problema resuelve la feature.
  - Qué decisiones de diseño se tomaron.
  - Cómo se puede probar.
- Aclarar dudas antes de hacer el merge.

---

# 1️⃣3️⃣ Merge

Una vez aprobada la review:

- Se realiza el merge hacia `develop`.
- `develop` debe seguir compilando correctamente.

---

# 📌 Reglas del Proyecto

- No trabajar directamente en `develop`
- Cada funcionalidad en su propia branch
- `develop` siempre debe compilar
- Hacer `git pull origin develop` antes de empezar
- No subir código que no compile
- Realizar Pull Request para integrar cambios
- Toda feature debe pasar por review

---

# 🎯 Estado Esperado del Entorno

✔ Compila correctamente  
✔ Ejecuta sin errores  
✔ Código formateado automáticamente  
✔ Uso correcto de branches  
✔ Revisión en equipo antes del merge  
✔ Rama principal estable  