
// System
#include <ctime>

// Qt

// Spacegame
#include <Profile.h>

QMap<const char*, long int> Profile::functionTimes_;

Profile::Profile(const char* description)
   : description_(description)
   , startTime_(clock())
{
}

Profile::~Profile()
{
   clock_t totalTime = (clock() - startTime_);

   functionTimes_[description_] += totalTime;
}

void Profile::printTimingInformation()
{
   qDebug("");
   qDebug("Timing Information:");
   foreach (const char* description, functionTimes_.keys())
   {
      double totalSeconds = functionTimes_[description] / (double)CLOCKS_PER_SEC;

      qDebug("  %12.5f %s", totalSeconds, qPrintable(description));
   }
   qDebug("");
   qDebug("");
}
