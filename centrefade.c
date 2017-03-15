/*
	centrefade

	Creates a ghostly black to green centre fade, from the outside-in.
*/

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define IMHEIGHT 1024
#define IMWIDTH  1280

// The image format is interleaved RGB
#define NUM_CHANNELS 3
#define IMAGE_SIZE_BYTES (NUM_CHANNELS * IMHEIGHT * IMWIDTH)
#define IMSTRIDE (IMWIDTH * NUM_CHANNELS)

int main(int argc, char **argv)
{
	uint8_t pixels[IMAGE_SIZE_BYTES];

#define CENTREX (IMWIDTH / 2.0f)
#define CENTREY (IMHEIGHT / 2.0f)
#define sqr(x) ((x) * (x))

	const float maxDistance = sqrtf(powf(CENTREX, 2.0f) + powf(CENTREY, 2.0f));

	uint32_t x, y;
	uint64_t pixel = 0;
	float distance, ratio;
	for (y = 0; y < IMHEIGHT; y++) {
		for (x = 0; x < IMWIDTH; x++) {
			distance = sqrtf(sqr(x - CENTREX) + sqr(y - CENTREY));

			ratio = (1.0f - distance / maxDistance) * 255.0f * 0.5f;

			pixels[pixel]     = (uint8_t) (ratio * 0.55f);
			pixels[pixel + 1] = (uint8_t) ratio;
			pixels[pixel + 2] = (uint8_t) (ratio * 0.8f);

			pixel += NUM_CHANNELS;
		}
	}

	stbi_write_png("centrefade.png", IMWIDTH, IMHEIGHT, 3, pixels, IMSTRIDE);

	return EXIT_SUCCESS;
}

