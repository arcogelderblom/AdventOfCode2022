#include <iostream>
#include <cassert>
#include <chrono>

#include <set>
#include <map>
#include <list>
#include <utility>
#include <algorithm>

#include "inputfile.hpp"
#include "stringoperations.hpp"

int getNewIndex(long long coordinate, long long currentIndex, long long maxIndex)
{
    return (currentIndex + coordinate) % maxIndex;
}

void mix(std::list<int> & uniqueIdentifiers, std::map<int, long long> uniqueIdentifierAndCoordinate)
{
    for (int identifier = 0; identifier < uniqueIdentifiers.size(); identifier++)
    {
        auto iter = std::find(uniqueIdentifiers.begin(), uniqueIdentifiers.end(), identifier);
        int currentIndex = std::distance(uniqueIdentifiers.begin(), iter);
        int newIndex = getNewIndex(uniqueIdentifierAndCoordinate[identifier], currentIndex, uniqueIdentifiers.size() - 1);

        if (uniqueIdentifierAndCoordinate[identifier] == 0) 
        {
            continue; // skip since it doesn't move
        }

        uniqueIdentifiers.erase(iter);

        if (uniqueIdentifierAndCoordinate[identifier] > 0)
        {
            uniqueIdentifiers.insert(std::next(uniqueIdentifiers.begin(), newIndex), identifier);
        }
        else if (uniqueIdentifierAndCoordinate[identifier] < 0)
        {
            uniqueIdentifiers.insert(std::next(uniqueIdentifiers.end(), newIndex), identifier);
        }
        else if (newIndex == 0)
        {
            uniqueIdentifiers.insert(uniqueIdentifiers.begin(), identifier);
        }
    }
}

int part1(const std::vector<int> & input) 
{
    std::list<int> uniqueIdentifiers;
    std::map<int, long long> uniqueIdentifierAndCoordinate;
    for (int i = 0; i < input.size(); i++)
    {
        uniqueIdentifierAndCoordinate[i] = input[i];
        uniqueIdentifiers.insert(uniqueIdentifiers.end(), i);
    }

    mix(uniqueIdentifiers, uniqueIdentifierAndCoordinate);

    std::vector<int> resultingVector;
    for (const int & uniqueIdentifier : uniqueIdentifiers)
    {
        resultingVector.push_back(uniqueIdentifierAndCoordinate[uniqueIdentifier]);
    }
    
    int indexFor0 = std::distance(resultingVector.begin(), std::find(resultingVector.begin(), resultingVector.end(), 0));
    int first = resultingVector[((1000 % resultingVector.size()) + indexFor0) % resultingVector.size()];
    int second = resultingVector[((2000 % resultingVector.size()) + indexFor0) % resultingVector.size()];
    int third = resultingVector[((3000 % resultingVector.size()) + indexFor0) % resultingVector.size()];
    
    return first + second + third;
}

long long part2(const std::vector<int> & input)
{
    const long long decryptionKey = 811589153;

    std::list<int> uniqueIdentifiers;
    std::map<int, long long> uniqueIdentifierAndCoordinate;
    for (int i = 0; i < input.size(); i++)
    {
        uniqueIdentifierAndCoordinate[i] = (long long)input[i] * 811589153;
        uniqueIdentifiers.insert(uniqueIdentifiers.end(), i);
    }
    
    for (int i = 0; i < 10; i++)
    {
        mix(uniqueIdentifiers, uniqueIdentifierAndCoordinate);
    }

    std::vector<long long> resultingVector;
    for (const int & uniqueIdentifier : uniqueIdentifiers)
    {
        resultingVector.push_back(uniqueIdentifierAndCoordinate[uniqueIdentifier]);
    }
    
    int indexFor0 = std::distance(resultingVector.begin(), std::find(resultingVector.begin(), resultingVector.end(), 0));
    long long first = resultingVector[((1000 % resultingVector.size()) + indexFor0) % resultingVector.size()];
    long long second = resultingVector[((2000 % resultingVector.size()) + indexFor0) % resultingVector.size()];
    long long third = resultingVector[((3000 % resultingVector.size()) + indexFor0) % resultingVector.size()];
    
    return first + second + third;
}

int main(void) 
{
    std::vector<int> testInput = {1, 2, -3, 3, -2, 0, 4};
    assert(part1(testInput) == 3);

    InputFile inputFile("AdventOfCodeInputFiles/2022/day20.txt");
    std::vector<int> input = inputFile.getContentAsInt("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 20, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 1623178306);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 20, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}