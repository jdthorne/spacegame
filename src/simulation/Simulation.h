#ifndef SIMULATION
#define SIMULATION

// Qt
#include <QString>

// Spacegame
class World;

/**
 ******************************************************************************
 *
 * \brief            Simulation
 *
 ******************************************************************************
 */
class Simulation
{

public:
   Simulation();
   virtual ~Simulation();

   World& world();
   void simulate();

protected:
   virtual void runSimulationSpecifics() = 0;

protected: // members
   World* world_;

};

#endif
