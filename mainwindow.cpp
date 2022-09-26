#include "mainwindow.h"

QLineEdit *MainWindow::getLineEdit_00Ptr() {return lineEdit_00;}
QLineEdit *MainWindow::getLineEdit_01Ptr() {return lineEdit_01;}

void MainWindow::setupUi(CalculatorMainWindow *window) {
  QFont font;
  font.setPointSize(10);

  QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  centralWidget = new QWidget;
  gridLayout = new QGridLayout(centralWidget);
  gridLayout->setSpacing(2);
  gridLayout->setMargin(4);

  lineEdit_00 = new QLineEdit(centralWidget);
  lineEdit_00->setMinimumSize(QSize(0, 32));
  lineEdit_00->setFont(font);
  lineEdit_00->setAlignment(Qt::AlignRight);
  lineEdit_00->setReadOnly(true);
  lineEdit_00->setFrame(false);
  lineEdit_00->setStyleSheet("QLineEdit {"
                             "  color: rgb(100, 100, 100);"
                             "  padding: 0 2px;"
                             "  background: rgb(230, 230, 230);"
                             "  selection-background-color: darkgray;"
                             "}");

  lineEdit_01 = new QLineEdit(centralWidget);
  lineEdit_01->setMinimumSize(QSize(0, 30));
  font.setPointSize(20);
  lineEdit_01->setFont(font);
  lineEdit_01->setAlignment(Qt::AlignRight);
  lineEdit_01->setReadOnly(true);
  lineEdit_01->setFrame(false);
  lineEdit_01->setStyleSheet("QLineEdit {"
                             "  padding: 0 2px;"
                             "  background: rgb(230, 230, 230);"
                             "  selection-background-color: darkgray;"
                             "}");

  verticalSpacer_00 = new QSpacerItem(
    20, 24, QSizePolicy::Minimum, QSizePolicy::Fixed);

  font.setPointSize(13);

  const QString pushButtonsNames[buttonsAmount] =
    {"%", "CE", "C", "⌫",
     "sin", "cos", "tan", "ln",
     "⅟ₓ", "x²", "√x", "÷",
     "7", "8", "9", "×",
     "4", "5", "6", "—",
     "1", "2", "3", "+",
     "+/-", "0", ".", "="};

  gridLayout->addWidget(lineEdit_00, 0, 0, 1, 4);
  gridLayout->addWidget(lineEdit_01, 1, 0, 1, 4);
  gridLayout->addItem(verticalSpacer_00, 2, 0, 1, 4);

  for (int i = 0; i < buttonsAmount; i++) {
    pushButtons[i] = new QPushButton(centralWidget);
    pushButtons[i]->setSizePolicy(sizePolicy);
    pushButtons[i]->setFont(font);
    pushButtons[i]->setText(pushButtonsNames[i]);
    if ((i / 4 < 3 || i % 4 == 3) && i != 27) {
      pushButtons[i]->setStyleSheet("QPushButton {"
                                    "  min-width: 64px;"
                                    "  min-height: 48px;"
                                    "  color: rgb(80, 80, 80);"
                                    "  border: 0px;"
                                    "  background-color: rgb(239,239,239);"
                                    "}"
                                    "QPushButton:pressed {"
                                    "  background-color: rgb(185, 185, 185);"
                                    "}"
                                    "QPushButton:hover:!pressed {"
                                    "  background-color: rgb(205, 205, 205);"
                                    "}");
    } else if (i == 27) {
      pushButtons[i]->setStyleSheet("QPushButton {"
                                    "  min-width: 64px;"
                                    "  min-height: 48px;"
                                    "  border: 0px;"
                                    "  background-color: rgb(128, 190, 250);"
                                    "  }"
                                    "  QPushButton:pressed {"
                                    "  background-color: rgb(110, 135, 200);"
                                    "  }"
                                    "  QPushButton:hover:!pressed {"
                                    "  background-color: rgb(110, 155, 220);"
                                    "}");
    } else if (i != 24 && i != 26) {
      pushButtons[i]->setStyleSheet("QPushButton {"
                                    "  min-width: 64px;"
                                    "  min-height: 48px;"
                                    "  border: 0px;"
                                    "  font: bold;"
                                    "  background-color: rgb(248, 248, 248);"
                                    "  }"
                                    "  QPushButton:pressed {"
                                    "  background-color: rgb(185, 185, 185);"
                                    "  }"
                                    "  QPushButton:hover:!pressed {"
                                    "  background-color: rgb(205 ,205, 205);"
                                    "}");
    } else {
      pushButtons[i]->setStyleSheet("QPushButton {"
                                    "  min-width: 64px;"
                                    "  min-height: 48px;"
                                    "  border: 0px;"
                                    "  background-color: rgb(248, 248, 248);"
                                    "  }"
                                    "  QPushButton:pressed {"
                                    "  background-color: rgb(185, 185, 185);"
                                    "  }"
                                    "  QPushButton:hover:!pressed {"
                                    "  background-color: rgb(205 ,205, 205);"
                                    "}");

    }
    gridLayout->addWidget(pushButtons[i], i / 4 + 3, i % 4, 1, 1);
  }

  window->setCentralWidget(centralWidget);
  window->setMinimumWidth(320);
  window->setMinimumHeight(455);
  window->setWindowTitle("Calculator");
  window->setStyleSheet("background-color: rgb(230, 230, 230);");

  QObject::connect(pushButtons[0], &QPushButton::clicked,
                   window, &CalculatorMainWindow::perc);
  QObject::connect(pushButtons[1], &QPushButton::clicked,
                   window, &CalculatorMainWindow::clearEntry);
  QObject::connect(pushButtons[2], &QPushButton::clicked,
                   window, &CalculatorMainWindow::clear);
  QObject::connect(pushButtons[3], &QPushButton::clicked,
                   window, &CalculatorMainWindow::backSpace);
  QObject::connect(pushButtons[4], &QPushButton::clicked,
                   window, &CalculatorMainWindow::sin);
  QObject::connect(pushButtons[5], &QPushButton::clicked,
                   window, &CalculatorMainWindow::cos);
  QObject::connect(pushButtons[6], &QPushButton::clicked,
                   window, &CalculatorMainWindow::tan);
  QObject::connect(pushButtons[7], &QPushButton::clicked,
                   window, &CalculatorMainWindow::ln);
  QObject::connect(pushButtons[8], &QPushButton::clicked,
                   window, &CalculatorMainWindow::multiplicative_inverse);
  QObject::connect(pushButtons[9], &QPushButton::clicked,
                   window, &CalculatorMainWindow::power_of_two);
  QObject::connect(pushButtons[10], &QPushButton::clicked,
                   window, &CalculatorMainWindow::sqrt);
  QObject::connect(pushButtons[11], &QPushButton::clicked,
                   window, &CalculatorMainWindow::div);
  QObject::connect(pushButtons[12], &QPushButton::clicked,
                   window, &CalculatorMainWindow::add7);
  QObject::connect(pushButtons[13], &QPushButton::clicked,
                   window, &CalculatorMainWindow::add8);
  QObject::connect(pushButtons[14], &QPushButton::clicked,
                   window, &CalculatorMainWindow::add9);
  QObject::connect(pushButtons[15], &QPushButton::clicked,
                   window, &CalculatorMainWindow::multiply);
  QObject::connect(pushButtons[16], &QPushButton::clicked,
                   window, &CalculatorMainWindow::add4);
  QObject::connect(pushButtons[17], &QPushButton::clicked,
                   window, &CalculatorMainWindow::add5);
  QObject::connect(pushButtons[18], &QPushButton::clicked,
                   window, &CalculatorMainWindow::add6);
  QObject::connect(pushButtons[19], &QPushButton::clicked,
                   window, &CalculatorMainWindow::sub);
  QObject::connect(pushButtons[20], &QPushButton::clicked,
                   window, &CalculatorMainWindow::add1);
  QObject::connect(pushButtons[21], &QPushButton::clicked,
                   window, &CalculatorMainWindow::add2);
  QObject::connect(pushButtons[22], &QPushButton::clicked,
                   window, &CalculatorMainWindow::add3);
  QObject::connect(pushButtons[23], &QPushButton::clicked,
                   window, &CalculatorMainWindow::add);
  QObject::connect(pushButtons[24], &QPushButton::clicked,
                   window, &CalculatorMainWindow::sign);
  QObject::connect(pushButtons[25], &QPushButton::clicked,
                   window, &CalculatorMainWindow::add0);
  QObject::connect(pushButtons[26], &QPushButton::clicked,
                   window, &CalculatorMainWindow::point);
  QObject::connect(pushButtons[27], &QPushButton::clicked,
                   window, &CalculatorMainWindow::calculate);
}