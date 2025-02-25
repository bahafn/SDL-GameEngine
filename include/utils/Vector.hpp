#ifndef VECTOR_H
#define VECTOR_H

class Vector {
    //
    // Static values
    //
    static Vector zero_vector;
    static Vector one_vector;
    static Vector up_vector;
    static Vector down_vector;
    static Vector right_vector;
    static Vector left_vector;

public:
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

    Vector operator*(float other) const;

    Vector operator/(float other) const;

    //
    // Static Methods
    //
    static Vector zero();

    static Vector one();

    static Vector up();

    static Vector right();

    static Vector down();

    static Vector left();

    //
    // Methods
    //
    float distance(const Vector &other) const;
};

#endif //VECTOR_H
