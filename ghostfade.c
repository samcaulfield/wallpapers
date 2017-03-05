/*
	ghostfade

	Creates a ghostly black to green linear fade, top-to-bottom.
*/

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define IMHEIGHT 1024
#define IMWIDTH  1280

// The image format is interleaved RGB, 1 Bpp
#define NUM_CHANNELS 3
#define IMAGE_SIZE_BYTES (NUM_CHANNELS * IMHEIGHT * IMWIDTH)
#define IMSTRIDE (IMWIDTH * NUM_CHANNELS)

int main(int argc, char **argv)
{
	uint8_t pixels[IMAGE_SIZE_BYTES];

	uint32_t x, y;
	uint64_t pixel = 0;
	for (y = 0; y < IMHEIGHT; y++) {
		for (x = 0; x < IMWIDTH; x++) {

			// Scale down the red and blue channels to achieve a
			// primarily green hue.
#define RB_SCALE (0.45454545f)

			// Create the linear fade based on y magnitude.
			const float pixval = UCHAR_MAX * y / (float) IMHEIGHT;

			pixels[pixel]     = (uint8_t) (pixval * RB_SCALE);

			pixels[pixel + 1] = (uint8_t) pixval;

			pixels[pixel + 2] = pixels[pixel];

			pixel += NUM_CHANNELS;
		}
	}

	stbi_write_png("ghostfade.png", IMWIDTH, IMHEIGHT, 3, pixels, IMSTRIDE);

	return EXIT_SUCCESS;
}

