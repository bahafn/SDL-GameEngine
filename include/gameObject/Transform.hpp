#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>
#include <memory>

#include "utils/Vector.hpp"

class Transform : public std::enable_shared_from_this<Transform> {
    Vector position = {0, 0};
    Vector scale = {1, 1};
    float rotation = 0;

    std::weak_ptr<Transform> parent;
    std::vector<std::shared_ptr<Transform> > children;

public:
    //
    // Constructors and Destructor
    //
    Transform();

    Transform(const Vector &position, const Vector &scale, float rotation);

    Transform(const Vector &position, const Vector &scale, float rotation,
              const std::weak_ptr<Transform> &parent);

    explicit Transform(const std::weak_ptr<Transform> &parent);

    ~Transform();

    //
    // Methods
    //
    /** @returns the position of the object relative to the Vector(0, 0). */
    Vector get_position() const;

    /** @returns the scale of the object relative to the Vector(1, 1). */
    Vector get_scale() const;

    /** @returns the rotation of the object relative to 0 degrees. */
    float get_rotation() const;

    std::shared_ptr<Transform> get_parent() const;

    bool has_parent() const;

    /** Sets the position of the object relative to the Vector(0, 0). */
    void set_position(const Vector &position);

    /** Sets the scale of the object relative to the Vector(1, 1) */
    void set_scale(const Vector &scale);

    /** Sets the rotation of the object relative to zero degrees. */
    void set_rotation(float rotation);

    void set_parent(const std::shared_ptr<Transform> &parent);

    /** Removes the parent of the object. */
    void detach_parent();

    /** @returns the position of the object relative to the parent.position. */
    Vector get_local_position() const;

    /** @returns the scale of the object relative to the parent.scale. */
    Vector get_local_scale() const;

    /** @returns the rotation of the object relative to the parent.rotation. */
    float get_local_rotation() const;

    /** Sets the position of the object relative to the parent.position. */
    void set_local_position(const Vector &position);

    /** Sets the scale of the object relative to the parent.scale. */
    void set_local_scale(const Vector &scale);

    /** Sets the rotation of the object relative to the parent.rotation. */
    void set_local_rotation(float rotation);

    std::shared_ptr<Transform> get_child(int index) const;

    void add_child(const std::shared_ptr<Transform> &child);

    void remove_child(const std::shared_ptr<Transform> &child);

    void remove_all_children();

    int get_child_count() const;

    bool is_child_of(const std::shared_ptr<Transform> &potential_ancestor) const;

private:
    bool is_descendent(const std::shared_ptr<Transform> &descendent) const;
};

#endif //TRANSFORM_H
