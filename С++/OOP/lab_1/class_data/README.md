# Laboratory work in C++ (Description of classes)
## class Date
### "Date" is an abstract implementation of dates. It contains data about years, months and days, as well as methods for working with this data:
- Constructors:
1. `Date(int d, int m, int y)` - constructor with arguments initializes an object with the given values of days, months and years.
- Data:
1. `int day` - Variable to store the number of days.
2. `int month` - Variable to store the number of months.
3. `int year` - Variable to store the number of years.
- get:
1. `int getDay()` - Method that returns the number of days.
2. `int getMonth()` - Method that returns the number of months.
3. `int getYear()` - Method that returns the number of years.
- set:
1. `void setDay(int d)` - Method that sets the number of days.
2. `void setMonth(int m)` - Method that sets the number of months.
3. `void setYear(int y)` - Method that sets the number of years.
- Methods for changing data:
1. `void add_days(int d)` - Methods that increases the current date by the specified number of days. If the total number of days exceeds 31, then the day is set equal to the remainder of division by 31, and the month is increased by 1. If the total number of months exceeds 12, then the month is set equal to the remainder of division by 12, and the year is increased by 1.
2. `void add_months(int m)` - Methods  that increases the current date by the specified number of months. If the total number of months exceeds 12, then the month is set equal to the remainder of division by 12, and the year is increased by 1.
3. `void add_years(int y)` - Methods that increases the current date by the specified number of years.
- Methods for mathematical operations:
1. `Date operator+(const Date& other)` - Addition operator that returns the new date obtained by adding the current date.
2. `Date operator-(const Date& other)` - Subtraction operator that returns the new date obtained by subtracting the current date from the other date.
3. `bool operator==(const Date& other)` - Comparison operator, which compares the current date with a date value, returns true if they are equal and false otherwise.
- Other methods:
1. `std::string toString()` - Method that returns a string in the format "дд.мм.гггг".
- Diagram:

