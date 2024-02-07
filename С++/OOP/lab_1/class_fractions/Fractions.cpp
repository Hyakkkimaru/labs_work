#include <iostream>

class Fractions{
    private:
        int numerator;
        int detominator;
    public:
        void setNumerator(int num) {
            numerator = num;
        }

        int getNumerator() const {
            return numerator;
        }

        void setDetominator(int den) {
            if (den == 0) {
                std::cout << "Error: Denominator cannot be 0. Setting to 1." << std::endl;
                detominator = 1;
            } 
            else {
                detominator = den;
            }
        }

        int getDetominator() const {
            return detominator;
        }
    // Method to add two fractions
        Fractions add(const Fractions& other) const {
            int newNum = numerator * other.getDetominator() + other.getNumerator() * detominator;
            int newDen = detominator * other.getDetominator();
            Fractions result;
            result.setNumerator(newNum);
            result.setDetominator(newDen);
            return result;
        }

    // Method to subtract two fractions
        Fractions subtract(const Fractions& other) const {
            int newNum = numerator * other.getDetominator() - other.getNumerator() * detominator;
            int newDen = detominator * other.getDetominator();
            Fractions result;
            result.setNumerator(newNum);
            result.setDetominator(newDen);
            return result;
        }

    // Method to multiply two fractions
        Fractions multiply(const Fractions& other) const {
            int newNum = numerator * other.getNumerator();
            int newDen = detominator * other.getDetominator();
            Fractions result;
            result.setNumerator(newNum);
            result.setDetominator(newDen);
            return result;
        }

    // Method to divide two fractions
        Fractions divide(const Fractions& other) const {
            int newNum = numerator * other.getDetominator();
            int newDen = detominator * other.getNumerator();
            Fractions result;
            result.setNumerator(newNum);
            result.setDetominator(newDen);
            return result;
        }

    // Method to print the fraction in a readable format
        void print() const {
            std::cout << numerator << "/" << detominator << std::endl;
        }
    // Comparison operators
        bool operator==(const Fractions& other) const {
            int a = numerator * other.getDetominator();
            int b = other.getNumerator() * detominator;
            return a == b;
        }

        bool operator!=(const Fractions& other) const {
            return !(*this == other);
        }

    // Function to simplify the fraction
        void simplify() {
            int gcd_val = gcd(numerator, detominator);
            numerator /= gcd_val;
            detominator /= gcd_val;
        }

    // Helper function to calculate the greatest common divisor
        int gcd(int a, int b) {
            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }
            return abs(a);
        }
};

int main() {
    Fractions fraction1;
    Fractions fraction2;

    fraction1.setNumerator(3);
    fraction1.setDetominator(4);

    fraction2.setNumerator(5);
    fraction2.setDetominator(6); 

    // Add the fractions
    if (fraction2.getDetominator() != 0) {
        Fractions sum = fraction1.add(fraction2);
        std::cout << "Sum: ";
        sum.simplify();
        sum.print();
    }

    // Subtract the fractions
    Fractions difference = fraction1.subtract(fraction2);
    if (fraction2.getDetominator() != 0) {
        std::cout << "Difference: ";
        difference.simplify();
        difference.print();
    }

    // Multiply the fractions
    Fractions product = fraction1.multiply(fraction2);
    std::cout << "Product: ";
    product.simplify();
    product.print();

    // Divide the fractions
    Fractions quotient = fraction1.divide(fraction2);
    if (fraction2.getNumerator() != 0) {
        std::cout << "Quotient: ";
        quotient.simplify();
        quotient.print();
    }

    return 0;
}