#include "Particle.h"

Particle::Particle(Vector & position, Vector & velocity)
    :position(position), velocity(velocity), bkPosition(position)
{
    //ctor
}

Particle::~Particle()
{
    //dtor
}
