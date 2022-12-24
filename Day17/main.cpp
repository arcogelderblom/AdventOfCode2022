#include <iostream>
#include <cassert>
#include <chrono>

#include <utility>
#include <set>
#include <map>
#include <algorithm>

#include "inputfile.hpp"
#include "stringoperations.hpp"

typedef std::pair<int, int> Coordinate;

std::vector<Coordinate> getNewShape(Coordinate start, std::string currentShape, const std::vector<std::string> & shapeStr)
{
    std::vector<std::set<Coordinate>> shapes = {{{0,0}, {1,0}, {2,0}, {3,0}},
                                                {{1,0}, {0,-1}, {1,-1}, {2,-1}, {1,-2}},
                                                {{2,0}, {2,-1}, {0,-2}, {1,-2}, {2,-2}},
                                                {{0,0}, {0,-1}, {0,-2}, {0,-3}},
                                                {{0,0}, {1,0}, {0,-1}, {1,-1}}};
    std::vector<Coordinate> shape;
    if (currentShape == "-")
    {
        // nothing needed
    }
    else if (currentShape == "+")
    {
        start.second += 2;
    }
    else if (currentShape == "_|")
    {
        start.second += 2;
    }
    else if (currentShape == "|")
    {
        start.second += 3;
    }
    else if (currentShape == "[]")
    {
        start.second += 1;
    }

    if (std::distance(shapeStr.begin(), std::find(shapeStr.begin(), shapeStr.end(), currentShape)) < shapes.size())
    {
        for (const Coordinate c : shapes[std::distance(shapeStr.begin(), std::find(shapeStr.begin(), shapeStr.end(), currentShape))])
        {
            Coordinate current = start;
            current.first += c.first;
            current.second += c.second;
            shape.push_back(current);
        }
    }
    return shape;
}

void processMoving(std::vector<Coordinate> & actualShape, const char & instruction, const std::vector<std::string> & chamber)
{
    // calculate bounds
    int minX = std::numeric_limits<int>::max();
    int maxX = 0;

    for (const Coordinate & c : actualShape)
    {
        if (c.first < minX)
        {
            minX = c.first;
        }
        if (c.first > maxX)
        {
            maxX = c.first;
        }
    }

    // proces the moving
    if (instruction == '>')
    {
        bool collisionRight = false;
        if (maxX < 6)
        {
            for (const Coordinate & c : actualShape)
            {
                Coordinate coordinateToCheck = c;
                coordinateToCheck.first += 1;
                if (chamber[coordinateToCheck.second][coordinateToCheck.first] == '#')
                {
                    collisionRight = true;
                }
            }
        }
        if (maxX < 6 && !collisionRight)
        {
            for (Coordinate & c : actualShape)
            {
                c.first += 1;
            }
        }
    }
    else if (instruction == '<')
    {
        bool collisionLeft = false;
        if (minX > 0)
        {
            for (const Coordinate & c : actualShape)
            {
                Coordinate coordinateToCheck = c;
                coordinateToCheck.first -= 1;
                if (chamber[coordinateToCheck.second][coordinateToCheck.first] == '#')
                {
                    collisionLeft = true;
                }
            }
        }
        if (minX > 0 && !collisionLeft)
        {
            for (Coordinate & c : actualShape)
            {
                c.first -= 1;
            }
        }
    }
}

bool checkCollisions(std::vector<Coordinate> & actualShape, const std::vector<std::string> & chamber)
{
    // check collisions
    for (const Coordinate & c : actualShape)
    {
        Coordinate coordinateToCheck = c;
        coordinateToCheck.second -= 1;
        if (coordinateToCheck.second < 0 || chamber[coordinateToCheck.second][coordinateToCheck.first] == '#')
        {
            return true;
        }
    }
    return false;
}

