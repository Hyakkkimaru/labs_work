#include <iostream>
#include <string>
#include <fstream>

class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
    /// Constructor with parameters
    Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {}

    /// Getters and setters
    int getHours() const {
        return hours;
    }

    void setHours(int h) {
        hours = h;
    }

    int getMinutes() const {
        return minutes;
    }

    void setMinutes(int m) {
        minutes = m;
    }

    int getSeconds() const {
        return seconds;
    }

    void setSeconds(int s) {
        seconds = s;
    }

    /// Methods for accessing and changing data
    void add_Hours(int h) {
        hours += h;
    }

    void add_Minutes(int m) {
        minutes += m;
        if (minutes >= 60) {
            int additionalHours = minutes / 60;
            minutes %= 60;
            hours += additionalHours;
        }
    }

    void add_Seconds(int s) {
        seconds += s;
        if (seconds >= 60) {
            int additionalMinutes = seconds / 60;
            seconds %= 60;
            add_Minutes(additionalMinutes);
        }
    }

    /// Convert time to seconds
    int toSeconds() {
        return hours * 3600 + minutes * 60 + seconds;
    }

    /// Convert time to string
    std::string toString() {
        return std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);
    }

    /// Operators
    Time operator+(const Time& other) {
        Time result;
        result.hours = hours + other.hours;
        result.minutes = minutes + other.minutes;
        result.seconds = seconds + other.seconds;
        return result;
    }

    Time operator-(const Time& other) {
        Time result;
        result.hours = hours - other.hours;
        result.minutes = minutes - other.minutes;
        result.seconds = seconds - other.seconds;
        return result;
    }

    bool operator==(const Time& other) const {
        return (hours == other.hours && minutes == other.minutes && seconds == other.seconds);
    }
};

int main() {
    /// Creating an Object
    Time time1(8, 20, 45);

    /// Changing data
    time1.add_Hours(2);
    time1.add_Minutes(15);
    time1.add_Seconds(30);

    /// Time output
    std::cout << "Time 1: " << time1.toString() << std::endl;

    /// Creating an object through dynamic memory allocation
    Time* time2 = new Time(5, 25, 0);

    /// Changing data through methods
    time2->add_Hours(1);
    time2->add_Minutes(30);

    /// Time output
    std::cout << "Time 2: " << time2->toString() << std::endl;

    Time sum = time1 + *time2;
    std::cout << "Sum of time1 and time2: " << sum.toString() << std::endl;

    Time difference = time1 - *time2;
    std::cout << "Difference of time1 and time2: " << difference.toString() << std::endl;

    /// Equality Test
    if (time1 == *time2) {
        std::cout << "Time 1 and Time 2 are equal" << std::endl;
    } 
    else {
        std::cout << "Time 1 and Time 2 are not equal" << std::endl;
    }

    /// Writing the state of objects to a file
    std::ofstream outputFile("prob.txt");
    if (outputFile.is_open()) {
        outputFile << time1.getHours() << " " << time1.getMinutes() << " " << time1.getSeconds() << std::endl;
        outputFile << time2->getHours() << " " << time2->getMinutes() << " " << time2->getSeconds() << std::endl;
        outputFile.close();
    } 
    else {
        std::cout << "Unable to open file" << std::endl;
    }

    /// Loading from file
    std::ifstream inputFile("prob.txt");
    if (inputFile.is_open()) {
        int hours, minutes, seconds;

        inputFile >> hours >> minutes >> seconds;
        Time time5(hours, minutes, seconds);

        inputFile >> hours >> minutes >> seconds;
        Time time6(hours, minutes, seconds);

        inputFile.close();

        std::cout << "Time1 from file: " << time5.toString() << std::endl;
        std::cout << "Time2 from file: " << time6.toString() << std::endl;
    } 
    else {
        std::cout << "Unable to open file" << std::endl;
    }
}
