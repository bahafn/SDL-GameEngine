#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "utils/Vector.hpp"

class Transform {
    Vector position = {0, 0};
    Vector scale = {1, 1};
    float rotation = 0;

    Transform *parent = nullptr;

public:
    //
    // Constructors
    //
    Transform();

    Transform(const Vector &position, const Vector &scale, float rotation);

    Transform(const Vector &position, const Vector &scale, float rotation, Transform *parent);

    explicit Transform(Transform *parent);

    //
    // Methods
    //
    /** @returns the position of the object relative to the Vector(0, 0). */
    Vector get_position() const;

    /** @returns the scale of the object relative to the Vector(1, 1). */
    Vector get_scale() const;

    /** @returns the rotation of the object relative to 0 degrees. */
    float get_rotation() const;

    Transform *get_parent() const;

    /** Sets the position of the object relative to the Vector(0, 0). */
    void set_position(const Vector &position);

    /** Sets the scale of the object relative to the Vector(1, 1) */
    void set_scale(const Vector &scale);

    /** Sets the rotation of the object relative to zero degrees. */
    void set_rotation(float rotation);

    void set_parent(Transform *parent);

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
};

#endif //TRANSFORM_H
