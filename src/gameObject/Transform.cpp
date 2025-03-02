#include "gameObject/Transform.hpp"

#include <pstl/execution_defs.h>

//
// Constructors
//
Transform::Transform() = default;

Transform::Transform(const Vector &position, const float rotation): position(position), rotation(rotation) {
}

Transform::Transform(const Vector &position, const float rotation, Transform *parent): position(position),
    rotation(rotation), parent(parent) {
}

Transform::Transform(Transform *parent): position(parent->position), rotation(parent->rotation), parent(parent) {
}

//
// Methods
//
Vector Transform::get_position() const { return this->position; }

float Transform::get_rotation() const { return this->rotation; }

Transform *Transform::get_parent() const { return this->parent; }

void Transform::set_position(const Vector &position) { this->position = position; }

void Transform::set_rotation(const float rotation) { this->rotation = rotation; }

void Transform::set_parent(Transform *parent) {
    if (parent == nullptr) {
        this->local_position = Vector::ZERO_VECTOR;
        this->parent = nullptr;
        return;
    }

    const Transform *ancestor = parent;
    while (ancestor != nullptr) {
        if (ancestor == this)
            return;

        ancestor = ancestor->get_parent();
    }

    this->parent = parent;
}

Vector Transform::get_local_position() const {
    if (parent == nullptr)
        return this->position;

    return this->position - parent->position;
}

float Transform::get_local_rotation() const {
    if (parent == nullptr)
        return this->rotation;

    return this->rotation - parent->rotation;
}

void Transform::set_local_position(const Vector &position) {
    if (parent != nullptr)
        this->position = parent->position + position;
    else
        this->position = position;
}

void Transform::set_local_rotation(const float rotation) {
    if (parent != nullptr)
        this->rotation = parent->rotation + rotation;
    else
        this->rotation = rotation;
}
