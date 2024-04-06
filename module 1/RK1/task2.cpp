#include <iostream>
#include <string>


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

template<typename T>
class stack {
    vector<T> data;
public:
    void push(T num) {
        data.push_back(num);
    }

    T pop() {
        if (data.size() == 0)
            return -1;
        auto num = data[data.size() - 1];
        data.pop_back();

        return num;
    }

    T size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }
};


void answer(std::istream &in, std::ostream &out) {
    stack<char> st;
    std::string inp;

    in >> inp;

    for (auto& ch: inp){
        if (ch == '('){
            st.push(ch);
        }else
            st.pop();
    }

    if (st.empty()){
        out << "YES\n";
        return;
    }
    out << "NO";
}

int main() {
    answer(std::cin, std::cout);
}
