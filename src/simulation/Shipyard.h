#ifndef SHIPYARD
#define SHIPYARD

// Qt
#include <QString>

// Spacegame
#include <Simulation.h>

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

};

#endif
