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

   virtual void triggerEvent() = 0;

protected:
   virtual void runSimulationSpecifics() = 0;

protected: // members
   World* world_;

};

#endif
