#include "gameObject/Transform.hpp"

Transform::Transform() = default;

Transform::Transform(const Vector &position, const float rotation): position(position), rotation(rotation) {
}

Transform::Transform(const Vector &position, const float rotation, Transform *parent): position(position),
    rotation(rotation), parent(parent) {
}


Vector Transform::get_position() const { return this->position; }

Vector Transform::get_local_position() const { return this->local_position; }

float Transform::get_rotation() const { return this->rotation; }

float Transform::get_local_rotation() const { return this->local_rotation; }

Transform *Transform::get_parent() const { return this->parent; }

void Transform::set_position(const Vector &position) {
    this->position = position;

    if (parent != nullptr)
        this->local_position = this->position - parent->get_position();
    else
        this->local_position = this->position;
}

void Transform::set_local_position(const Vector &position) {
    this->local_position = position;

    if (parent != nullptr)
        this->position = this->local_position + parent->get_position();
    else
        this->position = local_position;
}

void Transform::set_rotation(const float rotation) {
    this->rotation = rotation;

    if (parent != nullptr)
        this->local_rotation = this->rotation - parent->get_rotation();
    else
        this->local_rotation = this->rotation;
}

void Transform::set_local_rotation(const float rotation) {
    this->local_rotation = rotation;

    if (parent != nullptr)
        this->rotation = this->local_rotation + parent->get_rotation();
    else
        this->rotation = this->local_rotation;
}

void Transform::set_parent(Transform *parent) {
    const Transform *ancestor = parent;
    while (ancestor != nullptr) {
        if (ancestor == this)
            return;

        ancestor = ancestor->get_parent();
    }

    if (parent != nullptr) {
        this->local_position = this->position - parent->get_position();
        this->local_rotation = this->rotation - parent->get_rotation();
    } else {
        this->local_position = this->position;
        this->local_rotation = this->rotation;
    }

    this->parent = parent;
}
