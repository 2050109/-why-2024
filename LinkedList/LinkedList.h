#include <initializer_list>
#include <iostream>

template <typename T>
class SingleLinkedList
{
private:
    class Node
    {
    private:
        T data;
        Node *next = nullptr;
        Node(T _val) { data = _val; }

        friend class SingleLinkedList<T>;
    };

    Node *head = nullptr;
    int size = 0;
    Node *currentPos = nullptr;

    void _emptyList();
    void _copy(const SingleLinkedList<T> &_l);

public:
    // 返回当前位置的值
    T getCurrentVal() const;

    // 设置当前位置的值
    void setCurrentVal(const T &_val);

    // 判断链表是否为空
    bool isEmpty() const;

    // 获取链表的大小
    int getSize() const;

    // 清空链表
    void emptyList();

    // 查找指定值
    bool find(const T &_val);

    // 构造函数
    SingleLinkedList() {};

    // 析构函数
    ~SingleLinkedList();

    // 使用初始化列表的构造函数
    SingleLinkedList(std::initializer_list<T> _l);

    // 打印链表内容
    void printList() const;

    // 拷贝构造函数
    SingleLinkedList(const SingleLinkedList<T> &_l);

    // 赋值运算符重载
    SingleLinkedList<T> &operator=(const SingleLinkedList<T> &_l);

    // 在 currentPos 后面插入一个元素
    void insert(T _val);

    // 删除 currentPos 后面的元素
    void remove();
};

// 返回当前位置的值
template <typename T>
T SingleLinkedList<T>::getCurrentVal() const
{
    // 如果 currentPos 为空，输出错误信息，并返回默认值
    if (currentPos == nullptr)
    {
        std::cout << "Error: currentPos is null" << std::endl;
        return T(); // 返回 T 类型的默认值
    }
    return currentPos->data;
}

// 设置当前位置的值
template <typename T>
void SingleLinkedList<T>::setCurrentVal(const T &_val)
{
    if (currentPos == nullptr)
    {
        std::cout << "Error: currentPos is null" << std::endl;
        return;
    }
    currentPos->data = _val;
}

// 判断链表是否为空
template <typename T>
bool SingleLinkedList<T>::isEmpty() const
{
    return head == nullptr;
}

// 获取链表的大小
template <typename T>
int SingleLinkedList<T>::getSize() const
{
    return size;
}

// 清空链表
template <typename T>
void SingleLinkedList<T>::emptyList()
{
    _emptyList();
    head = nullptr;
    currentPos = nullptr;
    size = 0;
}

// 查找指定值
template <typename T>
bool SingleLinkedList<T>::find(const T &_val)
{
    Node *p = head;
    while (p != nullptr)
    {
        if (p->data == _val)
        {
            currentPos = p;
            return true;
        }
        p = p->next;
    }
    return false;
}

// 在 currentPos 后面插入一个元素
template <typename T>
void SingleLinkedList<T>::insert(T _val)
{
    // 如果链表为空，插入第一个节点
    if (isEmpty())
    {
        Node *newNode = new Node(_val);
        head = newNode;
        currentPos = head;
    }
    else
    {
        // 在 currentPos 后面插入一个新节点
        Node *newNode = new Node(_val);
        newNode->next = currentPos->next;
        currentPos->next = newNode;
    }
    ++size;
}

// 删除 currentPos 后面的元素
template <typename T>
void SingleLinkedList<T>::remove()
{
    // 如果 currentPos 为空或 currentPos 后面没有节点，输出错误信息
    if (currentPos == nullptr || currentPos->next == nullptr)
    {
        std::cout << "Error: Cannot remove, no element after currentPos." << std::endl;
        return;
    }

    Node *nodeToRemove = currentPos->next; // 要删除的节点
    currentPos->next = nodeToRemove->next;  // 跳过要删除的节点

    delete nodeToRemove; // 释放内存
    --size;
}

// 初始化列表构造函数
template <typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> _l)
{
    for (auto i = _l.begin(); i != _l.end(); ++i)
    {
        Node *newNode = new Node(*i);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
    }
}

// 打印链表内容
template <typename T>
void SingleLinkedList<T>::printList() const
{
    Node *p = head;
    while (p != nullptr)
    {
        std::cout << p->data << "\t";
        p = p->next;
    }
    std::cout << std::endl;
}

// 析构函数
template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    _emptyList();
}

// 拷贝链表内容
template <typename T>
void SingleLinkedList<T>::_copy(const SingleLinkedList<T> &_l)
{
    Node *p = _l.head;
    while (p != nullptr)
    {
        Node *newNode = new Node(p->data);
        if (head == nullptr)
        {
            head = newNode;
            currentPos = head;
        }
        else
        {
            currentPos->next = newNode;
            currentPos = newNode;
        }
        ++size;
        p = p->next;
    }
}

// 清空链表
template <typename T>
void SingleLinkedList<T>::_emptyList()
{
    Node *p = head;
    while (p != nullptr)
    {
        Node *t = p;
        p = p->next;
        delete t;
    }
}

// 拷贝构造函数
template <typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> &_l)
{
    _copy(_l);
}

// 赋值运算符重载
template <typename T>
SingleLinkedList<T> &SingleLinkedList<T>::operator=(const SingleLinkedList<T> &_l)
{
    if (this == &_l)
        return *this;
    emptyList();
    _copy(_l);
    return *this;
}
