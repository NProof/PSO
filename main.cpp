#include <iostream>
#include <random>
#include <cmath>

#include "Vector.h"
#include "Particle.h"
#include "Problem.h"

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

double Rastrigin(Vector v)
{
    double sum_f = .0;
    vector<double> vals = v.Getvals();
    for (int d = 0; d < v.Getdim(); ++d) {
        double dp = vals[d];
        sum_f += -10*cos(2*dp*M_PI)+dp*dp+10;
    }
	return sum_f;
}

int main() {
    std::vector<Particle> particles;
    double max = 3.0, min = -3.0;
    double tmp_vals[DIM_SPACE];
    for (int x = 0; x < P_SIZE; ++x) {
        for (int d = 0; d < DIM_SPACE; ++d) {
            tmp_vals[d] = (max - min) * rand() / (RAND_MAX + 1.0) + min;
        }
        Vector tmp_pos(DIM_SPACE, vector<double>(tmp_vals, tmp_vals + DIM_SPACE));
        for (int d = 0; d < DIM_SPACE; ++d) {
            tmp_vals[d] = (max - min) * rand() / (RAND_MAX + 1.0) + min;
        }
        Vector tmp_vel(DIM_SPACE, vector<double>(tmp_vals, tmp_vals + DIM_SPACE));
        particles.push_back(Particle(tmp_pos, tmp_vel));
    }

    Problem problem(Rastrigin);

    Vector gBest(particles[0].Getposition());

    for(auto p : particles) {
        cout << p.Getposition() << p.Getvelocity() << "\n";
        cout << "F: " << problem.fitness(p.Getposition()) << "\n";
        if (problem.fitness(p.Getposition()) < problem.fitness(gBest)) {
            gBest = p.Getposition();
            cout << "UPDATE gBest: " << gBest << "\n";
        }
    }
    }
    return 0;
}
