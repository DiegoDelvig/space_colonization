#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vec2.h"

vec2_t vec2_add(vec2_t a, vec2_t b)
{
	return (vec2_t){a.x + b.x, a.y + b.y};
}

vec2_t vec2_sub(vec2_t a, vec2_t b)
{
	return (vec2_t){a.x - b.x, a.y - b.y};
}

vec2_t vec2_scale(vec2_t v, float k)
{
	return (vec2_t){v.x * k, v.y * k};
}

float vec2_length(vec2_t v)
{
	return hypotf(v.x, v.y);
}

float vec2_dist(vec2_t a, vec2_t b)
{
	return vec2_length(vec2_sub(a, b));
}

/*
 * Si vecteur longueur Nulle, on renvoie un vecteur nul. {0, 0}
 */
vec2_t vec2_normalize(vec2_t v)
{
	float l = vec2_length(v);

	if (l == 0.0f)
	{
		return (vec2_t){0, 0};
	}

	return (vec2_t){v.x / l, v.y / l};
}

vec2_t vec2_getRandomPos(int maxWidth, int maxHeight)
{
	vec2_t v;
	v.x = ((float)rand() / (float)RAND_MAX) * maxWidth;
	v.y = ((float)rand() / (float)RAND_MAX) * maxHeight;
	return v;
}

bool vec2_isNull(vec2_t v)
{
	if (v.x == 0 && v.y == 0)
	{
		return true;
	}
	return false;
}

vec2_t vec2_reverse(vec2_t v)
{
	return (vec2_t){v.x *(-1), v.y * (-1)};
}

bool vec2_isEqual(vec2_t a, vec2_t b)
{
	if (a.x == b.x && a.y == b.y)
	{
		return true;
	}
	return false;
}

