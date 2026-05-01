#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *archivo = fopen("output/imagen.ppm", "w");

    if (archivo == NULL) {
        printf("Error al crear la imagen.\n");
        return 1;
    }

    int ancho = 400;
    int alto = 300;

    fprintf(archivo, "P3\n");
    fprintf(archivo, "%d %d\n", ancho, alto);
    fprintf(archivo, "255\n");

    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            int r = (x * 255) / ancho;
            int g = (y * 255) / alto;
            int b = 150;

            fprintf(archivo, "%d %d %d ", r, g, b);
        }
        fprintf(archivo, "\n");
    }

    fclose(archivo);

    printf("Imagen PPM generada correctamente.\n");
    return 0;
}
