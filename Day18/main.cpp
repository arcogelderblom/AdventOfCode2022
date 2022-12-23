#include <iostream>
#include <cassert>
#include <chrono>

#include <algorithm>
#include <tuple>

#include "inputfile.hpp"
#include "stringoperations.hpp"

typedef std::tuple<int, int, int> Coordinate3D;

std::vector<Coordinate3D> getNeighbours(int x, int y, int z)
{
    Coordinate3D cube1(x + 1, y, z);
    Coordinate3D cube2(x - 1, y, z);
    Coordinate3D cube3(x, y + 1, z);
    Coordinate3D cube4(x, y - 1, z);
    Coordinate3D cube5(x, y, z + 1);
    Coordinate3D cube6(x, y, z - 1);
    return std::vector<Coordinate3D>{ cube1, cube2, cube3, cube4, cube5, cube6 };
}

int part1(const std::vector<std::string> & input) 
{
    int result = 0;
    std::vector<Coordinate3D> allCubes;
    for (std::string line : input)
    {
        std::vector<std::string> lineSplitted = StringOperations::splitString(line, ",");
        Coordinate3D cube(std::stoi(lineSplitted[0]), std::stoi(lineSplitted[1]), std::stoi(lineSplitted[2]));
        
        result += 6;
        for (const Coordinate3D & cube : getNeighbours(std::get<0>(cube), std::get<1>(cube), std::get<2>(cube)))
        {
            if (std::find(allCubes.begin(), allCubes.end(), cube) != allCubes.end())
            {
                result -= 2;
            }
        }
        
        allCubes.push_back(cube);
    }
    
    return result;
}

void getOutsideCubes(const std::vector<Coordinate3D> & allDropletCubes, std::vector<Coordinate3D> & outsideCubes, const Coordinate3D & currentCube, int minCoordinate, int maxCoordinate)
{
    if (std::get<0>(currentCube) < minCoordinate || std::get<0>(currentCube) > maxCoordinate || 
        std::get<1>(currentCube) < minCoordinate || std::get<1>(currentCube) > maxCoordinate || 
        std::get<2>(currentCube) < minCoordinate || std::get<2>(currentCube) > maxCoordinate ||
        std::find(allDropletCubes.begin(), allDropletCubes.end(), currentCube) != allDropletCubes.end() ||
        std::find(outsideCubes.begin(), outsideCubes.end(), currentCube) != outsideCubes.end())
    {
        return;
    }
    outsideCubes.push_back(currentCube);

    // check neighbours
    for (const Coordinate3D & cube : getNeighbours(std::get<0>(currentCube), std::get<1>(currentCube), std::get<2>(currentCube)))
    {
        getOutsideCubes(allDropletCubes, outsideCubes, cube, minCoordinate, maxCoordinate);
    }
}

int part2(const std::vector<std::string> & input)
{
    std::vector<Coordinate3D> allDropletCubes;
    for (std::string line : input)
    {
        std::vector<std::string> lineSplitted = StringOperations::splitString(line, ",");
        Coordinate3D cube(std::stoi(lineSplitted[0]), std::stoi(lineSplitted[1]), std::stoi(lineSplitted[2]));
        allDropletCubes.push_back(cube);
    }
    
    int result = 0;
    std::vector<Coordinate3D> outsideCubes;
    getOutsideCubes(allDropletCubes, outsideCubes, Coordinate3D(0, 0, 0), -5, 25);
    for (const Coordinate3D & cube : outsideCubes)
    {
        for (const Coordinate3D & neighbour : getNeighbours(std::get<0>(cube), std::get<1>(cube), std::get<2>(cube)))
        {
            if (std::find(allDropletCubes.begin(), allDropletCubes.end(), neighbour) != allDropletCubes.end())
            {
                result += 1;
            }
        }
    }
    
    return result;
}

int main(void) 
{
    std::vector<std::string> testInput = {"2,2,2", "1,2,2", "3,2,2", "2,1,2", "2,3,2", "2,2,1", "2,2,3", "2,2,4", "2,2,6", "1,2,5", "3,2,5", "2,1,5", "2,3,5"};
    assert(part1(testInput) == 64);

    InputFile inputFile("AdventOfCodeInputFiles/2022/day18.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 18, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 58);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 18, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}