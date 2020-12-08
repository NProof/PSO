#ifndef PROBLEM_H
#define PROBLEM_H

#include "Vector.h"
#include <vector>
#include <utility>

class Problem
{
    public:
        Problem(double (*)(Vector), std::vector<std::pair<double, double> > &);
        virtual ~Problem();

        double fitness(Vector v);
        std::vector<std::pair<double, double> > c;
    protected:

    private:
        double (*fun_ptr)(Vector);
};

#endif // PROBLEM_H
