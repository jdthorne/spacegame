#ifndef CAMERASIDEBAR
#define CAMERASIDEBAR

// Qt
#include <QWidget>
#include <QVBoxLayout>
#include <QMap>
#include <QRadioButton>
#include <QString>

// Spacegame

/**
 ******************************************************************************
 *
 * \brief            CameraSidebar
 *
 ******************************************************************************
 */
class CameraSidebar : public QWidget
{
   Q_OBJECT
   
public:
   CameraSidebar(QWidget* parent);
   virtual ~CameraSidebar();

public:

private slots:
   void handleCameraSelectionChanged();

private: // helpers


private: // members
   QRadioButton* viewAll_;
   QMap<int, QRadioButton*> teams_;
   QMap<int, QRadioButton*> ships_;

};

#endif
