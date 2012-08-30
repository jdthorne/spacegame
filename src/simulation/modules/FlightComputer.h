#ifndef FLIGHTCOMPUTER
#define FLIGHTCOMPUTER

// Qt
#include <QString>

// Spacegame
#include <Module.h>

/**
 ******************************************************************************
 *
 * \brief            FlightComputer
 *
 ******************************************************************************
 */
class FlightComputer : public Module
{

public:
   FlightComputer(Ship& ship, const Vector position, const Quaternion orientation);
   ~FlightComputer();

public:

private: // helpers

private: // members

};

#endif
