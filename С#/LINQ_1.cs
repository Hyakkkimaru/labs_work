using System;
using System.Collections.Generic;
using System.Linq;

/// <summary>
/// Represents a book with properties such as title, author, price, publication date, publisher, and inventory numbers.
/// </summary>
struct Book
{
    public string Title { get; set; }
    public string AuthorLastName { get; set; }
    public double Price { get; set; }
    public DateTime PublicationDate { get; set; }
    public string Publisher { get; set; }
    public List<string> InventoryNumbers { get; set; }
}

/// <summary>
/// Represents a product with properties such as name, price, quantity, arrival dates, and manufacturer.
/// </summary>
struct Product
{
    public string Name { get; set; }
    public double Price { get; set; }
    public int Quantity { get; set; }
    public List<DateTime> ArrivalDates { get; set; }
    public string Manufacturer { get; set; }
}

/// <summary>
/// Represents a cinema with properties such as name, roominess, construction date, and rank.
/// </summary>
struct Cinema
{
    public string Name { get; set; }
    public double Roominess { get; set; }
    public DateTime ConstructionDate { get; set; }
    public string Rank { get; set; }
}

class Program
{
    static void Main(string[] args)
    {
        // Initialize lists of books, products and cinemas.
        List<Book> books = new List<Book>
        {
            new Book { Title = "Война и мир", AuthorLastName = "Толстой", Price = 1000, PublicationDate = new DateTime(1869, 1, 1), Publisher = "Publishing1", InventoryNumbers = new List<string>{"12345", "12346"}},
            new Book { Title = "Преступление и наказание", AuthorLastName = "Достоевский", Price = 800, PublicationDate = new DateTime(1866, 1, 1), Publisher = "Publishing2", InventoryNumbers = new List<string>{"23456"}},
            new Book { Title = "Мастер и Маргарита", AuthorLastName = "Булгаков", Price = 1200, PublicationDate = new DateTime(1967, 1, 1), Publisher = "Publishing3", InventoryNumbers = new List<string>{"34567", "34568"}}
        };

        List<Product> products = new List<Product>
        {
            new Product { Name = "1", Price = 100.5, Quantity = 45, ArrivalDates = new List<DateTime> { DateTime.Now }, Manufacturer = "Manufacturer1" },
            new Product { Name = "2", Price = 20, Quantity = 98, ArrivalDates = new List<DateTime> { DateTime.Now }, Manufacturer = "Manufacturer1" },
            new Product { Name = "3", Price = 86.99, Quantity = 152, ArrivalDates = new List<DateTime> { DateTime.Now }, Manufacturer = "Manufacturer2" },
            new Product { Name = "4", Price = 15.67, Quantity = 100, ArrivalDates = new List<DateTime> { DateTime.Now }, Manufacturer = "Manufacturer2" },
            new Product { Name = "5", Price = 50, Quantity = 45, ArrivalDates = new List<DateTime> { DateTime.Now }, Manufacturer = "Manufacturer3" }
        };

        List<Cinema> cinemas = new List<Cinema>
        {
            new Cinema { Name = "Киномакс", Roominess = 250, ConstructionDate = new DateTime(2020, 12, 2), Rank = "A" },
            new Cinema { Name = "Алмаз Синема", Roominess = 500, ConstructionDate = new DateTime(2004, 9, 8), Rank = "A" },
            new Cinema { Name = "Корстон", Roominess = 100, ConstructionDate = new DateTime(2015, 5, 15), Rank = "C" }
        };

        // Displaying all information about books, products and cinemas.
        Console.WriteLine("а) All books:");
        foreach (var book in books)
        {
            Console.WriteLine($"Tittle: {book.Title}, Author Last Name: {book.AuthorLastName}, Price: {book.Price}, Publication Date: {book.PublicationDate}, Publishing house: {book.Publisher}, Inventory Numbers: {string.Join(", ", book.InventoryNumbers)}");
        }

        Console.WriteLine("а) All products:");
        foreach (var product in products)
        {
            Console.WriteLine($"Name: {product.Name}, Price: {product.Price}, Quantity: {product.Quantity}, Arrival Dates: {string.Join(", ", product.ArrivalDates)}, Manufacturer: {product.Manufacturer}");
        }

        Console.WriteLine("a) All cinemas:");
        foreach (var cinema in cinemas)
        {
            Console.WriteLine($"Name: {cinema.Name}, Roominess: {cinema.Roominess}, Construction date: {cinema.ConstructionDate}, Rank: {cinema.Rank}");
        }

        // Filtering books, products and cinemas.
        string authorFilter = "Толстой";
        var filteredBooks = books.Where(b => b.AuthorLastName == authorFilter).ToList();
        Console.WriteLine("\nb) Books by Tolstoy:");
        foreach (var book in filteredBooks)
        {
            Console.WriteLine($"Tittle: {book.Title}, Author Last Name: {book.AuthorLastName}");
        }

        string productFilter = "1";
        var filteredProducts = products.Where(p => p.Name == productFilter).ToList();
        Console.WriteLine("\nb) Products by Manufacturer:");
        foreach(var product in filteredProducts)
        {
            Console.WriteLine($"Name: {product.Name}, Manufacturer1: {product.Manufacturer}");
        }

        string cinemaFilter = "C";
        var filteredCinemas = cinemas.Where(c => c.Name == cinemaFilter).ToList();
        Console.WriteLine("\nb) Cinemas by Rank C:");
        foreach (var cinema in filteredCinemas)
        {
            Console.WriteLine($"Name: {cinema.Name}, Rank: {cinema.Rank}");
        }

        // Sorting books, products and cinemas.
        var sortedBooksByPrice = books.OrderBy(b => b.Price).ToList();
        Console.WriteLine("\nc) Books sorted by price:");
        foreach (var book in sortedBooksByPrice)
        {
            Console.WriteLine($"Tittle: {book.Title}, Price: {book.Price}");
        }

        var sortedProductsByName = products.OrderBy(p => p.Name).ToList();
        Console.WriteLine("\nc) Products sorted by name:");
        foreach (var product in sortedProductsByName)
        {
            Console.WriteLine($"Name: {product.Name}, Price: {product.Price}");
        }

        var sortedCinemasByRoominess = cinemas.OrderBy(c => c.Roominess).ToList();
        Console.WriteLine("\nc) Cinemas sorted by roominess:");
        foreach (var cinema in sortedCinemasByRoominess)
        {
            Console.WriteLine($"Name: {cinema.Name}, Roominess: {cinema.Roominess}");
        }

        // Grouping books, products and cinemas.
        var groupedBooksByYear = books.GroupBy(b => b.PublicationDate.Year).ToList();
        Console.WriteLine("\nd) Books grouped by year of publication:");
        foreach (var group in groupedBooksByYear)
        {
            Console.WriteLine($"Year: {group.Key}");
            foreach (var book in group)
            {
                Console.WriteLine($"Tittle: {book.Title}");
            }
        }

        var groupedProductsByName = products.GroupBy(p => p.Manufacturer).ToList();
        Console.WriteLine("\nd) Products grouped by manufacturers:");
        foreach (var group in groupedProductsByName)
        {
            Console.WriteLine($"Manufactutet: {group.Key}");
            foreach (var product in group)
            {
                Console.WriteLine($"Price: {product.Price}");
            }
        }

        var groupedCinemasByRank = cinemas.GroupBy(c => c.Rank).ToList();
        Console.WriteLine("\nd) Cinemas grouped by rank:");
        foreach (var group in groupedCinemasByRank)
        {
            Console.WriteLine($"Rank: {group.Key}");
            foreach (var cinema in group)
            {
                Console.WriteLine($"Name: {cinema.Name}");
            }
        }

        // Formation of projection of books, products and cinemas.
        var projectedBooks = books.Select(b => new { Title = b.Title, Author = b.AuthorLastName }).ToList();
        Console.WriteLine("\ne) Projections of books - only title and author:");
        foreach (var book in projectedBooks)
        {
            Console.WriteLine($"Tittle: {book.Title}, Author: {book.Author}");
        }

        var projectedProducts = products.Select(p => new { Name = p.Name, Price = p.Price }).ToList();
        Console.WriteLine("\ne) Projections of products - only name and price:");
        foreach (var product in projectedProducts)
        {
            Console.WriteLine($"Name: {product.Name}, Price: {product.Price}");
        }

        var projectedCinemas = cinemas.Select(c => new { Name = c.Name, Roominess = c.Roominess }).ToList();
        Console.WriteLine("\ne) Projections of cinemas - only name and roominess:");
        foreach (var cinema in projectedCinemas)
        {
            Console.WriteLine($"Name: {cinema.Name}, Roominess: {cinema.Roominess}");
        }
    }
}
