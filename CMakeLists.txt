cmake_minimum_required(VERSION 3.27)
project(linear_form C)

set(CMAKE_C_STANDARD 23)

add_executable(linear_form main.c
        utility/FieldInfo.h
        utility/LinearForm.c
        utility/LinearForm.h
        utility/Interface.c
        utility/Interface.h
        utility/Exception.c
        utility/Exception.h
        types/Integer.c
        types/Integer.h
        types/Real.c
        types/Real.h
        types/Complex.c
        types/Complex.h
        tests/Test.c
        tests/Test.h
)
