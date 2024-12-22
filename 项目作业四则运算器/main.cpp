#include <iostream>
#include <iomanip>
#include "ExpressionEvaluator.h"

#define PRECISION setprecision(5)

using namespace std;

namespace ExpressionEvaluator {

// 获取运算符的优先级
int priority(char c) {
    switch (c) {
        case '~': return 3;  // 一元负号优先级最高
        case '^': return 2;  // 幂运算优先级
        case '*': case '/': return 1;  // 乘法和除法优先级
        case '+': case '-': return 0;  // 加法和减法优先级
        default: return -1;  // 非法运算符
    }
}

// 判断是否应该弹出栈中的运算符
bool shouldPop(char stackOp, char incomingOp) {
    return priority(stackOp) >= priority(incomingOp);
}

// 执行具体的运算
double performCalculation(char op, Stack<double>& numStack) {
    if (op == '~') {  // 一元运算符：负号
        if (numStack.empty()) {
            throw runtime_error("操作数不足：无法执行一元负号运算。");
        }
        double x = numStack.pop();  // 弹出一个操作数
        double result = -x;
        numStack.push(result);  // 将取负后的值压入栈
        return result;
    }
    else {  // 二元运算符
        if (numStack.empty()) {
            throw runtime_error("操作数不足：无法执行二元运算。");
        }
        double x = numStack.pop();  // 弹出第二个操作数
        if (numStack.empty()) {
            throw runtime_error("操作数不足：无法执行二元运算。");
        }
        double y = numStack.pop();  // 弹出第一个操作数

        double result;
        switch(op) {
            case '^':
                result = pow(y, x);  // 幂运算
                break;
            case '*':
                result = y * x;  // 乘法
                break;
            case '/':
                if (x == 0) {
                    throw runtime_error("除以零错误。");
                }
                result = y / x;  // 除法
                break;
            case '+':
                result = y + x;  // 加法
                break;
            case '-':
                result = y - x;  // 减法
                break;
            default:
                throw runtime_error("无效运算符：无法执行运算。");
        }
        numStack.push(result);  // 将结果压入栈
        return result;
    }
}

// 计算中缀表达式的函数
double calculateExpression(const string& expr_input) {
    string expr = expr_input;

    // 移除表达式中的所有空格
    expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());

    Stack<double> numStack(expr.size());  // 数字栈
    Stack<char> opStack(expr.size());     // 运算符栈

    TokenType lastToken = TokenType::NONE;  // 初始化上一个Token类型

    size_t i = 0;  // 当前解析的位置
    while (i < expr.length()) {
        char c = expr[i];

        if (isdigit(c) || c == '.') {  // 处理数字和小数点
            // 检查上一个Token是否合法接数字
            if (lastToken == TokenType::NUMBER || lastToken == TokenType::RIGHT_PAREN) {
                throw runtime_error("非法语法：数字或右括号后不能直接接数字。");
            }

            size_t len = 0;
            double num = 0.0;
            try {
                num = stod(expr.substr(i), &len);  // 解析数字，包括科学计数法
            } catch (...) {
                throw runtime_error("无效数字格式。");
            }
            numStack.push(num);  // 压入数字栈
            i += len;  // 移动到下一个未解析的位置
            lastToken = TokenType::NUMBER;  // 更新上一个Token类型
        }
        else {  // 处理运算符和括号
            if (c == '(') {  // 左括号直接压入运算符栈
                // 检查上一个Token是否合法接左括号
                if (lastToken == TokenType::NUMBER || lastToken == TokenType::RIGHT_PAREN) {
                    throw runtime_error("非法语法：数字或右括号后不能直接接左括号。");
                }
                opStack.push(c);
                i++;
                lastToken = TokenType::LEFT_PAREN;  // 更新上一个Token类型
            }
            else if (c == ')') {  // 右括号，弹出运算符直到遇到左括号
                // 检查上一个Token是否合法接右括号
                if (lastToken == TokenType::OPERATOR || lastToken == TokenType::LEFT_PAREN || lastToken == TokenType::NONE) {
                    throw runtime_error("非法语法：运算符、左括号或表达式开头后不能接右括号。");
                }

                while (!opStack.empty() && opStack.topElement() != '(') {
                    char op = opStack.pop();
                    performCalculation(op, numStack);
                }
                if (!opStack.empty() && opStack.topElement() == '(') {
                    opStack.pop();  // 弹出左括号
                }
                else {
                    throw runtime_error("括号不匹配。");
                }
                i++;
                lastToken = TokenType::RIGHT_PAREN;  // 更新上一个Token类型
            }
            else {  // 处理运算符
                // 判断是否为一元负号
                bool isUnaryMinus = false;
                if (c == '-' && (lastToken == TokenType::NONE || lastToken == TokenType::OPERATOR || lastToken == TokenType::LEFT_PAREN)) {
                    isUnaryMinus = true;
                    c = '~';  // 使用 '~' 表示一元负号
                }

                // 检查上一个Token是否合法接运算符
                if (lastToken == TokenType::OPERATOR && !isUnaryMinus) {
                    throw runtime_error("非法语法：连续运算符。");
                }
                if (isUnaryMinus && lastToken == TokenType::OPERATOR) {
                    // 为简化处理，不允许多个连续一元负号
                    throw runtime_error("非法语法：连续一元运算符。");
                }

                // 根据优先级弹出运算符并计算
                while (!opStack.empty() && opStack.topElement() != '(' && shouldPop(opStack.topElement(), c)) {
                    char op = opStack.pop();
                    performCalculation(op, numStack);
                }
                opStack.push(c);  // 压入当前运算符
                i++;
                lastToken = TokenType::OPERATOR;  // 更新上一个Token类型
            }
        }
    }

    // 剩余顺序
    while (!opStack.empty()) {
        char op = opStack.topElement();
        if (op == '(' || op == ')') {  // 检查是否有未匹配的括号
            throw runtime_error("括号不匹配。");
        }
        opStack.pop();
        performCalculation(op, numStack);
    }

    // 如果没有错误且数字栈中有结果，返回结果；否则抛出异常
    if (!numStack.empty()) {
        double result = numStack.pop();
        if (numStack.empty()) {
            return result;
        }
    }
    throw runtime_error("非法表达式结构。");
}

} // namespace ExpressionEvaluator

// 主函数，独立于库函数
int main() {
    string expr;
    getline(cin, expr);  // 读取输入的表达式

    try {
        double result = ExpressionEvaluator::calculateExpression(expr);  // 计算表达式
        cout << fixed << PRECISION << result << endl;  // 输出结果，保留五位小数
    }
    catch (const exception& e) {
        cout << "ILLEGAL" << endl;  // 表达式有误
    }

    return 0;
}




