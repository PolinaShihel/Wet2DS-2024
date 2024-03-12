cmake_minimum_required(VERSION 3.25)
project(Wet2DS_2024 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Wet2DS_2024
        hashTable.h Team.cpp Team.h Contestant.cpp Contestant.h main24a2.cpp Node.h AVL_tree.h olympics24a2.cpp olympics24a2.h wet2util.h)
