#include <iostream>
#include <string>
#include <cmath>
#include <Windows.h>
#include "stack.h"
#include <iomanip> // для форматирования вывода

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

double applyOp(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) throw std::runtime_error("Division by zero!");
        return a / b;
    case '^': return std::pow(a, b);
    default: throw std::runtime_error("Invalid operator!");
    }
}

bool isFunction(const std::string& token) {
    return token == "sin" || token == "cos";
}

double applyFunc(const std::string& func, double value) {
    if (func == "sin") return std::sin(value);
    if (func == "cos") return std::cos(value);
    throw std::runtime_error("Unknown function: " + func);
}

double evaluate(const std::string& expr) {
    stack<double> values;
    stack<char> ops;
    stack<std::string> functions;
    std::string rpn;

    for (size_t i = 0; i < expr.length(); i++) {
        if (isspace(expr[i])) continue;

        if (isdigit(expr[i])) {
            double val = 0;
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                if (expr[i] == '.') {
                    double fraction = 1;
                    i++;
                    while (i < expr.length() && isdigit(expr[i])) {
                        fraction /= 10;
                        val += (expr[i] - '0') * fraction;
                        i++;
                    }
                    break;
                }
                val = val * 10 + (expr[i] - '0');
                i++;
            }
            values.push(val);

            // Округляем перед добавлением в rpn
            int intVal = static_cast<int>(std::round(val));
            rpn += std::to_string(intVal) + " ";
            i--;
        }
        else if (expr[i] == '(') {
            ops.push(expr[i]);
        }
        else if (expr[i] == ')') {
            while (!ops.empty() && ops.peek() != '(') {
                char op = ops.pop();
                rpn += op;
                rpn += " ";
                double val2 = values.pop();
                double val1 = values.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.pop();

            if (!functions.empty()) {
                std::string func = functions.pop();
                double val = values.pop();
                values.push(applyFunc(func, val));

                // Округляем результат функции для добавления в rpn
                int intVal = static_cast<int>(std::round(val));
                rpn += func + "(" + std::to_string(intVal) + ") ";
            }
        }
        else if (isalpha(expr[i])) {
            std::string func;
            while (i < expr.length() && isalpha(expr[i])) {
                func += expr[i];
                i++;
            }
            functions.push(func);
            i--;
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^') {
            while (!ops.empty() && precedence(ops.peek()) >= precedence(expr[i])) {
                char op = ops.pop();
                rpn += op;
                rpn += " ";
                double val2 = values.pop();
                double val1 = values.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expr[i]);
        }
    }

    while (!ops.empty()) {
        char op = ops.pop();
        rpn += op;
        rpn += " ";
        double val2 = values.pop();
        double val1 = values.pop();
        values.push(applyOp(val1, val2, op));
    }

    std::cout << "Обратная польская нотация: " << rpn << std::endl;
    return values.peek();
}

int main() {
    setlocale(0, "rus");
    std::string expression;
    std::cout << "Введите математическое выражение: ";
    std::getline(std::cin, expression);

    try {
        double result = evaluate(expression);
        std::cout << "Результат: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    system("pause");
    return 0;
}
