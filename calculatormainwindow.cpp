#include "calculatormainwindow.h"

void CalculatorMainWindow::setLineEdit_01(const QString& str) {
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

void CalculatorMainWindow::addDigit (const QString& digit) {
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

void CalculatorMainWindow::function_execute() {
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

void CalculatorMainWindow::setLineEdit_00(QLineEdit *newLineEdit) {
  lineEdit_00 = newLineEdit;
  lineEdit_00->setText(line_00);
}

void CalculatorMainWindow::setLineEdit_01(QLineEdit *newLineEdit) {
  lineEdit_01 = newLineEdit;
  lineEdit_01->setText(line_01);
}

void CalculatorMainWindow::add0() {
  addDigit("0");
}

void CalculatorMainWindow::add1() {
  addDigit("1");
}

void CalculatorMainWindow::add2() {
  addDigit("2");
}

void CalculatorMainWindow::add3() {
  addDigit("3");
}

void CalculatorMainWindow::add4() {
  addDigit("4");
}

void CalculatorMainWindow::add5() {
  addDigit("5");
}

void CalculatorMainWindow::add6() {
  addDigit("6");
}

void CalculatorMainWindow::add7() {
  addDigit("7");
}

void CalculatorMainWindow::add8() {
  addDigit("8");
}

void CalculatorMainWindow::add9() {
  addDigit("9");
}

void CalculatorMainWindow::backSpace() {
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

void CalculatorMainWindow::clearEntry() {
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

void CalculatorMainWindow::clear() {
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

void CalculatorMainWindow::add() {
  cur_action = ADD;
  function_execute();
}

void CalculatorMainWindow::sub() {
  cur_action = SUB;
  function_execute();
}

void CalculatorMainWindow::multiply() {
  cur_action = MUL;
  function_execute();
}

void CalculatorMainWindow::div() {
  cur_action = DIV;
  function_execute();
}

void CalculatorMainWindow::sin () {
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

void CalculatorMainWindow::cos () {
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

void CalculatorMainWindow::tan () {
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

void CalculatorMainWindow::ln () {
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

void CalculatorMainWindow::perc () {
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

void CalculatorMainWindow::multiplicative_inverse () {
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

void CalculatorMainWindow::power_of_two () {
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

void CalculatorMainWindow::sqrt () {
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

void CalculatorMainWindow::point () {
  if (line_01.contains(".")) return;
  if (cur_action && !newNumberMode) {
    clearEntry();
    newNumberMode = true;
  }
  line_01 += ".";
  setLineEdit_01(line_01);
}

void CalculatorMainWindow::sign () {
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

void CalculatorMainWindow::calculate() {
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