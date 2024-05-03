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

    explicit Node(T _key) : key(_key), left(nullptr), right(nullptr), height(1), count(1) {}
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
        size_t from = 0, to = node->count; //поиск в полуинтервале [from; to)
        size_t node_left_size = get_count(node->left);
        while (k != from + node_left_size) {
            if (k < from + node_left_size) { //поиск в левом поддереве current_node
                to -= get_count(node->right) + 1;
                node = node->left;
            } else { //поиск в правом поддереве current_node
                from += node_left_size + 1;
                node = node->right;
            }
            node_left_size = get_count(node->left);
        }
        return node->key;
    }

    void erase(const T &value) {
        root = _erase(root, value);
    }

private:
    Node<T>* _erase(Node<T>* node, const T& value){
        if (node == nullptr) {
            return nullptr;
        }
        switch (cmp(value, node->key)) {
            case -1:
                node->left = _erase(node->left, value);
                break;
            case 1:
                node->right = _erase(node->right, value);
                break;
            default: //case 0: (equals)
                auto left = node->left, right = node->right;
                delete node;
                if (right == nullptr) {
                    return left;
                }
                Node<T> *right_min; //здесь будет указатель на минимальный узел правого поддерева удалённого узла node
                right = remove_min_node(right, right_min); //передаём указатель на правое поддерево узла node и ссылку
                right_min->left = left;
                right_min->right = right;
                return balance(right_min);
        }
        return balance(node);
    }
    Node<T>* remove_min_node(Node<T>* node, Node<T>* min_node) {
        if (node->left == nullptr) {
            min_node = node; //запоминаем минимальный узел текущего поддерева
            return node->right;
        }
        node->left = remove_min_node(node->left, min_node);
        return balance(node);
    }

    Node<T>* _insert(Node<T>* node, T& value){
        if (node == nullptr) {
            return new Node<T>(value);
        }
        switch (cmp(value, node->key)) {
            case -1:
                node->left = _insert(node->left, value);
                break;
            case 1:
                node->right = _insert(node->right, value);
                break;
            default:
                return root;
        }
        return balance(node);
    }

    Node<T>* balance(Node<T>* node){
        fix(node);
        int8_t balance_factor = b_factor(node);
        if (balance_factor == 2) {
            if (b_factor(node->right)) {
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);
        } else if (balance_factor == -2) {
            if (b_factor(node->left)) {
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        } else {
            return node;
        }
    }

    size_t get_height(Node<T>* node){
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    size_t get_count(Node<T>* node){
        if (node == nullptr) {
            return 0;
        }
        return node->count;
    }

    void fix(Node<T>* node){
        node->height = 1 + std::max(get_height(node->left), get_height(node->right));
        node->count = 1 + get_count(node->left) + get_count(node->right);
    }

    int b_factor(Node<T>* node){
        return get_height(node->right) - get_height(node->left);
    }

    Node<T>* rotate_left(Node<T>* node){
        Node<T>* ptr = node->right;
        node->right = ptr->left;
        ptr->left = node;

        fix(node);
        fix(ptr);
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
