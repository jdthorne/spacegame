#ifndef SHIPYARD
#define SHIPYARD

// Qt
#include <QString>

// Spacegame
#include <Simulation.h>

class Ship;

/**
 ******************************************************************************
 *
 * \brief            Shipyard
 *
 ******************************************************************************
 */
class Shipyard : public Simulation
{

public:
   Shipyard();
   ~Shipyard();

   virtual void runSimulationSpecifics();

private: // helpers

private: // members
   Ship* ship_;

};

#endif
