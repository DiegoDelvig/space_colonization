#include "points.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


points_t *points_create(size_t capacity)
{
	if (capacity == 0)
	{
		printf("capacity can't be equal to zero\n");
		return NULL;
	}
	points_t *points = malloc(sizeof(points_t));
	if (points == NULL)
	{
		printf("error allocation of points");
		return NULL;
	}

	points->items = malloc(sizeof(point_t) * capacity);
	points->count = 0;
	points->capacity = capacity;
	return points;
}

void points_destroy(points_t *points)
{
	if (points == NULL)
	{
		return;
	}

	free(points->items);
	free(points);
}

bool points_add(points_t *points, vec2_t pos)
{
	if (points == NULL)
	{
		return false;
	}

	if (points->count >= points->capacity)
	{
		points->capacity = points->capacity * 2;
		points->items = realloc(points->items,sizeof(points->capacity));
	}

	points->items[points->count].pos = pos;
	points->count++;
	return true;
}

void points_remove(points_t *points, size_t index)
{
	if (points == NULL || index >= points->count)
	{
		return;
	}
	points->items[index] = points->items[points->count-1];
	points->count--;
}
