using System;

class Fraction
{
    // Внутренние переменные для хранения дроби
    private int numerator;
    private int denominator;


    // Конструктор для инициализации дроби
    public int Numerator
    {
        get => numerator;
        set => numerator = value;
    }

    // Конструктор для инициализации дроби
    public int Denominator
    {
        get => denominator;
        set
        {
            if (value == 0)
                throw new ArgumentException("Знаменатель не может быть равен нулю");
            denominator = value;
        }
    }

    public Fraction(int numerator, int denominator)
    {
        Numerator = numerator;
        Denominator = denominator;
        Simplify();
    }

    //Нахождения наибольшего общего делителя
    public static int GCD(int a, int b) 
    {
        while (b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    //Сокращение дроби
    public void Simplify()
    {
        int gcd = GCD(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

    // Получение десятичной дроб числа
    public double Value
    {
        get { return (double)numerator / denominator; }
    }

    // Метод для вычисления суммы дробей
    public Fraction Add(Fraction secondFraction)
    {
        int newNumerator = numerator * secondFraction.denominator +
                            denominator * secondFraction.numerator;
        int newDenominator = denominator * secondFraction.denominator;

        return new Fraction(newNumerator, newDenominator);
    }

    // Метод для вычисления разности дробей
    public Fraction Subtract(Fraction secondFraction)
    {
        int newNumerator = numerator * secondFraction.denominator -
                            denominator * secondFraction.numerator;
        int newDenominator = denominator * secondFraction.denominator;

        return new Fraction(newNumerator, newDenominator);
    }

    // Метод для вычисления произведения дробей
    public Fraction Multiply(Fraction secondFraction)
    {
        int newNumerator = numerator * secondFraction.numerator;
        int newDenominator = denominator * secondFraction.denominator;

        return new Fraction(newNumerator, newDenominator);
    }

    // Метод для вычисления частного дробей
    public Fraction Divide(Fraction secondFraction)
    {
        int newNumerator = numerator * secondFraction.denominator;
        int newDenominator = denominator * secondFraction.numerator;

        return new Fraction(newNumerator, newDenominator);
    }

    // Метод для преобразования дроби в строку
    public override string ToString()
    {
        return $"{numerator}/{denominator}";
    }
}

class Program
{
    static void Main(string[] args)
    {
        Fraction fraction1 = new (1, 2);
        Fraction fraction2 = new(3, 4);

        Fraction sum = fraction1.Add(fraction2);
        Fraction difference = fraction1.Subtract(fraction2);
        Fraction product = fraction1.Multiply(fraction2);
        Fraction quotient = fraction1.Divide(fraction2);

        Console.WriteLine($"Сумма: {sum}");
        Console.WriteLine($"Разность: {difference}");
        Console.WriteLine($"Произведение: {product}");
        Console.WriteLine($"Частное: {quotient}");
    }
}
