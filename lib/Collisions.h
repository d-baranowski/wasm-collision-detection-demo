//
// Created by Daniel Baranowski on 21/11/2020.
//

#ifndef HAMDS_ON_GAME_DEVELOPMENT_WITH_WEBASSEMBLY_BOOK_COLLISIONS_H
#define HAMDS_ON_GAME_DEVELOPMENT_WITH_WEBASSEMBLY_BOOK_COLLISIONS_H

#include "Ray.h"
#include "Rectangle.h"
#include "Vector2D.h"

class CollisionInfo {
public:
    bool collision;
    Vector2D contact_point;
    Vector2D contact_normal;
    double t;
};

CollisionInfo RayVsRectangle(const Ray *ray, const Rectangle *target);

#endif //HAMDS_ON_GAME_DEVELOPMENT_WITH_WEBASSEMBLY_BOOK_COLLISIONS_H
