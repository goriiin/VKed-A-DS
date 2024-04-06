#include <iostream>
#include <cmath>

template<typename T>
class vector {
    T *data = nullptr;
    unsigned int cap = 0;
    unsigned int len = 0;
public:
    void input(std::istream &in, int count) {
        T elem;
        for (int i = 0; i < count; ++i) {
            in >> elem;
            this->push_back(elem);
        }
    }

    void out(std::ostream &out) const {
        for (int i = 0; i < len; ++i)
            out << data[i] << " ";
        out << std::endl;
    }

    vector() = default;

    vector &operator=(const vector &other) {
        if (this == &other) {
            return *this;
        }

        delete[] data;

        len = other.len;
        cap = other.cap;
        data = new T[cap];

        for (unsigned int i = 0; i < len; ++i) {
            data[i] = other.data[i];
        }

        return *this;
    }

    explicit vector(int size) : data(new T[size]), cap(size) {}

    vector(const vector &other) : data(new T[other.cap]), len(other.len), cap(other.cap) {
        for (int i = 0; i < len; ++i) {
            data[i] = other.data[i];
        }
    }

    ~vector() {
        delete[] data;
    }

    vector(vector &&vec) = delete;

    vector operator=(vector &&vec) = delete;

    bool empty() const {
        return len == 0;
    }

    unsigned int size() const {
        return len;
    }

    unsigned int capacity() const {
        return cap;
    }

    void resize(int new_cap) {
        T *new_data = new T[new_cap];
        for (int i = 0; i < len & i < new_cap; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;
        cap = new_cap;
        data = new_data;
    }

    T &get(unsigned int index) {
        return data[index];
    }

    T &get(unsigned int index) const {
        return data[index];
    }

    T &operator[](int index) {
        return data[index];
    }

    T &operator[](int index) const {
        return data[index];
    }

    void reserve(int new_cap) {
        if (new_cap < cap) {
            return;
        }

        T new_data = new T[new_cap];
        for (int i = 0; i < len; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;

        cap = new_cap;
        data = new_data;
    }

    void push_back(const T &num) {
        if (cap == 0) {
            this->resize(1);
        } else if (len == cap) {
            this->resize(cap * 2);
        }

        data[len++] = num;
    }

    void pop_back() {
        if (len == 0)
            return;

        --len;
        if (len == cap / 4) {
            this->resize(cap / 4);
        }
    }
};

struct point {
    int x, y;

    bool operator<(const point &other) const {
        if (this->x != other.x)
            return this->x < other.x;
        return this->y < other.y;
    }

    friend std::ostream &operator<<(std::ostream &out, point p) {
        out << p.x << " " << p.y;
        return out;
    }
};

bool comparePoints(const point& a, const point& b, const point& start) {
    point vectorA = {a.x - start.x, a.y - start.y};
    point vectorB = {b.x - start.x, b.y - start.y};

    double angleA = atan2(vectorA.y, vectorA.x);
    double angleB = atan2(vectorB.y, vectorB.x);

    return angleA > angleB;
}


template<typename T>
struct BaseFunctor {
    bool operator()(const T &l, const T &r) {
        return l < r;
    }
};

struct PointCmp {
    point min;

    bool operator()(const point &l, const point &r) {
        return comparePoints(l, r, min);
    }
};

template<typename T, class Comparator = BaseFunctor<T>>
void insertion_sort(vector<T> &arr, Comparator cmp = Comparator()) {
    int ptr = 0;

    for (int i = 1; i < arr.size(); ++i) {
        for (int j = i; j > 0 && cmp(arr[j - 1], arr[j]); --j) {
            ++ptr;
            std::swap(arr[j - 1], arr[j]);
        }
    }
}

void answer(std::istream &in, std::ostream &out) {
    int N;
    in >> N;
    vector<point> arr;

    for (int i = 0; i < N; ++i) {
        int x, y;
        in >> x >> y;
        arr.push_back({x, y});
    }

    point min = arr[0];

    for (int i = 1; i < N; ++i) {
        if (arr[i] < min)
            min = arr[i];
    }

    PointCmp cmp{};
    cmp.min = min;
    insertion_sort(arr, cmp);

    arr.out(out);
}

int main() {
    answer(std::cin, std::cout);
}