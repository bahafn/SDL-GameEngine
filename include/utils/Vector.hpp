#ifndef VECTOR_H
#define VECTOR_H

class Vector {
    /** If the difference between two floats is less than this, we consider them equal. */
    static constexpr float IGNOREABLE_DISTANCE = 1e-5;

public:
    //
    // Static values
    //
    /** Vector with default value used instead of constructing a new vector. */
    static const Vector ZERO_VECTOR,
            ONE_VECTOR,
            UP_VECTOR,
            DOWN_VECTOR,
            RIGHT_VECTOR,
            LEFT_VECTOR;

    //
    // Variables
    //
    float x, y;

    //
    // Constructors
    //
    Vector();

    Vector(float x, float y);

    //
    // Operators
    //
    Vector operator+(const Vector &other) const;

    Vector operator-(const Vector &other) const;

    Vector operator-() const;

    Vector operator*(float other) const;

    Vector operator/(float other) const;

    void operator+=(const Vector &other);

    void operator-=(const Vector &other);

    void operator*=(float other);

    void operator/=(float other);

    bool operator==(const Vector &other) const;

    bool operator!=(const Vector &other) const;

    //
    // Methods
    //
    /** Changes the vector to have a magnitude of one. */
    void normalize();

    //
    // Static Methods
    //
    static float distance(const Vector &a, const Vector &b);

    static float magnitude(const Vector &v);

    /** @returns Vector with the same direction but a magnitude of one. */
    static Vector normalize(const Vector &v);
};

#endif //VECTOR_H
