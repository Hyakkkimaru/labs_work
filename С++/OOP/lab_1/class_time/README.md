# Laboratory work in C++ (Description of classes)
## class Time
### "Time" is an abstract implementation of time. It contains data about hours, minutes and seconds, as well as methods for working with this data:
- Constructors:
1. `Time(int h, int m, int s)` - constructor with arguments initializes an object with the given values of hours, minutes and seconds
- Data:
1. `int hours` - Variable to store the number of hours.
2. `int minutes` - Variable to store the number of minutes.
3. `int seconds` - Variable to store the number of seconds.
- get:
1. `int getHours()` - Method that returns the number of hours.
2. `int getMinutes()` - Method that returns the number of minutes.
3. `int getSeconds()` - Method that returns the number of seconds.
- set:
1. `void setHours(int h)` - Method that sets the number of hours.
2. `void setMinutes(int m)` - Method that sets the number of minutes.
3. `void setSeconds(int s)` - Method that sets the number of seconds.
- Methods for changing data:
1. `void add_Hours(int h)` - Method that increases the number of hours by a given value h.
2. `void add_Minutes(int m)` - Method that increases the number of minutes by a given value m. If the total minutes are more than 60, then one hour is added and 60 is subtracted from the total minutes.
3. `void add_Seconds(int s)` - Method that increases the number of seconds by a given value s. If the total seconds are greater than 60, then one minute is added and 60 is subtracted from the total seconds.
- Methods for mathematical operations:
1. `Time operator+(const Time& other)` - Addition operator that returns the new time obtained by adding the current time.
2. `Time operator-(const Time& other)` - Subtraction operator that returns the new time obtained by subtracting the current time from the current time.
3. `bool operator==(const Time& other)` - Comparison operator, which compares the current time with a time value, returns true if they are equal and false otherwise.
- Other methods:
1. `int toSeconds()` - Method that returns the number of seconds corresponding to the current time value.
2. `std::string toString()` - Method that returns a string in the format "чч:мм:сс".
- Diagram:

![alt text](https://www.planttext.com/api/plantuml/png/ZP712eCm44Jl-OgSYcBz0K7ms4jFxRrO4pHWiYMxzbBwxqrYGYigz9QPURCRaWQfjJJfaR5kR17vLMd9Nwpa0qmMUSML8QUqCXF9hqRPWH59ioBqic7MHwxJ8HAv8tf99pyposEhS5EY5Oi-UO8ICtsUToxvPEgjncM-rRAHJ5mrMY5kU_jzjh_Bf_jp2TONSHvPPVfW8Ocgmg1T10zfMm9RPAw459xom846QJtivGzL_aNLzJPs1nZPcx566k5-_GC0)
