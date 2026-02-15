#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "USAGE: %s <command>\n", argv[0]);
        return 1;
    }
    printf("Hello, SHA Visualizer!\n");
    return 0;
}
