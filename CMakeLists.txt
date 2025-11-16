cmake_minimum_required(VERSION 3.29)
project(projektA2)

set(CMAKE_CXX_STANDARD 20)

add_executable(projektA2 pocet_slov.cpp
        BST.cpp
        InputProcesor.h
        InputProcesor.cpp
        BST.h
        AVL.h
        TreeBase.h
        AVL.cpp
        OPT.h
        main.cpp
        opt.cpp)
