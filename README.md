# Proyecto Docker – Embedded IoT

## Descripción

En esta práctica se trabajó con Docker para comprender cómo funciona la creación, construcción y ejecución de contenedores, así como su utilidad para automatizar entornos de desarrollo.

Se desarrollaron dos contenedores:

-  Un contenedor principal en lenguaje C que genera una imagen en formato JPG.
-  Un contenedor adicional en Python que genera una gráfica en formato PNG.

El objetivo fue aprender a utilizar Docker para crear entornos reproducibles, ejecutar programas dentro de contenedores y documentar correctamente el proceso.

---

##  Objetivos de aprendizaje

- Comprender el funcionamiento de Docker.
- Construir contenedores usando Dockerfile.
- Ejecutar programas dentro de contenedores.
- Automatizar procesos mediante Makefile.
- Documentar un proyecto técnico correctamente.
- Organizar un repositorio de manera clara.
- Proponer una solución adicional con Docker.

---

##  ¿Qué es Docker?

Docker es una herramienta que permite crear contenedores, los cuales son entornos aislados donde se ejecutan aplicaciones junto con todas sus dependencias.

Esto permite que un programa funcione igual en cualquier computadora sin importar el sistema operativo.

---

# Instalación de entorno (WSL + Docker)

## Introducción

Para poder ejecutar los contenedores Docker en esta práctica, fue necesario configurar un entorno de desarrollo en Windows utilizando WSL (Windows Subsystem for Linux) y Docker Desktop.

WSL permite ejecutar una distribución de Linux dentro de Windows, lo cual es útil ya que Docker funciona de manera más estable en entornos tipo Linux.

---

## ¿Qué es WSL?

WSL (Windows Subsystem for Linux) es una herramienta que permite ejecutar Linux dentro de Windows sin necesidad de instalar una máquina virtual.

Esto permite trabajar con comandos de Linux, instalar paquetes y ejecutar herramientas como Docker en un entorno compatible.

---

## Instalación de WSL

### Paso 1: Abrir PowerShell como administrador

Se abrió PowerShell con permisos de administrador para poder instalar WSL.

---

### Paso 2: Ejecutar el comando de instalación

```powershell
wsl --install
```

## Instalación de Docker
Paso 1: Instalación de dependencias
sudo apt install -y ca-certificates curl gnupg

Estas herramientas permiten gestionar repositorios y descargas seguras.

Paso 2: Agregar clave de Docker
sudo install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo tee /etc/apt/keyrings/docker.asc > /dev/null
sudo chmod a+r /etc/apt/keyrings/docker.asc

Esto permite verificar que los paquetes de Docker sean oficiales.

Paso 3: Agregar repositorio
echo \
"deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
$(. /etc/os-release && echo $VERSION_CODENAME) stable" | \
sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

Se añade el repositorio oficial de Docker para instalarlo correctamente.

Paso 4: Instalación de Docker
sudo apt update
sudo apt install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

Esto instala Docker y sus componentes principales.

## Verificación de instalación

Para comprobar que Docker funciona correctamente se ejecutó:

sudo docker run hello-world

Si aparece el mensaje:

Hello from Docker!

significa que Docker está instalado correctamente.

---

# Contenedor 1: Generación de imagen JPG en C

##  Descripción

Este contenedor ejecuta un programa en lenguaje C que genera una imagen en formato PPM mediante la manipulación de valores RGB por píxel. Posteriormente, la imagen es convertida a formato JPG utilizando ImageMagick.

---

## Explicación del código en C

Archivo: `generar_imagen.c`

### Inclusión de librerías

```c
#include <stdio.h>
```

función principal
int main() {

Es el punto de inicio del programa.

Creación del archivo
FILE *archivo = fopen("output/imagen.ppm", "w");

Crea el archivo donde se guardará la imagen en formato PPM.

Encabezado PPM
fprintf(archivo, "P3\n");
fprintf(archivo, "%d %d\n", ancho, alto);
fprintf(archivo, "255\n");

Define:

tipo de archivo (P3)
dimensiones
rango de color

Recorrido de píxeles
for (int y = 0; y < alto; y++) {
    for (int x = 0; x < ancho; x++) {

Recorre cada píxel de la imagen.

Cálculo de colores
int r = (x * 255) / ancho;
int g = (y * 255) / alto;
int b = 150;

Genera un degradado:

rojo depende de X
verde depende de Y
azul constante

Escritura del píxel
fprintf(archivo, "%d %d %d ", r, g, b);

Guarda los valores RGB.

Cierre del archivo
fclose(archivo);

Finaliza la escritura.

## Explicación del Makefile

El Makefile automatiza el flujo completo.

Variables
CC = gcc
SRC = src/generar_imagen.c
BIN = generar_imagen

Define compilador, archivo fuente y ejecutable.

## Compila el programa en C.

Ejecución
run:
	./$(BIN)

Ejecuta el programa generado.

Conversión
convert:
	convert output/imagen.ppm output/imagen.jpg

Convierte la imagen a JPG usando ImageMagick.

Flujo completo
all: build run convert

Ejecuta todo el proceso automáticamente.

## Explicación del Dockerfile
FROM ubuntu:22.04

Define el sistema base.

RUN apt-get update && apt-get install -y build-essential imagemagick make

Instala dependencias.

WORKDIR /usr/src/app

Define carpeta de trabajo.

COPY . .

Copia archivos al contenedor.

CMD ["make", "all"]

Ejecuta todo automáticamente.

## Construcción y ejecución
docker build -t contenedor-c-jpg .
docker run --rm -v "$PWD:/usr/src/app" contenedor-c-jpg
📷 Resultado

Se generan:

imagen.ppm
imagen.jpg

## Contenedor 2: Gráfica en Python

Este contenedor genera una gráfica PNG a partir de datos simulados.

## Explicación del código Python

Archivo: grafico.py

Importación
import matplotlib.pyplot as plt
import random

Se usan librerías para graficar y generar datos.

Datos
dias = ["Lun", "Mar", "Mié", "Jue", "Vie"]
valores = [random.randint(1, 10) for _ in dias]

Simula datos de sensor.

Gráfica
plt.plot(dias, valores, marker="o")

Dibuja la gráfica.

Etiquetas
plt.title("Datos simulados de sensor")
plt.xlabel("Días")
plt.ylabel("Valores")

Mejora la visualización.

Guardado
plt.savefig("output/grafico.png")

Genera la imagen final.

## Explicación del Dockerfile
FROM python:3.11-slim

Imagen base.

RUN pip install matplotlib

Instala dependencias.

COPY . .

Copia archivos.

CMD ["python", "grafico.py"]

## Ejecuta el script.
docker build -t contenedor-python-grafico .
docker run --rm -v "$PWD:/app" contenedor-python-grafico
📷 Resultado

Se genera:

grafico.png
##
