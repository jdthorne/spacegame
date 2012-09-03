
// Qt
#include <QHBoxLayout>

// Spacegame
#include <MainWindow.h>

MainWindow::MainWindow()
{
   widget_ = new QWidget(this);
   setCentralWidget(widget_);

   QHBoxLayout* layout = new QHBoxLayout(widget_);

   core_ = new OpenGlCore(this);
   core_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   layout->addWidget(core_);

   right_ = new CameraSidebar(this);
   right_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
   layout->addWidget(right_);

   widget_->setLayout(layout);
}

MainWindow::~MainWindow()
{
}

void MainWindow::loadSimulation(Simulation* simulation)
{
   core_->loadSimulation(simulation);
}
