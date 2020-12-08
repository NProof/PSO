#ifndef PROBLEM_H
#define PROBLEM_H

#include "Vector.h"

class Problem
{
    public:
        Problem(double (*)(Vector));
        virtual ~Problem();

        double fitness(Vector v);
    protected:

    private:
        double (*fun_ptr)(Vector);
};

#endif // PROBLEM_H
