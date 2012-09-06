#ifndef RACISTLIST
#define RACISTLIST

// Qt
#include <QString>
#include <QList>

// Spacegame
#include <Profile.h>

template <typename T>
class RacistList : public QList<T>
{

public:
   RacistList() : QList<T>() { };
   virtual ~RacistList() { };

public:

   /**
    ******************************************************************************
    *
    * \brief            List Management
    *
    ******************************************************************************
    */
   void append(const T& value)
   {
      segregatedMembers_[typeid(*value).name()].append(value);
      QList<T>::append(value);
   }

   void append(const QList<T>& value)
   {
      foreach(T item, value)
      {
         append(item);
      }
   }

   void removeAll(const T& value)
   {
      segregatedMembers_[typeid(*value).name()].removeAll(value);
      QList<T>::removeAll(value);      
   }

   void insert(int i, const T& value)
   {
      qWarning("insert() is not defined for a RacistList");
   }

   void prepend(const T& value)
   {
      segregatedMembers_[typeid(*value).name()].prepend(value);
      QList<T>::prepend(value);
   }

   void removeAt(int i)
   {
      qWarning("removeAt() is not defined for a RacistList");
   }

   /**
    ******************************************************************************
    *
    * \brief            Using the racism
    *
    ******************************************************************************
    */

   template <typename X>
   QList<X*> all() const
   {
      PROFILE_FUNCTION("RacistList::all()");

      const char* type = typeid(X).name();

      QList<X*> results;
      foreach (T item, segregatedMembers_[type])
      {
         X* itemAsX = reinterpret_cast<X*>(item);
         results.append(itemAsX);
      }

      return results;
   }

private: // helpers

private: // members
   QMap<const char*, QList<T> > segregatedMembers_;

};

#define objectIs(object, Type) (dynamic_cast<Type*>(object) != NULL)

#endif
