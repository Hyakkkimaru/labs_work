using System;

///<summary> This is custom exception class for issues related to the base salary </summary>
public class OkladException : Exception
{
    public OkladException(string message) : base(message) { }
}

///<summary> This is a custom exception class for handling issues related to bonuses </summary>
public class BonusException : Exception
{
    public BonusException(string message) : base(message) { }
}

///<summary> The Firm class represents a company and has a name property </summary>
public class Firm
{
    private string name;

    public string Name
    {
        get { return name; }
        set { name = value; }
    }
}

///<summary> The Department class represents a department within a company and has a name and number of employees properties </summary>
public class Department
{
    private string name;
    private int num_emp;

    public string Name
    {
        get { return name; }
        set { name = value; }
    }

    public int Num_Emp
    {
        get { return num_emp; }
        set { num_emp = value; }
    }
}

///<summary> The Employee class represents an employee and has a full name, position, salary properties </summary>
public class Employee
{
    private string fullName;
    private string position;
    private double salary;

    public string FullName
    {
        get { return fullName; }
        set { fullName = value; }
    }

    public string Position
    {
        get { return position; }
        set { position = value; }
    }

    public double Salary
    {
        get { return salary; }
        set { salary = value; }
    }

    ///<summary> The Calculate_Salary method calculates the employee's total salary, checking for negative salary </summary>
    public double Calculate_Salary()
    {
        try
        {
            if (salary < 0)
            {
                throw new OkladException($"It is impossible to create an employee - a negative salary is specified: {salary}");
            }

            return salary;
        }

        catch (OkladException ex)
        {
            Console.WriteLine(ex.Message);
            throw;
        }
    }
}

///<summary> The FullTimeEmployee class represents a full-time employee and inherits from the Employee class </summary>
public class FullTimeEmployee : Employee
{
    private double bonus;

    public double Bonus
    {
        get { return bonus; }
        set { bonus = value; }
    }

    ///<summary> The Calculate_Salary method calculates the full-time employee's total salary and checking for negative bonus </summary>
    public new double Calculate_Salary()
    {
        try
        {
            if (bonus < 0)
            {
                throw new BonusException($"Bonus cannot be negative: {bonus}");
            }

            return base.Calculate_Salary() + bonus;
        }

        catch (BonusException ex)
        {
            Console.WriteLine(ex.Message);
            throw;
        }
    }
}

///<summary> The ContractEmployee class represents a contract employee and inherits from the Employee class </summary>
public class ContractEmployee : Employee
{
    public new double Calculate_Salary()
    {
        return base.Calculate_Salary();
    }
}

///<summary> The Program class contains the entry point for the application </summary>
public class Program
{
    public static void Main()
    {
        Firm firm = new Firm() { Name = "Inc corporation" };
        Department department = new Department() { Name = "Research", Num_Emp = 10 };

        FullTimeEmployee fullTimeEmployee = new FullTimeEmployee()
        {
            FullName = "John",
            Position = "Senior Researcher",
            Salary = -1,
            Bonus = 1000
        };

        try
        {
            fullTimeEmployee.Calculate_Salary();
            Console.WriteLine($"Employee {fullTimeEmployee.FullName}'s salary: {fullTimeEmployee.Salary}");
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
        }

        ContractEmployee contractEmployee = new ContractEmployee()
        {
            FullName = "Alex",
            Position = "Contractor",
            Salary = 1000
        };

        try
        {
            contractEmployee.Calculate_Salary();
            Console.WriteLine($"Employee {contractEmployee.FullName}'s salary: {contractEmployee.Salary}");
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
        }
    }
}
