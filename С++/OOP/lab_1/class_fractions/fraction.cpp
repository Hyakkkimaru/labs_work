#include <iostream>

class Fractions {
private:
    int numerator;
    int denominator;
public:
    void setNumerator(int num) {
        numerator = num;
    }

    int getNumerator() const {
        return numerator;
    }

    void setDenominator(int den) {
        if (den == 0) {
            std::cout << "Ошибка: Знаменатель не может быть 0. Устанавливается стандартное значение 1." << std::endl;
            denominator = 1;
        } else {
            denominator = den;
        }
    }

    int getDenominator() const {
        return denominator;
    }

    Fractions operator+(const Fractions& other) const {
        Fractions result;
        result.setNumerator(numerator * other.getDenominator() + other.getNumerator() * denominator);
        result.setDenominator(denominator * other.getDenominator());
        return result;
    }

    Fractions operator-(const Fractions& other) const {
        Fractions result;
        result.setNumerator(numerator * other.getDenominator() - other.getNumerator() * denominator);
        result.setDenominator(denominator * other.getDenominator());
        return result;
    }

    Fractions operator*(const Fractions& other) const {
        Fractions result;
        result.setNumerator(numerator * other.getNumerator());
        result.setDenominator(denominator * other.getDenominator());
        return result;
    }

    Fractions operator/(const Fractions& other) const {
        Fractions result;
        result.setNumerator(numerator * other.getDenominator());
        result.setDenominator(denominator * other.getNumerator());
        return result;
    }

    bool operator==(const Fractions& other) const {
        int a = numerator * other.getDenominator();
        int b = other.getNumerator() * denominator;
        return a == b;
    }

    bool operator!=(const Fractions& other) const {
        return !(*this == other);
    }

    void simplify() {
        int gcd_val = gcd(numerator, denominator);
        numerator /= gcd_val;
        denominator /= gcd_val;
    }

    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
};

int main() {
    Fractions f1, f2, result;

    f1.setNumerator(3);
    f1.setDenominator(4);
    f2.setNumerator(5);
    f2.setDenominator(0);

    result = f1 + f2;
    result.simplify();
    std::cout << "Результат суммы: " << result.getNumerator() << "/" << result.getDenominator() << std::endl;

    result = f1 - f2;
    result.simplify();
    std::cout << "Результат вычитания: " << result.getNumerator() << "/" << result.getDenominator() << std::endl;

    result = f1 * f2;
    result.simplify();
    std::cout << "Результат умножения: " << result.getNumerator() << "/" << result.getDenominator() << std::endl;

    result = f1 / f2;
    result.simplify();
    std::cout << "Результат деления: " << result.getNumerator()<< "/" << result.getDenominator() << std::endl;

    if (f1 == f2) {
        std::cout << "Дроби равны." << std::endl;
    } else {
        std::cout << "Дроби не равны." << std::endl;
    }

    return 0;
}
