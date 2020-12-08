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
    std::vector<std::pair<double, double> > conditionRang;
    conditionRang.push_back(std::make_pair(3.0, -3.0));
    Problem problem(Rastrigin, conditionRang);

    double w = 0.8, c1 = 1.2, c2 = 0.6, lr = 0.5;

    std::vector<Particle *> particles;
    double tmp_vals[DIM_SPACE];
    for (int x = 0; x < P_SIZE; ++x) {
        for (int d = 0; d < DIM_SPACE; ++d) {
            tmp_vals[d] = (problem.c[d].first - problem.c[d].second) * rand() / (RAND_MAX + 1.0) + problem.c[d].second;
        }
        Vector tmp_pos(DIM_SPACE, vector<double>(tmp_vals, tmp_vals + DIM_SPACE));
        for (int d = 0; d < DIM_SPACE; ++d) {
            tmp_vals[d] = (problem.c[d].first - problem.c[d].second) * rand() / (RAND_MAX + 1.0) + problem.c[d].second;
        }
        Vector tmp_vel(DIM_SPACE, vector<double>(tmp_vals, tmp_vals + DIM_SPACE));
        particles.push_back(new Particle(tmp_pos, tmp_vel));
    }

    Vector gBest(particles[0]->Getposition());

//    cout << "--------- Trans ---------- " << endl;

    for(auto p : particles) {
        Vector new_velocity = p->Getvelocity() * w
            + (p->GetbkPosition() - p->Getposition()) * c1
            + (gBest - p->Getposition()) * c2;

        p->Setvelocity(new_velocity);

        Vector new_position = p->Getposition() + p->Getvelocity() * lr;

        p->Setposition(new_position);

        if (problem.fitness(new_position) < problem.fitness(p->GetbkPosition())) {
            p->SetbkPosition(new_position);
//            cout << "UPDATE p Best: " << p->GetbkPosition() << "\n";
            if (problem.fitness(new_position) < problem.fitness(gBest)) {
                gBest = p->Getposition();
//                cout << "UPDATE gBest: " << gBest << "\n";
            }
        }
    }

    return 0;
}
