#include "image.h"
#include "types_macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int arg, char **argv) {
    Image I;
    I = lire_fichier_image(argv[1]);
    ecrire_image(I);
    return 0;
}
