/* Space Marine - Edsel Apostol, Copyright 2013 */

#pragma once

#include <math.h>

template <class T>
class Vector2
{
public:
    Vector2() : x(0.0), y(0.0) {};
    Vector2(T X, T Y) : x(X), y(Y) {};
    Vector2(T theta) : x(cosf(theta)), y(sinf(theta)) {};
    Vector2(const Vector2 &vect) : x(vect.x), y(vect.y) {};

    ~Vector2() {};

    Vector2 <T> operator*(const T scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 <T> operator*(const Vector2 vect) const {
        return Vector2(x * vect.x, y * vect.y);
    }

    Vector2 <T> operator/(T scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    Vector2 <T> operator+(const Vector2 &vect) const {
        return Vector2(x + vect.x, y + vect.y);
    }

    Vector2 <T> operator-(const Vector2 &vect) const {
        return Vector2(x - vect.x, y - vect.y);
    }

    Vector2 <T>& operator*=(const T scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2 <T>& operator*=(const Vector2 &vect) {
        x *= vect.x;
        y *= vect.y;
        return *this;
    }

    Vector2 <T>& operator/=(const T scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    Vector2 <T>& operator+=(const Vector2 &vect) {
        x += vect.x;
        y += vect.y;
        return *this;
    }

    Vector2 <T>& operator-=(const Vector2 &vect) {
        x -= vect.x;
        y -= vect.y;
        return *this;
    }

    Vector2 <T>& operator=(const Vector2 &vect) {
        x = vect.x;
        y = vect.y;
        return *this;
    }

    Vector2 <T>& operator=(const T scalar) {
        x = scalar;
        y = scalar;
        return *this;
    }

    bool operator==(const T scalar) {
        return (x == scalar) && (y == scalar);
    }

    bool operator==(const Vector2 &vect) {
        return (x == vect.x) && (y == vect.y);
    }

    bool operator!=(const Vector2 &vect) {
        return (x != vect.x) || (y != vect.y);
    }

    bool operator!=(const T scalar) {
        return (x != scalar) && (y != scalar);
    }

    void rotate(T angle) {
        T xt = (x * cosf(angle)) - (y * sinf(angle));
        T yt = (y * cosf(angle)) + (x * sinf(angle));
        x = xt;
        y = yt;
    }

    Vector2 <T> normal() const {
        return Vector2 <T> (-y, x);
    }

    T cross(const Vector2 &vect2) const {
        return (this->x * vect2.y) - (this->y * vect2.x);
    }

    T magnitude() {
        return sqrtf(x * x + y * y);
    }

    T magnitudesq() {
        return (x * x + y * y);
    }

    void normalise() {
        T mag = sqrtf(x* x + y * y);
        this->x = x / mag;
        this->y = y / mag;
    }

    T dot(const Vector2 &vect) const {
        return (x * vect.x) + (y * vect.y);
    }

    static Vector2 <T> interpolate(const T& t, const Vector2& start, const Vector2& end) {
        T t2 = 1.0f - t;
        return Vector2(t2 * start.x + t * end.x, t2 * start.y + t * end.y);
    }

    T x, y;
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
