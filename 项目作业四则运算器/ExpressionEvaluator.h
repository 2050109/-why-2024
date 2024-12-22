#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include <string>
#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace ExpressionEvaluator {

// 自定义栈类模板
template <typename T>
class Stack {
public:
    // 构造函数，初始化栈的容量和栈顶索引
    Stack(size_t capacity) : maxSize(capacity), topIndex(0) {
        stackArray = new T[maxSize + 1];  // 动态分配栈数组
    }

    // 禁用拷贝构造函数和赋值运算符，防止浅拷贝
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    // 析构函数，释放栈数组的内存
    ~Stack() {
        delete[] stackArray;
    }

    // 压入栈顶
    void push(T value) {
        if (topIndex >= maxSize) {
            throw std::runtime_error("栈已满：无法压入新元素。");
        }
        stackArray[topIndex++] = value;
    }

    // 获取栈顶元素，不弹出
    T topElement() const {
        if (topIndex == 0) {
            throw std::runtime_error("栈为空：无法获取栈顶元素。");
        }
        return stackArray[topIndex - 1];
    }

    // 弹出栈顶元素
    T pop() {
        if (topIndex <= 0) {
            throw std::runtime_error("栈下溢：尝试从空栈弹出元素。");
        }
        return stackArray[--topIndex];
    }

    // 判断栈是否为空
    bool empty() const {
        return topIndex == 0;
    }

private:
    T* stackArray;      // 存储栈元素的数组
    size_t maxSize;     // 栈的最大容量
    size_t topIndex;    // 栈顶指针
};

// 获取运算符的优先级
int priority(char c);

// 判断是否应该弹出栈中的运算符
bool shouldPop(char stackOp, char incomingOp);

// 定义TokenType枚举，用于跟踪上一个Token的类型
enum class TokenType {
    NONE,
    NUMBER,
    OPERATOR,
    LEFT_PAREN,
    RIGHT_PAREN
};

// 执行具体的运算
double performCalculation(char op, Stack<double>& numStack);

// 计算中缀表达式的函数
double calculateExpression(const std::string& expr_input);

} // namespace ExpressionEvaluator

#endif // EXPRESSION_EVALUATOR_H








