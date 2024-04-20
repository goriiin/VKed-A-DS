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

void answer(std::istream &in, std::ostream &out);


int main() {
    answer(std::cin, std::cout);
    return 0;
}



enum status {
    deleted,
    nil,
    key
};
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
    size_t operator()(const std::string &str, size_t m, size_t a = 241) {
        if (m == 0)
            return 0;

        size_t hash = 0;
        for (auto &ch: str) {
            hash = (hash * a + ch) % m;
        }
        return hash;
    }

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
    size_t items_count = 0;

    Hasher hasher;
    const double RATIO  = 0.75;

    void rehash() {
        std::vector<table_item<T>> new_table;
        new_table.resize(data.size() * 2);
        items_count = 0;

        for (auto& item : data){
            if (item.flag == status::key){
                ++items_count;
                size_t index = hasher(item.data, new_table.size());
                for (int i = 0; i < new_table.size(); ++i){
                    index = next(index, i, new_table.size());
                    if (new_table[index].flag == status::nil){
                        new_table[index] = std::move(item);
                        break;
                    }
                }
            }
        }

        data = std::move(new_table);
        max_size = data.size() * RATIO;
    }

    size_t next(const size_t& index,const size_t& iteration,const size_t& lim){
        return (index + iteration * iteration)%lim;
    }

public:
    HashTable() {
        data.resize(8);
        max_size = static_cast<int>(8 * RATIO);
        items_count = 0;
    }

    [[maybe_unused]] explicit HashTable(size_t _size) {
        data.resize(_size);
        max_size = static_cast<size_t>((int)_size* RATIO);
        items_count = 0;
    }

    bool del(const T &item) {
        size_t ind = hasher(item, data.size());

        for (size_t i = 0; i < data.size(); ++i) {
            ind = next(ind, i, data.size());

            if (data[ind].flag == status::nil) {
                return false;
            }
            if (data[ind].flag == status::key && data[ind].data == item) {
                data[ind].flag = status::deleted;

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
            ind = next(ind, i, data.size());
            if (data[ind].flag == status::key && data[ind].data == item) {
                return false;
            }

            if (data[ind].flag == status::nil) {

                ++items_count;
                if (items_count > max_size){
                    rehash();

                    ind = hasher(item, data.size());
                    data[ind] = std::move(insert_item);
                }

                else {
                    if (deleted_ind > 0)
                        data[deleted_ind] = std::move(insert_item);
                    else
                        data[ind] = std::move(insert_item);
                }

                return true;
            }

            if (deleted_ind < 0 && data[ind].flag == status::deleted) {
                deleted_ind = static_cast<int>(ind);
            }
        }
        return false;
    }

    bool has(const T &item) {
        size_t ind = hasher(item, data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            ind = next(ind, i, data.size());
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
                break;
        }
    }
}
