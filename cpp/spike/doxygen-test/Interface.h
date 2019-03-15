#ifndef OPENENGINE_INTERFACE_H
#define OPENENGINE_INTERFACE_H

#include "Component.h"

//!
//! This class demonstrates an interface.
//!
//! Interfaces are used to describe what the class is capable without exposing
//! the implementation. They can be used to provide a stable (relatively) way of
//! communicating with a library that provides it.
//!
//! @version 1.0.0
//! @pre Understand how interfaces are used in C++.
//! @bug There are *no* bugs!
//! @warning Failure to define the implementation results in compiler errors!
//! @copyright GNU Public License
//! @date 1989-2018
//! @author jyates
//!
class Interface {
public:
    //!
    //! Pure virtual method that _MUST_ be defined in child classes.
    //!
    //! Describe what this method does. This should be helpful as the user will
    //! have no context or other information (aside from the declaration) on how
    //! to use this!
    //!
    virtual void pureVirtualMethod() = 0;

    //!
    //! Pure virtual getter method that _MUST_ be defined in the child class.
    //!
    //! Virtual getters might be useful to provide a way to get a dynamic type
    //! that is created at runtime, using polymorphism.
    //!
    //! @return Returns the component (@see Component) of the object that
    //!         is using this interface.
    virtual Component pureVirtualComponentGetter() const = 0;
};

#endif //OPENENGINE_INTERFACE_H
