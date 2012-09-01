#ifndef RACISTLIST
#define RACISTLIST

// Qt
#include <QString>
#include <QList>

// Spacegame

template <typename T>
class RacistList : public QList<T>
{

public:
   RacistList() : QList<T>() { };
   virtual ~RacistList() { };

public:
   template <typename X>
   QList<X> all() const
   {
      QList<X> results;
      foreach (T item, *this)
      {
         X itemAsX = dynamic_cast<X>(item);
         if (itemAsX != NULL)
         {
            results.append(itemAsX);
         }
      }
      return results;
   }

private: // helpers

private: // members

};

#define objectIs(object, Type) (dynamic_cast<Type*>(object) != NULL)

#endif
