//Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
//Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
//Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
//Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.


//1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
//g(k, i)=g(k, i-1) + i (mod m), m - степень двойки.

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cassert>

/*
+ в
OK
+dsgnmdf
OK
+ fkdnbn
OK
+d
OK
+d
FAIL
+d
FAIL
+q
OK
+q
FAIL
+w
OK
+e
OK
+r
OK
+r
FAIL
+r
FAIL
+t
OK
+u
OK

+u
FAIL
+d
FAIL
+s
OK
+a
OK
- fkdnbn
OK
- fkdnbn
FAIL
? fkdnbn
FAIL
? t
OK
- t
OK
+ t
OK
- t
OK
+ t
OK
+ t
FAIL
- a
OK
+ a
OK
+ a
FAIL
? a
OK
? dsgnmdf
OK
- dsgnmdf
OK
- dsgnmdf
FAIL
 */

/*+ ok
OK
+ ok
FAIL
- ok
OK
? ok
FAIL
+ a
OK
+ a
FAIL
+ a
FAIL
+ a
FAIL
 */

void answer(std::istream &in, std::ostream &out);

int main() {
    answer(std::cin, std::cout);
    return 0;
}

template<typename T>
struct [[maybe_unused]] Base_Hasher {
    size_t operator()(T item, size_t m = 8, size_t a = 241) {
        size_t hash = 0;
        while (item > 0) {
            hash = (hash * a + item % 10) % m;
            item /= 10;
        }
        return hash;
    }
};

struct String_Hasher {
    size_t operator()(const std::string &str, size_t m = 8, size_t a = 241) {
        size_t hash = 0;
        for (auto &ch: str) {
            hash = (hash * a + ch) % m;
        }
        return hash;
    }

};

enum status {
    deleted,
    nil,
    key
};

template<typename T>
struct table_item {
    T data;
    status flag;

    table_item() : flag(status::nil) {}

    table_item(T _data, status _flag) : data(std::move(_data)), flag(_flag) {}

    table_item(table_item<T> &&item) noexcept {
        data = std::move(item.data);
        flag = std::move(item.flag);
    }

    table_item<T> &operator=(table_item &&item) noexcept {
        this->data = std::move(item.data);
        this->flag = std::move(item.flag);
        return *this;
    }
};

template<typename T, class Hasher=Base_Hasher<T>>
class HashTable {
    std::vector<table_item<T>> data{};
    size_t max_size;
    Hasher hasher;
    size_t items_count = 0;
    double RATIO  = ((double)3)/4;

    void rehash() {
        auto new_table = HashTable<T, Hasher>(data.size() * 2);
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i].flag == status::key)
                new_table.add(std::move(data[i].data));
        }
        *this = std::move(new_table);
    }
    size_t next(size_t index, size_t iteration){
        return (index + iteration * iteration)%data.size();
    }
public:
    HashTable() {
        data.resize(8);
        max_size = static_cast<int>(8 * RATIO);
    }

    [[maybe_unused]] explicit HashTable(size_t _size) {
        data.resize(_size);
        max_size = static_cast<size_t>(RATIO * _size);
    }

    bool del(const T &item) {
        size_t ind = hasher(item, data.size());

        for (size_t i = 0; i < data.size(); ++i) {
            ind = next(ind, i);

            if (data[ind].flag == status::nil) {
                return false;
            }

            if (data[ind].flag == status::key && data[ind].data == item) {
                data[ind].flag = status::deleted;
                --items_count;
                return true;
            }
        }

        return false;
    }

    bool add(const T &item) {
        int deleted_ind = -1;
        size_t ind = hasher(item, data.size());
        auto insert_item = table_item(item, status::key);

        for (size_t i = 0; i < data.size(); ++i) {
            ind = next(ind, i);
            if (data[ind].flag == status::key && data[ind].data == item) {
                return false;
            }

            if (data[ind].flag == status::nil) {
                ++items_count;
                if (items_count >= max_size)
                    rehash();

                if (deleted_ind > 0)
                    data[deleted_ind] = std::move(insert_item);
                else
                    data[ind] = std::move(insert_item);

                return true;
            }

            if (deleted_ind < 0 && data[i].flag == status::deleted) {
                deleted_ind = static_cast<int>(i);
            }
        }
        return false;
    }

    bool has(const T &item) {
        size_t ind = hasher(item, data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            ind = next(ind, i);
            if (data[ind].flag == status::nil)
                return false;

            if (data[ind].flag == status::key && data[ind].data == item) {
                return true;
            }
        }
        return false;
    }

};

void answer(std::istream &in, std::ostream &out) {
    HashTable<std::string, String_Hasher> table;

    std::string word;
    char op;
    while (in >> op >> word) {
        switch (op) {
            case '+':
                out << (table.add(word) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                out << (table.del(word) ? "OK" : "FAIL") << std::endl;
                break;
            case '?':
                out << (table.has(word) ? "OK" : "FAIL") << std::endl;
                break;
            default:
                assert(false);
        }
    }
}
