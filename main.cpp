/*------------------------------------------------------------------------------
    Задача (37.4.) 1. Графический калькулятор
--------------------------------------------------------------------------------
  Что нужно сделать
  Реализуйте графическое приложение для основных операций с целыми числами:
сложение, вычитание, умножение, деление.
  В верхней части окна приложения расположено два текстовых поля для ввода двух
чисел. Чуть ниже — поле с выводом результата. Далее снизу — кнопки четырёх
основных действий: сложить, вычесть, умножить, разделить. Интерфейс должен быть
свободно масштабируемым в зависимости от размера самого окна.
  Если какая-то операция не может быть выполнена по причине некорректности
данных, в поле результата записывается текст «ERROR».

  Советы и рекомендации
  При желании вы можете усложнить себе задачу, реализовав работу калькулятора на
числах с плавающей точкой.

  Что оценивается
  Корректность работы программы и графического интерфейса.
------------------------------------------------------------------------------*/
#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <cmath>

class CalculatorMainWindow : public QMainWindow {

  enum Action {NONE, ADD, SUB, MUL, DIV};
  const QString symbols = " +-×÷";
  const int precise = 16;

  QLineEdit *lineEdit_00 = nullptr;
  QLineEdit *lineEdit_01 = nullptr;
  QString line_00;
  QString line_01 = "0";
  double num_00 = 0, num_01 = 0, result = 0;
  Action cur_action = NONE;
  Action prev_action = NONE;
  QString history_1;
  QString history_2;
  bool newNumberMode = false;
  bool calculated = false;
  bool function_executed = false;

  void setLineEdit_01(const QString& str) {
    if (str.contains("e")) {
      lineEdit_01->setText(str);
    } else {
      QString newStr;
      int dot = str.indexOf('.');
      if (dot == -1) dot = str.size();
      for (int i = 0; i < str.size(); i++) {
        int t = dot - 1 - i ;
        newStr.push_back(str[i]);
        if (i < dot - 1 && 0 == t % 3 && str[i] != '-') newStr.push_back(' ');
      }
      lineEdit_01->setText(newStr);
    }
  }

  void addDigit (const QString& digit) {
    if (line_01 == "0") line_01.clear();
    if (calculated && !newNumberMode) {
      line_00.clear();
      line_01.clear();
    }
    if (cur_action && !newNumberMode || function_executed) {
      line_01.clear();
      newNumberMode = true;
      function_executed = false;
    }
    if (
      line_01.size() < precise + line_01.contains(".") + line_01.contains("-")
      ) {
      line_01 += digit;
    }

    if (calculated) {
      if (cur_action) {
        num_00 = line_01.toDouble();
      } else {
        num_01 = line_01.toDouble();
      }
    } else {
      num_01 = line_01.toDouble();
    }

    lineEdit_00->setText(line_00);
    setLineEdit_01(line_01);
  }

  void function_execute() {
    if (calculated && newNumberMode) {
      calculated = false;
      newNumberMode = false;
      num_01 = num_00;
    }
    if (newNumberMode) {
      if (prev_action == ADD) result = num_00 + num_01;
      if (prev_action == SUB) result = num_00 - num_01;
      if (prev_action == MUL) result = num_00 * num_01;
      if (prev_action == DIV) result = num_00 / num_01;
      newNumberMode = false;
      num_00 = result;
    } else if (calculated) {
      num_00 = num_01 = result;
    } else {
      num_00 = result = num_01;
    }

    prev_action = cur_action;
    calculated = false;

    line_00 = QString::number(num_00, 'g', precise - 3) + " " +
              symbols[cur_action];
    line_01 = QString::number(result, 'g', precise - 3);

    lineEdit_00->setText(line_00);
    setLineEdit_01(line_01);
  }

public:
  explicit CalculatorMainWindow(QWidget* parent = nullptr):
  QMainWindow(parent) {}

  void setLineEdit_00(QLineEdit *newLineEdit) {
    lineEdit_00 = newLineEdit;
    lineEdit_00->setText(line_00);
  }

  void setLineEdit_01(QLineEdit *newLineEdit) {
    lineEdit_01 = newLineEdit;
    lineEdit_01->setText(line_01);
  }

  void add0() {
    addDigit("0");
  }

  void add1() {
    addDigit("1");
  }

  void add2() {
    addDigit("2");
  }

  void add3() {
    addDigit("3");
  }

  void add4() {
    addDigit("4");
  }

  void add5() {
    addDigit("5");
  }

  void add6() {
    addDigit("6");
  }

