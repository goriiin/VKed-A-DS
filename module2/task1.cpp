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

void answer(std::istream& in, std::ostream& out);

int main() {
    answer(std::cin, std::cout);
    return 0;
}

template<typename T>
struct [[maybe_unused]] Base_Hasher {
    size_t operator () (const T &item, size_t m = 8, size_t a = 67) {
        size_t hash = 0;
        while (item != 0) {
            hash = (hash * a + item % 10) % m;
            item /= 10;
        }
        return hash;
    }
};

struct String_Hasher{
    size_t operator () (const std::string &str, size_t m = 8, size_t a = 67){
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

    table_item() :data(""), flag(status::nil){}
    table_item(T _data, status _flag): data(std::move(_data)), flag(_flag) {}

    table_item(table_item<T>&& item)  noexcept {
        data = std::move(item.data);
        flag = std::move(item.flag);
    }

    table_item<T>& operator = (table_item&& item) noexcept {
        this->data = std::move(item.data);
        this->flag = std::move(item.flag);
        return *this;
    }
};

template<typename T, class Hasher = Base_Hasher<T>>
class HashTable {
    std::vector<table_item<T>> data{};
    size_t elements;
    size_t max_size;
    Hasher hasher;

    void rehash() {

    }
public:
    HashTable() : elements(0), max_size(6) {
        data.reserve(8);
    }

    [[maybe_unused]] explicit HashTable(size_t _size) : elements(0), max_size(_size * 3 / 4) {
        data.reserve(_size);
    }

    bool del(const std::string& str){
        size_t ind = hasher(str);
        for (size_t i = 0; i < data.size(); ++i) {
            ind = (ind + i*i)%data.size();
            if (data[ind].flag == status::nil)
                return false;
            if (data[i].data == str){
                if (data[i].flag == status::key){
                    data[i].flag = status::deleted;
                    --elements;
                    return true;
                }
                if (data[i].flag == status::deleted){
                    return false;
                }
            }
        }
        return false;
    }

    bool add(const std::string& str) {
        int insert_ind = -1;
        size_t ind = hasher(str);

        auto insert_item = table_item(str, status::key);
        for (size_t i = 0; i < data.size(); ++i) {
            ind = (ind + i*i)%data.size();
            if (data[ind].data == str){
                if (data[ind].flag == status::key)
                    return false;

                else if (insert_ind > 0)
                    data[insert_ind] = std::move(insert_item);
                else
                    data[ind] = std::move(insert_item);
                return true;
            }

            if (data[ind].flag == status::nil){
                if (elements == max_size)
                    rehash();

                if (insert_ind > 0)
                    data[insert_ind] = std::move(insert_item);
                else
                    data[ind] = std::move(insert_item);
                ++elements;
                return true;
            }
            if (insert_ind < 0 && i == status::deleted){
                insert_ind =static_cast<int>(i);
            }
        }
        return false;
    }

    bool has(const std::string &str) {
        size_t ind = hasher(str);
        for (size_t i = 0; i < data.size(); ++i) {
            ind = (ind + i*i)%data.size();
            if (ind == data.size())
                ind = 0;

            if (data[ind].flag == status::nil)
                return false;

            if (data[ind].data == str){
                if (data[ind].flag == status::key)
                    return true;
                if (data[ind].flag == status::deleted)
                    return false;
            }
        }
        return false;
    }

    bool operator[](const std::string &str) {
        return has(str);
    }
};

void answer(std::istream& in, std::ostream& out) {
    HashTable<std::string, String_Hasher> table;

    std::string  word;
    char op;
    while (in >> op >> word){
        switch( op ) {
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
                assert( false );
        }
    }
}


