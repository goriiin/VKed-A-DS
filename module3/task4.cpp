#include <iostream>
#include <array>
#include <unordered_map>
#include <queue>
#include <unordered_set>

int run(std::istream& in, std::ostream& out);

int main(){
    run(std::cin, std::cout);
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

const field_array EMPTY_STATE = {
        0, 0, 0, 0,//2+1 % 3 == 0
        0, 0, 0, 0,//5+1 % 3 == 0
        0, 0, 0, 0,//8
        0, 0, 0, 0//8
};

class field_state {
public:
    field_state() : state(), zero_pos(0), h(0), move(' ') {}

    field_state(const field_array &arr, char m = ' ') : state(arr),  h(0), move(m) {
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
        return h > other.h;
    }

    int get_f() const {
        return h;
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
    int h;
    field_array state;
    int zero_pos;
    char move;
private:
    int count_inversions() const {
        int inversions = 0;
        for (int i = 0; i < FIELD_SIZE - 1; ++i) {
            for (int j = i + 1; j < FIELD_SIZE; ++j) {
                if (state[i] != 0 && state[j] != 0 && state[i] > state[j]) {
                    inversions++;
                }
            }
        }
        return inversions;
    }

    int manhattan_distance(int pos1, int pos2) const {
        int row1 = pos1 / LINE_SIZE;
        int col1 = pos1 % LINE_SIZE;
        int row2 = pos2 / LINE_SIZE;
        int col2 = pos2 % LINE_SIZE;
        return abs(row1 - row2) + abs(col1 - col2);
    }

    field_state move_left() const {
        field_state next = *this;
        std::swap(next.state[zero_pos], next.state[zero_pos - 1]);
        next.zero_pos--;
        next.move = 'R';
        return next;
    }

    field_state move_right() const {
        field_state next = *this;
        std::swap(next.state[zero_pos], next.state[zero_pos + 1]);
        next.zero_pos++;
        next.move = 'L';
        return next;
    }

    field_state move_down() const {
        field_state next = *this;
        std::swap(next.state[zero_pos], next.state[zero_pos + LINE_SIZE]);
        next.zero_pos += LINE_SIZE;
        next.move = 'U';
        return next;
    }

    field_state move_up() const {
        field_state next = *this;
        std::swap(next.state[zero_pos], next.state[zero_pos - LINE_SIZE]);
        next.zero_pos -= LINE_SIZE;
        next.move = 'D';
        return next;
    }
};

// Структура для сравнения состояний в очереди с приоритетом
struct field_state_comparator {
    bool operator()(const field_state &a, const field_state &b) const {
        return a.get_f() > b.get_f();
    }
};

// Хеш-функция для field_state (необходима для unordered_set)
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
    const field_state empty(EMPTY_STATE);


    if (!start.is_solve()) {
        out << "-1\n";
        return;
    }

    std::priority_queue<field_state, std::vector<field_state>, field_state_comparator> q;
    std::unordered_set<field_state, field_state_hash> visited;
    std::unordered_map<field_state, field_state, field_state_hash> parents;

    q.push(start);

    while (!q.empty()) {
        field_state current = q.top();
        q.pop();

        if (visited.find(current) != visited.end()) {
            continue;
        }

        visited.insert(current);

        if (current.state == GOAL_STATE) {
            std::string path;
            while (current.move != ' ') {
                path = current.move + path;
                current = parents[current];
            }
            out << path.length() << std::endl;
            out << path << std::endl;
            return;
        }

        for (auto &neighbor: current.get_next_vertices()) {
            if (visited.find(neighbor) == visited.end()) {

                if (parents.find(neighbor) == parents.end()) {
                    parents[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }
    }
    out << "-1\n";
}

int run(std::istream& in, std::ostream& out) {
    field_array start_state;
    for (int i = 0; i < FIELD_SIZE; ++i) {
        std::cin >> start_state[i];
    }

    field_state start(start_state);
    a_star(start, out);
    return 0;
}