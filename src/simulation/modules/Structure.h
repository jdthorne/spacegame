#ifndef STRUCTURE
#define STRUCTURE

// Qt
#include <QString>

// Spacegame
#include <Module.h>

/**
 ******************************************************************************
 *
 * \brief            Structure
 *
 ******************************************************************************
 */
class Structure : public Module
{

public:
   Structure(Ship& ship, const Vector position, const Quaternion orientation);
   virtual ~Structure();

public:

private: // helpers

private: // members

};

#endif