  void add7() {
    addDigit("7");
  }

  void add8() {
    addDigit("8");
  }

  void add9() {
    addDigit("9");
  }

  void backSpace() {
    if (calculated) {
      line_00.clear();
      lineEdit_00->setText(line_00);
    }
    if (cur_action && !newNumberMode) return;
    line_01.remove(line_01.size() - 1, 1);
    if (line_01.isEmpty() || line_01 == "-") line_01 = "0";
    num_01 = line_01.toDouble();
    function_executed = false;

    setLineEdit_01(line_01);
  }

  void clearEntry() {
    if (calculated) {
      line_00.clear();
      num_00 = 0;
      lineEdit_00->setText(line_00);
    } else {
      num_01 = 0;
    }
    function_executed = false;
    line_01 = "0";
    lineEdit_01->setText(line_01);
  }

  void clear() {
    num_00 = num_01 = result = 0;
    line_00.clear();
    line_01 = "0";

    cur_action = NONE;
    prev_action = NONE;
    newNumberMode = false;
    calculated = false;
    function_executed = false;

    lineEdit_00->setText(line_00);
    lineEdit_01->setText(line_01);
  }

  void add() {
    cur_action = ADD;
    function_execute();
  }

  void sub() {
    cur_action = SUB;
    function_execute();
  }

  void multiply() {
    cur_action = MUL;
    function_execute();
  }

  void div() {
    cur_action = DIV;
    function_execute();
  }

  void sin () {
    if (calculated && newNumberMode) {
      calculated = false;
      newNumberMode = false;
      num_01 = num_00;
    }

    if (calculated) {
      if (function_executed) {
        line_00 = " sin(" + line_00 + ")";
      } else {
        line_00 = " sin(" + QString::number(result, 'g', precise) + ")";
      }
      result = std::sin(result);
      num_00 = result;
      line_01 = QString::number(result, 'g', precise);
    } else {
      if (function_executed) {
        history_2 = "sin(" + history_2 + ")";
        line_00 = history_1 + " " + history_2;
      } else {
        if (cur_action) {
          history_1 = line_00;
        } else {
          history_1.clear();
        }
        history_2 = "sin(" + QString::number(num_01, 'g', precise) + ")";
        line_00 += " " + history_2;
      }
      num_01 = std::sin(num_01);
      line_01 = QString::number(num_01, 'g', precise);
    }

    function_executed = true;
    lineEdit_00->setText(line_00);
    setLineEdit_01(line_01);
  }

  void cos () {
    if (calculated && newNumberMode) {
      calculated = false;
      newNumberMode = false;
      num_01 = num_00;
    }

    if (calculated) {
      if (function_executed) {
        line_00 = " cos(" + line_00 + ")";
      } else {
        line_00 = " cos(" + QString::number(result, 'g', precise) + ")";
      }
      result = std::cos(result);
      num_00 = result;
      line_01 = QString::number(result, 'g', precise);
    } else {
      if (function_executed) {
        history_2 = "cos(" + history_2 + ")";
        line_00 = history_1 + " " + history_2;
      } else {
        if (cur_action) {
          history_1 = line_00;
        } else {
          history_1.clear();
        }
        history_2 = "cos(" + QString::number(num_01, 'g', precise) + ")";
        line_00 += " " + history_2;
      }
      num_01 = std::sin(num_01);
      line_01 = QString::number(num_01, 'g', precise);
    }

    function_executed = true;
    lineEdit_00->setText(line_00);
    setLineEdit_01(line_01);
  }

  void tan () {
    if (calculated && newNumberMode) {
      calculated = false;
      newNumberMode = false;
      num_01 = num_00;
    }

    if (calculated && (std::cos(result) != 0) ||
      (!calculated && (std::cos(num_01) != 0))) {
      if (calculated) {
        if (function_executed) {
          line_00 = " tan(" + line_00 + ")";
        } else {
          line_00 = " tan(" + QString::number(result, 'g', precise) + ")";
        }
        result = std::tan(result);
        num_00 = result;
        line_01 = QString::number(result, 'g', precise);
      } else {
        if (function_executed) {
          history_2 = "tan(" + history_2 + ")";
          line_00 = history_1 + " " + history_2;
        } else {
          if (cur_action) {
            history_1 = line_00;
          } else {
            history_1.clear();
          }
          history_2 = "tan(" + QString::number(num_01, 'g', precise) + ")";
          line_00 += " " + history_2;
        }
        num_01 = std::tan(num_01);
        line_01 = QString::number(num_01,'g', precise);
      }
    } else {
      line_00 = "888";
      line_01 = "Invalid input";
      lineEdit_00->setText(line_00);
      lineEdit_01->setText(line_01);
      return;
    }

    function_executed = true;
    lineEdit_00->setText(line_00);
    setLineEdit_01(line_01);
  }

