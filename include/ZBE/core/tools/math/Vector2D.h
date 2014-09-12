/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Vector2d.h
 * @since 2010/07/22
 * @date 2014/09/12
 * @author ludo
 * @brief 2D vector
 */

#ifndef SRC_VECTOR2D_H_
#define SRC_VECTOR2D_H_

#include <cmath>

namespace zbe {

class Vector2D {
  public:
    Vector2D();
    Vector2D(const Vector2D &v);

    Vector2D& operator=(const Vector2D& v);
    Vector2D operator+(const Vector2D& v) const;
    Vector2D operator-(const Vector2D& v) const;
    Vector2D operator*(double d) const;
    virtual ~Vector2D();

    void setX(double x);
    void setY(double y);
    void setXY(double x, double y);

    void setRads(double rads);
    void setDegrees(double degrees);
    void setModule(double m);

    double getX()const;
    double getY()const;

    double getRads()const;
    double getDegrees()const;
    double getModule()const;
    double getSqrModule()const;

    Vector2D getNormalA()const;
    Vector2D getNormalB()const;

    double sumVector(const Vector2D& v);
    double increaseVector(double increment);

    double increaseX(double increment);
    double increaseY(double increment);

    double mulByScalar(double scalar);

    void reflect(const Vector2D& v);

    bool isNullVector();

    // const  vectors
    static const Vector2D NULL_VECTOR;
    static const Vector2D ZERO_VECTOR;

    // static methods
    static Vector2D sumVector(Vector2D v1, Vector2D v2);
    static Vector2D mulVectByScalar(Vector2D v, double scalar);
    static double mulVectScalar(Vector2D v1, Vector2D v2);
    static double getRadsAB(Vector2D v1, Vector2D v2);
    static Vector2D reflect(const Vector2D &v1, const Vector2D &v2);


  protected:
    double x;  // vector X coordenate
    double y;  // vector Y coordenate
};
}
#endif  // SRC_VECTOR2D_H_
