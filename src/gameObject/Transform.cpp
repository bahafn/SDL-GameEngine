#include "gameObject/Transform.hpp"
#include <cmath>

using std::shared_ptr;
using std::weak_ptr;

//
// Constructors
//
Transform::Transform() = default;

Transform::Transform(const Vector &position, const Vector &scale, const float rotation): position(position),
    scale(scale), rotation(rotation) {
}

Transform::Transform(const Vector &position, const Vector &scale, const float rotation,
                     const weak_ptr<Transform> &parent): position(position), scale(scale), rotation(rotation),
                                                              parent(parent) {
}

Transform::Transform(const weak_ptr<Transform> &parent): parent(parent) {
}

Transform::~Transform() { remove_all_children(); }

//
// Methods
//
Vector Transform::get_position() const {
    Vector world_position = position;
    shared_ptr<Transform> ancestor = get_parent();

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
        world_position = Vector(rotated_x, rotated_y) + ancestor->position;

        ancestor = ancestor->get_parent();
    }

    return world_position;
}


Vector Transform::get_scale() const {
    Vector world_scale = scale;

    shared_ptr<Transform> ancestor = get_parent();
    while (ancestor != nullptr) {
        world_scale = {world_scale.x * ancestor->scale.x, world_scale.y * ancestor->scale.y};
        ancestor = ancestor->get_parent();
    }

    return world_scale;
}

float Transform::get_rotation() const {
    float world_rotation = rotation;

    shared_ptr<Transform> ancestor = get_parent();
    while (ancestor != nullptr) {
        world_rotation += ancestor->rotation;
        ancestor = ancestor->get_parent();
    }

    return world_rotation;
}

shared_ptr<Transform> Transform::get_parent() const { return parent.lock(); }

bool Transform::has_parent() const { return get_parent() != nullptr; }

void Transform::set_position(const Vector &position) {
    if (has_parent()) {
        const Vector parent_global = get_parent()->get_position();
        const float parent_rotation = get_parent()->get_rotation();
        const Vector parent_scale = get_parent()->get_scale();
        const auto rad = static_cast<float>(-parent_rotation * (M_PI / 180.0f));

        Vector delta = (position - parent_global);
        delta.x /= parent_scale.x;
        delta.y /= parent_scale.y;
        float local_x = delta.x * cosf(rad) + delta.y * sinf(rad);
        float local_y = -delta.x * sinf(rad) + delta.y * cosf(rad);

        this->position = {local_x, local_y};
    } else
        this->position = position;
}

void Transform::set_scale(const Vector &scale) {
    // TODO: Add error handling
    if (scale.x < 0 || scale.y < 0)
        return;

    if (has_parent()) {
        const Vector parent_scale = get_parent()->get_scale();
        this->scale = {
            parent_scale.x != Vector::IGNOREABLE_DISTANCE ? scale.x / parent_scale.x : 0,
            parent_scale.y != Vector::IGNOREABLE_DISTANCE ? scale.y / parent_scale.y : 0
        };
    } else
        this->scale = scale;
}

void Transform::set_rotation(const float rotation) {
    if (has_parent())
        this->rotation = rotation - get_parent()->get_rotation();
    else
        this->rotation = rotation;
}

void Transform::set_parent(const shared_ptr<Transform> &parent) {
    if (parent == nullptr) {
        detach_parent();
        return;
    }

    // TODO: Add error handling.
    if (get_parent() == shared_from_this() || is_descendent(parent))
        return;

    if (has_parent())
        this->get_parent()->remove_child(shared_from_this());

    // Save the world position so we return to it after changing the parent.
    const Vector global_position = this->get_position();
    const Vector global_scale = this->get_scale();
    const float global_rotation = this->get_rotation();

    this->parent = parent;
    if (has_parent())
        get_parent()->children.push_back(shared_from_this());

    set_position(global_position);
    set_scale(global_scale);
    set_rotation(global_rotation);
}

void Transform::detach_parent() {
    if (has_parent()) {
        get_parent()->remove_child(shared_from_this());
        this->parent.reset();
    }
}

bool Transform::is_descendent(const shared_ptr<Transform> &descendent) const {
    if (descendent == nullptr)
        return false;

    shared_ptr<Transform> ancestor = descendent->get_parent();
    while (ancestor != nullptr) {
        if (ancestor.get() == this)
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

shared_ptr<Transform> Transform::get_child(const int index) const {
    // TODO: Add error handling.
    if (index < 0 || index >= get_child_count())
        return nullptr;

    return children.at(index);
}

void Transform::add_child(const shared_ptr<Transform> &child) { child->set_parent(shared_from_this()); }

void Transform::remove_child(const shared_ptr<Transform> &child) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if (*it != child)
            continue;

        (*it)->parent.reset();
        children.erase(it);
        return;
    }
}

void Transform::remove_all_children() { children.clear(); }

int Transform::get_child_count() const { return static_cast<int>(children.size()); }

bool Transform::is_child_of(const shared_ptr<Transform> &potential_ancestor) const {
    shared_ptr<Transform> ancestor = get_parent();
    while (ancestor != nullptr) {
        if (ancestor == potential_ancestor)
            return true;

        ancestor = ancestor->get_parent();
    }

    return false;
}
