#include <iostream>
#include <random>

#include "Vector.h"
#include "Particle.h"

#define P_SIZE 7
#define DIM_SPACE 1

using namespace std;

std::ostream & operator<<(std::ostream & os, const Vector & obj) {
    os << "[" << obj.Getdim() << "] ";
    os << "<";
    for (auto v : obj.Getvals()) {
        os << v << ", ";
    }
    os << ">";
    return os;
}

int main() {
    std::vector<Particle> particles;
    double max = 3.0, min = -3.0;
    double tmp_vals[DIM_SPACE];
    for (int x=0; x<P_SIZE; ++x) {
        for (int d=0; d<DIM_SPACE; ++d) {
            tmp_vals[d] = (max - min) * rand() / (RAND_MAX + 1.0) + min;
        }
        Vector tmp_pos(DIM_SPACE, vector<double>(tmp_vals, tmp_vals + DIM_SPACE));
        for (int d=0; d<DIM_SPACE; ++d) {
            tmp_vals[d] = (max - min) * rand() / (RAND_MAX + 1.0) + min;
        }
        Vector tmp_vel(DIM_SPACE, vector<double>(tmp_vals, tmp_vals + DIM_SPACE));
        particles.push_back(Particle(tmp_pos, tmp_vel));
    }

    for(auto p : particles) {
        cout << p.Getposition() << p.Getvelocity() << "\n";
    }
    return 0;
}
