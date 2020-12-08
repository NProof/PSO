#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <ostream>

class Vector
{
    public:
        Vector(unsigned int, std::vector<double>);
        virtual ~Vector();
        Vector(const Vector& other);
        Vector& operator=(const Vector& other);

        unsigned int Getdim() const { return dim; }
        void Setdim(unsigned int val) { dim = val; }
        std::vector<double> Getvals() const { return vals; }
        void Setvals(std::vector<double> val) { vals = val; }

        friend std::ostream & operator<<(std::ostream & os, const Vector & obj);
    protected:

    private:
        unsigned int dim;
        std::vector<double> vals;
};

#endif // VECTOR_H
