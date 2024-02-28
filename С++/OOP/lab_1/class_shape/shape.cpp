#include <iostream>
#include <stdexcept>
#include <fstream>

class Shape {
private:
    double width;
    double height;

    void validateDimensions() const {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Invalid shape dimensions");
        }
    }

public:
    Shape(double width, double height) : width(width), height(height) {
        validateDimensions();
    }

    double getWidth() const { 
        return width; 
    }

    double getHeight() const { 
        return height; 
    }

    void setWidth(double newWidth) {
        if (newWidth > 0) {
            width = newWidth;
        }
        else {
            throw std::invalid_argument("Invalid width");
        }
    }
    void setHeight(double newHeight) {
        if (newHeight > 0) {
            height = newHeight;
        }
        else {
            throw std::invalid_argument("Invalid height");
        }
    }

    double getArea() const { 
        return width * height; 
    }

    double getPerimeter() const { 
        return 2 * (width + height); 
    }

    bool operator==(const Shape& other) const {
        return (width == other.width && height == other.height);
    }

    void saveStateToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << width << " " << height << std::endl;
            file.close();
        }
        else {
            throw std::runtime_error("Unable to open file for writing");
        }
    }
    void loadStateFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> width >> height;
            validateDimensions();
            file.close();
        }
        else {
            throw std::runtime_error("Unable to open file for reading");
        }
    }
};
int main() {
    try 
    {
        std::cout << "Checking the creation of geometric shapes and their comparison" << std::endl;
        Shape shape1(2, 3);
        std::cout << "Shape1 Area: " << shape1.getArea() << std::endl;
        std::cout << "Shape1 Perimeter: " << shape1.getPerimeter() << std::endl;

        Shape shape2(4, 5);
        std::cout << "Shape2 area: " << shape2.getArea() << std::endl;
        std::cout << "Shape2 perimeter: " << shape2.getPerimeter() << std::endl;

        if (shape1 == shape2) {
            std::cout << "Shapes are equal!" << std::endl;
        }
        else {
            std::cout << "Shapes are not equal!" << std::endl;
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        std::cout << "\nChecking the creation of  dynamic, massive and dynamic massive geometric shapes " << std::endl;
        Shape* dynamicShape = new Shape(2, 3);
        std::cout << "Dynamic shape area: " << dynamicShape->getArea() << std::endl;
        std::cout << "Dynamic shape perimeter: " << dynamicShape->getPerimeter() << std::endl;

        Shape shapes[3] = { Shape(2, 3), Shape(4, 5), Shape(6, 7) };
        std::cout << "Area of massive shape: " << shapes[0].getArea() << std::endl;
        std::cout << "Perimeter of massive shape: " << shapes[0].getPerimeter() << std::endl;

        Shape* shapePtrs[3] = { new Shape(2, 3), new Shape(4, 5), new Shape(6, 7) };
        std::cout << "Area of dynamic massive shape: " << shapePtrs[0]->getArea() << std::endl;
        std::cout << "Perimeter of dynamic massive shape: " << shapePtrs[0]->getPerimeter() << std::endl;
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try 
    {
        std::cout << "\nChecking the save and load from file" << std::endl;
        Shape shape(2, 3);
        shape.saveStateToFile("shape_state.txt");
        std::cout << "Save Area: " << shape.getArea() << std::endl;
        std::cout << "Save Perimeter: " << shape.getPerimeter() << std::endl;
        Shape loadedShape(4, 5);
        loadedShape.loadStateFromFile("shape_state.txt");
        std::cout << "Loaded Shape Area: " << loadedShape.getArea() << std::endl;
        std::cout << "Loaded Shape Perimeter: " << loadedShape.getPerimeter() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "File error: " << e.what() << std::endl;
    }
}
