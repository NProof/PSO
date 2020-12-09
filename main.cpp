#include <iostream>
#include <random>
#include <cmath>
#include <fstream>
#include <iomanip>

#include "Vector.h"
#include "Particle.h"
#include "Problem.h"

#define P_SIZE 7
#define DIM_SPACE 1
#define TIMES_EXP 100

using namespace std;

struct Record {
    long _count_Fit;
    Vector _gBest;
    double _fit;

    Record(long count_Fit, Vector & gBest, double fit)
        :_gBest(gBest), _count_Fit(count_Fit), _fit(fit){
    }
};

std::ostream & operator<<(std::ostream & os, const Vector & obj) {
    vector<double> vals = obj.Getvals();
    int d = 0;
    os << "< " << vals[d];
    for (d= 1; d < DIM_SPACE; ++d) {
        os << ", " << vals[d];
    }
    return os << " >";
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

double absVector(Vector v)
{
    double sum_f = .0;
    vector<double> vals = v.Getvals();
    for (int d = 0; d < v.Getdim(); ++d) {
        double dp = vals[d];
        sum_f += abs(dp);
    }
	return sum_f;
}

double Variance(std::vector<Particle *> ps) {
    double mean[DIM_SPACE] = {0};
    for (auto p : ps) {
        vector<double> vals = p->Getposition().Getvals();
        for (int d = 0; d < DIM_SPACE; ++d) {
            mean[d] += vals[d];
        }
    }
    for (int d = 0; d < DIM_SPACE; ++d) {
        mean[d] /= P_SIZE;
    }
    Vector vMean(DIM_SPACE, vector<double>(mean, mean + DIM_SPACE));
    double sum = 0.0;
    for (auto p : ps) {
        vector<double> diffv = (p->Getposition() - vMean).Getvals();
        for (int d = 0; d < DIM_SPACE; ++d) {
            double vDif = diffv[d];
            sum += vDif * vDif;
        }
    }
    return sum / P_SIZE;
}

int main() {
    std::vector<std::pair<double, double> > conditionRang;
    conditionRang.push_back(std::make_pair(3.0, -3.0));
    Problem problem(Rastrigin, conditionRang);

    double w = 0.8, c1 = 1.2, c2 = 0.5, lr = 0.7, vc = 0.2;
    double vMax = 2;

    vector<Record> allRecord;
    for(int e = 0; e < TIMES_EXP; ++e) {
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

//        cout << "--------- GBest ---------- " << endl;

        for(auto p : particles) {
            Vector position = p->Getposition();
            if (problem.fitness(position) < problem.fitness(gBest)) {
                gBest = position;
//                cout << "UPDATE gBest: " << gBest << "\n";
            }
        }

        long times = 0;
        int counts = 0;
        int outs = 0;
        double valVar;
        while ((valVar = Variance(particles)) > vc || (valVar <= vc && counts < 8)) {
            ++times;
            if (valVar <= vc) {
                outs = 0;
                ++counts;
                if (counts % 3 == 0) {
                    vc /= 1.25;
                }
            }
            else {
                counts = 0;
                ++outs;
                if (outs % 5 == 0) {
                    vc *= 2.0;
                }
            }

//            cout << "--------- Trans ---------- " << endl;
//
//            cout << times << " C " << counts << " [Var] : " << valVar << endl;

            double r1, r2;
            r1 =  rand() / (RAND_MAX + 1.0);
            r2 =  rand() / (RAND_MAX + 1.0);

            for(auto p : particles) {
                Vector new_velocity = p->Getvelocity() * w
                    + (p->GetbkPosition() - p->Getposition()) * c1 * r1
                    + (gBest - p->Getposition()) * c2 * r2;

                double distV = new_velocity.euclidean_Metric();
                if (distV > vMax) {
                    new_velocity = new_velocity * vMax / distV;
                }

                p->Setvelocity(new_velocity);

                Vector new_position = p->Getposition() + p->Getvelocity() * lr;
                auto c = problem.c;
                auto new_vals = new_position.Getvals();
                for (int d = 0; d < DIM_SPACE; ++d) {
                    if (new_vals[d] <= c[d].first && new_vals[d] >= c[d].second) ;
                    else if (new_vals[d] > c[d].first) {
                        new_vals[d] = c[d].first;
                    }
                    else new_vals[d] = c[d].second;
                }
                new_position.Setvals(new_vals);

                p->Setposition(new_position);

                if (problem.fitness(new_position) < problem.fitness(p->GetbkPosition())) {
                    p->SetbkPosition(new_position);
    //                cout << "UPDATE p Best: " << p->GetbkPosition() << "\n";
                    if (problem.fitness(new_position) < problem.fitness(gBest)) {
                        gBest = p->Getposition();
    //                    cout << "UPDATE gBest: " << gBest << "\n";
                    }
                }
            }
        }

        Record r(times * P_SIZE, gBest, problem.fitness(gBest));
        allRecord.push_back(r);
    }

    std::ofstream summaryfile;
    summaryfile.open("summary.csv");

    double mean_times = .0;
    double mean_fit = .0;
    for (int e = 0; e < TIMES_EXP; ++e) {
        auto r = allRecord[e];
        mean_times += r._count_Fit;
        mean_fit += r._fit;
    }
    mean_times /= TIMES_EXP;
    mean_fit /= TIMES_EXP;

    summaryfile << 0 << ", " << mean_times << ", " << std::setprecision(20 ) << mean_fit << "\n";
    for (int e = 0; e < TIMES_EXP; ++e) {
        auto r = allRecord[e];
        summaryfile << e + 1 << ", " << r._count_Fit << ", " << std::setprecision(20 ) << r._fit << "\n";
    }

    return 0;
}
