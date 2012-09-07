#ifndef SHIPYARDSIDEBAR
#define SHIPYARDSIDEBAR

// Qt
#include <QList>
#include <QWidget>
#include <QString>

// Spacegame

class QGridLayout;
class QPushButton;
class QWidget;

class Shipyard;
class OpenGlCore;

/**
 ******************************************************************************
 *
 * \brief            ShipyardSidebar
 *
 ******************************************************************************
 */
class ShipyardSidebar : public QWidget
{
   Q_OBJECT

public:
   ShipyardSidebar(QWidget* parent, Shipyard& shipyard, OpenGlCore& openGlCore);
   ~ShipyardSidebar();

public:

private slots:
   void handleInstallModuleClicked();

   void handleCheckableButtonClicked();

private: // helpers
   void addSimpleInstallLine(QWidget* base, QGridLayout* layout, QString name, const char* slot);

private: // members
   Shipyard& shipyard_;
   OpenGlCore& openGlCore_;

   QList<QPushButton*> checkableButtons_;
};

#endif
