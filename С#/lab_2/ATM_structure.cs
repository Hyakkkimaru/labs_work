using System;

///<summary> This is a custom exception class for when there is an error while withdrawing from an account </summary>
public class WithdrawException : Exception 
{
    ///<summary> Exception constructor </summary>
    public WithdrawException() : base("Error when withdrawing from account") { }
}

///<summary> This is a custom class for when there an issue creating an account due to an incorrect balance value </summary>
public class BalanceException : Exception
{
    ///<summary> Exception constructor </summary>
    public BalanceException() : base("Unable to create an account - the balance value is incorrect") { }
}

///<summary> This is the Bank class, which contains information about the bank </summary>
public class Bank
{
    ///<summary> The name of the bank </summary>
    private string name;
    public string Name
    {
       get { return name; }
       set { name = value; }
    }
}

///<summary> This is the Account class, which is the base class for RegularAccount and SpecialAccount </summary>
class Account
{
    ///<summary> The account number, pin code and balance of the account </summary>
    private string number;
    private int pinCode;
    private decimal balance;

    ///<summary> Properties for the account number, pin code, and balance </summary>
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

    ///<summary> This is the virtual Withdraw method, which is overridden in the RegularAccount and SpecialAccount classes </summary>
    public virtual void Withdraw(decimal amount)
    {
        try
        {
            ///<summary> If the amount is less than 0 or greater than the balance, throw a WithdrawException </summary>
            if (amount < 0 || amount > Balance)
            {
                throw new WithdrawException();
            }
            
            ///<summary> Otherwise, subtract the amount from the balance and print a success message </summary>
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

///<summary> This is the RegularAccount class, which inherits from the Account class </summary>
class RegularAccount : Account
{
    ///<summary> Overrides the Withdraw method from the Account class </summary>
    public override void Withdraw(decimal amount)
    {
        try
        {
            ///<summary> Call the Withdraw method from the base Account class </summary>
            base.Withdraw(amount);
        }
        catch (WithdrawException ex)
        {
            Console.WriteLine(ex.Message);
        }
    }
}

///<summary> This is the SpecialAccount class, which inherits from the Account class </summary>
class SpecialAccount : Account
{
    ///<summary> Overrides the Withdraw method from the Account class </summary>
    public override void Withdraw(decimal amount)
    {
        try
        {
            ///<summary> Call the Withdraw method from the base Account class </summary>
            base.Withdraw(amount);
        }
        catch (WithdrawException ex)
        {
            Console.WriteLine(ex.Message);
        }
    }
}

///<summary> This is the ATM class, which contains information about the ATM </summary>
class ATM
{
    ///<summary> The address of the ATM and identification number of the ATM
    private string address;
    private string identificationNumber;

    ///<summary> Properties for the address and identification number </summary>
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

///<summary> This is the main Program class, which contains the main method </summary>
class Program
{
    ///<summary> The main method, which is the entry point of the program </summary>
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

        Console.WriteLine($"ATM: " + bankomat.IdentificationNumber + "; " + bankomat.Address);

        Console.WriteLine("Testing Regular Account:");
        regularAccount.Withdraw(500);
        regularAccount.Withdraw(600);

        Console.WriteLine("\nTesting Special Account:");
        specialAccount.Withdraw(500);
        specialAccount.Withdraw(6000);
    }
}
