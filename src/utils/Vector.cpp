#include "utils/Vector.hpp"
#include "cmath"

//
// Static Values
//
Vector Vector::zero_vector = Vector();
Vector Vector::one_vector = Vector(1, 1);

Vector Vector::up_vector = Vector(0, 1);
Vector Vector::down_vector = Vector(0, -1);
Vector Vector::right_vector = Vector(1, 0);
Vector Vector::left_vector = Vector(-1, 0);

//
// Constructors
//
Vector::Vector(): x(0), y(0) {
}

Vector::Vector(const float x, const float y): x(x), y(y) {
}

//
// Operators
//
Vector Vector::operator+(const Vector &other) const { return {x + other.x, y + other.y}; }

Vector Vector::operator-(const Vector &other) const { return {x - other.x, y - other.y}; }

Vector Vector::operator*(const float other) const { return {x * other, y * other}; }

Vector Vector::operator/(const float other) const { return {x / other, y / other}; }

//
// Methods
//
float Vector::distance(const Vector &other) const {
    return sqrtf(powf(x - other.x, 2) + powf(y - other.y, 2));
}

//
// Static Methods
//
Vector Vector::zero() { return zero_vector; }

Vector Vector::one() { return one_vector; }

Vector Vector::up() { return up_vector; }

Vector Vector::down() { return down_vector; }

Vector Vector::right() { return right_vector; }

Vector Vector::left() { return left_vector; }
