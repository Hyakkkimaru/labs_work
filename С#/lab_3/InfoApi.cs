using System;
using System.Net;
using Newtonsoft.Json;
using System.Collections.Generic;
using System.Diagnostics.Metrics;
using System.Net.Http.Json;
using System.Reflection;

public class People
{
    public string PhoneNumber { get; set; }
    public string Operator { get; set; }
    public string FullName { get; set; }
    public string INN { get; set; }
    public string Country { get; set; }
    public string Gender { get; set; }
}

class NumberInfo
{
    public string Phone { get; set; }
    public string Provider { get; set; }
    public string Country { get; set; }
}

class InnInfo
{
    public List<Suggestions> Suggestions { get; set; }
}

public class PrettyName
{
    public string Result { get; set; }
    public string Gender { get; set; }
}

public class Suggestions
{
    public Data Data { get; set; }
}
public class Data
{
    public Management Management { get; set; }
}
public class Management
{
    public string Name { get; set; }
}

public class Request
{
    public string Query { get; set; }
}

public class People_List
{
    public List<People> PeopleCollection { get; set; }

    public People_List()
    {
        PeopleCollection = new List<People>();
    }

    public void append(People people)
    {
        this.PeopleCollection.Add(people);
    }

    public void displayAll()
    {
        foreach (var person in PeopleCollection)
        {
            Console.WriteLine(person);
            Console.WriteLine();
        }
    }

    public void SaveToFile()
    {
        using (StreamWriter writer = new StreamWriter("info.txt", append:true))
        {
            foreach (var person in PeopleCollection)
            {
                writer.WriteLine($"ФИО: {person.FullName}, Телефон: {person.PhoneNumber}, Оператор: {person.Operator}, ИНН: {person.INN}, Страна: {person.Country}, Пол: {person.Gender}");
            }
        }
    }
}

class Program
{
    static HttpClient httpClient = new HttpClient();

    static async Task Main(string[] args)
    {
        httpClient.DefaultRequestHeaders.Add("Authorization", "Token 1c9d99544a70cc6ed3a3e480284e4cd4252472e0");
        httpClient.DefaultRequestHeaders.Add("X-Secret", "b0d8f4442383485befe255f4c32ebe06c6ff4ffc");

        People_List peopleList = new People_List();
        try
        {
            while (true)
            {
                Console.WriteLine("Menu:");
                Console.WriteLine("1. Add person");
                Console.WriteLine("2. Display all people");
                Console.WriteLine("3. Save to file");
                Console.WriteLine("4. Exit");

                Console.Write("Choose an option: ");
                int choice = Convert.ToInt32(Console.ReadLine());

                switch (choice)
                {
                    case 1:
                        People person = new People();
                        Console.WriteLine("Enter phone number: ");
                        string phoneNumber = Console.ReadLine();
                        var numberResponse = await httpClient.PostAsJsonAsync("https://cleaner.dadata.ru/api/v1/clean/phone", new[] { phoneNumber });
                        var numberResult = await numberResponse.Content.ReadFromJsonAsync<List<NumberInfo>>();

                        foreach (var num_info in numberResult)
                        {
                            person.PhoneNumber = num_info.Phone;
                            person.Operator = num_info.Provider;
                            person.Country = num_info.Country;
                        };

                        Console.WriteLine("Enter INN: ");
                        string inn = Console.ReadLine();
                        var innResponse = await httpClient.PostAsJsonAsync("http://suggestions.dadata.ru/suggestions/api/4_1/rs/findById/party", new Request { Query = inn });
                        var innInfo = await innResponse.Content.ReadFromJsonAsync<InnInfo>();

                        person.INN = inn;
                        person.FullName = innInfo.Suggestions[0].Data.Management.Name;

                        string[] names = { person.FullName };
                        var nameResponse = await httpClient.PostAsJsonAsync("https://cleaner.dadata.ru/api/v1/clean/name", names);
                        var prettyNames = await nameResponse.Content.ReadFromJsonAsync<List<PrettyName>>();

                        foreach (var prettyName in prettyNames)
                        {
                            person.FullName = prettyName.Result;
                            person.Gender = prettyName.Gender;
                        }

                        peopleList.append(person);
                        break;
                    case 2:
                        peopleList.displayAll();
                        break;
                    case 3:
                        peopleList.SaveToFile();
                        Console.WriteLine("File saved.");
                        break;
                    case 4:
                        return;
                    default:
                        Console.WriteLine("Invalid option. Please try again.");
                        break;
                }
            }
        }  
        catch (Exception ex) 
        { 
            Console.WriteLine(ex.Message); 
        }
    }
}
