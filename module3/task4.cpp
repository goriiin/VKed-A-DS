#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <queue>

void run(std::istream &in, std::ostream &out);

int main() {
    run(std::cin, std::cout);
}


static const size_t LINE_SIZE = 4;
static const size_t FIELD_SIZE = LINE_SIZE * LINE_SIZE;

using field_array = std::array<uint8_t, FIELD_SIZE>;

const field_array EMPTY_STATE = {
        0, 0, 0, 0,  //2+1 % 3 == 0
        0, 0, 0, 0,  //5+1 % 3 == 0
        0, 0, 0, 0,  //8
        0, 0, 0, 0   //8

};

const field_array GOAL_STATE = {
        1, 2, 3, 4,   //0
        5, 6, 7, 8,   //3
        9, 10, 11, 12,
        13, 14, 15, 0//6 % 3 == 0
};

class field_state {
public:
    field_state() : state(EMPTY_STATE), zero_pos(0) {};

    field_state(const field_array &arr, uint8_t zero = 0) : state(arr), zero_pos(zero) {
        for (uint8_t i = 0; i < arr.size(); ++i)
            if (arr[i] == 0) {
                zero_pos = i;
                break;
            }
    }

    std::vector<field_state> get_next_vertices() const {
        std::vector<field_state> res;
        if (zero_pos < LINE_SIZE) { // UP
            res.push_back(move_up());
        }

        if (zero_pos < FIELD_SIZE - LINE_SIZE) { // DOWN
            res.push_back(move_down());
        }

        if (zero_pos % LINE_SIZE == 0) { // LEFT
            res.push_back(move_left());
        }

        if ((zero_pos + 1) % LINE_SIZE != 0) { // RIGHT
            res.push_back(move_right());
        }

        return res;
    }

    bool operator==(const field_state &r) const {
        return state == r.state;
    }

    bool operator!=(const field_state &r) const {
        return state != r.state;
    }

    bool operator<(const field_state &r) const {
        return state < r.state;
    }

    void print() const {
        for (int i = 0; i < state.size(); ++i) {
            std::cout << (int) state[i] << " ";
            if ((i + 1) % LINE_SIZE == 0) {
                std::cout << std::endl;
            }
        }
    }

private:
    field_state move_left() const {
        field_state fs(*this);
        uint8_t new_zero_pos = fs.zero_pos - 1;
        std::swap(fs.state[fs.zero_pos], fs.state[new_zero_pos]);
        fs.zero_pos = new_zero_pos;

        return fs;
    }

    field_state move_right() const {
        field_state fs(*this);
        uint8_t new_zero_pos = fs.zero_pos + 1;
        std::swap(fs.state[fs.zero_pos], fs.state[new_zero_pos]);
        fs.zero_pos = new_zero_pos;

        return fs;
    }

    field_state move_down() const {
        field_state fs(*this);
        uint8_t new_zero_pos = fs.zero_pos + LINE_SIZE;
        std::swap(fs.state[fs.zero_pos], fs.state[new_zero_pos]);
        fs.zero_pos = new_zero_pos;

        return fs;
    }

    field_state move_up() const {
        field_state fs(*this);
        uint8_t new_zero_pos = fs.zero_pos - LINE_SIZE;
        std::swap(fs.state[fs.zero_pos], fs.state[new_zero_pos]);
        fs.zero_pos = new_zero_pos;
        return fs;
    }

    field_array state;
    uint8_t zero_pos;
};

void bfs(field_state &start) {
    const field_state goal(GOAL_STATE);
    const field_state empty(EMPTY_STATE);

    // по first будем проверять были ли мы в этом state, также будем использовать для отмотки пути
    std::queue<field_state> q;
    std::map<field_state, field_state> parents;// TO - FROM

    parents.insert(std::make_pair(start, empty));
    field_state cur(EMPTY_STATE);
    q.push(start);

    while (!q.empty()) {
        cur = q.front();
        q.pop();

        if (cur == goal)
            break;

        std::vector<field_state> children = cur.get_next_vertices();
        for (auto &child: children) {
            if (parents.find(child) == parents.end()) {
                parents.insert(std::make_pair(child, cur));
                q.push(child);
            }
        }
    }
    int step_count = 0;
    if (cur == goal) {
        while (cur != empty) {
            ++step_count;
            cur.print();

            auto it = parents.find(cur);
            cur = it->second;
            std::cout << "--------------------------------" << std::endl;
        }
        std::cout << "Solution found, steps_count=" << step_count << std::endl;
    } else {
        std::cout << "Solution NOT found, vertices count=" << parents.size() << std::endl;
    }
}

void run(std::istream &in, std::ostream &out) {
    field_state start({
                              1, 2, 3, 0,
                              5, 6, 7, 4,
                              9, 10, 11, 8,
                              13, 14, 15, 12,
                      });
    bfs(start);
}