int part1(const std::string & input) 
{
    std::vector<std::string> shapes = {"-", "+", "_|", "|", "[]"};
    auto currentShape = shapes.begin();
    auto iterInput = input.begin();
    int amountOfRocksFallen = 1;
    std::vector<std::string> chamber(3500, ".......");
    while (amountOfRocksFallen <= 2022)
    {
        // get start coordinate
        Coordinate startCoordinate = std::make_pair(2, 0);
        int currentRow = 0;
        for (std::string row : chamber)
        {
            if (row.find('#') == std::string::npos)
            {
                startCoordinate.second = currentRow + 3;
                break;
            }
            currentRow++;
        }
        
        // get the shape with the start coordinate taken into account
        std::vector<Coordinate> actualShape = getNewShape(startCoordinate, *currentShape, shapes);

        // let it fall
        bool falling = true;
        while (falling)
        {
            processMoving(actualShape, *iterInput, chamber);
            falling = !checkCollisions(actualShape, chamber);
            
            // fall
            if (falling)
            {
                for (Coordinate & c : actualShape)
                {
                    c.second -= 1;
                }
            }

            iterInput++;
            if (iterInput == input.end())
            {
                iterInput = input.begin();
            }
        }

        for (Coordinate c : actualShape)
        {
            chamber[c.second][c.first] = '#';
        }

        // rock has fallen
        amountOfRocksFallen++;
        // use next shape
        currentShape++;
        if (currentShape == shapes.end())
        {
            currentShape = shapes.begin();
        }
    }

    for (int currentRow = 0; currentRow < chamber.size(); currentRow++)
    {
        if (chamber[currentRow].find('#') == std::string::npos)
        {
            return currentRow;
        }
    }
    return 0;
}

typedef std::tuple<std::string, std::string, int> State;

unsigned long long part2(const std::string & input)
{
    std::vector<std::string> shapes = {"-", "+", "_|", "|", "[]"};
    
    auto currentShape = shapes.begin();
    auto iterInput = input.begin();
    int amountOfRocksFallen = 0;
    std::vector<std::string> chamber(7500, ".......");

    std::vector<State> states;
    std::map<State, std::pair<int, int>> stateWithRockCountAndOutcome;

    while (true)
    {
        // get start coordinate
        Coordinate startCoordinate = std::make_pair(2, 0);
        int currentRow = 0;
        for (std::string row : chamber)
        {
            if (row.find('#') == std::string::npos)
            {
                startCoordinate.second = currentRow + 3;
                break;
            }
            currentRow++;
        }
        
        if (currentRow - 1 >= 0)
        {
            State currentState(chamber[currentRow - 1], *currentShape, std::distance(input.begin(), iterInput));
            auto iter = std::find(states.begin(), states.end(), currentState);
            if (iter != states.end())
            {
                if ((1000000000000 - amountOfRocksFallen) % (amountOfRocksFallen - stateWithRockCountAndOutcome[*iter].first)== 0)
                {
                    return (((1000000000000 - amountOfRocksFallen) / (amountOfRocksFallen - stateWithRockCountAndOutcome[*iter].first)) * (currentRow - stateWithRockCountAndOutcome[*iter].second)) + currentRow;
                }
            }
            else
            {
                stateWithRockCountAndOutcome[currentState] = std::make_pair(amountOfRocksFallen, currentRow);
                states.push_back(State(chamber[currentRow - 1], *currentShape, std::distance(input.begin(), iterInput)));
            }
        }
        // get the shape with the start coordinate taken into account
        std::vector<Coordinate> actualShape = getNewShape(startCoordinate, *currentShape, shapes);
        
        // let it fall
        bool falling = true;
        while (falling)
        {
            processMoving(actualShape, *iterInput, chamber);
            falling = !checkCollisions(actualShape, chamber); // if no collision then keep on falling

            // fall
            if (falling)
            {
                for (Coordinate & c : actualShape)
                {
                    c.second -= 1;
                }
            }

            iterInput++;
            if (iterInput == input.end())
            {
                iterInput = input.begin();
            }
        }

        for (Coordinate c : actualShape)
        {
            chamber[c.second][c.first] = '#';
        }

        // rock has fallen
        amountOfRocksFallen++;
        
        // use next shape
        currentShape++;
        if (currentShape == shapes.end())
        {
            currentShape = shapes.begin();
        }
    }

    for (int currentRow = 0; currentRow < chamber.size(); currentRow++)
    {
        if (chamber[currentRow].find('#') == std::string::npos)
        {
            return currentRow;
        }
    }
    return 0;
}

int main(void) 
{
    std::vector<std::string> testInput = {">>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>"};
    assert(part1(testInput[0]) == 3068);

    InputFile inputFile("AdventOfCodeInputFiles/2022/day17.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 17, puzzle 1: " << std::flush << part1(input[0]) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput[0]) == 1514285714288);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 17, puzzle 2: " << std::flush << part2(input[0]) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}