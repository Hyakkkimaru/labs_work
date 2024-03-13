#include <iostream>
#include <string>
#include <typeinfo>
#include <exception>

class Any {
private:
   // Base class for the polymorphic hierarchy
   class Base {
   public:
       // Destructor
       virtual ~Base() {}
       // Pure virtual function for cloning the object
       virtual Base* clone() const = 0;
       // Pure virtual function for getting the type info
       virtual const std::type_info& type() const = 0;
   };

   // Template derived class for storing the actual value
   template<typename T>
   class Derived : public Base {
   public:
       // The stored value
       T value;

       Derived(const T& value) : value(value) {}

       // Clone function implementation
       Base* clone() const override {
           return new Derived<T>(value);
       }

       // Type info function implementation
       const std::type_info& type() const override {
           return typeid(value);
       }
   };

   Base* object; // Pointer to the stored object

public:
   // Default constructor
   Any() : object(nullptr) {}

   // Constructor with a value
   template<typename T>
   Any(const T& value) : object(new Derived<T>(value)) {}

   // Copy constructor
   Any(const Any& other) {
       // Clone the object if it's not null
       if (other.object) {
           object = other.object->clone();
       }
   }

   // Copy assignment operator
   Any& operator=(const Any& other) {
       // Check for self-assignment
       if (&other != this) {
           // Delete the current object and set a new one
           delete object;
           object = other.object ? other.object->clone() : nullptr;
       }
       return *this;
   }

   // Destructor
   ~Any() {
       delete object;
   }

   // Check if the object is empty
   bool Empty() const {
       return object == nullptr;
   }

   // Clear the stored object
   void Clear() {
       delete object;
       object = nullptr;
   }

   // Get the type info of the stored object
   const std::type_info& Type() const {
       return object ? object->type() : typeid(void);
   }

   // Get the value as a specific type
   template<typename T>
   T GetValue() const {
       // Check if the stored type matches the requested type
       if (typeid(T) != object->type()) {
           throw std::bad_cast();
       }
       // Cast and return the value
       return static_cast<Derived<T>*>(object)->value;
   }
};

int main() {
   Any a = 10; // int value
   std::cout << a.GetValue<int>() << std::endl;

   a = std::string("Hello"); // string value
   std::cout << a.GetValue<std::string>() << std::endl;

   if (!a.Empty()) { // Check Any object is not empty
       std::cout << a.Type().name() << std::endl; // stored type name
   }

   try {
       std::cout << a.GetValue<int>() << std::endl; // Try to get an int value
   } catch (const std::bad_cast& e) { // Catch bad_cast exception
       std::cout << "Bad cast detected" << std::endl;
   }

   a.Clear();
   std::cout << std::boolalpha << a.Empty() << std::endl; // Print if the Any object is empty

   return 0;
}
