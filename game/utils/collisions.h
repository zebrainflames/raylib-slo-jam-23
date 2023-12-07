//
// Created by greyfriar on 20.3.2021.
//

#ifndef INC_0X37_EVALUATE_RAYLIB_COLLISIONS_H
#define INC_0X37_EVALUATE_RAYLIB_COLLISIONS_H

#include <raylib.h>
#include "cute_c2.h"

c2AABB rectToAABB(Rectangle a);

c2Manifold getColManifold(Rectangle a, Rectangle b);

void resolveRects(Rectangle* a, Rectangle* b, c2Manifold m);

void drawManifold(c2Manifold m);

#endif // INC_0X37_EVALUATE_RAYLIB_COLLISIONS_H
