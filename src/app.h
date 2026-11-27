#ifndef APP_H
#define APP_H

#include "points.h"
#include "vec2.h"

points_t *app_getAttractorsInZone(point_t node, points_t *attractators);
vec2_t app_calculateSumVec(point_t currNode, points_t *aInZone, float jump);
void app_getNextNode(points_t *nodes, vec2_t sumVec);
void app_killAttractor(point_t currNode, points_t *aInZone);


#endif /* APP_H */


