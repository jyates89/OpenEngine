
################################################################################
# Common flags that are conditionally set depending on the build type. Placed
# here so that it doesn't need to be repeated everywhere it is used.
set(COMMON_COMPILE_FLAGS
        # Conditional debug flags:
        PRIVATE $<$<CONFIG:DEBUG>:-Wall>        # turn on all warnings
        PRIVATE $<$<CONFIG:DEBUG>:-O0>          # turn off all optimizations
        PRIVATE $<$<CONFIG:DEBUG>:-ggdb3>       # enhanced GDB debugging support
        PRIVATE $<$<CONFIG:DEBUG>:-gdwarf-4>    # enhanced debugging in DWARF
        # annotate assignments to user variables early in the compilation
        PRIVATE $<$<CONFIG:DEBUG>:-fvar-tracking-assignments>
        PRIVATE $<$<CONFIG:DEBUG>:-rdynamic>    # support for dlopen
        PRIVATE $<$<CONFIG:DEBUG>:-funwind-tables>
        PRIVATE $<$<CONFIG:DEBUG>:-fno-builtin> # disable built-in replacements
        PRIVATE $<$<CONFIG:DEBUG>:-fno-inline>  # disable inlining
        PRIVATE $<$<CONFIG:DEBUG>:-fno-eliminate-unused-debug-types>

        # Conditional release flags:
        PRIVATE $<$<CONFIG:RELEASE>:-Os>        # optimize for binary size
        PRIVATE $<$<CONFIG:RELEASE>:-s>         # strip symbol table from binary
        )

################################################################################
# Common feature sets that are used. Right now just the standard C++11 spec
# is all we need to specify.
set(COMMON_COMPILE_FEATURES
        cxx_std_11
        )

# Disable GNU extensions to assist with being cross-platform; needed when using
# the above 'cxx_std_11', otherwise gnu++11 would be used instead of c++11.
set(CMAKE_CXX_EXTENSIONS OFF)

################################################################################
# Enable Various Tools
# --------------------
# LINK_WHAT_YOU_USE: enable warnings for needless linking of libraries.
set(CMAKE_LINK_WHAT_YOU_USE ON)
