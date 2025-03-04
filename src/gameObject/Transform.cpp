#include "gameObject/Transform.hpp"

//
// Constructors
//
Transform::Transform() = default;

Transform::Transform(const Vector &position, const float rotation): position(position), rotation(rotation) {
}

Transform::Transform(const Vector &position, const float rotation, Transform *parent): position(position),
    rotation(rotation), parent(parent) {
}

Transform::Transform(Transform *parent):parent(parent) {
}

//
// Methods
//
Vector Transform::get_position() const {
    if (parent == nullptr)
        return position;

    return this->position + parent->position;
}

Vector Transform::get_scale() const {
    if (parent == nullptr)
        return scale;

    return {scale.x * parent->scale.x, scale.y * parent->scale.y};
}

float Transform::get_rotation() const {
    if (parent == nullptr)
        return rotation;

    return this->rotation + parent->rotation;
}

Transform *Transform::get_parent() const { return this->parent; }

void Transform::set_position(const Vector &position) {
    if (parent != nullptr)
        this->position = position - parent->position;
    else
        this->position = position;
}

void Transform::set_scale(const Vector &scale) {
    if (parent != nullptr)
        this->scale = Vector(scale.x / parent->scale.x, scale.y / parent->scale.y);
    else
        this->scale = scale;
}

void Transform::set_rotation(const float rotation) {
    if (parent != nullptr)
        this->rotation = rotation - parent->rotation;
    else
        this->rotation = rotation;
}

void Transform::set_parent(Transform *parent) {
    const Transform *ancestor = parent;
    while (ancestor != nullptr) {
        if (ancestor == this)
            return;

        ancestor = ancestor->get_parent();
    }

    this->parent = parent;
}

Vector Transform::get_local_position() const { return this->position; }

Vector Transform::get_local_scale() const { return this->scale; }

float Transform::get_local_rotation() const { return this->rotation; }

void Transform::set_local_position(const Vector &position) { this->position = position; }

void Transform::set_local_scale(const Vector &scale) { this->scale = scale; }

void Transform::set_local_rotation(const float rotation) { this->rotation = rotation; }
