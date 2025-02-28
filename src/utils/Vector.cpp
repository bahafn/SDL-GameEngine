#include "utils/Vector.hpp"
#include "cmath"

//
// Static Values
//
const Vector Vector::ZERO_VECTOR = Vector();
const Vector Vector::ONE_VECTOR = Vector(1, 1);

const Vector Vector::UP_VECTOR = Vector(0, 1);
const Vector Vector::DOWN_VECTOR = Vector(0, -1);
const Vector Vector::RIGHT_VECTOR = Vector(1, 0);
const Vector Vector::LEFT_VECTOR = Vector(-1, 0);

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

Vector Vector::operator-() const { return {-x, -y}; }

void Vector::operator+=(const Vector &other) {
    x += other.x;
    y += other.y;
}

void Vector::operator-=(const Vector &other) {
    x -= other.x;
    y -= other.y;
}

bool Vector::operator==(const Vector &other) const {
    const float x_diff = other.x - x;
    const float y_diff = other.y - y;
    return x_diff < IGNOREABLE_DISTANCE && y_diff < IGNOREABLE_DISTANCE;
}

bool Vector::operator!=(const Vector &other) const { return !(*this == other); }

//
// Methods
//
float Vector::distance(const Vector &other) const {
    return sqrtf(powf(x - other.x, 2) + powf(y - other.y, 2));
}
