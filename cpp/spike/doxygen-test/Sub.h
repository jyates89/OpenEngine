#ifndef OPENENGINE_SUB_H
#define OPENENGINE_SUB_H

#include "Super.h"
#include "Interface.h"

#include "Component.h"

#include <cstdio>

//! A sub, or child, class, that inherits from a parent AND an interface.
//!
//! This class demonstrates a sub class in inheritance, along with the use of
//! an interface. Inheritance is used when you want to have an is-a relationship
//! between classes. For instance, a *car* is-a *automobile*, or alternatively, a
//! *truck* is-a *automobile*. Interfaces are used when you want to define a way
//! to use the class (which will not commonly change). This is especially
//! important for binary API compatibility.
//!
//! @version 1.0.0
//! @pre Understand inheritance.
//! @bug There are *no* bugs!
//! @warning Beware of using inheritance when it isn't needed.
//! @copyright GNU Public License
//! @date 1989-2018
//! @author jyates
//!
class Sub : public Super, public Interface {
    //! A simple member which has the type INT.
    //!
    //! You might generally use this paragraph to describe what exactly this
    //! member variable is used for.
    //!
    int m_subMember;

    //! This variable is a component (composition is used).
    //!
    //! Composition should be used when you have components that need to be
    //! associated with an object, but that do not have an _is-a_ relationship.
    //!
    Component m_componentMember;

public:
    //! This is the constructor for Sub.
    //!
    //! The constructor is marked explicit, as that is recommended when the
    //! constructor only has a single argument. This avoids unintentional
    //! implicit conversions.
    //!
    //! @note The constructor is defined because we need to initialize the
    //!       member variables of this class.
    //!
    //! @param[in] component We use the constructor to provide the initial state.
    //!
    explicit Sub(const Component& component);

    //! The destructor for this child class.
    //!
    //! We are explicitly declaring this destructor to ensure it is marked as
    //! as an override to the destructor in the parent class. At the same time,
    //! it is marked as using the default implementation that will be generated
    //! by the compiler.
    //!
    //! @note Virtual is not needed here, as override already indicates that this
    //!       is a virtual method that is overriding a method in the parent class.
    ~Sub() override = default;

    //! A simple method declared in this child class.
    //!
    //! Use this paragraph to describe what exactly this method does; such as,
    //! whether or not the state of the object changes after calling it!
    //!
    void subMethod();

    //! This is a method that overrides a virtual method in the parent class.
    //!
    //! For C++11 onward, it is recommended that the keyword _override_ be used
    //! when overriding virtual methods in a parent class. In this case, we are
    //! overriding the pure virtual method provided in the interface class
    //! (@see Interface).
    //!
    void pureVirtualMethod() override;


    //! Getter to return the integer stored in an instance of this class.
    //!
    //! A const qualified getter to obtain the current value of the member
    //! variable stored in an instance of this class.
    //!
    //! @return Return the integer stored in this object.
    //!
    int subMember() const;

    //! Setter used to update the integer stored in an instance of this class.
    //!
    //! A simple setter that takes an integer by value and updates the variable
    //! stored in the given instance of this class.
    //!
    //! @param subMember This is an integer.
    //!
    void subMember(int subMember);

    //! Getter used to return the component stored.
    //!
    //! If a pointer is used as the return value for a virtual method, it can
    //! be used for polymorphism.
    //!
    //! @return Return the component member of this class.
    //!
    Component pureVirtualComponentGetter() const override;
};

Sub::Sub(const Component& component) :
    Super(Super::SuperEnum::ENUM_ONE),
    m_subMember(0),
    m_componentMember(component) {
}

void Sub::subMethod() {
    std::printf("%s: %d: %s: we are a normal method, and calling a protected"
                " method in the parent class!\n",
                __FILE__, __LINE__, __FUNCTION__);
    superProtectedMethod();
}

void Sub::pureVirtualMethod() {
    std::printf("%s: %d: %s: we are purely virtual and defined here!\n",
                __FILE__, __LINE__, __FUNCTION__);
}

int Sub::subMember() const {
    std::printf("%s: %d: %s: returning a normal member variable ('%d')!\n",
                __FILE__, __LINE__, __FUNCTION__, m_subMember);
    return m_subMember;
}

void Sub::subMember(int subMember) {
    std::printf("%s: %d: %s: setting a normal member variable! ('%d')\n",
                __FILE__, __LINE__, __FUNCTION__, subMember);
    m_subMember = subMember;
}


Component Sub::pureVirtualComponentGetter() const {
    std::printf("%s: %d: %s: returning the component!\n",
                __FILE__, __LINE__, __FUNCTION__);
    return m_componentMember;
}

#endif //OPENENGINE_SUB_H
