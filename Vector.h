#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <cmath>
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

        double euclidean_Metric();

        friend std::ostream & operator<<(std::ostream & os, const Vector & obj);

//        friend Vector operator*(double m, Vector & v);

        Vector operator*(double m) {
            double new_vals[dim];
            for(int d = 0; d < dim; ++d) {
                new_vals[d] = vals[d] * m;
            }
            return Vector(dim, std::vector<double>(new_vals, new_vals + dim));
        }

        Vector operator-(const Vector & oth) {
            double new_vals[dim];
            auto oth_vals = oth.Getvals();
            for(int d = 0; d < dim; ++d) {
                new_vals[d] = vals[d] - oth_vals[d];
            }
            return Vector(dim, std::vector<double>(new_vals, new_vals + dim));
        }

        Vector operator+(const Vector & oth) {
            double new_vals[dim];
            auto oth_vals = oth.Getvals();
            for(int d = 0; d < dim; ++d) {
                new_vals[d] = vals[d] + oth_vals[d];
            }
            return Vector(dim, std::vector<double>(new_vals, new_vals + dim));
        }

    protected:

    private:
        unsigned int dim;
        std::vector<double> vals;
};

//Vector operator*(double m, Vector & v) {
//    Vector tmp = v * m;
//    return tmp;
//}

#endif // VECTOR_H
