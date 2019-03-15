#include <memory>

#include "Interface.h"

#include "Super.h"
#include "Sub.h"

#include "Component.h"

#include "ArrayTemplate.h"
#include "Calculations.h"

int main(int argc, char** argv) {

    //! Demonstrate composition (stored in Sub object below):
    Component component(0xDEADBEEF);

    //! Demonstrate interfaces:
    std::unique_ptr<Interface> interface;
    interface = std::unique_ptr<Interface>(
            new Sub(component));

    //! Demonstrate virtual methods:
    interface->pureVirtualComponentGetter();

    //! Demonstrate inheritance and polymorphism:
    auto sub = std::unique_ptr<Sub>(
            dynamic_cast<Sub*>(interface.release()));
    if (sub != nullptr) {
        sub->subMethod();
        sub->superMethod();
        sub->superEnum();

        //! Demonstrate polymorphism through the interface:
        sub->pureVirtualMethod();
    } else {

        // If sub is not really a Sub type, a nullptr is returned.
        std::printf("%s: %d: %s: sub is a nullptr!\n",
                    __FILE__, __LINE__, __FUNCTION__);
        sub.reset();
    }

    //! Demonstrate the templated array with default size:
    Array<char> smallArray;
    smallArray[0] = '?';

    //! Demonstrate templated array holding a simple string:
    Array<char, 100> largeArray;
    largeArray[0] = 'T';
    largeArray[1] = 'h';
    largeArray[2] = 'i';
    largeArray[3] = 's';
    largeArray[4] = 0;
    std::printf("%s: %d: %s: LargeArray = '%s'\n",
            __FILE__, __LINE__, __FUNCTION__, largeArray.raw());

    //! Demonstrate a templated array supporting modern for loops:
    Array<int, 20> mediumArray(1);
    for (auto& it : mediumArray) {
        std::printf("%s: %d: %s: contents of '%p' = '%d'\n",
                __FILE__, __LINE__, __FUNCTION__, &it, it);
    }

    //! Demonstrate templated functions in a namespace:
    int a = 5, b = 10;
    std::printf("%s: %d: %s: '%d' + '%d' = '%d'\n",
            __FILE__, __LINE__, __FUNCTION__,
            a, b, Calculator::add(a, b));

    std::printf("%s: %d: %s: '%d' - '%d' = '%d'\n",
            __FILE__, __LINE__, __FUNCTION__,
            a, b, Calculator::sub(a, b));
}
