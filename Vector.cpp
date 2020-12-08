#include "Vector.h"

Vector::Vector(unsigned int dim, std::vector<double> vals)
{
    //ctor
    this->dim = dim;
    this->vals = vals;
}

Vector::~Vector()
{
    //dtor
}

Vector::Vector(const Vector& other)
{
//
    this->dim = other.Getdim();
    this->vals = other.Getvals();
}

Vector& Vector::operator=(const Vector& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    this->dim = rhs.Getdim();
    this->vals = rhs.Getvals();
    return *this;
}
