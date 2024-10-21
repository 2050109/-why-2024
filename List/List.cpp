#include <iostream>
#include "list.h" // 假设 List 类定义在这个头文件中

int main() {
    // 测试 List 的默认构造函数
    List<int> myList;
    std::cout << "初始化一个空的 List: " << (myList.empty() ? "成功" : "失败") << std::endl;

    // 测试 push_back 和 size 函数
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    std::cout << "向 List 尾部插入元素 10, 20, 30" << std::endl;
    std::cout << "List 的大小: " << myList.size() << std::endl;

    // 测试 front 和 back 函数
    std::cout << "List 的第一个元素: " << myList.front() << std::endl;
    std::cout << "List 的最后一个元素: " << myList.back() << std::endl;

    // 测试 push_front 函数
    myList.push_front(0);
    std::cout << "向 List 头部插入元素 0" << std::endl;
    std::cout << "List 的第一个元素: " << myList.front() << std::endl;

    // 测试前置递增（operator++）
    auto it = myList.begin();
    std::cout << "前置递增前指向的元素: " << *it << std::endl;
    ++it;
    std::cout << "前置递增后指向的元素: " << *it << std::endl;

    // 测试后置递增（operator++(int)）
    auto it_post_inc = it++;
    std::cout << "后置递增前指向的元素: " << *it_post_inc << std::endl;
    std::cout << "后置递增后指向的元素: " << *it << std::endl;

    // 测试前置递减（operator--）
    --it;
    std::cout << "前置递减后指向的元素: " << *it << std::endl;

    // 测试后置递减（operator--(int)）
    auto it_post_dec = it--;
    std::cout << "后置递减前指向的元素: " << *it_post_dec << std::endl;
    std::cout << "后置递减后指向的元素: " << *it << std::endl;

    // 测试运算符*（解引用）
    std::cout << "当前迭代器解引用的元素: " << *it << std::endl;

    // 测试运算符== 和 !=
    auto it2 = myList.begin();
    std::cout << "当前迭代器解引用的元素: " << *it2 << std::endl;
    std::cout << "it 和 it2 是否相等 (预期: 是): " << (it == it2 ? "是" : "否") << std::endl;
    ++it2;
    std::cout << "it 和 it2 是否相等 (预期: 否): " << (it != it2 ? "否" : "是") << std::endl;

    // 测试遍历功能 (使用前向迭代器)
    std::cout << "正向遍历 List: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试 pop_front 和 pop_back
    myList.pop_front();
    std::cout << "删除 List 的头部元素" << std::endl;
    myList.pop_back();
    std::cout << "删除 List 的尾部元素" << std::endl;
    std::cout << "删除后的 List 大小: " << myList.size() << std::endl;

    // 再次遍历 (验证 pop_front 和 pop_back)
    std::cout << "删除后遍历 List: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试插入函数（在中间插入）
    it = myList.begin();
    ++it; // 指向第二个元素
    myList.insert(it, 15);
    std::cout << "在第二个元素前插入 15 后的 List: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "在头部插入 5:" << std::endl;
    myList.insert(myList.begin(), 5);
    std::cout << "列表元素: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 在尾部插入
    std::cout << "在尾部插入 20:" << std::endl;
    myList.insert(myList.end(), 20); // 在尾部插入
    std::cout << "列表元素: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试 erase 函数
    it = myList.begin();
    ++it; // 指向第二个元素
    myList.erase(it); // 删除第二个元素
    std::cout << "删除第二个元素后的 List: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试拷贝构造函数
    List<int> copyList = myList;
    std::cout << "拷贝后的 List: ";
    for (auto it = copyList.begin(); it != copyList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试初始化列表构造函数
    List<int> initList{1, 2, 3, 4, 5};
    std::cout << "使用初始化列表构造的 List: ";
    for (auto it = initList.begin(); it != initList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    it=initList.begin();
     std::cout << "head 指针的地址: " << *it << std::endl;


    List<int> sectList{};
    std::cout << "使用初始化列表构造的 List: ";
    for (auto it = sectList.begin(); it != sectList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    it=sectList.begin();
     std::cout << "head 指针的地址: " << *it << std::endl;
    // 测试 clear 函数
    myList.clear();
    std::cout << "清空 List 后，List 是否为空: " << (myList.empty() ? "是" : "否") << std::endl;

    return 0;
}


