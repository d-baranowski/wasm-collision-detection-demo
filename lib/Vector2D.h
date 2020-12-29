#pragma once

#include <math.h>
#include <iostream>

#ifndef HAMDS_ON_GAME_DEVELOPMENT_WITH_WEBASSEMBLY_BOOK_VECTOR_H
#define HAMDS_ON_GAME_DEVELOPMENT_WITH_WEBASSEMBLY_BOOK_VECTOR_H

class Vector2D {
private:
public:
    double x, y;
    explicit Vector2D(double nX = 0.0, double nY = 0.0);

    void SetXY(double nX, double nY);
    void SetDM(double dir, double mag);

    double GetDir();
    double GetMag();
    double X() const;
    double Y() const;

    Vector2D& operator+=(const Vector2D& v);
    Vector2D& operator-=(const Vector2D& v);
    Vector2D& operator/(const Vector2D& v);
    Vector2D& operator*(const Vector2D& v);
    Vector2D& operator*=(double t);
    Vector2D& operator/=(double t);
    Vector2D& operator&=(const Vector2D& v);
    Vector2D operator-(void) const;
    Vector2D operator+(const Vector2D& v) const;
    Vector2D operator-(const Vector2D& v) const;
    Vector2D operator*(double t) const;
    Vector2D operator/(double t) const;
    bool operator==(const Vector2D& v) const;
    bool operator!=(const Vector2D& v) const;
    Vector2D& Rotate(double angle);

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
    friend std::istream& operator>>(std::istream& os, Vector2D& v);
};

Vector2D operator* (double lhs, const Vector2D& rhs);
Vector2D operator/ (double lhs, const Vector2D& rhs);

#endif //HAMDS_ON_GAME_DEVELOPMENT_WITH_WEBASSEMBLY_BOOK_VECTOR_H
