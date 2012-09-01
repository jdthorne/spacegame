#ifndef BATTLEDEV
#define BATTLEDEV

// Qt
#include <QString>

// Spacegame
#include <Simulation.h>

/**
 ******************************************************************************
 *
 * \brief            BattleDev
 *
 ******************************************************************************
 */
class BattleDev : public Simulation
{

public:
   BattleDev();
   ~BattleDev();

public:
   virtual void triggerEvent();
   virtual void runSimulationSpecifics();

private: // helpers
   void addShip(int team);

private: // members

};

#endif
