#include "Problem.h"

Problem::Problem(double (*fun_ptr)(Vector), std::vector<std::pair<double, double> > & c)
{
    this->fun_ptr = fun_ptr;
    this->c = c;
}

Problem::~Problem()
{
    //dtor
}

double Problem::fitness(Vector v) {
    return this->fun_ptr(v);
}
