#include <QMainWindow>
#include <QLineEdit>
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

  void setLineEdit_01(const QString& str);
  void addDigit (const QString& digit);
  void function_execute();

public:
  explicit CalculatorMainWindow(QWidget* parent = nullptr):
    QMainWindow(parent) {}

  void setLineEdit_00(QLineEdit *newLineEdit);
  void setLineEdit_01(QLineEdit *newLineEdit);
  void add0();
  void add1();
  void add2();
  void add3();
  void add4();
  void add5();
  void add6();
  void add7();
  void add8();
  void add9();
  void backSpace();
  void clearEntry();
  void clear();
  void add();
  void sub();
  void multiply();
  void div();
  void sin ();
  void cos ();
  void tan ();
  void ln ();
  void perc ();
  void multiplicative_inverse ();
  void power_of_two ();
  void sqrt ();
  void point ();
  void sign ();
  void calculate();
};