#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "utils/Vector.hpp"

class Transform {
    /** Position of the object on the screen. */
    Vector position = {0, 0};
    /** Position of the object relative to the parent's position. */
    Vector local_position = {0, 0};
    /** Rotation of the object on the screen in degrees. */
    float rotation = 0;
    /** Rotation of the object relative to the parent's rotation on degrees. */
    float local_rotation = 0;

    Transform *parent = nullptr;

public:
    //
    // Constructors
    //
    Transform();

    Transform(const Vector &position, float rotation);

    Transform(const Vector &position, float rotation, Transform *parent);

    explicit Transform(Transform *parent);

    //
    // Methods
    //
    Vector get_position() const;

    float get_rotation() const;

    Transform *get_parent() const;

    void set_position(const Vector &position);

    void set_rotation(float rotation);

    void set_parent(Transform *parent);

    Vector get_local_position() const;

    float get_local_rotation() const;

    void set_local_position(const Vector &position);

    void set_local_rotation(float rotation);
};

#endif //TRANSFORM_H
