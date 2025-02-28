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

void Vector::operator*=(float other) {
    x *= other;
    y *= other;
}

void Vector::operator/=(float other) {
    x /= other;
    y /= other;
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
void Vector::normalize() {
    const float magnitude = Vector::magnitude(*this);

    if (magnitude > IGNOREABLE_DISTANCE)
        *this /= magnitude;

    *this = ZERO_VECTOR;
}

std::ostream &operator<<(std::ostream &out, const Vector &data) {
    out << "x: " << data.x << " y: " << data.y << "\n";
    return out;
}

//
// Static Methods
//
float Vector::distance(const Vector &a, const Vector &b) {
    return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
}

float Vector::magnitude(const Vector &v) {
    return sqrtf(powf(v.x, 2) + powf(v.y, 2));
}

Vector Vector::normalize(const Vector &v) {
    const float magnitude = Vector::magnitude(v);

    if (magnitude > IGNOREABLE_DISTANCE)
        return v / magnitude;

    return ZERO_VECTOR;
}
