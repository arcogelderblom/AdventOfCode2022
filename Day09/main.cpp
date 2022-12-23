#include <iostream>
#include <cassert>
#include <chrono>

#include <map>
#include <set>
#include <utility>

#include "inputfile.hpp"
#include "stringoperations.hpp"

void moveHead(std::pair<int, int> & head, const std::string & direction)
{
    if (direction == "U")
    {
        head = std::make_pair(head.first, head.second + 1);
    }
    else if (direction == "D")
    {
        head = std::make_pair(head.first, head.second - 1);
    }
    else if (direction == "L")
    {
        head = std::make_pair(head.first - 1, head.second);
    }
    else if (direction == "R")
    {
        head = std::make_pair(head.first + 1, head.second);
    }
}

void moveTrailingKnot(const std::pair<int, int> & head, std::pair<int, int> & knot)
{
    if (std::abs(head.first - knot.first) >= 2 && std::abs(head.second - knot.second) >= 2)
    {
        knot.first += (knot.first < head.first) ? 1 : -1;
        knot.second += (knot.second < head.second) ? 1 : -1;
    }
    else if (std::abs(head.first - knot.first) >= 2)
    {
        knot.first = (knot.first < head.first) ? knot.first + 1 : knot.first - 1;
        knot.second = head.second;
    }
    else if (std::abs(head.second - knot.second) >= 2)
    {
        knot.first = head.first;
        knot.second = (knot.second < head.second) ? knot.second + 1 : knot.second - 1;
    }
}

int part1(std::vector<std::string> input) 
{
    std::pair<int, int> head = std::make_pair(0, 0);
    std::pair<int, int> tail = std::make_pair(0, 0);
    std::set<std::pair<int, int>> visitedLocations = { tail };

    for (std::string instruction : input)
    {
        for (int step = 0; step < std::stoi(instruction.substr(instruction.find(' '))); step++)
        {
            moveHead(head, instruction.substr(0, 1));

            moveTrailingKnot(head, tail);
            visitedLocations.insert(tail);
        }
    }

    return visitedLocations.size();
}

int part2(std::vector<std::string> input) 
{
    std::pair<int, int> head = std::make_pair(0, 0);
    std::pair<int, int> knot1 = std::make_pair(0, 0);
    std::pair<int, int> knot2 = std::make_pair(0, 0);
    std::pair<int, int> knot3 = std::make_pair(0, 0);
    std::pair<int, int> knot4 = std::make_pair(0, 0);
    std::pair<int, int> knot5 = std::make_pair(0, 0);
    std::pair<int, int> knot6 = std::make_pair(0, 0);
    std::pair<int, int> knot7 = std::make_pair(0, 0);
    std::pair<int, int> knot8 = std::make_pair(0, 0);
    std::pair<int, int> tail = std::make_pair(0, 0);
    std::set<std::pair<int, int>> visitedLocations = { tail };

    for (std::string instruction : input)
    {
        for (int step = 0; step < std::stoi(instruction.substr(instruction.find(' '))); step++)
        {
            moveHead(head, instruction.substr(0, 1));
            moveTrailingKnot(head, knot1);
            moveTrailingKnot(knot1, knot2);
            moveTrailingKnot(knot2, knot3);
            moveTrailingKnot(knot3, knot4);
            moveTrailingKnot(knot4, knot5);
            moveTrailingKnot(knot5, knot6);
            moveTrailingKnot(knot6, knot7);
            moveTrailingKnot(knot7, knot8);
            moveTrailingKnot(knot8, tail);
            
            visitedLocations.insert(tail); 
        }
        
    }

    return visitedLocations.size();
}

int main(void) 
{
    std::vector<std::string> testInput = {"R 4", "U 4", "L 3", "D 1", "R 4", "D 1", "L 5", "R 2"};
    assert(part1(testInput) == 13);

    InputFile inputFile("AdventOfCodeInputFiles/2022/day09.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 9, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 1);  
    std::vector<std::string> testInput2 = {"R 5", "U 8", "L 8", "D 3", "R 17", "D 10", "L 25", "U 20"};
    assert(part2(testInput2) == 36);  
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 9, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}