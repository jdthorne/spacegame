
// Qt

// Spacegame
#include <FlightComputer.h>

FlightComputer::FlightComputer(Ship& ship, const Vector position, const Quaternion orientation)
   : Module(ship, position, orientation)
{

}

FlightComputer::~FlightComputer()
{
}

