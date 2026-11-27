/*
 * vec2.h
 *
 *  Created on: Nov 23, 2026
 *      Author: dvdgo
 */

#ifndef SRC_VEC2_H_
#define SRC_VEC2_H_

#include <stdbool.h>

typedef struct
{
	float x;
	float y;
} vec2_t;

vec2_t vec2_add(vec2_t a, vec2_t b);
vec2_t vec2_sub(vec2_t a, vec2_t b);
vec2_t vec2_scale(vec2_t v, float k);
float vec2_length(vec2_t v);
float vec2_dist(vec2_t a, vec2_t b);
/*
 * If length = 0, return {0, 0}
 */
vec2_t vec2_normalize(vec2_t v);
vec2_t vec2_getRandomPos(int maxWidth, int maxHeight);
bool vec2_isNull(vec2_t v);
vec2_t vec2_reverse(vec2_t v);
bool vec2_isEqual(vec2_t a, vec2_t b);

#endif /* SRC_VEC2_H_ */
