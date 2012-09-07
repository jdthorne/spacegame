
// Qt
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>

// Spacegame
#include <ShipyardSidebar.h>
#include <Shipyard.h>
#include <OpenGlCore.h>

ShipyardSidebar::ShipyardSidebar(QWidget* parent, Shipyard& shipyard, OpenGlCore& openGlCore)
   : QWidget(parent)
   , shipyard_(shipyard)
   , openGlCore_(openGlCore)
{
   QVBoxLayout* layout = new QVBoxLayout(this);

   QGroupBox* modules = new QGroupBox(this);
   modules->setTitle("Modules");

   QGridLayout* modulesLayout = new QGridLayout(modules);
   addSimpleInstallLine(modules, modulesLayout, "Structure", SLOT(handleInstallModuleClicked()));
   addSimpleInstallLine(modules, modulesLayout, "Engine Pod", SLOT(handleInstallModuleClicked()));
   addSimpleInstallLine(modules, modulesLayout, "Gyroscope", SLOT(handleInstallModuleClicked()));
   addSimpleInstallLine(modules, modulesLayout, "Torpedo", SLOT(handleInstallModuleClicked()));
   modulesLayout->setSpacing(4);
   modulesLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, 
                                                  QSizePolicy::Minimum), 
                          modulesLayout->rowCount(), 0);
   layout->addWidget(modules);

   layout->setMargin(0);
   layout->setSpacing(0);
   layout->setContentsMargins(0, 0, 0, 0);

   layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
   setLayout(layout);
   setMinimumWidth(200);
}

ShipyardSidebar::~ShipyardSidebar()
{
}

void ShipyardSidebar::addSimpleInstallLine(QWidget* base, QGridLayout* layout, QString name, const char* slot)
{
   int row = layout->rowCount();

   QLabel* label = new QLabel(base);
   label->setText(name);
   layout->addWidget(label, row, 0);

   QPushButton* button = new QPushButton(base);
   button->setText("Add");
   button->setCheckable(true);
   layout->addWidget(button, row, 1);  

   connect(button, SIGNAL(clicked()), this, SLOT(handleCheckableButtonClicked()));
   connect(button, SIGNAL(clicked()), this, slot);

   checkableButtons_.append(button); 
}

void ShipyardSidebar::handleInstallModuleClicked()
{
   openGlCore_.renderConnectionPoints(true);
}

void ShipyardSidebar::handleCheckableButtonClicked()
{
   foreach(QPushButton* button, checkableButtons_)
   {
      if (button != QObject::sender())
      {
         button->setChecked(false);
      }
   }
}

