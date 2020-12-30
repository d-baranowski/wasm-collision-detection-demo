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

    /**
     * A force generator that applies a spring force only
     * when extended.
     */
    class ParticleBungee : public ParticleForceGenerator {
        /** The particle at the other end of the spring. */
        Particle *other;

        /** Holds the sprint constant. */
        real springConstant;

        /**
         * Holds the length of the bungee at the point it begins to
         * generator a force.
         */
        real restLength;

    public:

        /** Creates a new bungee with the given parameters. */
        ParticleBungee(Particle *other,
                       real springConstant, real restLength);

        /** Applies the spring force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };

    /**
     * A force generator that applies a buoyancy force for a plane of
     * liquid parrallel to XZ plane.
     */
    class ParticleBuoyancy : public ParticleForceGenerator {
        /**
         * The maximum submersion depth of the object before
         * it generates its maximum boyancy force.
         */
        real maxDepth;

        /**
         * The volume of the object.
         */
        real volume;

        /**
         * The height of the water plane above y=0. The plane will be
         * parrallel to the XZ plane.
         */
        real waterHeight;

        /**
         * The density of the liquid. Pure water has a density of
         * 1000kg per cubic meter.
         */
        real liquidDensity;

    public:

        /** Creates a new buoyancy force with the given parameters. */
        ParticleBuoyancy(real maxDepth, real volume, real waterHeight,
                         real liquidDensity = 1000.0f);

        /** Applies the buoyancy force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };

    /**
 * A force generator that applies a Spring force, where
 * one end is attached to a fixed point in space.
 */
    class ParticleAnchoredSpring : public ParticleForceGenerator {
    protected:
        /** The location of the anchored end of the spring. */
        Vector3 *anchor;

        /** Holds the sprint constant. */
        real springConstant;

        /** Holds the rest length of the spring. */
        real restLength;

    public:
        ParticleAnchoredSpring();

        /** Creates a new spring with the given parameters. */
        ParticleAnchoredSpring(Vector3 *anchor,
                               real springConstant,
                               real restLength);

        /** Retrieve the anchor point. */
        const Vector3 *getAnchor() const { return anchor; }

        /** Set the spring's properties. */
        void init(Vector3 *anchor,
                  real springConstant,
                  real restLength);

        /** Applies the spring force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };

    /**
    * A force generator that applies a bungee force, where
    * one end is attached to a fixed point in space.
    */
    class ParticleAnchoredBungee : public ParticleAnchoredSpring {
    public:
        /** Applies the spring force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };

    /**
     * A force generator that fakes a stiff spring force, and where
     * one end is attached to a fixed point in space.
     */
    class ParticleFakeSpring : public ParticleForceGenerator {
        /** The location of the anchored end of the spring. */
        Vector3 *anchor;

        /** Holds the sprint constant. */
        real springConstant;

        /** Holds the damping on the oscillation of the spring. */
        real damping;

    public:

        /** Creates a new spring with the given parameters. */
        ParticleFakeSpring(Vector3 *anchor, real springConstant,
                           real damping);

        /** Applies the spring force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };
}

