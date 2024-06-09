cmake_minimum_required(VERSION 3.28)
project(exe3)

set(CMAKE_CXX_STANDARD 11)

#add_executable(exe3 main.cpp
#        Player.hpp
#        "Demo (2).cpp"
#        Board.hpp
#        Board.cpp
#        Catan.hpp
#        Catan.cpp
#        Countable.hpp
#        DevelopmentCard.hpp
#        Dice.hpp
#        Graph.hpp
#        Graph.cpp
#        Hexagon.hpp
#        Identifiable.hpp
#        Land.hpp
#        Player.cpp
#        Property.cpp
#        Property.hpp
#        ResourceCard.cpp
#        ResourceCard.hpp
#        GameSet.hpp
#)

add_executable(Catan
        Demo.cpp
        Board.hpp
        Board.cpp
        Catan.cpp
        Catan.hpp
        Countable.hpp
        Dice.hpp
        Graph.cpp
        Graph.hpp
        Identifiable.hpp
        Land.hpp
        Player.cpp
        Player.hpp
        Property.cpp
        Property.hpp
        GameSet.hpp
)

add_executable(Test Test.cpp TestCounter.cpp doctest.h
        Board.hpp
        Board.cpp
        Catan.cpp
        Catan.hpp
        Countable.hpp
        Dice.hpp
        Graph.cpp
        Graph.hpp
        Identifiable.hpp
        Land.hpp
        Player.cpp
        Player.hpp
        Property.cpp
        Property.hpp
        GameSet.hpp
)
