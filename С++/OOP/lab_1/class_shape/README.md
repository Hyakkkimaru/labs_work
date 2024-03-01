# Laboratory work in C++ (Description of classes)
## class Shape
### "Shape" is an abstract implementation of geometric figure that is defined by its width and height. Has the following methods and functions:
- Constructors:
1. `Shape(double width, double height)` - constructor with arguments initializes an object with the given values of width and height.
- Data:
1. `double width` - Variable to store the width value.
2. `double height` - Variable to store the height value.
- get:
1. `getWidth()` - Returns the value of the width data member.
2. `getHeight()` - Returns the value of the height data member.
3. `getArea()` - Calculates and returns the area of the shape.
4. `getPerimeter()` - Calculates and returns the perimeter of the shape.
- set:
1. `setWidth(double newWidth)` - Sets the value of the width data member to newWidth if it is positive; otherwise, throws an std::invalid_argument exception.
2. `setHeight(double newHeight)` - Sets the value of the height data member to newHeight if it is positive; otherwise, throws an std::invalid_argument exception.
- Methods for mathematical operations:
1. `operator==(const Shape& other)` - Overloads the equality operator to compare two Shape objects based on their width and height.
- Methods for checking:
1. `validateDimensions() const` - Validates if the dimensions (width and height) are positive. If not, it throws an std::invalid_argument exception.
- Methods to save and load from file:
1. `saveStateToFile(const std::string& filename) const` - Saves the width and height to a file. If the file cannot be opened, it throws an std::runtime_error exception.
2. `loadStateFromFile(const std::string& filename)` - Loads the width and height from a file. If the file cannot be opened, it throws an std::runtime_error exception. It also validates the loaded dimensions using the validateDimensions method.
- Diagram:

![alt]()
