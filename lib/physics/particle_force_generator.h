#pragma once

#include "vector3.h"
#include "particle.h"

namespace cyclone {
    class ParticleForceGenerator {
    public:
        virtual void updateForce(Particle *particle, real duration) = 0;
    };

/**
 * A force generator that applies a gravitational force. One instance
 * can be used for multiple particles.
 */
    class ParticleGravity : public ParticleForceGenerator {
        /** Holds the acceleration due to gravity. */
        Vector3 gravity;

    public:
        /** Creates the generator with the given acceleration. */
        ParticleGravity(const Vector3 &gravity);

        /** Applies the gravitational force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };

    /**
     * A force generator that applies a drag force. One instance
     * can be used for multiple particles.
     */
    class ParticleDrag : public ParticleForceGenerator {
        /** Holds the velocity drag coeffificent. */
        real k1;

        /** Holds the velocity squared drag coeffificent.
         * Drag that has a k2 value will grow faster at higher speeds. This is the case with
         * the aerodynamic drag that keeps a car from accelerating indefinitely. At slow speeds
         * the car feels almost no drag from the air, but for every doubling of the speed the drag
         * almost quadruples.
         * */
        real k2;

    public:
        /** Creates the generator with the given coefficients. */
        ParticleDrag(real k1, real k2);

        /** Applies the drag force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };

    /**
    * A force generator that applies a Spring force.
    */
    class ParticleSpring : public ParticleForceGenerator {
        /** The particle at the other end of the spring. */
        Particle *other;

        /** Holds the sprint constant. */
        real springConstant;

        /** Holds the rest length of the spring. */
        real restLength;

    public:

        /** Creates a new spring with the given parameters. */
        ParticleSpring(Particle *other,
                       real springConstant, real restLength);

        /** Applies the spring force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };

}

