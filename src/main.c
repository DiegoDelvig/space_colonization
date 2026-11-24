#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "vec2.h"
#include "draw.h"
#include "points.h"
#include "app.h"

/* CONSTANTES */
#define WIDTH 600
#define HEIGHT 600

static const float RADIUS = 50.0;
static const size_t attractorsCapacity = 20;
static const size_t pointsCapacity      = 4;


int main(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "SDL Failed to initialise : %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	SDL_Window *win =  SDL_CreateWindow("Space Colonization",
										SDL_WINDOWPOS_UNDEFINED,
										SDL_WINDOWPOS_UNDEFINED,
										WIDTH,
										HEIGHT,
										0);

	if (win == NULL)
	{
		fprintf(stderr, "SDL Window failed to initialise : %s\n", SDL_GetError());
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (ren == NULL)
	{
		fprintf(stderr, "SDL Renderer failed to initialise : %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	srand((unsigned int)time(NULL));

	SDL_Event winEvent;

	/* Attractors Init*/
	points_t *attractors = points_create(attractorsCapacity);
	for (int i = 0; i < attractors->capacity; i++)
	{
		points_add(attractors, vec2_getRandomPos(WIDTH, HEIGHT));
	}

	/* Nodes Init */
	points_t *nodes = points_create(pointsCapacity); // At first only one
	points_add(nodes, (vec2_t){WIDTH/2,HEIGHT/2});

	points_t *attractorsInZone = app_getAttractorsInZone(nodes->items[0], attractors);

	vec2_t vec = app_calculateSumVec(nodes->items[0], attractorsInZone);


	/* COLORS */
	const color_t baseColor       = draw_addColor(30, 30, 46, 255);
	const color_t attractorsColor = draw_addColor(166, 227, 46, 255);
	const color_t nodesColor      = draw_addColor(243, 139, 168, 255);
	const color_t pinkColor       = draw_addColor(245, 194, 231, 255);

	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&winEvent))
		{
			if (SDL_QUIT == winEvent.type)
			{
				running = false;
				break;
			}
		}
		/* DRAW */
		SDL_SetRenderDrawColor(ren, baseColor.r, baseColor.g, baseColor.b, baseColor.alpha);
		SDL_RenderClear(ren);

		/* Attractors */
		for (int i = 0; i < attractors->count; i++)
		{
			draw_filledCircle(ren, attractors->items[i].pos, RADIUS, attractorsColor);
		}

		/* nodes */
		for (int i = 0; i < nodes->count; i++)
		{
			draw_filledCircle(ren, nodes->items[i].pos, RADIUS, nodesColor);
		}

		for (int i = 0; i < attractorsInZone->count; i++)
		{
			draw_filledCircle(ren, attractorsInZone->items[i].pos, RADIUS, pinkColor);
		}

		SDL_RenderPresent(ren);

		/* END DRAWING */

	}

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return EXIT_SUCCESS;
}

