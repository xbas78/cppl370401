#include <QGridLayout>
#include <QPushButton>
#include "calculatormainwindow.h"

class MainWindow {
  static const unsigned int buttonsAmount = 28;

  QWidget *centralWidget;
  QGridLayout *gridLayout;
  QLineEdit *lineEdit_00;
  QLineEdit *lineEdit_01;
  QSpacerItem *verticalSpacer_00;
  QPushButton *pushButtons[buttonsAmount];

public:
  QLineEdit *getLineEdit_00Ptr();
  QLineEdit *getLineEdit_01Ptr();

  void setupUi(CalculatorMainWindow *window);
};