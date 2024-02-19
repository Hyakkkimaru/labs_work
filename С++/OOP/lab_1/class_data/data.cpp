#include <iostream>
#include <string>
#include <fstream>

class Date {
private:
    int day;
    int month;
    int year;

public:
    /// Constructor with parameters
    Date(int d = 0, int m= 0, int y = 0) : day(d), month(m), year(y) { }

    bool isValid() const {
        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) {
            return false;
        }
        return true;
    }

    /// Getters and setters
    int getDay() const {
        return day;
    }

    void setDay(int d) {
        day = d;
    }

    int getMonth() const {
        return month;
    }

    void setMonth(int m) {
        month = m;
    }

    int getYear() const {
        return year;
    }

    void setYear(int y) {
        year = y;
    }

    /// Methods for accessing and changing data
    void add_days(int d) {
        day += d;
        if (day > 31) {
            month++;
            day -= 31;
        }
        if (month > 12) {
            year++;
            month -= 12;
        }
        isValid();
    }

    void add_months(int m) {
        month += m;
        if (month > 12) {
            year++;
            month -= 12;
        }
        isValid();
    }

    void add_years(int y) {
        year += y;
        isValid();
    }

    /// Convert date to string
    std::string toString() {
        return std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
    }

    /// Operators
    Date operator+(const Date& other) const {
        int newDay = day + other.day;
        int newMonth = month + other.month;
        int newYear = year + other.year;

        if (newDay > 31) {
            newDay -= 31;
            newMonth++;
        }

        if (newMonth > 12) {
            newMonth -= 12;
            newYear++;
        }

        return Date(newDay, newMonth, newYear);
    }

    Date operator-(const Date& other) const {
        int newDay = day - other.day;
        int newMonth = month - other.month;
        int newYear = year - other.year;

        if (newDay < 1) {
            newDay += 31;
            newMonth--;
        }

        if (newMonth < 1) {
            newMonth += 12;
            newYear--;
        }

        return Date(newDay, newMonth, newYear);
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }
};

int main() {
    /// Creating an Object
    Date date1(1, 1, 2000);

    /// Changing data
    date1.add_days(3);
    date1.add_months(4);
    date1.add_years(30);

    /// Date output
    std::cout << "Date 1: " << date1.toString() << std::endl;

    /// Creating an object through dynamic memory allocation
    Date* date2 = new Date(3, 4, 2005);

    /// Changing data through methods
    date2->add_days(6);
    date2->add_months(3);

    /// Date output
    std::cout << "Date 2: " << date2->toString() << std::endl;

    Date sum = date1 + *date2;
    std::cout << "Sum of date1 and date2: " << sum.toString() << std::endl;

    Date difference = date1 - *date2;
    std::cout << "Difference of date1 and date2: " << difference.toString() << std::endl;

    /// Equality Test
    if (date1 == *date2) {
        std::cout << "Date1 and Date2 are equal" << std::endl;
    }
    else {
        std::cout << "Date1 and Date2 are not equal" << std::endl;
    }

    /// Writing the state of objects to a file
    std::ofstream outputFile("prob.txt");
    if (outputFile.is_open()) {
        outputFile << date1.getDay() << " " << date1.getMonth() << " " << date1.getYear() << std::endl;
        outputFile << date2->getDay() << " " << date2->getMonth() << " " << date2->getYear() << std::endl;
        outputFile.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }

    /// Loading from file
    std::ifstream inputFile("prob.txt");
    if (inputFile.is_open()) {
        int days, months, years;

        inputFile >> days >> months >> years;
        Date date3(days, months, years);

        inputFile >> days >> months >> years;
        Date date4(days, months, years);

        inputFile.close();

        std::cout << "Date1 from file: " << date3.toString() << std::endl;
        std::cout << "Date2 from file: " << date4.toString() << std::endl;
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }
}
