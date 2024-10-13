#include "LinkedList.h"
#include <iostream>

int main()
{
    // 创建并初始化一个链表
    SingleLinkedList<int> link1{1, 2, 3, 4, 5};
    std::cout << "Initial list: ";
    link1.printList();

    // 测试复制构造函数
    SingleLinkedList<int> link2(link1);
    std::cout << "Copied list (link2): ";
    link2.printList();

    // 测试赋值运算符
    SingleLinkedList<int> link3 = link1;
    std::cout << "Assigned list (link3): ";
    link3.printList();

    // 打印原始链表
    std::cout << "Original list (link1): ";
    link1.printList();

    // 测试 isEmpty 方法
    std::cout << "Is link1 empty? " << (link1.isEmpty() ? "Yes" : "No") << std::endl;

    // 测试 getCurrentVal 和 setCurrentVal 方法
    link1.find(3); // 找到元素 3
    std::cout << "Current value (before setting): " << link1.getCurrentVal() << std::endl;
    link1.setCurrentVal(99);
    std::cout << "Current value (after setting to 99): " << link1.getCurrentVal() << std::endl;
    std::cout << "List after setting current value: ";
    link1.printList();

    // 测试 insert 方法
    std::cout << "Inserting 6 after current position." << std::endl;
    link1.insert(6);
    std::cout << "List after inserting 6: ";
    link1.printList();

    // 测试 remove 方法
    std::cout << "Removing element after current position." << std::endl;
    link1.remove();
    std::cout << "List after removing: ";
    link1.printList();

    // 测试 isEmpty 方法
    std::cout << "Is link1 empty? " << (link1.isEmpty() ? "Yes" : "No") << std::endl;

    // 清空链表并检查状态
    link1.emptyList();
    std::cout << "List after emptying link1: ";
    link1.printList();
    std::cout << "Is link1 empty after clearing?                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                " << (link1.isEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}
