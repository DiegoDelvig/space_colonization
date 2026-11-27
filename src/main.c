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
static const size_t nodesCapacity     = 1;
/* COLORS */
static const color_t baseColor       = {30, 30, 46, 255};
static const color_t attractorsColor = {166, 227, 46, 255};
static const color_t nodesColor      = {243, 139, 168, 255};
static const color_t pinkColor       = {245, 194, 231, 255};

static bool initializePoints(points_t **atractors, points_t **nodes);

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

	static points_t *attractors = NULL;
	static points_t *nodes      = NULL;

	bool status = initializePoints(&attractors, &nodes);
	if (!status)
	{
		fprintf(stderr,"erreur de initializePoints");
		points_destroy(attractors);
		points_destroy(nodes);
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

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
		SDL_SetRenderDrawColor(ren, baseColor.r, baseColor.g, baseColor.b, baseColor.alpha);
		SDL_RenderClear(ren);

		point_t last = nodes->items[nodes->count - 1];
		points_t *inZone = app_getAttractorsInZone(last, attractors);

		if (inZone == NULL)
		{
			break;
		}

		if (inZone->count > 0)
		{
			vec2_t dir = app_calculateSumVec(last, inZone, 10);
			app_getNextNode(nodes, dir);
		}



		/* DRAW */
		for (int i = 0; i < attractors->count; i++)
		{
			draw_filledCircle(ren, attractors->items[i].pos, RADIUS, attractorsColor);
		}

		for (int i = 0; i < nodes->count; i++)
		{
			draw_filledCircle(ren, nodes->items[i].pos, RADIUS, nodesColor);
		}

		for (int i = 0; i < inZone->count; i++)
		{
			draw_filledCircle(ren, inZone->items[i].pos, RADIUS, pinkColor);
		}
		points_destroy(inZone);
		SDL_RenderPresent(ren);
		SDL_Delay(60);
	}

	points_destroy(attractors);
	points_destroy(nodes);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return EXIT_SUCCESS;
}

static bool initializePoints(points_t **attractors, points_t **nodes)
{
	/* Initialization */
	*attractors = points_create(attractorsCapacity);
	*nodes 	 = points_create(nodesCapacity);
	bool status;
	for (size_t i = 0; i < attractorsCapacity; i++)
	{
		status = points_add(*attractors, vec2_getRandomPos(WIDTH, HEIGHT));
		if (!status)
		{
			fprintf(stderr,"erreur de points_add");
			return false;
		}
	}
	status = points_add(*nodes, vec2_getRandomPos(WIDTH/2, HEIGHT));
	if (!status)
	{
		fprintf(stderr,"erreur de points_add");
		return false;
	}
	return true;
}
