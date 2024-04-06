//Группа людей называется современниками если был такой момент, когда они могли собраться вместе. Для этого в этот момент каждому из них должно было уже исполниться 18 лет, но ещё не исполниться 80 лет. Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников. В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
//Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях принимать участие в собраниях он не мог.
//
//Формат ввода
//Сначала на вход программы поступает число N — количество людей (меньше 10000).
//Далее в N строках вводится по 6 чисел — первые три задают дату (день, месяц, год) рождения, следующие три — дату смерти (она всегда не ранее даты рождения). День (в зависимости от месяца, а в феврале — еще и года) от 1 до 28, 29, 30 или 31, месяц — от 1 до 12, год — от 1 до 2005.
//Формат вывода
//Единственное число – максимальное количество современников.


#include <iostream>

void answer(std::istream &in, std::ostream &out);

///test1
//4
//2 2 1975 5 5 2010
//3 3 1920 4 4 1990
//4 12 2010 3 1 2050
//5 3 1986 6 6 2045

// out : 2

//test2
//2
//1 1 1990 1 1 2060
//1 1 2020 1 1 2080

//out : 2

//test3
//5
//2 3 1950 5 5 2000
//3 4 1985 6 6 2030
//1 1 1970 2 2 2010
//4 7 1995 3 12 2040
//5 11 1910 3 5 1940

//out : 3

//test4
//4
//2 2 1970 5 5 2010
//3 3 1920 4 4 2020
//1 1 2000 1 1 2080
//4 6 1955 3 3 1990

//out : 3

//test 5
//1
//1 1 1930 1 1 1980

//out : 1

// test 6
//3
//1 1 2000 1 1 2010
//3 3 1970 5 5 2040
//2 2 1960 4 4 2030

//out : 2

//test 7
//2
//2 3 1980 4 5 2020
//1 2 1960 3 4 1980

// out 1

int main() {
    answer(std::cin, std::cout);
    return 0;
}

struct line {
    int start;
    int end;
};

template<typename T>
struct BaseFunctor {
    bool operator()(const T &l, const T &r) {
        return l < r;
    }
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

template<typename T, class Compare = BaseFunctor<T>>
void merge(vector<T> &original, const line &left, const line &right, Compare cmp = BaseFunctor<T>()) {
    int l_ptr = 0, r_ptr = 0;
    vector<T> left_buf, right_buf;
    for (int i = left.start; i <= left.end; ++i) {
        left_buf.push_back(original[i]);
    }

    for (int i = right.start; i <= right.end; ++i) {
        right_buf.push_back(original[i]);
    }

    for (int i = left.start; i <= right.end; ++i) {
        if (l_ptr >= left_buf.size()) {
            original[i] = right_buf[r_ptr++];
        } else if (r_ptr >= right_buf.size()) {
            original[i] = left_buf[l_ptr++];
        } else if (cmp(left_buf[l_ptr], right_buf[r_ptr])) {
            original[i] = left_buf[l_ptr++];

        } else {
            original[i] = right_buf[r_ptr++];
        }
    }
}

template<typename T, class Compare = BaseFunctor<T>>
void mergeSort(vector<T> &array, Compare cmp = BaseFunctor<T>()) {
    int split_size = 1, size = array.size();

    while (split_size < size) {
        for (int i = 0; i < size - split_size; i += 2 * split_size) {
            merge(
                    array,
                    {i, i + split_size - 1},
                    {i + split_size, std::min(i + 2 * split_size - 1, size - 1)},
                    cmp
            );
        }
        split_size *= 2;
    }
}

class date {
    int day;
    int month;
    int year;
    int begin;

public:

    int getDay() const {
        return day;
    }

    int getMonth() const {
        return month;
    }

    int getYear() const {
        return year;
    }

    void setBegin() {
        this->begin = 1;
    }

    void setEnd() {
        this->begin = -1;
    }


    [[nodiscard]] bool isBegin() const {
        return (begin == 1);
    }

    date():day(1), month(1), year(1){
        begin = true;
    };

    date(int _day, int _month, int _year) :
            day(_day), month(_month), year(_year) {
        if (month == 2 && !isLeapYear(year) && day == 29) {
            ++month;
            day = 1;
        }
        begin = 1;
    }

    date(int _day, int _month, int _year, int _begin) :
            day(_day), month(_month), year(_year), begin(_begin) {
        if (month == 2 && !isLeapYear(year) && day == 29) {
            ++month;
            day = 1;
        }
    }


    bool operator<(const date &other) const {
        if (this->year != other.year)
            return this->year < other.year;

        if (this->month != other.month)
            return this->month < other.month;

        if (this->day != other.day)
            return this->day < other.day;

        return this->begin < other.begin;
    }

    bool operator>(const date &other) const {
        return other < *this;
    }

    bool operator==(const date &other) const {
        return (
                (this->day == other.day) &&
                (this->month == other.month) &&
                (this->year == other.year)
        );
    }

    bool operator!=(const date &other) const {
        return !(*this == other);
    }

    static int daysInMonth(int month, int year) {
        if (month == 2) {
            if (isLeapYear(year)) {
                return 29;
            } else {
                return 28;
            }
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            return 30;
        } else {
            return 31;
        }
    }

    static bool isLeapYear(int _year) {
        return (_year % 4 == 0 && _year % 100 != 0) || (_year % 400 == 0);
    }

    friend std::ostream &operator<<(std::ostream &out, date &d) {
        if (d.isBegin())
            out << "begin: ";
        else
            out << "end: ";

        out << d.day << " " << d.month << " " << d.year;

        return out;
    }
};

bool makeLegit(date &begin, date &end) {
    if (end == begin)
        return false;

    auto y18 = date(begin.getDay(), begin.getMonth(), begin.getYear() + 18);

    if (end < y18 || y18 == end)
        return false;

    auto y80 = date(begin.getDay(), begin.getMonth(), begin.getYear() + 80, -1);
    if (end > y80)
        end = y80;
    begin = y18;

    return true;
}

void answer(std::istream &in, std::ostream &out) {
    vector<date> arr;
    int N;
    in >> N;

    for (int i = 0; i < N; ++i) {
        int day, month, year;
        in >> day >> month >> year;
        date d1(day, month, year, 1);
        in >> day >> month >> year;
        date d2(day, month, year, -1);

        if (makeLegit(d1, d2)) {
            arr.push_back(d1);
            arr.push_back(d2);
        }
    }
    mergeSort(arr);

    int max_count = 0, count = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i].isBegin()) {
            ++count;
            if (count > max_count)
                max_count = count;
        } else {
            if (count > max_count)
                max_count = count;
            --count;
        }
    }
    out << max_count << std::endl;
}