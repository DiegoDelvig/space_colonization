#ifndef SRC_DRAW_H_
#define SRC_DRAW_H_

#include "vec2.h"
#include "SDL2/SDL.h"

typedef struct
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int alpha;
} color_t;

color_t draw_addColor(unsigned int r, unsigned int g, unsigned int b, unsigned int alpha);
void draw_filledCircle(SDL_Renderer *ren, vec2_t pos, float radius, color_t color);
void draw_lineBetweenTwoPoints(SDL_Renderer *ren, vec2_t pos1, vec2_t pos2, color_t color);

#endif /* SRC_DRAW_H_ */
