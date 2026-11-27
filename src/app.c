#include "app.h"

#include "points.h"
#include "vec2.h"

#include <stdio.h>
#include <stdbool.h>

#define D 5 /* Distance a new node is placed from its parent */
#define dk 140 /* Minimum distance before an attractor is removed from consideration */
#define di 200 /* Maximum distance within which an attractor can influence a node */

points_t *app_getAttractorsInZone(point_t node, points_t *attractors)
{
	points_t *attractorsInZone = points_create(attractors->capacity);
	if (attractorsInZone == NULL)
	{
		fprintf(stderr, "erreur dans app_getAttractorsInZone\n");
	}

	for (size_t i = 0; i < attractors->count; i++)
	{
		if (vec2_dist(node.pos, attractors->items[i].pos) < di)
		{
			bool status = points_add(attractorsInZone, attractors->items[i].pos);
			if (status != true)
			{
				printf("Erreur lors de l'ajout d'un points\n");
				exit(1);
			}
		}
	}

	return attractorsInZone;
}

vec2_t app_calculateSumVec(point_t currNode, points_t *aInZone, float jump)
{
	vec2_t sumVec = (vec2_t){0, 0};
	for (int i = 0; i < aInZone->count; i++)
	{
		/* Risque de division par 0 */
		float attractionForce = 1/vec2_dist(currNode.pos, aInZone->items[i].pos);
		vec2_t v = vec2_sub(currNode.pos, aInZone->items[i].pos);
		v = vec2_scale(v, attractionForce);
		if (vec2_isNull(sumVec))
		{
			sumVec = v;
		}
		else
		{
			sumVec = vec2_add(sumVec, v);
		}
	}
	sumVec = vec2_normalize(sumVec);
	sumVec = vec2_scale(sumVec, jump);
	sumVec = vec2_reverse(sumVec);
	return sumVec;
}

void app_getNextNode(points_t *nodes, vec2_t sumVec)
{
	vec2_t nextPos = vec2_add(nodes->items[nodes->count-1].pos, sumVec);
	bool status = points_add(nodes, nextPos);
	if (status != true)
	{
		printf("Erreur lors de l'ajout d'un points\n");
		exit(1);
	}
}

void app_killAttractor(point_t currNode, points_t *aInZone)
{
	for (int i = 0; i < aInZone->count; i++)
	{
		if (vec2_dist(currNode.pos, aInZone->items[i].pos) < dk)
		{
			points_remove(aInZone, i);
		}
	}
}
