#include <iostream>
#include <string>
#include <typeinfo>
#include <exception>

class Any {
private:
    class Base {
    public:
        virtual ~Base() {}
        virtual Base* clone() const = 0;
        virtual const std::type_info& type() const = 0;
    };

    template<typename T>
    class Derived : public Base {
    public:
        T value;

        Derived(const T& value): value(value) {}

        Base* clone() const override {
            return new Derived<T>(value);
        }

        const std::type_info& type() const override {
            return typeid(value);
        }
    };

    Base* object = nullptr;

public:
    Any() : object(nullptr) {}

    template<typename T>
    Any(const T& value) : object(new Derived<T>(value)) {}

    Any(const Any& other) {
        if (other.object) {
            object = other.object->clone();
        }
    }

    Any& operator=(const Any& other) {
        if (&other != this) {
            delete object;
            object = other.object ? other.object->clone() : nullptr;
        }
        return *this;
    }

    ~Any() {
        delete object;
    }

    bool Empty() const {
        return object == nullptr;
    }

    void Clear() {
        delete object;
        object = nullptr;
    }

    const std::type_info& Type() const {
        return object ? object->type() : typeid(void);
    }

    template<typename T>
    T GetValue() const {
        if (typeid(T) != object->type()) {
            throw std::bad_cast();
        }
        return static_cast<Derived<T>*>(object)->value;
    }
};

int main() {
    Any a = 10;
    std::cout << a.GetValue<int>() << std::endl;

    a = std::string("Hello");
    std::cout << a.GetValue<std::string>() << std::endl;

    if (!a.Empty()) {
        std::cout << a.Type().name() << std::endl;
    }

    try 
    {
        std::cout << a.GetValue<int>() << std::endl;
    } 
    catch (const std::bad_cast& e) 
    {
        std::cout << "Bad cast detected" << std::endl;
    }

    a.Clear();
    std::cout << std::boolalpha << a.Empty() << std::endl;

    return 0;
}
