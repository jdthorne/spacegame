
// Qt

// Spacegame
#include <FlightComputer.h>

FlightComputer::FlightComputer(Ship& ship, const Vector position, const Quaternion orientation)
   : Structure(ship, position, orientation)
{

}

FlightComputer::~FlightComputer()
{
}

