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

    size_t count{};
    uint8_t height{};

    Node() = default;

    ~Node() {
        delete left;
        delete right;
    }

    explicit Node(T _key) : key(_key), left(nullptr), right(nullptr), height(0), count(0) {}
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

public:
    avl_tree() : root(nullptr) {}

    ~avl_tree() {
        delete root;
    }

    void insert(T &key) {
        root = _insert(root, key);
    }

    T kth_stat(size_t k) {
        auto node = root;
        size_t left_count = get_count(node->left);
        size_t a = 0, b = get_count(node);
        while (k != a + left_count){
            if (k < a + left_count){
                b -= get_count(node->right);
                node = node->left;
            } else {
                a += left_count + 1;
                node = node->right;
            }
            left_count = get_count(node->left);
        }
        return node->key;
    }

    void erase(const T &value) {
        root = _erase(root, value);
    }

private:
    Node<T>* _erase(Node<T>* node, const T& value){
        if (!node)
            return nullptr;

        auto cmp_res = cmp(value, node->key);

        if (cmp_res == -1)
            node->left = _erase(node->left, value);
        else if (cmp_res == 1)
            node->right = _erase(node->right, value);
        else {
            Node<T>* left = node->left;
            Node<T>* right = node->right;

            delete node;
            if (!right){
                return left;
            }
            Node<T>* min_node = find_min(right);
            right = remove_min_node(right);

            min_node->left = left;
            min_node->right = right;

            return balance(min_node);
        }
        return balance(node);
    }
    Node<T>* remove_min_node(Node<T>* node) {
        if (!node->left) {
            return node->right;
        }

        node->left = remove_min_node(node->left);
        return balance(node);
    }

    Node<T>* find_min(Node<T>* node) {
        if (!node->left) {
            return node;
        }
        return find_min(node->left);
    }

    Node<T>* _insert(Node<T>* node, T& value){
        if (!node)
            return new Node<T>(value);

        if (value < node->key){
            node->left = _insert(node->left, value);
        }else{
            node->right = _insert(node->right, value);
        }
        return balance(node);
    }

    Node<T>* balance(Node<T>* node){
        fix(node);

        auto bf = b_factor(node);
        if (bf == 2){
            if (b_factor(node->right) < 0)
                node->right = rotate_right((node->right));
            return rotate_left(node);
        }
        if (bf == -2){
            if (b_factor(node->left) > 0)
                node->left = rotate_left(node->left);
            return rotate_right(node);
        }
        return node;
    }

    size_t get_height(Node<T>* node){
        return ((node)? node->height : 0);
    }

    size_t get_count(Node<T>* node){
        return ((node)? node->count : 0);
    }

    void fix(Node<T>* node){
        node->height = std::max(get_height(node->left), get_height(node->right), cmp);
        node->count = 1 + get_count(node->left) + get_height(node->right);
    }

    int b_factor(Node<T>* node){
        return get_height(node->left) - get_height(node->right);
    }

    Node<T>* rotate_left(Node<T>* node){
        Node<T>* ptr = node->right;
        node->right = ptr->left;
        ptr->left = node;

        fix(ptr);
        fix(node);
        return ptr;
    }

    Node<T>* rotate_right(Node<T>* node){
        Node<T>* ptr = node->left;
        node->left = ptr->right;
        ptr->right = node;

        fix(node);
        fix(ptr);
        return ptr;
    }
};

void run(std::istream &in, std::ostream &out) {
    int N;
    in >> N;
    avl_tree<int64_t> tree{};
    for (int i = 0; i < N; ++i) {
        int64_t num;
        int pos;
        in >> num >> pos;
        if (num > 0)
            tree.insert(num);
        else
            tree.erase(-num);

        out << tree.kth_stat(pos);
    }
}
