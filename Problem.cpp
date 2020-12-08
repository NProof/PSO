#include "Problem.h"

Problem::Problem(double (*fun_ptr)(Vector))
{
    this->fun_ptr = fun_ptr;
}

Problem::~Problem()
{
    //dtor
}

double Problem::fitness(Vector v) {
    return this->fun_ptr(v);
}
