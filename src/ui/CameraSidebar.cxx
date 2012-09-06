
// Qt
#include <QLabel>
#include <QRadioButton>
#include <QSpacerItem>

// Spacegame
#include <CameraSidebar.h>

CameraSidebar::CameraSidebar(QWidget* parent)
   : QWidget(parent)
{
   /*
   QVBoxLayout* layout = new QVBoxLayout(this);

   viewAll_ = new QRadioButton(this);
   viewAll_->setText("View Entire Battle");
   viewAll_->setChecked(true);
   connect(viewAll_, SIGNAL(clicked()), this, SLOT(handleCameraSelectionChanged()));
   layout->addWidget(viewAll_);

   for (int teamId = 0; teamId < 2; teamId++)
   {
      QRadioButton* team = new QRadioButton(this);
      team->setText(QString("Team %1").arg(teamId));

      connect(team, SIGNAL(clicked()), this, SLOT(handleCameraSelectionChanged()));

      layout->addWidget(team);
   }

   layout->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

   setLayout(layout);
   */
   setMinimumWidth(200);
}

CameraSidebar::~CameraSidebar()
{
}

void CameraSidebar::handleCameraSelectionChanged()
{
   qDebug("Selection changed!");
}

