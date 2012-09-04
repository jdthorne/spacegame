
// Qt
#include <QHBoxLayout>

// Spacegame
#include <MainWindow.h>

MainWindow::MainWindow()
{
   widget_ = new QWidget(this);
   setCentralWidget(widget_);
   layout()->setContentsMargins(0, 0, 0, 0);

   QHBoxLayout* layout = new QHBoxLayout(widget_);

   core_ = new OpenGlCore(this);
   core_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   layout->addWidget(core_);

   right_ = new CameraSidebar(this);
   right_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
   layout->addWidget(right_);

   widget_->setLayout(layout);
   layout->setContentsMargins(0, 0, 0, 0);
}

MainWindow::~MainWindow()
{
}

void MainWindow::loadSimulation(Simulation* simulation)
{
   core_->loadSimulation(simulation);
}
