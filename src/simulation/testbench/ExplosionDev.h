#ifndef EXPLOSIONDEV
#define EXPLOSIONDEV

// Qt
#include <QString>

// Spacegame
#include <Simulation.h>

/**
 ******************************************************************************
 *
 * \brief            ExplosionDev
 *
 ******************************************************************************
 */
class ExplosionDev : public Simulation
{

public:
   ExplosionDev();
   ~ExplosionDev();

public:
   virtual void triggerEvent();
   virtual void runSimulationSpecifics();

private: // helpers

private: // members

};

#endif
