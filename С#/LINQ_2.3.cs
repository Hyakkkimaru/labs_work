using System;
using System.Collections.Generic;
using System.Linq;

/// <summary>
/// Represents a product with properties for name, length, max width, number of tributaries and river code.
/// </summary>
struct River
{
    public string Name { get; set; }
    public double Length { get; set; }
    public double MaxWidth { get; set; }
    public int TributariesCount { get; set; }
    public string Code { get; set; }
}

/// <summary>
/// Represents a sea with properties for name, area and sea code.
/// </summary>
struct Sea
{
    public string Name { get; set; }
    public double Area { get; set; }
    public string Code { get; set; }
}

/// <summary>
/// Represents a ship with properties for name, passengers count, shipping company, year built, type and river or sea code.
/// </summary>
struct Ship
{
    public string Name { get; set; }
    public int PassengersCount { get; set; }
    public string ShippingCompany { get; set; }
    public int YearBuilt { get; set; }
    public string Type { get; set; }
    public string RiverOrSeaCode { get; set; }
}

class Program
{
    static void Main(string[] args) 
    {
        // Initialize lists of rivers, seas and ships.
        List<River> rivers = new List<River>
        {
            new River { Name = "Volga", Length = 3530, MaxWidth = 1000, TributariesCount = 200, Code = "R1" },
            new River { Name = "Nile", Length = 6650, MaxWidth = 2500, TributariesCount = 2, Code = "R2" },
            new River { Name = "Amazon", Length = 6575, MaxWidth = 1500, TributariesCount = 1100, Code = "R3" },
            new River { Name = "Yamuna", Length = 5240, MaxWidth = 950, TributariesCount = 1, Code = "R4" },
            new River { Name = "Ganges", Length = 1000, MaxWidth = 1000, TributariesCount = 500, Code = "R5" }
        };

        List<Sea> seas = new List<Sea>
        {
            new Sea { Name = "Mediterranean", Area = 2500000, Code = "S1" },
            new Sea { Name = "Caspian", Area = 371000, Code = "S2" },
            new Sea { Name = "Black Sea", Area = 500000, Code = "S3" },
            new Sea { Name = "Yellow Sea", Area = 6500000, Code = "S4" },
            new Sea { Name = "Red Sea", Area = 2400000, Code = "S5" }
        };

        List<Ship> ships = new List<Ship>
        {
            new Ship { Name = "Titanic", PassengersCount = 2200, ShippingCompany = "White Star Line", YearBuilt = 1912, Type = "Sea", RiverOrSeaCode = "S1" },
            new Ship { Name = "Mississippi Queen", PassengersCount = 160, ShippingCompany = "Delta Queen Steamboat Company", YearBuilt = 1976, Type = "River", RiverOrSeaCode = "R1" },
            new Ship { Name = "Magelan", PassengersCount = 600, ShippingCompany = "Sea group", YearBuilt = 1998, Type = "Sea", RiverOrSeaCode = "S5"},
            new Ship { Name = "Titanic 2", PassengersCount = 468, ShippingCompany = "River group", YearBuilt = 1912, Type = "River", RiverOrSeaCode = "R4" },
            new Ship { Name = "Putin Ship", PassengersCount = 1400, ShippingCompany = "Delta Queen Steamboat Company", YearBuilt = 1976, Type = "River", RiverOrSeaCode = "R1" },
        };

        // Sort river by length.
        Console.WriteLine("a) Sorted rivers:");
        var sortedRivers = rivers.OrderBy(r => r.Length);
        foreach (var river in sortedRivers)
        {
            Console.WriteLine($"Name {river.Name} - Length {river.Length}");
        }

        // Group ship by shipping company and year of construction.
        Console.WriteLine("\nb) Grouped ships:");
        var groupedShips = ships.GroupBy(s => new { s.ShippingCompany, s.YearBuilt });
        foreach (var group in groupedShips)
        {
            Console.WriteLine($"Shipping Company: {group.Key.ShippingCompany}, Year Built: {group.Key.YearBuilt}, Count: {group.Count()}");
        }

        // Counting the number of ships in a shipping company.
        var shipsCountByShippingCompany = ships.GroupBy(s => s.ShippingCompany).Select(g => new { ShippingCompany = g.Key, ShipCount = g.Count() });
        Console.WriteLine("\nc) Ship count:");
        foreach (var item in shipsCountByShippingCompany)
        {
            Console.WriteLine($"Shipping Company {item.ShippingCompany} - Ship Count {item.ShipCount}");
        }

        // Connect ship and river using code field.
        var joinedData = ships.Join(rivers, s => s.RiverOrSeaCode, r => r.Code, (ship, river) => new { ShipName = ship.Name, RiverName = river.Name });
        Console.WriteLine("\nd) Joined ships and rivers:");
        foreach (var item in joinedData)
        {
            Console.WriteLine($"Ship name {item.ShipName} - River name {item.RiverName}");
        }
    }
}
