#ifndef FLIGHTCOMPUTER
#define FLIGHTCOMPUTER

// Qt
#include <QString>

// Spacegame
#include <Structure.h>

/**
 ******************************************************************************
 *
 * \brief            FlightComputer
 *
 ******************************************************************************
 */
class FlightComputer : public Structure
{

public:
   FlightComputer(Ship& ship, const Vector position, const Quaternion orientation);
   ~FlightComputer();

public:

private: // helpers

private: // members

};

#endif
