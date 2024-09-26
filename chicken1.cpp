#include <iostream>
#include <cstring>
#include <initializer_list>
#include <stdexcept>  

#define NIL -1

  
class Chicken {  
private:  
    int age;  
    char* name;  
  
public:  
    // 默认构造函数  
    Chicken() : age(24), name(nullptr) {}  
  
    // 带参数的构造函数  
    Chicken(int _age, const char* _name) : age(_age), name(nullptr) {  
        if (_name != nullptr) {  
            name = new char[strlen(_name) + 1];  
            strcpy(name, _name); // 使用strcpy确保字符串被正确复制  
        }  
    }  
  
    // 拷贝构造函数（实现深拷贝）  
    Chicken(const Chicken& other) : age(other.age), name(nullptr) {  
        if (other.name != nullptr) {  
            name = new char[strlen(other.name) + 1];  
            strcpy(name, other.name); // 使用strcpy确保字符串被正确复制  
        }  
    }  
  
    // 赋值运算符（实现深拷贝）  
    Chicken& operator=(const Chicken& other) {  
        if (this != &other) { // 防止自赋值  
            age = other.age;  
            char* newName = nullptr;  
            if (other.name != nullptr) {  
                newName = new char[strlen(other.name) + 1];  
                strcpy(newName, other.name); // 使用strcpy确保字符串被正确复制  
            }  
            delete[] name; // 释放旧内存  
            name = newName;  
        }  
        return *this;  
    }  
  
    // 析构函数  
    ~Chicken() {  
        delete[] name;  
    }  
  
    // 设置年龄  
    void setAge(int _age) {  
        age = _age;  
    }  
  
    // 设置名字，支持深拷贝  
    void setName(const char* _name) {  
        delete[] name; // 先释放旧内存  
        name = nullptr;  
        if (_name != nullptr) {  
            name = new char[strlen(_name) + 1];  
            strcpy(name, _name); // 使用strcpy确保字符串被正确复制  
        }  
    }  
  
    // 获取名字  
    const char* getName() const {  
        return name ? name : "";  
    }  
  
    // 获取年龄  
    int getAge() const {  
        return age;  
    }  
};  

  
template <typename t_ele>
class ArrayList
{
private:
    int size = 0;
    t_ele *data = nullptr;
public:
    ArrayList(){};
    ArrayList(std::initializer_list<t_ele> _l)   // 这里不能左值引用，为啥？
    {
        size = _l.size();
        data = new t_ele [size];
        int i = 0;
        for (t_ele e : _l)
        {
            data[i] = e;
            i++;
        }
    };

    ArrayList(const ArrayList &_l)
    {
        size = _l.size;
        data = new t_ele [size];
        for (int i = 0; i < size; i++)
            data[i] = _l.data[i];
    }

    ArrayList &operator=(const ArrayList &_l)
    {
        if (this == &_l)
            return *this;
        makeEmpty();
        size = _l.size;
        data = new t_ele [size];
        for (int i = 0; i < size; i++)
            data[i] = _l.data[i];
        return *this;
    }

    void printList() const
    {
        std::cout << "Values: " << std::endl;
        for (int i = 0; i < size; i++)
            std::cout << data[i] << "\t";
        std::cout << std::endl;    
    };
    void makeEmpty()
    {
        size = 0;
        if (data != nullptr)
            delete [] data;
        data = nullptr;             // avoid double free.
    }
    int find(const t_ele &_v) const; // 左值引用，避免复制。当 t_ele 是复杂数据结构时。
    void insert(const t_ele &_v, int _p);  // insert _v after pos _p. 同理。
    void push_ahead(const t_ele &_v);      // insert _v to the first pos.
    void remove(const t_ele &_v);          // remove the first ele equals to _v, do nothing if not found.
    ~ArrayList()
    {
        if (data != nullptr)        // avoid double free.
            makeEmpty();
    }
};

template <typename t_ele>
void ArrayList<t_ele>::push_ahead(const t_ele &_v)
{
    if (size == 0)
    {
        data = new t_ele;
        *data = _v;
        size ++;
        return;        
    }
    t_ele *new_data = new t_ele[size + 1];
    *new_data = _v;
    for (int i = 1; i < size + 1; i++)
        new_data[i] = data[i - 1];  
    delete [] data;         
    data = new_data;
    size ++; 
}

template <typename t_ele>
int ArrayList<t_ele>::find(const t_ele& _v) const
{
    for (int i = 0; i < size; i++)
        if (_v == data[i])
            return i;
    return NIL;
}

template <typename t_ele>
void ArrayList<t_ele>::remove(const t_ele &_v)
{
    int idx = find(_v);
    if (idx == NIL)
        return;
    t_ele *new_data = new t_ele [size - 1];
    for (int i = 0; i < idx; i++)
        new_data[i] = data[i];
    for (int i = idx + 1; i < size; i++)
        new_data[i - 1] = data[i];
    if (data != nullptr) {  
    delete[] data;  
}        
    data = new_data;
    size --;                // ???
}



