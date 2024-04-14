#include <iostream>
//7_3. Binary MSD для long long.
//Дан массив неотрицательных целых 64-разрядных чисел.
// Количество чисел не больше 106. Отсортировать массив методом MSD по битам (бинарный QuickSort).
using uint64 = unsigned long long;

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

template<typename T>
void swap(T& l, T& r){
    auto tmp = l;
    l = r;
    r = tmp;
}

bool bit(uint64 num, unsigned short digit) {
    return num & ((uint64)1 << digit);
}

void MSD_sort(vector<uint64> &arr, pair<int, int> lim, int bit_ptr) {
    if (lim.second <= lim.first || bit_ptr < 0)
        return;

    int l = lim.first, r = lim.second;
    while (l != r){
        while(!bit(arr[l], bit_ptr) && (l < r)) ++l;
        while (bit(arr[r], bit_ptr) && (l < r)) --r;
        swap(arr[l], arr[r]);
    }

    if (!bit(arr[lim.second], bit_ptr))
        ++r;

    MSD_sort(arr, {lim.first, r-1}, bit_ptr - 1);
    MSD_sort(arr, {r, lim.second}, bit_ptr - 1);
}

void answer(std::istream& in, std::ostream& out)  {
    int N;
    std::cin >> N;
    vector<uint64> arr;

    arr.input(in, N);

    MSD_sort(arr, {0, arr.size() - 1}, 63);
    arr.out(out);
}

int main() {
    answer(std::cin, std::cout);
    return 0;
}

