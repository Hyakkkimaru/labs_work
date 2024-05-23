using System;
using System.Collections.Generic;
using System.Linq;

/// <summary>
/// Represents a product with properties for name, price, quantity and manufacturer ID.
/// </summary>
struct Product
{
    public string Name { get; set; }
    public decimal Price { get; set; }
    public int Quantity { get; set; }
    public string ManufacturerCode { get; set; }
}

/// <summary>
/// Represents a warehouse with properties for name, area, fork lifts and year built.
/// </summary>
struct Warehouse
{
    public string Name { get; set; }
    public double Area { get; set; }
    public int Forklifts { get; set; }
    public int YearBuilt { get; set; }
}

/// <summary>
/// Represents a manufacturer with properties for name, supervisor and code.
/// </summary>
struct Manufacturer
{
    public string Name { get; set; }
    public string Supervisor { get; set; }
    public string Code { get; set; }
}

class Program
{
    static void Main(string[] args)
    {
        // Initialize lists of products, warehouses and manufacturers.
        List<Product> products = new List<Product>
        {
            new Product { Name = "Product A", Price = 100, Quantity = 50, ManufacturerCode = "M1" },
            new Product { Name = "Product B", Price = 80, Quantity = 30, ManufacturerCode = "M2" },
            new Product { Name = "Product C", Price = 120, Quantity = 20, ManufacturerCode = "M1" },
            new Product { Name = "Product D", Price = 150, Quantity = 10, ManufacturerCode = "M3" },
            new Product { Name = "Product E", Price = 200, Quantity = 10, ManufacturerCode = "M2" }};

        List<Warehouse> warehouses = new List<Warehouse>
        {
            new Warehouse { Name = "Warehouse 1", Area = 1000, Forklifts = 5, YearBuilt = 2000 },
            new Warehouse { Name = "Warehouse 2", Area = 800, Forklifts = 3, YearBuilt = 2010 },
            new Warehouse { Name = "Warehouse 3", Area = 500, Forklifts = 2, YearBuilt = 2010 }
        };

        List<Manufacturer> manufacturers = new List<Manufacturer>
        {
            new Manufacturer { Name = "Manufacturer 1", Supervisor = "John Smith", Code = "M1" },
            new Manufacturer { Name = "Manufacturer 2", Supervisor = "Alice Johnson", Code = "M2" },
            new Manufacturer { Name = "Manufacturer 3", Supervisor = "Jane Doe", Code = "M3" }
        };

        // Sort products by price.
        Console.WriteLine("a) Sorted products:");
        var sortedProducts = products.OrderBy(p => p.Price);
        foreach (var product in sortedProducts)
        {
            Console.WriteLine($"Product: {product.Name}, Price: {product.Price}");
        }

        // Grouping warehouses by number of forklifts and year of construction.
        Console.WriteLine("\nb) Grouped warehouses:");
        var groupedWarehouses = warehouses.GroupBy(w => new { w.Forklifts, w.YearBuilt });
        foreach (var group in groupedWarehouses)
        {
            Console.WriteLine($"Forklifts: {group.Key.Forklifts}, YearBuilt: {group.Key.YearBuilt}");
        }

        // Connecting products and manufacturers using the code field.
        Console.WriteLine("\nc) Joined products and manufacturers:");
        var joinedData = products.Join(manufacturers, p => p.ManufacturerCode, m => m.Code, (p, m) => new { ProductName = p.Name, ManufacturerName = m.Name });
        foreach (var data in joinedData)
        {
            Console.WriteLine($"Product: {data.ProductName}, Manufacturer: {data.ManufacturerName}");
        }
    }
}
