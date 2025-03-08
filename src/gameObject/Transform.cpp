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

Transform::~Transform() { remove_all_children(); }

//
// Methods
//
Vector Transform::get_position() const {
    Vector world_position = position;
    const Transform *ancestor = parent;

    while (ancestor != nullptr) {
        // Apply scaling
        world_position.x *= ancestor->scale.x;
        world_position.y *= ancestor->scale.y;

        // Apply rotation
        const float angle = ancestor->rotation;
        const auto rad = static_cast<float>(angle * (M_PI / 180.0f));

        const float rotated_x = world_position.x * cosf(rad) - world_position.y * sinf(rad);
        const float rotated_y = world_position.x * sinf(rad) + world_position.y * cosf(rad);

        // Apply translation
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
    if (parent != nullptr) {
        const Vector parent_global = parent->get_position();
        const float parent_rotation = parent->get_rotation();
        const Vector parent_scale = parent->get_scale();
        const auto rad = static_cast<float>(-parent_rotation * (M_PI / 180.0f));

        float local_x = ((position.x - parent_global.x) / parent_scale.x) * cosf(rad) + (
                            (position.y - parent_global.y) / parent_scale.y) * sinf(rad);
        float local_y = -((position.x - parent_global.x) / parent_scale.x) * sinf(rad) + (
                            (position.y - parent_global.y) / parent_scale.y) * cosf(rad);

        this->position = {local_x, local_y};
    } else
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

    if (this->parent != nullptr)
        this->parent->remove_child(this);

    // Save the world position so we return to it after changing the parent.
    const Vector global_position = this->get_position();
    const Vector global_scale = this->get_scale();
    const float global_rotation = this->get_rotation();

    this->parent = parent;
    if (parent != nullptr)
        parent->children.push_back(this);

    set_position(global_position);
    set_scale(global_scale);
    set_rotation(global_rotation);
}

bool Transform::is_descendent(const Transform *descendent) const {
    if (descendent == nullptr)
        return false;

    const Transform *ancestor = descendent->get_parent();
    while (ancestor != nullptr) {
        if (ancestor == this)
            return true;

        ancestor = ancestor->get_parent();
    }

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

Transform *Transform::get_child(const int index) const {
    // TODO: Add error handling.
    if (index < 0 || index >= get_child_count())
        return nullptr;

    return children.at(index);
}

void Transform::add_child(Transform *child) { child->set_parent(this); }

void Transform::remove_child(const Transform *child) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if (*it != child)
            continue;

        children.erase(it);
        return;
    }
}

void Transform::remove_all_children() { children.clear(); }

int Transform::get_child_count() const { return static_cast<int>(children.size()); }

bool Transform::is_child_of(const Transform *potential_ancestor) const {
    const Transform *ancestor = parent;
    while (ancestor != nullptr) {
        if (ancestor == potential_ancestor)
            return true;

        ancestor = ancestor->parent;
    }

    return false;
}
