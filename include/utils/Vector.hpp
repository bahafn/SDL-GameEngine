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

    bool operator==(const Vector &other) const;

    bool operator!=(const Vector &other) const;

    //
    // Methods
    //
    float distance(const Vector &other) const;
};

#endif //VECTOR_H
