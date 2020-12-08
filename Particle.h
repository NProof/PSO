#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector.h"

class Particle
{
    public:
        Particle(Vector &, Vector &);
        virtual ~Particle();

        Vector Getposition() { return position; }
        void Setposition(Vector & val) { position = val; }
        Vector Getvelocity() { return velocity; }
        void Setvelocity(Vector & val) { velocity = val; }
        Vector GetbkPosition() { return bkPosition; }
        void SetbkPosition(Vector & val) { bkPosition = val; }

    protected:

    private:
        Vector position;
        Vector velocity;
        Vector bkPosition;
};

#endif // PARTICLE_H
