#include <iostream>

template<typename T1, typename T2>
struct pair {
    T1 first;
    T2 second;

    pair() = default;

    pair(T1 f, T2 s) : first(f), second(s) {}
};

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

    [[maybe_unused]] explicit vector(int size) : data(new T[size]), cap(size) {}

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

    [[nodiscard]] bool empty() const {
        return len == 0;
    }

    [[nodiscard]] int size() const {
        return len;
    }

    [[maybe_unused]] [[nodiscard]] int capacity() const {
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

    [[maybe_unused]] T &get(unsigned int index) {
        return data[index];
    }

    [[maybe_unused]] [[nodiscard]] T &get(unsigned int index) const {
        return data[index];
    }

    T &operator[](int index) {
        return data[index];
    }

    T &operator[](int index) const {
        return data[index];
    }

    [[maybe_unused]] void reserve(int new_cap) {
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

void swap(uint64_t& l, uint64_t& r){
    auto tmp = l;
    l = r;
    r = tmp;
}

bool bit(uint64_t num, unsigned short digit) {
    return ((num >> digit) & 1);
}

int BitsCount(uint64_t num) {
    for (int i = sizeof(int64_t) * 8 - 1; i >= 0; --i) {
        if (bit(num, i)) {
            return i;
        }
    }
    return 0;
}

int findMax(vector<uint64_t> &arr) {
    uint64_t max = arr[0];
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return (int)max;
}

void MSD_sort(vector<uint64_t> &arr, pair<int, int> lim, int bit_ptr) {
    if (lim.second <= lim.first || bit_ptr < 0)
        return;
    int l = lim.first, r = lim.second;
    while (l != r){
        while(!bit(arr[l], bit_ptr) && l < r){++l;}
        while (bit(arr[r], bit_ptr) && l < r){--r;}
        if (l < r)
            swap(arr[l], arr[r]);
    }
    if (!bit(arr[r], bit_ptr))
        ++r;

    MSD_sort(arr, {lim.first, r-1}, --bit_ptr);
    MSD_sort(arr, {r, lim.second}, --bit_ptr);
}

void answer() {
    int N;
    std::cin >> N;
    vector<uint64_t> arr;

    arr.input(std::cin, N);
    int bit_ptr = BitsCount(findMax(arr));

    MSD_sort(arr, {0, arr.size() - 1}, bit_ptr);
    arr.out(std::cout);
}

int main() {
    answer();
    return 0;
}

