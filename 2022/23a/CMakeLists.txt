cmake_minimum_required(VERSION 3.14)

project(23a LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(23a
    grid.h grid.cpp
    main.cpp
)
target_link_libraries(23a)
target_compile_options(23a PRIVATE -Werror -Wbool-compare -Waddress -Wall -Wconversion -Wextra -pedantic-errors -Wsign-conversion -fsyntax-only -Wpedantic -pedantic-errors -w  -Wextra  -Wall  -Waddress  -Waddress-of-packed-member -Waggregate-return  -Waligned-new -Walloc-zero
    -Walloca  -Wno-aggressive-loop-optimizations  -Warray-bounds -Wno-attributes
    -Wbool-compare  -Wbool-operation -Wno-builtin-declaration-mismatch -Wno-builtin-macro-redefined -Wc++11-compat  -Wc++14-compat
    -Wc++17-compat -Wcast-align  -Wcast-align=strict  -Wcast-function-type  -Wcast-qual -Wchar-subscripts  -Wcatch-value  -Wclobbered  -Wcomment  -Wconditionally-supported
    -Wconversion  -Wcoverage-mismatch  -Wno-cpp  -Wdangling-else  -Wdate-time -Wdelete-incomplete -Wno-attribute-warning -Wno-deprecated  -Wno-deprecated-declarations
    -Wdisabled-optimization -Wno-div-by-zero  -Wdouble-promotion -Wduplicated-branches  -Wduplicated-cond -Wempty-body  -Wenum-compare
    -Wno-endif-labels  -Wexpansion-to-defined -Wextra-semi  -Wfatal-errors -Wfloat-equal  -Wformat  -Wformat=2 -Wno-format-contains-nul  -Wno-format-extra-args
    -Wformat-nonliteral -Wformat-security  -Wformat-signedness -Wformat-y2k  -Wframe-address  -Wno-free-nonheap-object
    -Whsa  -Wif-not-aligned -Wignored-qualifiers  -Wignored-attributes -Wimplicit-fallthrough
    -Winit-self  -Winline -Wint-in-bool-context -Wno-int-to-pointer-cast  -Winvalid-memory-model  -Wno-invalid-offsetof
    -Winvalid-pch  -Wlogical-op  -Wlogical-not-parentheses  -Wlong-long -Wmain  -Wmaybe-uninitialized  -Wmemset-elt-size  -Wmemset-transposed-args -Wmisleading-indentation
    -Wmissing-attributes  -Wmissing-braces -Wmissing-field-initializers  -Wmissing-format-attribute -Wmissing-include-dirs  -Wmissing-noreturn  -Wmissing-profile -Wno-multichar
    -Wmultistatement-macros  -Wnonnull  -Wnonnull-compare -Wnull-dereference  -Wodr  -Wno-overflow  -Wopenmp-simd -Woverlength-strings
    -Wpacked  -Wpacked-bitfield-compat -Wpacked-not-aligned  -Wpadded -Wparentheses  -Wno-pedantic-ms-format -Wplacement-new -Wpointer-arith  -Wpointer-compare
    -Wno-pragmas  -Wno-prio-ctor-dtor  -Wredundant-decls -Wrestrict  -Wno-return-local-addr -Wreturn-type  -Wsequence-point  -Wshadow -Wshadow=global
    -Wshift-overflow -Wshift-count-negative  -Wshift-count-overflow  -Wshift-negative-value -Wsign-compare  -Wsign-conversion
    -Wfloat-conversion -Wno-scalar-storage-order  -Wsizeof-pointer-div -Wsizeof-pointer-memaccess  -Wsizeof-array-argument -Wstack-protector   -Wstrict-aliasing
    -Wstrict-overflow  -Wstringop-truncation  -Wsubobject-linkage
    -Wsuggest-final-types   -Wsuggest-final-methods  -Wsuggest-override -Wswitch  -Wswitch-bool  -Wswitch-default  -Wswitch-enum -Wswitch-unreachable  -Wsync-nand -Wsystem-headers
    -Wtautological-compare  -Wtrampolines  -Wtrigraphs -Wtype-limits  -Wundef -Wuninitialized  -Wunknown-pragmas -Wunused  -Wunused-function -Wunused-label
    -Wunused-local-typedefs  -Wunused-macros -Wunused-parameter  -Wno-unused-result -Wunused-value  -Wunused-variable -Wunused-const-variable  -Wunused-but-set-parameter
    -Wunused-but-set-variable -Wuseless-cast  -Wvariadic-macros  -Wvector-operation-performance -Wvla -Wvolatile-register-var -Wwrite-strings
    -Wzero-as-null-pointer-constant)
install(TARGETS 23a
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
