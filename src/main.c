#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "vec2.h"
#include "draw.h"
#include "points.h"

/* CONSTANTES */
#define WIDTH 600
#define HEIGHT 600

static const float RADIUS = 3.0f;
static const size_t attractorsCapacity = 100;
static const size_t nodesCapacity     = 1;
static const float D_STEP = 5.0f;   /* longueur d'un pas */
static const float DI     = 200.0f; /* distance d'influence */
static const float DK     = 8.0f;   /* distance de kill */
/* COLORS */
static const color_t baseColor       = {30, 30, 46, 255};
static const color_t attractorsColor = {166, 227, 46, 255};
static const color_t nodesColor      = {243, 139, 168, 255};

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

		size_t n = nodes->count; /* Les nouveaux noeuds attend prochain tour de boucle */
		vec2_t *sum = calloc(n, sizeof *sum);
		size_t *cnt = calloc(n, sizeof *cnt);
		if (sum == NULL || cnt == NULL)
		{
			fprintf(stderr,"allocation failed\n");
			free(sum);
			free(cnt);
			running = false;
			break;
		}

		for (size_t a = 0; a < attractors->count; a++)
		{
			size_t best = 0;
			float bestDist = vec2_dist(nodes->items[0].pos, attractors->items[a].pos);

			for (size_t i = 1; i < n; i++)
			{
				float d = vec2_dist(nodes->items[i].pos, attractors->items[a].pos);
				if (d < bestDist)
				{
					bestDist = d;
					best = i;
				}
			}

			if (bestDist < DI)
			{
				vec2_t dir = vec2_normalize(vec2_sub(attractors->items[a].pos, nodes->items[best].pos));
				sum[best] = vec2_add(sum[best], dir);
				cnt[best]++;
			}
		}

		for (size_t i = 0; i < n; i++)
		{
			if (cnt[i] == 0)
			{
				continue;
			}

			vec2_t dir = vec2_normalize(sum[i]);
			if (vec2_isNull(dir))
			{
				continue;
			}

			vec2_t pos = vec2_add(nodes->items[i].pos, vec2_scale(dir, D_STEP));
			if (!points_add(nodes, pos))
			{
				fprintf(stderr,"points_add failed");
				running = false;
				break;
			}
		}

		free(sum);
		free(cnt);

		for (size_t a = attractors->count; a-- > 0; )
		{
			for (size_t i = 0; i < nodes->count; i++)
			{
				if (vec2_dist(nodes->items[i].pos, attractors->items[a].pos) < DK)
				{
					points_remove(attractors, a);
					break;
				}
			}
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


		SDL_RenderPresent(ren);
		SDL_Delay(60);
	}

	printf("Simulation terminée\n");
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
