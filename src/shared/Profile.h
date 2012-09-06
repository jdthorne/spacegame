#ifndef PROFILE
#define PROFILE

// Qt
#include <QMap>
#include <QString>

// Spacegame

/**
 ******************************************************************************
 *
 * \brief            Profile
 *
 ******************************************************************************
 */
class Profile
{

public:
   Profile(const char* description);
   ~Profile();

public:
   static void printTimingInformation();

private: // members
   static QMap<const char*, long int> functionTimes_;

   const char* description_;
   long int startTime_;

};

#define PROFILE_FUNCTION(description) Profile profiledFunction(description)

#endif
