/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Vector2d.cpp
 * @since 2010/07/22
 * @date 2014/09/12
 * @author ludo
 * @brief 2D vector
 */

#include "ZBE/core/tools/math/Vector2D.h"

#define M_PI		3.14159265358979323846

namespace zbe {

const Vector2D Vector2D::NULL_VECTOR;
const Vector2D Vector2D::ZERO_VECTOR;

/**
 * @fn Vector2D::Vector2D
 * @brief void constructor
 */
Vector2D::Vector2D(): x(0), y(0) {}

/**
 * @fn Vector2D::Vector2D
 * @param v input vector
 * @brief copy constructor
 */
Vector2D::Vector2D(const Vector2D &v): x(v.getX()), y(v.getY()) {}

/**
 * @fn Vector2D::operator=
 * @return result in a Vector2D
 * @param v input vector
 * @brief Make itself equal to given Vector2d
 */
Vector2D& Vector2D::operator= (const Vector2D& v) {
  x = v.x;
  y = v.y;
  return (*this);
};

/**
 * @fn Vector2D::operator+
 * @return result in a Vector2D
 * @param v second input vector
 * @param u first input vector
 * @brief sums two vector2d
 */
Vector2D Vector2D::operator+(const Vector2D& v) const{
  Vector2D aux;
  aux.setXY(x+v.getX(),y+v.getY());
  return (aux);
}

/**
 * @fn Vector2D::operator+
 * @return result in a Vector2D
 * @param v second input vector
 * @param u first input vector
 * @brief sums two vector2d
 */
Vector2D Vector2D::operator-(const Vector2D& v) const{
  Vector2D aux;
  aux.setXY(x-v.getX(),y-v.getY());
  return (aux);
}

Vector2D Vector2D::operator*(double d) const {
  Vector2D aux;
    aux.setXY(d*(this->getX()),d*(this->getY()));
    return (aux);
}

/**
 * @fn Vector2D::~Vector2D
 * @brief destructor
 */
Vector2D::~Vector2D() {}

/**
 * @fn Vector2D::setX
 * @param x value for x coord
 * @return assigned value
 * @brief Set the X coord of vector
 */
void Vector2D::setX(double x) {
  this->x = x;
}

/**
 * @fn Vector2D::setY
 * @param x value for x coord
 * @return assigned value
 * @brief Set the Y coord of vector
 */
void Vector2D::setY(double y) {
  this->y = y;
}

/**
 * @fn Vector2D::setXY
 * @param x value for x coord
 * @param y value for y coord
 * @return assigned value
 * @brief Set the Y coord of vector
 */
void Vector2D::setXY(double x, double y) {
  this->x = x;
  this->y = y;
}

/**
 * @fn Vector2D::getX
 * @return value for x coord
 * @brief Returns value for x coord
 */
double Vector2D::getX()const {
  return (x);
}

/**
 * @fn Vector2D::getY
 * @return value for y coord
 * @brief Returns value for y coord
 */
double Vector2D::getY()const {
  return (y);
}

/**
 * @fn Vector2D::setRads
 * @param rads value in rads
 * @return assigned value
 * @brief Set value in rads for vector
 */
void Vector2D::setRads(double rads) {
  double m = this->getModule();
  x = (cos(rads) * (m));
  y = (cos(rads) * (m));
}

/**
 * @fn Vector2D::setDegrees
 * @param degrees value in degrees
 * @return assigned value
 * @brief Set value in degrees for vector
 */
void Vector2D::setDegrees(double degrees) {
  double r = degrees*(M_PI / 180);
  this->setRads(r);
}

/**
 * @fn Vector2D::setModule
 * @param degrees value in degrees
 * @return assigned value
 * @brief Set value in degrees for vector
 */
void Vector2D::setModule(double m) {
  //double r = this->getRads();
  double mod = this->getModule();
  x = (x/mod * (m));
  y = (y/mod * (m));
}

/**
 * @fn Vector2D::getRads
 * @return angle value in rads
 * @brief Returns angle value in rads
 */
double Vector2D::getRads()const {
  double rad;
  if (x > 0 && y >= 0) {
    rad = atan(static_cast<double>(y) / static_cast<double>(x));
  }  else if (x > 0 && y < 0) {
    rad = atan(static_cast<double>(y) / static_cast<double>(x)) + 2.0 * M_PI;
  }  else if (x < 0)  {
    rad = atan(static_cast<double>(y) / static_cast<double>(x)) + M_PI;
  }  else if (x == 0 && y >= 0) {
    rad = M_PI / 2.0;
  }  else {
    rad = 3.0*M_PI / 2.0;
  }
  return (rad);
}

/**
 * @fn Vector2D::getDegrees
 * @return angle value in rads
 * @brief Returns angle value in rads
 */
double Vector2D::getDegrees()const {
  return ((atan(y / x)) * (180 / M_PI));
}

/**
 * @fn Vector2D::getModule
 * @return module from the vector
 * @brief Returns module from the vector
 */
double Vector2D::getModule()const {
  return (sqrt((y * y) + (x * x)));
}

/**
 * @fn Vector2D::getModule
 * @return module from the vector
 * @brief Returns squared module from the vector, avoiding square-root computation
 */
double Vector2D::getSqrModule() const {
  return ((y * y) + (x * x));
}


Vector2D Vector2D::getNormalA()const {
  Vector2D aux;
  aux.setXY(y,-x);
  return (aux);
}

Vector2D Vector2D::getNormalB()const {
  Vector2D aux;
  aux.setXY(-y,x);
  return (aux);
}

/**
 * @fn Vector2D::sumVector
 * @param v vetor to add
 * @return result value
 * @brief add given vector to this one and returns the result value
 */
double Vector2D::sumVector(const Vector2D& v) {
  x = x + v.getX();
  y = y + v.getY();

  return (this->getModule());
}

/**
 * @fn Vector2D::increaseVector
 * @param increment value to add to the vector module
 * @return result vector
 * @brief add an increment given to this one (module) and returns the result value
 */
double Vector2D::increaseVector(double increment) {
  double m = this->getModule();
  m = m + increment;
  this->setModule(m);
  return (m);
}

/**
 * @fn Vector2D::increaseX
 * @param increment value to increase
 * @return result x
 * @brief add a increment to the x coord of this vector an returns the result value
 */
double Vector2D::increaseX(double increment) {
  x = x + increment;
  return (x);
}

/**
 * @fn Vector2D::increaseY
 * @param increment value to increase
 * @return result y
 * @brief add a increment to the y coord of this vector an returns the result value
 */
double Vector2D::increaseY(double increment) {
  y = y + increment;
  return (y);
}

/**
 * @fn Vector2D::mulByScalar
 * @param scalar scalar value to multiply by
 * @return result module
 * @brief multiply this vector by an scalar value and returns the result module
 */
double Vector2D::mulByScalar(double scalar) {
  double m = this->getModule();
  m = m * scalar;
  this->setModule(m);
  return (m);
}

/**
 * @fn Vector2D::reflect
 * @param normal Vector normal to the collision plane.
 * @brief calculates the resulting path of reflection of a ray or impact of an object with a plane.
 */
void Vector2D::reflect(const Vector2D& normal) {
  (*this) =  reflect((*this),normal);
}

/**
 * @fn Vector2D::mulVectScalar
 * @param v1 first operand
 * @param v2 second operand
 * @return scalar multiply result
 * @brief make a scalar multiply with two vectors
 */
double Vector2D::mulVectScalar(Vector2D v1, Vector2D v2) {
  return (v1.x*v2.x + v1.y*v2.y);
}

/**
 * @fn Vector2D::sumVector
 * @param v1 first operand
 * @param v2 second operand
 * @return vector sum result
 * @brief sum two vectors
 */
Vector2D Vector2D::sumVector(Vector2D v1, Vector2D v2) {
  Vector2D v3;
  v3.setX(v1.getX() + v2.getX());
  v3.setY(v1.getY() + v2.getY());
  return (v3);
}

/**
 * @fn Vector2D::mulVectByScalar
 * @param v vector, first operand
 * @param scalar scalar second operand
 * @return keyboard state
 * @brief Returns the keyboard state
 */
Vector2D Vector2D::mulVectByScalar(Vector2D v, double scalar) {
  Vector2D v1;
  v1.setModule(scalar * v.getModule());
  v1.setRads(v.getRads());
  return (v1);
}

/**
 * @fn Vector2D::getRadsAB
 * @param v1 first operand
 * @param v2 second operand
 * @return angle diference between vectors in rads
 * @brief calculate angle diference between vectors in rads
 */
double Vector2D::getRadsAB(Vector2D v1, Vector2D v2) {
  return (fabs(v1.getRads() - v2.getRads()));
}

/**
 * @fn Vector2D::reflect
 * @param ray Vector with the ray or object path.
 * @param normal Vector normal to the collision plane.
 * @return Vector with the ray or object path reflected.
 * @brief calculates the resulting path of reflection of a ray or impact of an object with a plane.
 */
//
//                      1 - 2(normal.x^2)
//  ray.x = ray.x * -------------------------
//                   normal.x^2 + normal.y^2
//
//                    2(normal.x * normal.y)
//        - ray.y * -------------------------
//                   normal.x^2 + normal.y^2
//
//
//                    -2(normal.x * normal.y)
//  ray.y = ray.x * -------------------------
//                   normal.x^2 + normal.y^2
//
//                      1 - 2(normal.y^2)
//        + ray.y * -------------------------
//                   normal.x^2 + normal.y^2
//
Vector2D Vector2D::reflect(const Vector2D &ray, const Vector2D &normal) {
  Vector2D v;
  Vector2D normalAux = normal;
  normalAux.setModule(1.0);

  double nx = normalAux.getX();
  double ny = normalAux.getY();
  double nx2 = nx*nx;
  double ny2 = ny*ny;
  double nxy = nx*ny;
  double nx2ny2 = nx2+ny2;

  double rx = ray.getX();
  double ry = ray.getY();

  v.setX(rx * (1-(2*nx2))/(nx2ny2)-
         ry * (2*nxy)/(nx2ny2));

  v.setY(rx * (-(2*nxy))/(nx2ny2)+
         ry * (1-(2*ny2))/(nx2ny2));

  return (v);
}

bool Vector2D::isNullVector() {
  return (x == 0 && y == 0);
}

}

