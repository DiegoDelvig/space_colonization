#include "draw.h"
#include "vec2.h"

color_t draw_addColor(unsigned int r, unsigned int g, unsigned int b, unsigned int alpha)
{
	color_t c;
	c.r = r;
	c.g = g;
	c.b = b;
	c.alpha = alpha;
	return c;
}

void draw_filledCircle(SDL_Renderer *ren, vec2_t pos, float radius, color_t color)
{
	SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.alpha);
	const unsigned int diameter = radius * 2;

	for (int i = 0; i < diameter; i++)
	{
		for (int j = 0; j < diameter; j++)
		{
			int dx = radius - i;
			int dy = radius - j;
			if ((dx*dx + dy*dy) < diameter)
			{
				SDL_RenderDrawPoint(ren, pos.x + dx, pos.y + dy);
			}
		}
	}
}

void draw_lineBetweenTwoPoints(SDL_Renderer *ren, vec2_t pos1, vec2_t pos2, color_t color)
{
	SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.alpha);
	SDL_RenderDrawLine(ren,(int)pos1.x,(int)pos1.y,(int)pos2.x,(int)pos2.y);
}
