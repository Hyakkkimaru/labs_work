using System;

public class WithdrawException : Exception 
{
    public WithdrawException() : base("Error when withdrawing from account") { }
}

public class BalanceException : Exception
{
    public BalanceException() : base("Unable to create an account - the balance value is incorrect") { }
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

class Account
{
    private string number;
    private int pinCode;
    private decimal balance;

    public string Number 
    { 
        get { return number; } 
        set { number = value; } 
    }

    public int PinCode 
    { 
        get { return pinCode; } 
        set { pinCode = value; } 
    }

    public decimal Balance 
    { 
        get { return balance; } 
        set { balance = value; } 
    }

    public virtual void Withdraw(decimal amount)
    {
        try
        {
            if (amount < 0 || amount > Balance)
            {
                throw new WithdrawException();
            }
            else
            {
                Balance -= amount;
                Console.WriteLine($"The amount {amount} was successfully withdrawn from the account {Number}");
            }
        }
        catch (WithdrawException ex)
        {
            Console.WriteLine(ex.Message);
        }
    }
}

class RegularAccount : Account
{
    public override void Withdraw(decimal amount)
    {
        try
        {
            base.Withdraw(amount);
        }
        catch (WithdrawException ex)
        {
            Console.WriteLine(ex.Message);
        }
    }
}

class SpecialAccount : Account
{
    public override void Withdraw(decimal amount)
    {
        try
        {
            base.Withdraw(amount);
        }
        catch (WithdrawException ex)
        {
            Console.WriteLine(ex.Message);
        }
    }
}

class ATM
{
    private string address;
    private string identificationNumber;

    public string Address
    {
        get { return address; }
        set { address = value; }
    }

    public string IdentificationNumber
    {
        get { return identificationNumber; }
        set { identificationNumber = value; }
    }
}

class Program
{
    static void Main()
    {
        Bank bank = new Bank() { Name = "My Bank" };

        ATM bankomat = new ATM();
        bankomat.IdentificationNumber = "001";
        bankomat.Address = "str LD 234";

        RegularAccount regularAccount = new RegularAccount();
        regularAccount.Number = "1234567890";
        regularAccount.PinCode = 1234;
        regularAccount.Balance = 1000;

        SpecialAccount specialAccount = new SpecialAccount();
        specialAccount.Number = "0987654321";
        specialAccount.PinCode = 5678;
        specialAccount.Balance = 2000;


        Console.WriteLine("ADT: " + bankomat.IdentificationNumber + "; " + bankomat.Address);
      
        Console.WriteLine("\nAccount: " + regularAccount.Number + "; " + regularAccount.Balance);
        Console.WriteLine("Testing Regular Account:");
        regularAccount.Withdraw(500);
        regularAccount.Withdraw(600);
      
        Console.WriteLine("\nAccount: " + regularAccount.Number + "; " + regularAccount.Balance);
        Console.WriteLine("Testing Special Account:");
        specialAccount.Withdraw(500);
        specialAccount.Withdraw(6000);
    }
}
