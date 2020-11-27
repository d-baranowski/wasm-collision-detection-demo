//
// Created by Daniel Baranowski on 21/11/2020.
//

#include "Collisions.h"

CollisionInfo RayVsRectangle(const Ray *ray, const Rectangle *target) {
    CollisionInfo result;
    Vector2D t_near = (target->pos - ray->origin) / ray->direction;
    Vector2D t_far = (target->pos + target->size - ray->origin) / ray->direction;
    Vector2D invdir = 1.0f / ray->direction;

    if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
    if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

    if (t_near.x > t_far.y || t_near.y > t_far.x) {
        result.collision = false;
        return result;
    }

    double t_hit_near = std::max(t_near.x, t_near.y);
    double t_hit_far = std::min(t_far.x, t_far.y);

    if (t_hit_far < 0) {
        result.collision = false;
        return result;
    }

    // Contact point of collision from parametric line equation
    Vector2D contact_point = ray->origin + t_hit_near * ray->direction;

    Vector2D contact_normal;
    if (t_near.x > t_near.y) {
        if (invdir.x < 0) {
            contact_normal = Vector2D(1, 0);
        } else {
            contact_normal = Vector2D(-1, 0);
        }
    } else if (t_near.x < t_near.y) {
        if (invdir.y < 0) {
            contact_normal = Vector2D(0, 1);
        } else {
            contact_normal = Vector2D(0, -1);
        }
    }

    result.collision = true;
    result.contact_point = contact_point;
    result.t = t_hit_near;
    result.contact_normal = contact_normal;

    return result;
}
