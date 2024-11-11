#include <iostream>
#include <cmath>

class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree() : root{ nullptr } {}

    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {}

    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{ rhs.root } {
        rhs.root = nullptr;
    }

    ~BinarySearchTree() {
        makeEmpty();
    }

    const Comparable &findMin() const {
        if (isEmpty())
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    const Comparable &findMax() const {
        if (isEmpty())
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree" << std::endl;
        } else {
            printTree(root, out);
        }
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    void insert(const Comparable &x) {
        insert(x, root);
    }

    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    void remove(const Comparable &x) {
        remove(x, root);
    }

    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
        if (this != &rhs) {
            BinarySearchTree temp(rhs);
            std::swap(root, temp.root);
        }
        return *this;
    }

    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

protected:
    struct BinaryNode {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        int height;

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt, int h = 1)
            : element{ theElement }, left{ lt }, right{ rt }, height{ h } { }

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt, int h = 1)
            : element{ std::move(theElement) }, left{ lt }, right{ rt }, height{ h } { }
    };

    BinaryNode *root;

    BinaryNode *findMin(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }
        return findMin(t->left);
    }

    BinaryNode *findMax(BinaryNode *t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    bool contains(const Comparable &x, BinaryNode *t) const {
        if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left);
        } else if (x > t->element) {
            return contains(x, t->right);
        } else {
            return true;
        }
    }

    void printTree(BinaryNode *t, std::ostream &out) const {
        if (t != nullptr) {
            printTree(t->left, out);
            out << t->element << std::endl;
            printTree(t->right, out);
        }
    }

    void makeEmpty(BinaryNode *&t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }

    int height(BinaryNode *t) const {
        return t == nullptr ? 0 : t->height;
    }

    void updateHeight(BinaryNode *node) {
        node->height = std::max(height(node->left), height(node->right)) + 1;
    }

    void rotateLeft(BinaryNode *&k2) {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;

        updateHeight(k2);
        updateHeight(k1);
        k2 = k1;
    }

    void rotateRight(BinaryNode *&k1) {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;

        updateHeight(k1);
        updateHeight(k2);
        k1 = k2;
    }

    void leftChild(BinaryNode *&k3) {
        rotateRight(k3->left);
        rotateLeft(k3);
    }

    void rightChild(BinaryNode *&k1) {
        rotateLeft(k1->right);
        rotateRight(k1);
    }

    static const int IMBALANCE = 1;

    void balance(BinaryNode *&t) {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > IMBALANCE) {
            if (height(t->left->left) >= height(t->left->right)) {
                rotateLeft(t);
            } else {
                leftChild(t);
            }
        } else if (height(t->right) - height(t->left) > IMBALANCE) {
            if (height(t->right->right) >= height(t->right->left)) {
                rotateRight(t);
            } else {
                rightChild(t);
            }
        }
        updateHeight(t);
    }

    void insert(const Comparable &x, BinaryNode *&t) {
        if (t == nullptr) {
            t = new BinaryNode{x, nullptr, nullptr};
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        }

        balance(t);
    }

    void insert(Comparable &&x, BinaryNode *&t) {
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        }

        balance(t);
    }

    BinaryNode *detachMin(BinaryNode *&t) {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            BinaryNode *minNode = t;
            return minNode;
        }
        return detachMin(t->left);
    }

    void remove(const Comparable &x, BinaryNode *&t) {
        if (!t) {
            return;
        }

        if (x < t->element) {
            remove(x, t->left);
        } else if (x > t->element) {
            remove(x, t->right);
        } else {    //找到要删除的元素
            if (!t->left && !t->right) {  // 无子节点，直接删除
                delete t;
                t = nullptr; 
            } else {   // 至少有一个子节点
                if (height(t->left) > height(t->right)) {
                    rotateLeft(t);
                    remove(x, t->right);  // 转到右子树
                } else {
                    rotateRight(t);
                    remove(x, t->left);    // 转到左子树
                }
            }
        }

        balance(t);
    }

    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
};
