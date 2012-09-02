#ifndef HUD
#define HUD

// Qt
#include <QString>
#include <QList>

// Spacegame
#include <Vector.h>

/**
 ******************************************************************************
 *
 * \brief            Hud
 *
 ******************************************************************************
 */
class Hud
{

public:
   Hud();
   ~Hud();

public:
   void clear();
   void display(const Vector vector);

   QList<Vector> vectors();

private: // helpers

private: // members
   QList<Vector> vectors_;

};

#endif