  void ln () {
    if (calculated && newNumberMode) {
      calculated = false;
      newNumberMode = false;
      num_01 = num_00;
    }

    if ((result > 0 && calculated) || (!calculated && num_01 > 0)) {
      if (calculated) {
        if (function_executed) {
          line_00 = " ln(" + line_00 + ")";
        } else {
          line_00 = " ln(" + QString::number(result, 'g', precise) + ")";
        }
        result = std::log(result);
        num_00 = result;
        line_01 = QString::number(result, 'g', precise);
      } else {
        if (function_executed) {
          history_2 = "ln(" + history_2 + ")";
          line_00 = history_1 + " " + history_2;
        } else {
          if (cur_action) {
            history_1 = line_00;
          } else {
            history_1.clear();
          }
          history_2 = "ln(" + QString::number(num_01, 'g', precise) + ")";
          line_00 += " " + history_2;
        }
        num_01 = std::log(num_01);
        line_01 = QString::number(num_01,'g', precise);
      }
    } else {
      line_00 = "<= 0";
      line_01 = "Invalid input";
      lineEdit_00->setText(line_00);
      lineEdit_01->setText(line_01);
      return;
    }

    function_executed = true;
    lineEdit_00->setText(line_00);
    setLineEdit_01(line_01);
  }

  void perc () {
    if (calculated && newNumberMode) {
      calculated = false;
      newNumberMode = false;
      num_01 = num_00;
    }

    if (calculated) {
      if (function_executed) {
      } else {
        line_00 = QString::number(result, 'g', precise);
      }
      result = result * result / 100;
      num_00 = result;
      line_01 = QString::number(result, 'g', precise);
    } else {
      num_01 = num_00 / 100 * num_01;
      line_01 = QString::number(num_01,'g', precise);
      if (function_executed) {
        line_00 = history_1 + " " + history_2;
      } else {
        if (cur_action) {
          history_1 = line_00;
        } else {
          history_1.clear();
        }
        history_2 = QString::number(num_01, 'g', precise);
        line_00 += " " + history_2;
      }
    }

    function_executed = true;
    lineEdit_00->setText(line_00);
    setLineEdit_01(line_01);
  }

  void multiplicative_inverse () {
    if (calculated && newNumberMode) {
      calculated = false;
      newNumberMode = false;
      num_01 = num_00;
    }

    if ((result != 0 && calculated) || (!calculated && num_01 != 0)) {
      if (calculated) {
        if (function_executed) {
          line_00 = " 1/(" + line_00 + ")";
        } else {
          line_00 = " 1/(" + QString::number(result, 'g', precise) + ")";
        }
        result = 1 / result;
        num_00 = result;
        line_01 = QString::number(result, 'g', precise);
      } else {
        if (function_executed) {
          history_2 = "1/(" + history_2 + ")";
          line_00 = history_1 + " " + history_2;
        } else {
          if (cur_action) {
            history_1 = line_00;
          } else {
            history_1.clear();
          }
          history_2 = "1/(" + QString::number(num_01, 'g', precise) + ")";
          line_00 += " " + history_2;
        }
        num_01 = 1 / num_01;
        line_01 = QString::number(num_01, 'g', precise);
      }
    } else {
      line_00 = "1/(0)";
      line_01 = "Cannot divide by zero";
    }

    function_executed = true;
    lineEdit_00->setText(line_00);
    setLineEdit_01(line_01);
  }

  void power_of_two () {
    if (calculated && newNumberMode) {
      calculated = false;
      newNumberMode = false;
      num_01 = num_00;
    }

    if (calculated) {
      if (function_executed) {
        line_00 = " (" + line_00 + ")^2";
      } else {
        line_00 = " (" + QString::number(result, 'g', precise) + ")^2";
      }
      result = result * result;
      num_00 = result;
      line_01 = QString::number(result, 'g', precise);
    } else {
      if (function_executed) {
        history_2 = "(" + history_2 + ")^2";
        line_00 = history_1 + " " + history_2;
      } else {
        if (cur_action) {
          history_1 = line_00;
        } else {
          history_1.clear();
        }
        history_2 = "(" + QString::number(num_01, 'g', precise) + ")^2";
        line_00 += " " + history_2;
      }
      num_01 = num_01 * num_01;
      line_01 = QString::number(num_01, 'g', precise);
    }

    function_executed = true;
    lineEdit_00->setText(line_00);
    setLineEdit_01(line_01);
  }

