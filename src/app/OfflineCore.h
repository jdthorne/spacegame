#ifndef OFFLINECORE
#define OFFLINECORE

// Qt
#include <QString>

// Spacegame

class Simulation;

/**
 ******************************************************************************
 *
 * \brief            OfflineCore
 *
 ******************************************************************************
 */
class OfflineCore
{

public:
   OfflineCore();
   ~OfflineCore();

public:
   static bool isSimMode(int argc, char** argv);
   static void runSimulation(Simulation* simulation);

private: // helpers

private: // members

};

#endif
