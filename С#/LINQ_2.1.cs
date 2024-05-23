using System;
using System.Collections.Generic;
using System.Linq;

/// <summary>
/// Represents a movie with properties for title, release year, genre and director.
/// </summary>
struct Movie
{
    public string Title { get; set; }
    public int ReleaseYear { get; set; }
    public string Genre { get; set; }
    public string Director { get; set; }
}

/// <summary>
/// Represents a show with properties for title, author, genre and lead actor id.
/// </summary>
struct Show
{
    public string Title { get; set; }
    public string Author { get; set; }
    public string Genre { get; set; }
    public int LeadActorId { get; set; }
}

/// <summary>
/// Represents an actor with properties for last name, first name, middle name, birth year, role and id.
/// </summary>
struct Actor
{
    public string LastName { get; set; }
    public string FirstName { get; set; }
    public string MiddleName { get; set; }
    public int BirthYear { get; set; }
    public string Role { get; set; }
    public int Id { get; set; }
}

class Program
{
    static void Main(string[] args) {
        // Initialize lists of movies, plays and actors.
        List<Movie> movies = new List<Movie>
        {
            new Movie { Title = "Movie A", ReleaseYear = 2000, Genre = "Action", Director = "Director A" },
            new Movie { Title = "Movie B", ReleaseYear = 1995, Genre = "Comedy", Director = "Director B" },
            new Movie { Title = "Movie C", ReleaseYear = 2005, Genre = "Action", Director = "Director C" },
            new Movie { Title = "Movie D", ReleaseYear = 1990, Genre = "Comedy", Director = "Director D" }
        };

        List<Show> plays = new List<Show>
        {
            new Show { Title = "Play A", Author = "Author A", Genre = "Drama", LeadActorId = 1 },
            new Show { Title = "Play B", Author = "Author B", Genre = "Comedy", LeadActorId = 2 },
            new Show { Title = "Play C", Author = "Author C", Genre = "Drama", LeadActorId = 1 },
            new Show { Title = "Play D", Author = "Author D", Genre = "Comedy", LeadActorId = 2 }
        };

        List<Actor> actors = new List<Actor>
        {
            new Actor { LastName = "Actor1", FirstName = "First1", MiddleName = "Middle1", BirthYear = 1980, Role = "Lead", Id = 1 },
            new Actor { LastName = "Actor2", FirstName = "First2", MiddleName = "Middle2", BirthYear = 1975, Role = "Supporting", Id = 2 },
            new Actor { LastName = "Actor3", FirstName = "First3", MiddleName = "Middle3", BirthYear = 1985, Role = "Lead", Id = 3 },
            new Actor { LastName = "Actor4", FirstName = "First4", MiddleName = "Middle4", BirthYear = 1990, Role = "Supporting", Id = 4 }
        };

        // Sort movies by release year.
        Console.WriteLine("a) Sorted movies:");
        var sortedMovies = movies.OrderBy(m => m.ReleaseYear);
        foreach (var movie in sortedMovies)
        {
            Console.WriteLine($"Title: {movie.Title}, Year: {movie.ReleaseYear}, Genre: {movie.Genre}, Director: {movie.Director}");
        }

        // Group actors by Role and BirthYear
        Console.WriteLine("\nb) Grouped actors:");
        var groupedActors = actors.GroupBy(a => new { a.Role, a.BirthYear });
        foreach (var group in groupedActors)
        {
            Console.WriteLine($"Role: {group.Key.Role}, Birth Year: {group.Key.BirthYear}");
            foreach (var actor in group)
            {
                Console.WriteLine($"Actor: {actor.LastName}, {actor.FirstName}, {actor.MiddleName}");
            }
        }

        // Merge movies and plays
        Console.WriteLine("\nc) Merged movies and plays:");
        var mergedData = movies.Select(m => new { m.Title, m.Genre, Director_Author = m.Director }).Concat(plays.Select(p => new { p.Title, p.Genre, Director_Author = p.Author }));
        foreach (var item in mergedData)
        {
            Console.WriteLine($"Title: {item.Title}, Genre: {item.Genre}, Director/Author: {item.Director_Author}");
        }

        // Join plays and actors
        Console.WriteLine("\nd) Joined plays and actors:");
        var playActorData = plays.Join(actors, p => p.LeadActorId, a => a.Id,(p, a) => new { p.Title, Author = p.Author, LeadActor = a.LastName });
        foreach (var item in playActorData)
        {
            Console.WriteLine($"Play: {item.Title}, Author: {item.Author}, Lead Actor: {item.LeadActor}");
        }
    }
}