  void sqrt () {
    if (calculated && newNumberMode) {
      calculated = false;
      newNumberMode = false;
      num_01 = num_00;
    }

    if ((result >= 0 && calculated) || (!calculated && num_01 >= 0)) {
      if (calculated) {
        if (function_executed) {
          line_00 = " sqrt(" + line_00 + ")";
        } else {
          line_00 = " sqrt(" + QString::number(result, 'g', precise) + ")";
        }
        result = std::sqrt(result);
        num_00 = result;
        line_01 = QString::number(result, 'g', precise);
      } else {
        if (function_executed) {
          history_2 = "sqrt(" + history_2 + ")";
          line_00 = history_1 + " " + history_2;
        } else {
          if (cur_action) {
            history_1 = line_00;
          } else {
            history_1.clear();
          }
          history_2 = "sqrt(" + QString::number(num_01, 'g', precise) + ")";
          line_00 += " " + history_2;
        }
        num_01 = std::sqrt(num_01);
        line_01 = QString::number(num_01, 'g', precise);
      }
    } else {
      line_00 = "< 0";
      line_01 = "Invalid input";
      lineEdit_00->setText(line_00);
      lineEdit_01->setText(line_01);
      return;
    }

    function_executed = true;
    lineEdit_00->setText(line_00);
    setLineEdit_01(line_01);
  }

  void point () {
    if (line_01.contains(".")) return;
    if (cur_action && !newNumberMode) {
      clearEntry();
      newNumberMode = true;
    }
    line_01 += ".";
    setLineEdit_01(line_01);
  }

  void sign () {
    if (calculated) {
      result *= -1;
      num_00 = result;
      line_00 = QString::number(num_00, 'g', precise - 3) + " =";
      lineEdit_00->setText(line_00);
      line_01 = QString::number(result, 'g', precise);
    } else {
      num_01 *= -1;
      line_01 = QString::number(num_01, 'g', precise);
    }
    setLineEdit_01(line_01);
  }

  void calculate() {
    if (cur_action == ADD) result = num_00 + num_01;
    if (cur_action == SUB) result = num_00 - num_01;
    if (cur_action == MUL) result = num_00 * num_01;
    if (cur_action == DIV) result = num_00 / num_01;
    if (cur_action == NONE) {
      result = num_01;
      num_00 = num_01;
      line_00 = QString::number(num_00, 'g', precise - 3) + " =";
    } else {
      line_00 = QString::number(num_00, 'g', precise - 3) + " " +
                symbols[cur_action] + " " +
                QString::number(num_01, 'g', precise - 3) + " =";
    }
    line_01 = QString::number(result, 'g', precise - 3);

    num_00 = result;

    calculated = true;
    prev_action = cur_action;
    newNumberMode = false;
    function_executed = false;

    lineEdit_00->setText(line_00);
    setLineEdit_01(line_01);
  }
};

class MainWindow {
  static const unsigned int buttonsAmount = 28;

  QWidget *centralWidget;
  QGridLayout *gridLayout;
  QLineEdit *lineEdit_00;
  QLineEdit *lineEdit_01;
  QSpacerItem *verticalSpacer_00;
  QPushButton *pushButtons[buttonsAmount];

public:
  QLineEdit *getLineEdit_00Ptr() {return lineEdit_00;}
  QLineEdit *getLineEdit_01Ptr() {return lineEdit_01;}

  void setupUi(CalculatorMainWindow *window) {
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
      {"%",   "CE",  "C",   "⌫",
       "sin", "cos", "tan", "ln",
       "⅟ₓ",   "x²",  "√x",  "÷",
       "7",   "8",   "9",   "×",
       "4",   "5",   "6",   "—",
       "1",   "2",   "3",   "+",
       "+/-", "0",   ".",   "="};

    gridLayout->addWidget(lineEdit_00, 0, 0, 1, 4);
    gridLayout->addWidget(lineEdit_01, 1, 0, 1, 4);
    gridLayout->addItem(verticalSpacer_00, 2, 0, 1, 4);

    for (int i = 0 ; i < buttonsAmount; i++) {
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
};

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  CalculatorMainWindow window;
  MainWindow calculator{};
  calculator.setupUi(&window);
  window.setLineEdit_00(calculator.getLineEdit_00Ptr());
  window.setLineEdit_01(calculator.getLineEdit_01Ptr());
  window.show();
  return QApplication::exec();
}