#ifndef SHIPCONTROL
#define SHIPCONTROL

// Qt
#include <QString>
#include <QList>

// Spacegame
#include <Vector.h>
#include <Quaternion.h>

class Ship;

/**
 ******************************************************************************
 *
 * \brief            Helper Classes
 *
 ******************************************************************************
 */
struct SensorResult
{
   Vector vector_;
   Vector velocity_;
   bool friendly_;
};

/**
 ******************************************************************************
 *
 * \brief            ShipControl
 *
 ******************************************************************************
 */
class ShipControl
{

public:
   ShipControl(Ship& ship);
   ~ShipControl();

public: // Debug
   void displayOnHud(const Vector vector);

   // Physics
   const Vector angularVelocity();
   const Vector angularMomentum();
   const Vector inertialTensor();
   void setGyroPowerLevel(Vector power);

   double maximumTorque();

   // Sensors
   QList<SensorResult> scan();

   // Weapons
   void fireWeapons();

private: // helpers

private: // members
   Ship& ship_;
};

#endif
