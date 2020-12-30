#pragma once
#include "precision.h"
#include "particle.h"
#include "particle_contact_recolver.h"
#include "particle_force_registry.h"

namespace cyclone {
    /**
 * Keeps track of a set of particles, and provides the means to
 * update them all.
 */
    class ParticleWorld
    {
        /**
        * Holds one particle in the linked list of particles.
        */
        struct ParticleRegistration
        {
            Particle *particle;
            ParticleRegistration *next;
        };

        /**
        * Holds the list of registrations.
        */
        ParticleRegistration* firstParticle;

/**
* Holds the force generators for the particles in this world.
*/
        ParticleForceRegistry registry;
/**
* Holds the resolver for contacts.
*/
        ParticleContactResolver resolver;
/**
* Holds one registered contact generator.
*/
        struct ContactGenRegistration
        {
            ParticleContactGenerator *gen;
            ContactGenRegistration *next;
        };
/**
* Holds the list of contact generators.
*/
        ContactGenRegistration *firstContactGen;

/**
* Holds the list of contacts.
*/
        ParticleContact *contacts;

/**
* Holds the maximum number of contacts allowed (i.e., the
* size of the contacts array).
*/
        unsigned maxContacts;

    public:
/**
* Creates a new particle simulator that can handle up to the
* given number of contacts per frame. You can also optionally
* give a number of contact-resolution iterations to use. If you
* don’t give a number of iterations, then twice the number of
* contacts will be used.
*/
        ParticleWorld(unsigned maxContacts, unsigned iterations=0);

/**
* Calls each of the registered contact generators to report
* their contacts. Returns the number of generated contacts.
*/
        unsigned generateContacts();
/**
* Integrates all the particles in this world forward in time
* by the given duration.
*/
        void integrate(real duration);

/**
* Processes all the physics for the particle world.
*/
        void runPhysics(real duration);

/**
* Initializes the world for a simulation frame. This clears
* the force accumulators for particles in the world. After
* calling this, the particles can have their forces for this
* frame added.
*/
        void startFrame();

        void addParticle(Particle *particle);

/**
 * Returns the force registry.
 */
        ParticleForceRegistry& getForceRegistry();

        void addContact(ParticleContactGenerator *gen);
    };
}


