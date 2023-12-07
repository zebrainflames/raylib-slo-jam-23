//
// Created by greyfriar on 20.3.2021.
//
#include "collisions.h"

#define CUTE_C2_IMPLEMENTATION
#include "cute_c2.h"

c2AABB rectToAABB(Rectangle a) {
    c2v min;
    c2v max;
    min.x = a.x;
    min.y = a.y;
    max.x = a.x + a.width;
    max.y = a.y + a.height;
    c2AABB ab;
    ab.max = max;
    ab.min = min;
    return ab;
}

c2Manifold getColManifold(Rectangle r_a, Rectangle r_b) {
    c2AABB a = rectToAABB(r_a);
    c2AABB b = rectToAABB(r_b);
    c2Manifold m;
    c2AABBtoAABBManifold(a, b, &m);
    return m;
}

void resolveRects(Rectangle* a, Rectangle* b, c2Manifold m) {
    c2v min_trans  = {0};
    float min_len = 999999.0f;
    for (int  i = 0;  i < m.count; ++ i)
    {
        c2v n = m.n;
        //c2v p = m.contact_points[i];
        float d = m.depths[i];
        c2v translation = c2Mulvs(n, d);
        float len = c2Len(translation);
        if (len < min_len) {
            min_len = len;
            min_trans = translation;
        }
    }
    if (m.count > 0) {
        min_trans = c2Div(min_trans, 2.0f);
        a->x -= min_trans.x;
        a->y -= min_trans.y;
        b->x += min_trans.x;
        b->y += min_trans.y;
    }

}

void drawManifold(c2Manifold m) {

    for (int  i = 0;  i < m.count; ++ i)
    {
        c2v n = m.n;
        c2v p = m.contact_points[i];
        float d = m.depths[i];
        n = c2Mulvs(n, d);
        DrawCircle((int)p.x, (int)p.y, 5.f, RED);
        p = c2Add(p, n);
        DrawCircle((int)p.x, (int)p.y, 5.f, BLUE);
    }
}
