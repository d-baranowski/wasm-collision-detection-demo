#include "particle_force_generator.h"


using namespace cyclone;

ParticleGravity::ParticleGravity(const Vector3 &gravity) : gravity(gravity) {}

void ParticleGravity::updateForce(Particle *particle, real duration) {
    // Check that we do not have infinite mass
    if (!particle->hasFiniteMass()) return;

    // Apply the mass-scaled force to the particle
    particle->addForce(gravity * particle->getMass());
}

ParticleDrag::ParticleDrag(real k1, real k2) : k1(k1), k2(k2) {}

void ParticleDrag::updateForce(Particle *particle, real duration) {
    Vector3 force;
    particle->getVelocity(&force);

    // Calculate the total drag coefficient
    real dragCoeff = force.magnitude();
    dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

    // Calculate the final force and apply it
    force.normalise();
    force *= -dragCoeff;
    particle->addForce(force);
}

ParticleSpring::ParticleSpring(Particle *other, real sc, real rl)
        : other(other), springConstant(sc), restLength(rl) {}

void ParticleSpring::updateForce(Particle *particle, real duration) {
    // Calculate the vector of the spring
    Vector3 force;
    particle->getPosition(&force);
    force -= other->getPosition();

    // Calculate the magnitude of the force
    real magnitude = force.magnitude();
    magnitude = real_abs(magnitude - restLength);
    magnitude *= springConstant;

    // Calculate the final force and apply it
    force.normalise();
    force *= -magnitude;
    particle->addForce(force);
}


ParticleBungee::ParticleBungee(Particle *other, real sc, real rl)
        : other(other), springConstant(sc), restLength(rl) {
}

void ParticleBungee::updateForce(Particle *particle, real duration) {
    // Calculate the vector of the spring
    Vector3 force;
    particle->getPosition(&force);
    force -= other->getPosition();

    // Check if the bungee is compressed
    real magnitude = force.magnitude();
    if (magnitude <= restLength) return;

    // Calculate the magnitude of the force
    magnitude = springConstant * (restLength - magnitude);

    // Calculate the final force and apply it
    force.normalise();
    force *= -magnitude;
    particle->addForce(force);
}


ParticleBuoyancy::ParticleBuoyancy(real maxDepth,
                                   real volume,
                                   real waterHeight,
                                   real liquidDensity)
        :
        maxDepth(maxDepth), volume(volume),
        waterHeight(waterHeight), liquidDensity(liquidDensity) {
}

void ParticleBuoyancy::updateForce(Particle *particle, real duration) {
    // Calculate the submersion depth
    real depth = particle->getPosition().y;

    // Check if we're out of the water
    if (depth >= waterHeight + maxDepth) return;
    Vector3 force(0, 0, 0);

    // Check if we're at maximum depth
    if (depth <= waterHeight - maxDepth) {
        force.y = liquidDensity * volume;
        particle->addForce(force);
        return;
    }

    // Otherwise we are partly submerged
    force.y = liquidDensity * volume *
              (depth - maxDepth - waterHeight) / (2 * maxDepth);
    particle->addForce(force);
}


ParticleAnchoredSpring::ParticleAnchoredSpring() {
}

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3 *anchor,
                                               real sc, real rl)
        : anchor(anchor), springConstant(sc), restLength(rl) {
}

void ParticleAnchoredSpring::init(Vector3 *anchor, real springConstant,
                                  real restLength) {
    ParticleAnchoredSpring::anchor = anchor;
    ParticleAnchoredSpring::springConstant = springConstant;
    ParticleAnchoredSpring::restLength = restLength;
}

