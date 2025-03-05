#include "gameObject/Transform.hpp"
#include <cmath>

//
// Constructors
//
Transform::Transform() = default;

Transform::Transform(const Vector &position, const Vector &scale, const float rotation): position(position),
    scale(scale), rotation(rotation) {
}

Transform::Transform(const Vector &position, const Vector &scale, const float rotation,
                     Transform *parent): position(position), scale(scale), rotation(rotation), parent(parent) {
}

Transform::Transform(Transform *parent): parent(parent) {
}

//
// Methods
//
Vector Transform::get_position() const {
    Vector world_position = position;
    const Transform *ancestor = parent;

    while (ancestor != nullptr) {
        const float angle = ancestor->rotation;
        const float rad = angle * (M_PI / 180.0f);

        const float rotated_x = world_position.x * cosf(rad) - world_position.y * sinf(rad);
        const float rotated_y = world_position.x * sinf(rad) + world_position.y * cosf(rad);

        world_position = {rotated_x + ancestor->position.x, rotated_y + ancestor->position.y};
        ancestor = ancestor->parent;
    }

    return world_position;
}

Vector Transform::get_scale() const {
    Vector world_scale = scale;

    const Transform *ancestor = parent;
    while (ancestor != nullptr) {
        world_scale = {world_scale.x * ancestor->scale.x, world_scale.y * ancestor->scale.y};
        ancestor = ancestor->parent;
    }

    return world_scale;
}

float Transform::get_rotation() const {
    float world_rotation = rotation;

    const Transform *ancestor = parent;
    while (ancestor != nullptr) {
        world_rotation += ancestor->rotation;
        ancestor = ancestor->parent;
    }

    return world_rotation;
}

Transform *Transform::get_parent() const { return this->parent; }

void Transform::set_position(const Vector &position) {
    if (parent != nullptr)
        this->position = position - parent->get_position();
    else
        this->position = position;
}

void Transform::set_scale(const Vector &scale) {
    // TODO: Add error handling
    if (scale.x < 0 || scale.y < 0)
        return;

    if (parent != nullptr) {
        const Vector parent_scale = parent->get_scale();
        this->scale = {
            parent_scale.x != Vector::IGNOREABLE_DISTANCE ? scale.x / parent_scale.x : 0,
            parent_scale.y != Vector::IGNOREABLE_DISTANCE ? scale.y / parent_scale.y : 0
        };
    } else
        this->scale = scale;
}

void Transform::set_rotation(const float rotation) {
    if (parent != nullptr)
        this->rotation = rotation - parent->get_rotation();
    else
        this->rotation = rotation;
}

void Transform::set_parent(Transform *parent) {
    // TODO: Add error handling.
    if (parent == this || is_descendent(parent))
        return;

    // Save the world position so we return to it after changing the parent.
    const Vector global_position = this->get_position();
    const Vector global_scale = this->get_scale();
    const float global_rotation = this->get_rotation();

    this->parent = parent;

    set_position(global_position);
    set_scale(global_scale);
    set_rotation(global_rotation);
}

bool Transform::is_descendent(const Transform *descendent) const {
    if (descendent == nullptr)
        return false;

    for (const Transform *ancestor = descendent->get_parent(); ancestor != nullptr; ancestor = ancestor->get_parent())
        if (ancestor == this)
            return true;

    return false;
}


Vector Transform::get_local_position() const { return this->position; }

Vector Transform::get_local_scale() const { return this->scale; }

float Transform::get_local_rotation() const { return this->rotation; }

void Transform::set_local_position(const Vector &position) { this->position = position; }

void Transform::set_local_scale(const Vector &scale) {
    // TODO: Add error handling
    if (scale.x < 0 || scale.y < 0)
        return;

    this->scale = scale;
}

void Transform::set_local_rotation(const float rotation) { this->rotation = rotation; }
