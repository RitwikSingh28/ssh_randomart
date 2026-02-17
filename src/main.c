#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define WIDTH 500
#define HEIGHT 500

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} RGBA;

typedef struct {
    float x, y;
} Vector2;

typedef struct {
    float r, g, b;
} Color;

RGBA pixels[WIDTH * HEIGHT];

void render_pixels(Color (*f)(Vector2)) {
    for (size_t y = 0; y < HEIGHT; y++) {
        float ny = ((float)y / HEIGHT) * 2.0f - 1.0f;
        for (size_t x = 0; x < WIDTH; x++) {
            size_t index = y*WIDTH + x;

            float nx = ((float)x / WIDTH) * 2.0f - 1.0f;
            Color c = f((Vector2) {nx, ny});

            // mapping from [-1,1] to [0,255]
            pixels[index].r = (c.r + 1) * 127.5f;
            pixels[index].g = (c.g + 1) * 127.5f;
            pixels[index].b = (c.b + 1) * 127.5f;
            pixels[index].a = 255;
        }
    }
}

Color another_generator(Vector2 vector2) {
    if (vector2.x * vector2.y > 0) {
        return (Color) {vector2.x, vector2.y, 1};
    }
    float r = fmod(vector2.x + 1e-4, vector2.y + 1e-4);
    return (Color) {r, r, r};
}

Color gray_gradient(Vector2 vector2) {
     return (Color) {
        .r = vector2.x,
        .g = vector2.x,
        .b = vector2.x,
    };
}

int main(void) {
    // Populate the pixels
    render_pixels(another_generator);

    // write the pixels to hard-disk
    const char* output_path = "output.png";
    if (!stbi_write_png(output_path, WIDTH, HEIGHT, 4, pixels, WIDTH*sizeof(RGBA))) {
        fprintf(stderr, "Failed to write to %s", output_path);
        return 1;
    }

    return 0;
}
