#ifndef OBJECTTYPE
#define OBJECTTYPE

// Qt
#include <QString>

// Spacegame

/**
 ******************************************************************************
 *
 * \brief            ObjectType
 *
 ******************************************************************************
 */

#define typeOf(object) QString(typeid(*object).name())
#define typeIs(objectType, class) (objectType.endsWith(QString(#class)))

#define objectIs(object, Type) (dynamic_cast<Type*>(object) != NULL)

// Mwahahaha!
typedef QString ObjectType;

#define NullType QString("")

#endif
