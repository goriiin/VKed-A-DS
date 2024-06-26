//2_3. Обход дерева в порядке post-order
//Дано число N ≤ 104 и последовательность целых чисел из [-2^31..2^31]
// длиной N. Требуется построить бинарное дерево, заданное наивным порядком
// вставки. Т.е., при добавлении очередного числа K в дерево с корнем root,
// если root→T ≤ K, то узел K добавляется в правое поддерево root; иначе в
// левое поддерево root. Выведите элементы в порядке post-order (снизу вверх).
//
//Рекурсия запрещена.

#include <iostream>
#include <stack>

void answer(std::istream& in, std::ostream& out);

int main() {
    answer(std::cin, std::cout);
    return 0;
}

template <typename T>
struct Node{
    T data;
    Node<T>* left;
    Node<T>* right;

    Node() : left(nullptr), right(nullptr){}
    Node(T _data) : data(std::move(_data)), left(nullptr), right(nullptr){}
};

template <typename T>
struct Base_Comparator{
    bool operator () (const T& l, const T& r){
        return l < r;
    }
};

template <typename T, class Comparator = Base_Comparator<T>>
class Tree{
    Node<T>* root;
    Comparator cmp;

public:
    Tree() : root(nullptr){}
    ~Tree(){
        std::stack<Node<T>*> st;
        st.push(root);

        while(!st.empty()){
            root = st.top();
            st.pop();

            if (root->left != nullptr)
                st.push(root->left);
            if (root->right != nullptr)
                st.push(root->right);
            delete root;
        }
    }

    void add(const T& item ){
        Node<T>* new_node = new Node<T>(item);
        if (root == nullptr){
            root = new_node;
            return;
        }

        Node<T>* tmp = root;
        Node<T>* parent = nullptr;

        while (tmp != nullptr){
            parent = tmp;
            if (item < tmp->data)
                tmp = tmp->left;
            else
                tmp = tmp->right;
        }
        if (item < parent->data)
            parent->left = new_node;
        else
            parent->right = new_node;
    }

    void post_order(std::ostream& out){
        std::stack<Node<T>*> st;
        auto tmp = root;
        Node<T>* last_visited = nullptr;

        while (!st.empty() || tmp != nullptr){
            if (tmp != nullptr){
                st.push(tmp);
                tmp = tmp->left;
            }
            else{
                auto peek = st.top();
                if (peek->right!= nullptr && last_visited != peek->right){
                    tmp = peek->right;
                }else{
                    out << peek->data << ' ' ;
                    last_visited = peek;
                    st.pop();
                }
            }
        }
    }
};


void answer(std::istream& in, std::ostream& out){
    Tree<int> tr;
    int N = 0;
    std::cin >> N;
    int m;
    for (int i = 0; i < N; ++i) {
        in >> m;
        tr.add(m);
    }
    tr.post_order(out);
}
