#ifndef ENDLESSBATTLE
#define ENDLESSBATTLE

// Qt
#include <QString>

// Spacegame
#include <Simulation.h>

/**
 ******************************************************************************
 *
 * \brief            EndlessBattle
 *
 ******************************************************************************
 */
class EndlessBattle : public Simulation
{

public:
   EndlessBattle();
   ~EndlessBattle();

public:
   virtual void runSimulationSpecifics();

   void addRandomShip();

private: // members
   bool ftl_;

};

#endif
