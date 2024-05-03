#include <unordered_set>
#include <string>
#include <iostream>

struct Node {
    std::string product_name;
    int color;
    int size;
};

int string_hasher(const std::string &str, size_t a = 241) {
    size_t hash = 0;
    for (auto &ch: str) {
        hash = (hash * a + ch);
    }
    return hash;
}

namespace std {
    template<>
    struct hash<Node> {
        size_t operator()(const Node& node) const {
            size_t _hash = 0;
            _hash = _hash * 31 + string_hasher(node.product_name);
            _hash = _hash * 31 + hash<int>()(node.color);
            _hash = _hash * 31 + hash<int>()(node.size);
            return _hash;
        }
    };
}

bool operator==(const Node &lhs, const Node &rhs) {
    return lhs.product_name == rhs.product_name && lhs.color == rhs.color && lhs.size == rhs.size;
}

int main() {
    std::unordered_set<Node> node_set;

    std::string operation;
    Node node;
    while (std::cin >> operation >> node.product_name >> node.color >> node.size) {
        if (operation == "+") {
            if (node_set.insert(node).second) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "FAIL" << std::endl;
            }
        } else if (operation == "-") {
            if (node_set.erase(node) > 0) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "FAIL" << std::endl;
            }
        } else if (operation == "?") {
            if (node_set.find(node) != node_set.end()) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "FAIL" << std::endl;
            }
        }
    }

    return 0;
}