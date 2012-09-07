
// Qt
#include <QHBoxLayout>

// Spacegame
#include <MainWindow.h>
#include <ObjectType.h>

#include <Shipyard.h>
#include <ShipyardSidebar.h>

MainWindow::MainWindow()
{
   widget_ = new QWidget(this);
   setCentralWidget(widget_);
   layout()->setContentsMargins(0, 0, 0, 0);

   QHBoxLayout* layout = new QHBoxLayout(widget_);

   core_ = new OpenGlCore(this);
   core_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   layout->addWidget(core_);

   rightSidebar_ = new QWidget(this);
   rightSidebar_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
   rightSidebar_->setMinimumSize(0, 0);
   rightSidebar_->setMaximumSize(250, 999999);
   rightSidebarLayout_ = new QVBoxLayout(rightSidebar_);

   layout->addWidget(rightSidebar_);

   widget_->setLayout(layout);
   layout->setMargin(0);
   layout->setSpacing(0);
   layout->setContentsMargins(0, 0, 0, 0);
}

MainWindow::~MainWindow()
{
}

void MainWindow::loadSimulation(Simulation* simulation)
{
   foreach(QObject* sidebarItem, rightSidebar_->children())
   {
      if (objectIs(sidebarItem, QWidget))
      {
         delete sidebarItem;
      }
   }

   core_->loadSimulation(simulation);

   if (objectIs(simulation, Shipyard))
   {
      ShipyardSidebar* sidebar = new ShipyardSidebar(rightSidebar_, 
                                                     *(dynamic_cast<Shipyard*>(simulation)), 
                                                     *core_);
      rightSidebarLayout_->addWidget(sidebar);
   }
}
