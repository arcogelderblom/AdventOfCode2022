#include <iostream>
#include <cassert>
#include <chrono>

#include <map>
#include <set>
#include <utility>

#include "inputfile.hpp"
#include "stringoperations.hpp"

typedef std::pair<int, int> Coordinate;

int part1(const std::vector<std::string> & input, const int & resultY) 
{
    std::set<Coordinate> beaconsAndSensorsInY;
    std::map<Coordinate, char> map;
    for (const std::string & line : input)
    {
        std::vector<std::string> splitted = StringOperations::splitString(line, ": ");
        int sensorX = std::stoi(splitted[0].substr(std::string("Sensor at x=").size(), splitted[0].find(',') - std::string("Sensor at x=").size()));
        int sensorY = std::stoi(splitted[0].substr(splitted[0].find('y') + std::string("y=").size()));

        int closestBeaconX = std::stoi(splitted[1].substr(std::string("closest beacon is at x=").size(), splitted[1].find(',') - std::string("closest beacon is at x=").size()));
        int closestBeaconY = std::stoi(splitted[1].substr(splitted[1].find('y') + std::string("y=").size()));
        if (sensorY == resultY)
        {
            beaconsAndSensorsInY.insert(std::make_pair(sensorX, sensorY));
        }
        if (closestBeaconY == resultY)
        {
            beaconsAndSensorsInY.insert(std::make_pair(closestBeaconX, closestBeaconY));
        }
        int manhattanDistance = std::abs(sensorX - closestBeaconX) + std::abs(sensorY - closestBeaconY);
        
        if (((sensorY - manhattanDistance) < resultY && resultY <= sensorY) || ((sensorY + manhattanDistance) > resultY && resultY >= sensorY))
        {
            for (int x = sensorX - (manhattanDistance - std::abs(resultY - sensorY)); x <= sensorX + (manhattanDistance - std::abs(resultY - sensorY)); x++)
            {
                Coordinate c = std::make_pair(x, resultY);
                if (map.find(c) == map.end())
                {
                    map[c] = '#';
                }
            }
        }
    }
    return map.size() - beaconsAndSensorsInY.size();
}

long long part2(const std::vector<std::string> & input, int maxDimension) 
{
    std::map<int, std::set<std::pair<int, int>>> map;
    for (const std::string & line : input)
    {
        std::vector<std::string> splitted = StringOperations::splitString(line, ": ");
        int sensorX = std::stoi(splitted[0].substr(std::string("Sensor at x=").size(), splitted[0].find(',') - std::string("Sensor at x=").size()));
        int sensorY = std::stoi(splitted[0].substr(splitted[0].find('y') + std::string("y=").size()));

        int closestBeaconX = std::stoi(splitted[1].substr(std::string("closest beacon is at x=").size(), splitted[1].find(',') - std::string("closest beacon is at x=").size()));
        int closestBeaconY = std::stoi(splitted[1].substr(splitted[1].find('y') + std::string("y=").size()));
        int manhattanDistance = std::abs(sensorX - closestBeaconX) + std::abs(sensorY - closestBeaconY);
        
        for (int x = sensorX - manhattanDistance; x <= sensorX + manhattanDistance; x++)
        {
            if (x < 0)
            {
                x = 0;
            }
            else if (x > maxDimension)
            {
                break;
            }
            int minY = sensorY - (manhattanDistance - std::abs(sensorX - x));
            int maxY = sensorY + (manhattanDistance - std::abs(sensorX - x));
            if (minY < 0) minY = 0;
            if (maxY > maxDimension) maxY = maxDimension;
            map[x].insert(std::make_pair(minY, maxY));
        }
    }
    
    for (int x = 0; x < maxDimension; x++)
    {
        std::set<std::pair<int, int>> currentSet = map[x];
        int minY = currentSet.begin()->first;
        int maxY = currentSet.begin()->second;
        
        for (const std::pair<int, int> & current : currentSet)
        {
            if (current.first > maxY + 1)
            {
                return (long long)x * 4000000 + (long long)current.first - 1;
            }
            else
            {
                if (current.second > maxY)
                {
                    maxY = current.second;
                }
            }
        }
    }
    
    return 0;
}

int main(void) 
{
    std::vector<std::string> testInput = {"Sensor at x=2, y=18: closest beacon is at x=-2, y=15", "Sensor at x=9, y=16: closest beacon is at x=10, y=16", "Sensor at x=13, y=2: closest beacon is at x=15, y=3", "Sensor at x=12, y=14: closest beacon is at x=10, y=16", "Sensor at x=10, y=20: closest beacon is at x=10, y=16", "Sensor at x=14, y=17: closest beacon is at x=10, y=16", "Sensor at x=8, y=7: closest beacon is at x=2, y=10", "Sensor at x=2, y=0: closest beacon is at x=2, y=10", "Sensor at x=0, y=11: closest beacon is at x=2, y=10", "Sensor at x=20, y=14: closest beacon is at x=25, y=17", "Sensor at x=17, y=20: closest beacon is at x=21, y=22", "Sensor at x=16, y=7: closest beacon is at x=15, y=3", "Sensor at x=14, y=3: closest beacon is at x=15, y=3", "Sensor at x=20, y=1: closest beacon is at x=15, y=3"};
    assert(part1(testInput, 10) == 26);

    InputFile inputFile("InputFiles/day15.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 15, puzzle 1: " << std::flush << part1(input, 2000000) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput, 20) == 56000011);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 15, puzzle 2: " << std::flush << part2(input, 4000000) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}