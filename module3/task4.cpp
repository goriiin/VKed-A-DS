#include <iostream>
#include <array>
#include <unordered_map>
#include <set>
#include <vector>
#include <unordered_set>

void run(std::istream &in, std::ostream &out);

int main() {
    run(std::cin, std::cout);
    return 0;
}

const size_t LINE_SIZE = 4;
const size_t FIELD_SIZE = LINE_SIZE * LINE_SIZE;

using field_array = std::array<int, FIELD_SIZE>;

const field_array GOAL_STATE = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 0
};

class field_state {
public:
    field_state() : state(), zero_pos(0), g(0), h(0), move(' ') {}

    field_state(const field_array &arr, char m = ' ') : state(arr), g(0), h(0), move(m) {
        for (int i = 0; i < FIELD_SIZE; ++i) {
            if (state[i] == 0) {
                zero_pos = i;
                break;
            }
        }
        calculate_heuristic();
    }

    bool operator==(const field_state &other) const {
        return state == other.state;
    }

    bool operator<(const field_state &other) const {
        if (g + h != other.g + other.h) {
            return (g + h) < (other.g + other.h);
        } else {
            return move < other.move;
        }
    }

    int get_f() const {
        return g + h;
    }

    void calculate_heuristic() {
        h = 0;
        for (size_t i = 0; i < FIELD_SIZE; ++i) {
            if (state[i] != 0) {
                h += manhattan_distance(i, state[i] - 1);
            }
        }
    }

    std::vector<field_state> get_next_vertices() const {
        std::vector<field_state> result;

        if (zero_pos >= LINE_SIZE) {
            result.push_back(move_up());
        }
        if (zero_pos < FIELD_SIZE - LINE_SIZE) {
            result.push_back(move_down());
        }
        if (zero_pos % LINE_SIZE != 0) {
            result.push_back(move_left());
        }
        if ((zero_pos + 1) % LINE_SIZE != 0) {
            result.push_back(move_right());
        }

        return result;
    }

    // (n + k) % 2 != 0 ? (решения нет) : (решение есть)
    // k - номер строки с нулем, нумеруем с 1,
    // n - количество элементов больше чем iый, стоит до него
    bool is_solve() const {
        auto k = zero_pos / LINE_SIZE + 1;
        auto n = count_inversions();
        return (n + k) % 2 == 0;
    }

    int g;
    int h;
    field_array state;
    int zero_pos;
    char move;
private:
    int manhattan_distance(int pos1, int pos2) const {
        int row1 = pos1 / LINE_SIZE;
        int col1 = pos1 % LINE_SIZE;
        int row2 = pos2 / LINE_SIZE;
        int col2 = pos2 % LINE_SIZE;
        return abs(row1 - row2) + abs(col1 - col2);
    }

    int count_inversions() const {
        int inversions = 0;
        for (int i = 0; i < FIELD_SIZE - 1; ++i) {
            if (state[i] == 0) {
                continue;
            }
            for (int j = i + 1; j < FIELD_SIZE; ++j) {
                if (state[j] == 0) {
                    continue;
                }
                if (state[i] > state[j]) {
                    inversions++;
                }
            }
        }
        return inversions;
    }

    field_state move_left() const {
        field_state next = *this;
        std::swap(next.state[zero_pos], next.state[zero_pos - 1]);
        next.zero_pos--;
        next.g++;
        next.move = 'R';
        next.calculate_heuristic();
        return next;
    }

    field_state move_right() const {
        field_state next = *this;
        std::swap(next.state[zero_pos], next.state[zero_pos + 1]);
        next.zero_pos++;
        next.g++;
        next.move = 'L';
        next.calculate_heuristic();
        return next;
    }

    field_state move_down() const {
        field_state next = *this;
        std::swap(next.state[zero_pos], next.state[zero_pos + LINE_SIZE]);
        next.zero_pos += LINE_SIZE;
        next.g++;
        next.move = 'U';
        next.calculate_heuristic();
        return next;
    }

    field_state move_up() const {
        field_state next = *this;
        std::swap(next.state[zero_pos], next.state[zero_pos - LINE_SIZE]);
        next.zero_pos -= LINE_SIZE;
        next.g++;
        next.move = 'D';
        next.calculate_heuristic();
        return next;
    }
};

struct field_state_hash {
    size_t operator()(const field_state &fs) const {
        size_t hash = 0;
        for (int i = 0; i < FIELD_SIZE; ++i) {
            hash = hash * 31 + fs.state[i];
        }
        return hash;
    }
};

void a_star(const field_state &start, std::ostream &out) {
    const field_state goal(GOAL_STATE);

    if (!start.is_solve()) {
        out << "-1\n";
        return;
    }

    std::set<field_state> q;
    std::unordered_set<field_state, field_state_hash> visited;
    std::unordered_map<field_state, field_state, field_state_hash> parents;

    q.insert(start);
    parents[start] = start;

    while (!q.empty()) {
        auto it = q.begin();
        field_state current = *it;
        q.erase(it);

        if (current == goal) {
            std::string path;
            while (!(current == parents[current])) {
                path = current.move + path;
                current = parents[current];
            }
            out << path.length() << std::endl;
            out << path << std::endl;
            return;
        }

        if (visited.find(current) != visited.end()) {
            continue;
        }

        visited.insert(current);

        for (auto &neighbor: current.get_next_vertices()) {
            if (visited.find(neighbor) == visited.end()) {
                int new_g = current.g + 1;
                if (parents.find(neighbor) == parents.end() || new_g < neighbor.g) {
                    neighbor.g = new_g;
                    parents[neighbor] = current;

                    if (q.find(neighbor) != q.end()) {
                        q.erase(neighbor);
                    }

                    q.insert(neighbor);
                }
            }
        }
    }
    out << "-1\n";
}

void run(std::istream &in, std::ostream &out) {
    field_array start_state;
    for (int i = 0; i < FIELD_SIZE; ++i) {
        in >> start_state[i];
    }

    field_state start(start_state);
    a_star(start, out);
}