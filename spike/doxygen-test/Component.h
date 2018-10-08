#ifndef OPENENGINE_COMPONENT_H
#define OPENENGINE_COMPONENT_H

//! Some component to be used in other classes.
//!
//! This is class is used to provide an example of composition.
//!
//! @version 1.0.0
//! @pre Understand composition.
//! @bug There are *no* bugs!
//! @copyright GNU Public License
//! @date 1989-2018
//! @author jyates
//!
class Component {
    //! Simple component of type INT.
    int m_someComponentMember;

public:
    //! Explicit constructor used to initialize an instance of Component.
    //!
    //! @param componentMember Value used for initialization.
    //!
    explicit Component(int componentMember);

    //! Explicitly declared destructor marked as default.
    //!
    //! We explicitly declare this to ensure it is marked as virtual, which
    //! makes this class safe to use for inheritance. However, being marked as
    //! default, the compiler will generate a simple implementation for us.
    //!
    virtual ~Component() = default;

    //! Simple getter for the component member variable.
    int someComponentMember() const;
};

inline Component::Component(int componentMember) :
    m_someComponentMember(componentMember) { }

inline int Component::someComponentMember() const {
    return m_someComponentMember;
}

#endif //OPENENGINE_COMPONENT_H
