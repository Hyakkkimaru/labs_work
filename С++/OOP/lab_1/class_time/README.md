# Laboratory work in C++ (Description of classes)
## class Time
### "Time" is an abstract implementation of time. It contains data about hours, minutes and seconds, as well as methods for working with this data:
- Constructors:
1. Time(int h, int m, int s) constructor with arguments initializes an object with the given values of hours, minutes and seconds
- Data:
1. int hours: Variable to store the number of hours.
2. int minutes: Variable to store the number of minutes.
3. int seconds: Variable to store the number of seconds.
- get:
1. int getHours(): Method that returns the number of hours.
2. int getMinutes(): Method that returns the number of minutes.
3. int getSeconds(): Method that returns the number of seconds.
- set:
1. void setHours(int h): Method that sets the number of hours.
2. void setMinutes(int m): Method that sets the number of minutes.
3. void setSeconds(int s): Method that sets the number of seconds.
- Methods for changing data:
1. void add_Hours(int h): Метод, который увеличивает количество часов на заданное значение h.
2. void add_Minutes(int m): Метод, который увеличивает количество минут на заданное значение m. Если суммарные минуты больше 60, то добавляется один час и из суммарных минут вычитается 60.
3. void add_Seconds(int s): Метод, который увеличивает количество секунд на заданное значение s. Если суммарные секунды больше 60, то добавляется одна минута и из суммарных секунд вычитается 60.
- Methods for mathematical operations:
1. Time operator+(const Time& other): Оператор сложения, который возвращает новое время, полученное сложением текущего времени и времени, переданного в качестве аргумента other.
2. Time operator-(const Time& other): Оператор вычитания, который возвращает новое время, полученное вычитанием из текущего времени времени, переданного в качестве аргумента other.
3. bool operator==(const Time& other) const: Оператор сравнения, который сравнивает текущее время со значением времени, переданным в качестве аргумента other и возвращает true, если они равны, и false в противном случае. 
