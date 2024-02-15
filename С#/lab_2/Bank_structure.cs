using System;

public class QuantityException : Exception
{
    public QuantityException(string message) : base(message) { }
}

public class DepositException : Exception
{
    public DepositException(string message) : base(message) { }
}

public class Bank
{
    private string name;

    public string Name
    {
        get { return name; }
        set { name = value; }
    }
}

public class Branch
{
    private string name;
    private double sum;

    public string Name
    {
        get { return name; }
        set { name = value; }
    }

    public double All_Sum_Branch
    {
        get { return sum; }
        set { sum = value; }
    }
}

public class Deposit
{
    private string fullName;
    private double sum;

    public string FullName
    {
        get { return fullName; }
        set { fullName = value; }
    }

    public double All_Sum_Deposit
    {
        get { return sum; }
        set { sum = value; }
    }

    public double Sum_Deposit(int amount_month)
    {
        try
        {
            if (sum < 0)
            {
                throw new DepositException($"It is impossible to create a deposit - a negative deposit amount is indicated: {sum}");
            }
            return sum;
        }

        catch (DepositException ex)
        {
            Console.WriteLine(ex.Message);
            return 0;
        }
    }
}

public class LongTermDeposit : Deposit
{
    public new double Sum_Deposit(int months)
    {
        try
        {
            if (months < 0)
            {
                throw new QuantityException("The number of months cannot be negative.");
            }

            return base.Sum_Deposit(months) * months;
        }

        catch (QuantityException ex)
        {
            Console.WriteLine(ex.Message);
            return 0;
        }
    }
}

public class DepositUntilDemand : Deposit
{
    public double CalculateDepositAmount(int months)
    {
        try
        {
            if (months < 0)
            {
                throw new QuantityException("The number of months cannot be negative.");
            }

            return base.Sum_Deposit(months) * months;
        }

        catch (QuantityException ex)
        {
            Console.WriteLine(ex.Message);
            return 0;
        }
    }
}

public class Program
{
    public static void Main()
    {
        Bank bank = new Bank { Name = "MyBank" };
        Branch branch = new Branch { Name = "Main Branch", All_Sum_Branch = 0 };

        Deposit deposit = new Deposit { FullName = "John Doe", All_Sum_Deposit = 1000 };

        try
        {
            Console.WriteLine($"Deposit amount for {deposit.FullName}: {deposit.Sum_Deposit(12)}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }

        LongTermDeposit longTermDeposit = new LongTermDeposit { FullName = "Jane Doe", All_Sum_Deposit = 5000 };

        try
        {
            Console.WriteLine($"Long-term deposit amount for {longTermDeposit.FullName}: {longTermDeposit.Sum_Deposit(60)}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }

        DepositUntilDemand depositUntilDemand = new DepositUntilDemand { FullName = "Jim Brown", All_Sum_Deposit = 2000 };

        try
        {
            Console.WriteLine($"Deposit amount for {depositUntilDemand.FullName}: {depositUntilDemand.CalculateDepositAmount(48)}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
    }
}
