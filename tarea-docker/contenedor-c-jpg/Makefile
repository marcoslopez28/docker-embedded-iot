CC = gcc
CFLAGS = -Wall -O2
SRC = src/generar_imagen.c
BIN = generar_imagen
OUT = output/imagen.jpg

all: prepare build run convert

prepare:
	mkdir -p output

build:
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

run:
	./$(BIN)

convert:
	convert output/imagen.ppm $(OUT)
	@echo "Imagen JPG generada en: $(OUT)"

clean:
	rm -f $(BIN)
	rm -f output/*.ppm output/*.jpg
