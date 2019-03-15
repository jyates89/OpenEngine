#ifndef OPENENGINE_SUPER_H
#define OPENENGINE_SUPER_H

#include <cstdio>

//! A class that can be inherited from in addition to being used standalone.
//!
//! This class demonstrates a typical class that might expect to be inherited
//! from, but that also supports being used standalone. Since there are no
//! pure virtual methods, the class can be used as-is. However, since the
//! destructor is virtual, it is safe to inherit from as well.
//!
//! @version 1.0.0
//! @pre Understand inheritance.
//! @bug There are *no* bugs!
//! @warning Beware of using inheritance when it isn't needed.
//! @copyright GNU Public License
//! @date 1989-2018
//! @author jyates
//!
class Super {
protected:
    //! Protected method that can only be called by the owning and child classes.
    //!
    //! This method is only accessible to the class that owns it and any child
    //! class that inherits from it.
    //!
    void superProtectedMethod();

public:
    //! A simple enumeration.
    //!
    //! This paragraph might be used to describe the purpose of this enumeration
    //! along with what the values can be used for.
    enum class SuperEnum {
        ENUM_ONE, //!< ENUM_ONE = 0
        ENUM_TWO, //!< ENUM_TWO = 1
    };

    //! This is the constructor for Super..
    //!
    //! The constructor is marked explicit, as that is recommended when the
    //! constructor only has a single argument. This avoids unintentional
    //! implicit conversions.
    //!
    //! @note The constructor is defined because we need to initialize the
    //!       member variables of this class.
    //!
    //! @param[in] superEnum We use the constructor to provide the initial state.
    //!
    explicit Super(SuperEnum superEnum);


    //! The virtual destructor for this class.
    //!
    //! We are explicitly declaring this destructor to ensure it is marked as
    //! as virtual (avoid memory leaks when using a sub class that inherits from
    //! this class. At the same time, it is marked as using the default
    //! implementation that will be generate by the compiler.
    //!
    virtual ~Super() = default;

    //! Virtual parent method.
    //!
    //! This method will be called if there is nothing in a child class that
    //! overrides it.
    //!
    virtual void superMethod();

    //! Getter for the enumeration stored in the parent class.
    //!
    //! @return Returns the enumeration stored in this object.
    //!
    SuperEnum superEnum() const;

private:
    //! An enumerated member variable.
    //!
    //! This can be used to determine the object type, or for any other purpose.
    //!
    Super::SuperEnum m_superEnum;
};

void Super::superProtectedMethod() {
    std::printf("%s: %d: %s: printing stuff!\n",
            __FILE__, __LINE__, __FUNCTION__);
}

Super::Super(Super::SuperEnum superEnum) :
    m_superEnum(superEnum) { }

void Super::superMethod() {
    std::printf("%s: %d: %s: we are inside the parent method!\n",
                __FILE__, __LINE__, __FUNCTION__);
}

Super::SuperEnum Super::superEnum() const {
    std::printf("%s: %d: %s: we are returning the enumeration value ('%d')!\n",
                __FILE__, __LINE__, __FUNCTION__, m_superEnum);
    return m_superEnum;
}

#endif //OPENENGINE_SUPER_H
