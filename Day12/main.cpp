#include <iostream>
#include <cassert>
#include <chrono>

#include <utility>
#include <cmath>
#include <map>
#include <set>
#include <limits>
#include <queue>
#include <list>

#include "inputfile.hpp"
#include "stringoperations.hpp"

typedef std::pair<int, int> Coordinate;

// this function returns a map with the distance to the end from any given coordinate using Breadth First Search
std::map<Coordinate, int> getAmountOfStepsToEndFromCoordinates(std::vector<std::string> input)
{
    Coordinate endCoordinate;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].find('S') != std::string::npos)
        {
            input[i].replace(input[i].find('S'), 1, "a");
        }
        if (input[i].find('E') != std::string::npos)
        {
            endCoordinate = std::make_pair(input[i].find('E'), i);
            input[i].replace(input[i].find('E'), 1, "z");
        }
    }

    const std::vector<Coordinate> directions = { {1, 0}, // right
                                                 {0, 1}, // down 
                                                 {-1, 0}, // left
                                                 {0, -1} }; // up

    std::map<Coordinate, int> coordinateWithSteps;
    std::list<std::pair<Coordinate, int>> toBeVisited;
    int currentSteps = 0;
    
    // do a bfs
    toBeVisited.push_back(std::make_pair(endCoordinate, currentSteps));
    while(toBeVisited.size() > 0)
    {
        const Coordinate currentCoordinate = toBeVisited.front().first;
        currentSteps = toBeVisited.front().second;
        toBeVisited.pop_front();

        for (const Coordinate & direction : directions)
        {
            Coordinate option = currentCoordinate;
            option.first += direction.first;
            option.second += direction.second;
            if (option.first >= 0 && option.first < input[0].size() && option.second >= 0 && option.second < input.size())
            {
                char current = input[currentCoordinate.second][currentCoordinate.first];
                char target = input[option.second][option.first];
               
                if (target - current >= -1 && coordinateWithSteps.find(option) == coordinateWithSteps.end())
                {
                    coordinateWithSteps[option] = currentSteps+1;
                    toBeVisited.push_back(std::make_pair(option, currentSteps + 1));
                }
            }
        }
    }

    return coordinateWithSteps;
}

int part1(std::vector<std::string> input)
{
    Coordinate startCoordinate;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].find('S') != std::string::npos)
        {
            startCoordinate = std::make_pair(input[i].find('S'), i);
        }
    }

    std::map<Coordinate, int> m = getAmountOfStepsToEndFromCoordinates(input);
    return m[startCoordinate];
}

int part2(std::vector<std::string> input) 
{
    std::vector<Coordinate> possibleStartPoints;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].size(); j++)
        {
            if (input[i][j] == 'a')
            {
                possibleStartPoints.push_back(std::make_pair(j, i));
            }
        }
    }

    std::map<Coordinate, int> m = getAmountOfStepsToEndFromCoordinates(input);

    int lowestAmountOfSteps = std::numeric_limits<int>::max();
    for (const Coordinate & c : possibleStartPoints)
    {
        if (m.find(c) != m.end())
        {
            if (m[c] < lowestAmountOfSteps)
            {
                lowestAmountOfSteps = m[c];
            }
        }
    }
    return lowestAmountOfSteps;
}

int main(void) 
{
    std::vector<std::string> testInput = {"Sabqponm", "abcryxxl", "accszExk", "acctuvwj", "abdefghi"};
    assert(part1(testInput) == 31);

    InputFile inputFile("InputFiles/day12.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 12, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 29);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 12, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}