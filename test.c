// tcc -DRWIMG_PNG -DRWIMG_JPEG -DRWIMG_GIF -ljpeg -lpng -lgif readimage.c rwgif.c rwjpeg.c  rwpng.c writeimage.c -run test.c
//  gcc -shared -static -DRWIMG_PNG -DRWIMG_JPEG -DRWIMG_GIF  readimage.c  rwgif.c  rwjpeg.c  rwpng.c  writeimage.c -ljpeg -lpng -lgif -lz -o rwimg.dll && strip rwimg.dll
// tcc -DRWIMG_PNG -DRWIMG_JPEG -DRWIMG_GIF -L. -lrwimg -run test.c

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "readimage.h"
#include "writeimage.h"

int main(int argc, char *argv[])
{
	unsigned char *data;
	int width, height;
	int pixel_stride = 4;
	int size;
	int line;
	//
	width = 512;
	height = 512;
	line = height * pixel_stride;
	size = width * height * pixel_stride;
	data = malloc(size);
	memset(data, 0, size);
	//
	for (int h = 0; h < height; ++h)
	{
		for (int w = 0; w < width; ++w)
		{
			int offset = h*line + w*pixel_stride;
			data[offset] = 255;
			data[offset + 1] = 255;
			data[offset + 2] = 255;
			data[offset + 3] = 128;
		}
	}
	//
	write_image("test.png", width, height, data, pixel_stride, width * pixel_stride, IMAGE_FORMAT_AUTO);

	return 0;
}
