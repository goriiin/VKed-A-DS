#include <iostream>
#include <stack>
#include <queue>


void answer(std::istream &in, std::ostream &out);

int main() {
    answer(std::cin, std::cout);
    return 0;
}


struct Node {
    int data{};
    Node *left;
    Node *right;

    Node() : left(nullptr), right(nullptr) {}

    explicit Node(int _data) : data(_data), left(nullptr), right(nullptr) {}
};

template<typename T>
struct Base_Comparator {
    bool operator()(const T &l, const T &r) {
        return l < r;
    }
};


class Tree {
    Node *root;

public:
    Tree() : root(nullptr) {}

    ~Tree() {
        std::stack<Node *> st;
        st.push(root);

        while (!st.empty()) {
            root = st.top();
            st.pop();

            if (root->left != nullptr)
                st.push(root->left);
            if (root->right != nullptr)
                st.push(root->right);
            delete root;
        }
    }

    void add(const int &item) {
        Node *new_node = new Node(item);
        if (root == nullptr) {
            root = new_node;
            return;
        }

        Node *tmp = root;
        Node *parent = nullptr;

        while (tmp != nullptr) {
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


    bool areAllValuesEqual() {
        if (root == nullptr)
            return true;
        int val = root->data;
        std::stack<Node *> st;
        st.push(root);
        while (!st.empty()) {
            Node *curr = st.top();
            st.pop();
            if (curr->data != val) {
                return false;
            }
            if (curr->right != nullptr) {
                st.push(curr->right);
            }
            if (curr->left != nullptr) {
                st.push(curr->left);
            }
        }
        return true;
    }

    int shortest_dist() {
        if (root == nullptr) {
            return 0;
        }
        std::queue<std::pair<Node *, int>> q;
        q.push({root, 1});
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            if (curr.first->left == nullptr && curr.first->right == nullptr) {
                return curr.second;
            }
            if (curr.first->right != nullptr) {
                q.push({curr.first->right, curr.second + 1});
            }
            if (curr.first->left != nullptr) {
                q.push({curr.first->left, curr.second + 1});
            }
        }
        return -1;
    }

};


void answer(std::istream &in, std::ostream &out) {
    Tree tr;
    int value;
//    int N;
//    std::cin >> N;
//    for (int i = 0; i < N; ++i) {
//
//
//    }
    while (std::cin >> value) {
        tr.add(value);
    }

    std::cout << tr.shortest_dist() << std::endl;
}
