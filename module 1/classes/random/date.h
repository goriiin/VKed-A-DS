//
// Created by dmitry on 28.03.2024.
//

#ifndef MODULE_1_BIRTHDATE_H
#define MODULE_1_BIRTHDATE_H


class date {
    int day;
    int month;
    int year;

    bool begin = true;



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

    void setBegin(bool begin) {
        this->begin = begin;
    }

    bool isBegin() const {
        return begin;
    }

    date() = default;
    date(int _day, int _month, int _year):
        day(_day), month(_month), year(_year){}

    bool operator < (const date& other) const {
        if (this->year < other.year)
            return true;

        if (this->year == other.year){
            if (this->month < other.month)
                return true;
            if (this->month == other.month)
                if (this->day < other.day)
                    return true;
        }

        return false;
    }

    bool operator > (const date& other) const {
        return other < *this;
    }

    bool operator == (const date& other) const {
        return (
                (this->day == other.day ) &&
                (this->month == other.month) &&
                (this->year == other.year)
        );
    }

    bool operator != (const date& other) const {
        return !(*this == other);
    }

    // Возвратит true, если получится
    bool makeLegit(date& begin, date& end){
        if ( begin == end )
            return false;
        auto days = daysBetweenDates({1, 1, this->year+18});
        auto y18 = date(1, 1, this->year+18) + days;
        if ( y18 == end )
            return false;
        if (end < date(1, 1, begin.year+80) + days)
            return true;

    }

    date operator + (int days){
        addDays(days);
        return *this;
    }

    int daysInMonth(int month, int year) const {
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

    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int daysBetweenDates(const date& other) {
        int totalDays = 0;

        // Рассчитываем количество дней с начала года для каждой даты
        for (int i = this->year; i < other.year; i++) {
            totalDays += isLeapYear(i) ? 366 : 365;
        }

        for (int i = 1; i < this->month; i++) {
            totalDays -= daysInMonth(i, this->year);
        }
        totalDays -= this->day;

        for (int i = 1; i < other.month; i++) {
            totalDays += daysInMonth(i, other.year);
        }
        totalDays += other.day;

        return totalDays;
    }

    void addDays(int days) {
        while (days != 0) {
            if (days > 0) {
                ++day;
                --days;
                if (day > daysInMonth(month, year)) {
                    day = 1;
                    ++month;
                    if (month > 12) {
                        month = 1;
                        ++year;
                    }
                }
            } else {
                --day;
                ++days;
                if (day < 1) {
                    --month;
                    if (month < 1) {
                        month = 12;
                        --year;
                    }
                    day = daysInMonth(month, year);
                }
            }
        }
    }

    friend std::istream & operator >> (std::istream& in, date& d) {
        int a,b,c;
        in >> a >> b >> c;
        d.day = a;
        d.month = b;
        d.year = c;
    }

    friend std::ostream & operator << (std::ostream& out, date& d) {
        out << d.day << " " << d.month << " " << d.year;
    }
};


#endif //MODULE_1_BIRTHDATE_H
