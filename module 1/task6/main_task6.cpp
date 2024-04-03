#include <iostream>

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

    void out(std::ostream &out)const {
        for (int i = 0; i < len; ++i)
            out << data[i] << " ";
        out << std::endl;
    }

    vector() = default;
    vector& operator=(const vector& other) {
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

    T& get(unsigned int index) {
        return data[index];
    }

    T& get(unsigned int index) const {
        return data[index];
    }

    T& operator[](int index) {
        return data[index];
    }

    T& operator[](int index) const{
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

    void push_back(const T& num) {
        if (cap == 0){
            this->resize(1);
        }
        else if (len == cap) {
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

template <typename T>
struct BaseFunctor {
    bool operator () (const T& l, const T& r){
        return l < r;
    }
};

template <typename T, class Comparator = BaseFunctor<T>>
int med(vector<T>& arr, int l, int r, Comparator cmp = Comparator()){
    int mid = (r+l - 1)/2;
    T a = arr[l], b = arr[r-1], c = arr[mid];

    // b < a
    if (cmp(b, a)){
        // a < c
        if (cmp(a, c))
            // b < a < c
            return l;
        if (cmp(b, c))
            return mid;
        // b < c < a
        return r-1;
    }
    if (cmp(b,c))
        // a < b < c
        return r-1;

    // находим меньшее
    return (cmp(c, a) ? l:mid);
}

template <typename T, class Comparator = BaseFunctor<T>>
int partition(vector<T>& arr, int l, int r, Comparator cmp = Comparator()) {
    std::swap( arr[r-1], arr[med(arr,l,r,cmp)] );
    T& pivot = arr[r-1];
    // i -- начало, j -- конец группы > pivot
    int i = l, j = l;

    // пока не дойдем до элемента предшетствующего pivot
    while (j < r-1){
        if (cmp(arr[j], pivot)) {
            std::swap(arr[i++], arr[j]);
        }
        ++j;
    }

    std::swap( arr[i], arr[r - 1] );
    return i;
}

template <typename T, typename Comparator = BaseFunctor<T>>
T kth_element(vector<T>& arr, int k, Comparator cmp = Comparator())
{
    int l = 0;
    int r = arr.size();

    while(true) {
        int m = partition(arr, l, r, cmp);
        if (k == m) {
            return arr[m];
        } else if (k < m) {
            r = m;
        } else { // k > m
            l = m + 1;
        }
    }
}

void answer(std::istream& in, std::ostream& out){
    int N;
    in >> N;
    vector<int> arr;
    arr.input(in, N);

    int p10 = arr.size() / 10, p50 = arr.size()/2, p90 = arr.size() * 9/10;

    out << kth_element(arr, p10) << std::endl;
    out << kth_element(arr, p50) << std::endl;
    out<< kth_element(arr, p90) << std::endl;
}


int main(){
    answer(std::cin, std::cout);
}