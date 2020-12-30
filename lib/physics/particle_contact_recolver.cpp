#include "particle_contact_recolver.h"


using namespace cyclone;

void ParticleContact::resolve(real duration) {
    resolveVelocity(duration);
    resolveInterpenetration(duration);
}

real ParticleContact::calculateSeparatingVelocity() const {
    Vector3 relativeVelocity = particle[0]->getVelocity();
    if (particle[1]) {
        relativeVelocity -= particle[1]->getVelocity();
    }

    return relativeVelocity * contactNormal;
}

void ParticleContact::resolveVelocity(real duration) {
    // Find the velocity in the direction of the contact
    real separatingVelocity = calculateSeparatingVelocity();
    if (separatingVelocity > 0) {
        // contact is either separating or stationary - there's no impulse required
        return;
    }

    // Calculate the new separating velocity
    real newSepVelocity = -separatingVelocity * restitution;

    // Check the velocity build-up due to acceleration only.
    Vector3 accCausedVelocity = particle[0]->getAcceleration();
    if (particle[1]) accCausedVelocity -= particle[1]->getAcceleration();
    real accCausedSepVelocity = accCausedVelocity * contactNormal * duration;

    // If we’ve got a closing velocity due to acceleration build-up,
    // remove it from the new separating velocity.
    if (accCausedSepVelocity < 0) {
        newSepVelocity += restitution * accCausedSepVelocity;
        // Make sure we haven’t removed more than was
        // there to remove.
        if (newSepVelocity < 0) newSepVelocity = 0;
    }

    real deltaVelocity = newSepVelocity - separatingVelocity;

    // We apply the change in velocity to each object in proportion to
    // its inverse mass (i.e., those with lower inverse mass [higher
    // actual mass] get less change in velocity).

    real totalInverseMass = particle[0]->getInverseMass();
    if (particle[1]) {
        totalInverseMass += particle[1]->getInverseMass();
    }

    // If all particles have infinite mass, then impulses have no effect.
    if (totalInverseMass <= 0) return;

    // Calculate the impulse to apply.
    real impulse = deltaVelocity / totalInverseMass;

    // Find the amount of impulse per unit of inverse mass.
    Vector3 impulsePerIMass = contactNormal * impulse;

    // Apply impulses: they are applied in the direction of the contact,
    // and are proportional to the inverse mass.
    particle[0]->setVelocity(
            particle[0]->getVelocity() + impulsePerIMass * particle[0]->getInverseMass()
    );
    if (particle[1]) {
        // Particle 1 goes in the opposite direction.
        particle[1]->setVelocity(
                particle[1]->getVelocity() + impulsePerIMass * -particle[1]->getInverseMass()
        );
    }
}

void ParticleContact::resolveInterpenetration(real duration) {
    // If we don't have any penetration skip this step.
    if (penetration <= 0) {
        return;
    }

    // The movement of each object is based on its inverse mass, so
    // total that.
    real totalInverseMass = particle[0]->getInverseMass();
    if (particle[1]) {
        totalInverseMass += particle[1]->getInverseMass();
    }

    // If all particles have infinite mass, then we do nothing.
    if (totalInverseMass <= 0) return;

    // Find the amount of penetration resolution per unit of inverse mass.
    Vector3 movePerIMass = contactNormal * (-penetration / totalInverseMass);

    // Apply the penetration resolution.
    particle[0]->setPosition(
            particle[0]->getPosition() + movePerIMass * particle[0]->getInverseMass()
    );
    if (particle[1]) {
        particle[1]->setPosition(
                particle[1]->getPosition() + movePerIMass * particle[1]->getInverseMass()
        );
    }
}

void ParticleContactResolver::resolveContacts(ParticleContact *contactArray, unsigned int numContacts, real duration) {
    iterationsUsed = 0;

    while (iterationsUsed < iterations) {
        // Find the contact with the largest closing velocity;
        real max = 0;
        unsigned maxIndex = numContacts;

        for (unsigned i = 0; i < numContacts; i++) {
            real sepVel = contactArray[i].calculateSeparatingVelocity();
            if (sepVel < max) {
                max = sepVel;
                maxIndex = i;
            }
        }

        // Resolve this contact.
        contactArray[maxIndex].resolve(duration);
        iterationsUsed++;
    }
}

void ParticleContactResolver::setIterations(unsigned int iterations) {
    this->iterations = iterations;
}

ParticleContactResolver::ParticleContactResolver(unsigned int iterations) {
    this->iterations = iterations;
}