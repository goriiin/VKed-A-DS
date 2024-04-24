#include <iostream>

void run(std::istream &in, std::ostream &out);

int main() {
    run(std::cin, std::cout);
    return 0;
}

template<typename T>
struct Node {
    T key;
    Node *left;
    Node *right;

    uint8_t height{};

    Node() = default;

    ~Node() {
        delete left;
        delete right;
    }

    explicit Node(T _key) : key(_key), left(nullptr), right(nullptr), height(0) {}
};

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
    Node<T> *root;
    Comparator cmp;

    uint8_t get_height(const Node<T> *node) const {
        return (node ? node->height : 0);
    }

    int bfactor(const Node<T> *node) const {
        return get_height(node->left) - get_height(node->right);
    }

    void fix_height(Node<T> *node) {
        node->height = std::max(get_height(node->left), get_height(node->right))+ 1;
    }

    void destroy(Node<T> *node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    Node<T> *_find(Node<T> *node, T value) {
        if (node == nullptr)
            return nullptr;
        if (cmp(node->key, value) == 0)
            return node;

        if (cmp(value, node->key) < 0) {
            _find(node->left, value);
        } else {
            _find(node->right, value);
        }
        return nullptr;
    }

    Node<T> *find_parent_min(Node<T> *node) {
        return (node->left->left == nullptr) ? node : find_parent_min(node->left);
    }

    Node<T> *find(const T &value) {
        Node<T> *node = root;
        return _find(node, value);
    }

    // TODO: сделать
    Node<T> *rotate_right(Node<T> *node) {

    }

    // TODO: сделать
    Node<T> *rotate_left(Node<T> *node) {

    }

    Node<T>* balance(Node<T>* node){
        fix_height(node);

        auto bf = bfactor(node);
        if (bf == 2){
            if (bfactor(node->right) < 0){
                node->righe = rotate_right(node->right);
            }
            return rotate_left(node);
        }
        if (bf == -2){
            if (bfactor(node->left) > 0){
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }
        return node;
    }
public:
    avl_tree() = default;

    ~avl_tree() {
        delete root;
    }

    void add(const T &key) {

    }

    T kth_stat(size_t k) {

    }

    bool has(const T &val) {
        return find(val) != nullptr;
    }

    void del(const T &value) {
        auto node = find(value);
        if (node->left == nullptr) {
            auto r = node->right;
            delete node;

            node = r;
        } else if (node->right == nullptr) {
            auto l = node->left;
            delete node;
            node = l;
        } else {
            auto parent_min = find_parent_min(node->right);
            auto min = parent_min->left;

            node->key = min->key;
            (parent_min->left == min ? parent_min->left : parent_min->right) =
                    min->right;
            delete min;
        }
    }
};

template<typename T, class Comparator = DefaultComparator<T>>
T abs_num(const T &num) {
    Comparator cmp;
    if (cmp(num, T(0)) < 0) {
        return -1 * num;
    }

    return num;
}


void run(std::istream &in, std::ostream &out) {
    int N;
    in >> N;
    avl_tree<int64_t> tree{};
    for (int i = 0; i < N; ++i) {
        int64_t num;
        int pos;
        in >> num >> pos;
        if (num > 0)
            tree.add(num);
        else
            tree.del(abs_num(num));
        out << tree.kth_stat(pos);
    }
}
