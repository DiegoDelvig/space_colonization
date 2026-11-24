#ifndef SRC_POINTS_H_
#define SRC_POINTS_H_

#include <stdbool.h>
#include <stdlib.h>
#include "vec2.h"

typedef struct
{
	vec2_t pos;
} point_t;

typedef struct
{
	point_t *items;
	size_t  count;
	size_t  capacity;
} points_t;

points_t *points_create(size_t capacity);
void     points_destroy(points_t *points);
bool     points_add(points_t *points, vec2_t pos);
void     points_remove(points_t *points, size_t index);
point_t  getLastPoint(points_t *points);

#endif /* SRC_POINTS_H_ */
