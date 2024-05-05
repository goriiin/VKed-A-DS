//4_2. Порядковые статистики
//
//Дано число N и N строк. Каждая строка содержащит команду
//добавления или удаления натуральных чисел, а также запрос на
//получение k-ой порядковой статистики. Команда добавления числа
//A задается положительным числом A, команда удаления числа A
//задается отрицательным числом “-A”. Запрос на получение k-ой
//порядковой статистики задается числом k. Требуемая скорость
//выполнения запроса - O(log n).

#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>

void run(std::istream &in, std::ostream &out);

void run_test();

int main() {
//    run_test();
    run(std::cin, std::cout);
    return 0;
}

template<typename T>
struct [[maybe_unused]] DefaultComparator {
    int operator()(const T &l, const T r) {
        if (l < r)
            return -1;
        if (l > r)
            return 1;
        return 0;
    }
};

template<typename T, class Comparator = DefaultComparator<T>>
class avl_tree {
    Comparator cmp;

    struct Node {
        T key;
        Node *left;
        Node *right;
        size_t count{};
        int height{};

        explicit Node(T _key) :
                key(_key),
                left(nullptr),
                right(nullptr),
                height(1),
                count(1) {}
    };

    Node *root;

public:
    avl_tree() : root(nullptr) {}

    ~avl_tree() {
        destroy_tree(root);
    }

    void insert(const T &value) {
        root = _insert(root, value);
    }

    void erase(const T &value) {
        root = _erase(root, value);
    }

    T kth_stat(size_t k) {
        if (k >= count()) {
            throw std::out_of_range("kth_stat: k is out of range");
        }
        return _kth_stat(root, k);
    }

    size_t count() {
        return get_count(root);
    }

private:
    T _kth_stat(Node *node, size_t k) {
        size_t left_count = get_count(node->left);

        if (k < left_count) {
            return _kth_stat(node->left, k);
        } else if (k == left_count) {
            return node->key;
        } else {
            return _kth_stat(node->right, k - left_count - 1);
        }
    }

    void destroy_tree(Node *node) {
        if (node) {
            destroy_tree(node->left);
            destroy_tree(node->right);
            delete node;
        }
    }

    Node *_insert(Node *node, const T &value) {
        if (node == nullptr) {
            return new Node(value);
        }
        auto res = cmp(value, node->key);
        if (res < 0) {
            node->left = _insert(node->left, value);
        } else {
            node->right = _insert(node->right, value);
        }
        return balance(node);
    }

    Node *rotate_right(Node *node) {
        Node *ptr = node->left;
        node->left = ptr->right;
        ptr->right = node;

        fix(node);
        fix(ptr);
        return ptr;
    }

    Node *rotate_left(Node *node) {
        Node *ptr = node->right;
        node->right = ptr->left;
        ptr->left = node;

        fix(node);
        fix(ptr);
        return ptr;
    }

    int get_height(Node *node) {
        if (node == nullptr)
            return 0;

        return node->height;
    }

    int get_count(Node *node) {
        if (node == nullptr) {
            return 0;
        }

        return node->count;
    }

    void fix(Node *node) {
        node->height = std::max(get_height(node->left), get_height(node->right), cmp) + 1;
        node->count = get_count(node->left) + get_count(node->right) + 1;
    }

    int b_factor(Node *node) {
        return get_height(node->right) - get_height(node->left);
    }

    Node *balance(Node *node) {
        fix(node);
        if (b_factor(node) == 2) {
            if (b_factor(node->right) < 0) {
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);
        } else if (b_factor(node) == -2) {
            if (b_factor(node->left) > 0) {
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }
        return node;
    }

    Node *_erase(Node *node, const T &value) {
        if (node == nullptr) {
            return nullptr;
        }

        auto res = cmp(value, node->key);

        if (res < 0) {
            node->left = _erase(node->left, value);
        } else if (res > 0) {
            node->right = _erase(node->right, value);
        } else {

            Node* right = node->right;
            Node* left = node->left;

            delete node;

            if (right == nullptr) {
                return left;
            }

            std::pair<Node*, Node*> pair = find_erase_min(right);
            Node* min = pair.first;
            min->right = pair.second;
            min->left = left;
            node = min;

            return balance(node);
        }

        return balance(node);
    }

    std::pair<Node*, Node*> find_erase_min(Node *node) {
        if (node->left == nullptr) {
            return { node, node->right };
        }
        std::pair<Node*, Node*> pair = find_erase_min(node->left);
        node->left = pair.second;
        return {pair.first,balance(node)};
    }
};

void test() {
    srand(time(0));
    for (int i = 0; i < 10000; ++i) {
        avl_tree<int> tree;
        int n = 1 + rand() % 15;
        std::vector<int> a;
        for (int k = 0; k < n; ++k) {
            int val = rand() % 400 + 1;
            a.push_back(val);
            tree.insert(val);
            std::cout << "zap_ " << val << std::endl;
        }
        std::sort(a.begin(), a.end());
        for (int j = 0; j < n; j++) {
            int stat = tree.kth_stat(j);
            std::cout << "a[j] -- stat " << a[j] << " " << stat << std::endl;
            assert (a[j] == stat);
        }

        for (int j = 0; j < n - 1; j++) {
            int pos = rand() % (a.size());
            int el = a[pos];
            a.erase(a.begin() + pos);
            tree.erase(el);
            std::sort(a.begin(), a.end());
            for (int k = 0; k < a.size(); k++) {

                int stat = tree.kth_stat(k);
                std::cout << "del : a[j] -- stat" << a[k] << " " << stat << std::endl;
                assert (a[k] == stat);
            }
        }
    }
    std::cout << "all test OK";
}

void run_test() {
    test();
}

void run(std::istream &in, std::ostream &out) {
    int N;
    in >> N;
    avl_tree<int> tree{};
    for (int i = 0; i < N; ++i) {
        int num;
        int pos;
        in >> num >> pos;
        if (num > 0)
            tree.insert(num);
        else {
            num *= -1;
            tree.erase(num);
        }

        out << tree.kth_stat(pos) << std::endl;
    }
}
