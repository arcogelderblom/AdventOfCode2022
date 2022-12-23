#include <iostream>
#include <cassert>
#include <chrono>
#include <numeric>
#include <algorithm>

#include "inputfile.hpp"
#include "stringoperations.hpp"

int part1(std::vector<std::string> input) 
{
    int amountThatFullyContains = 0;
    for (std::string inputStr : input)
    {
        std::vector<std::string> splittedInput = StringOperations::splitString(inputStr, ",");
        std::string part1Str = splittedInput[0];
        std::string part2Str = splittedInput[1];

        std::vector<int> part1(std::stoi(part1Str.substr(part1Str.find('-') + 1)) - std::stoi(part1Str.substr(0, part1Str.find('-'))) + 1);
        std::iota(part1.begin(), part1.end(), std::stoi(part1Str.substr(0, part1Str.find('-'))));
        std::vector<int> part2(std::stoi(part2Str.substr(part2Str.find('-') + 1)) - std::stoi(part2Str.substr(0, part2Str.find('-'))) + 1);
        std::iota(part2.begin(), part2.end(), std::stoi(part2Str.substr(0, part2Str.find('-'))));
        
        bool part1ContainsPart2 = std::all_of(part2.begin(), part2.end(), [&part1](int value){ return std::find(part1.begin(), part1.end(), value) != part1.end(); });
        bool part2ContainsPart1 = std::all_of(part1.begin(), part1.end(), [&part2](int value){ return std::find(part2.begin(), part2.end(), value) != part2.end(); });
        if (part1ContainsPart2 || part2ContainsPart1)
        {
            amountThatFullyContains++;
        }
    }
    
    return amountThatFullyContains;
}

int part2(std::vector<std::string> input) 
{
    int amountThatContains = 0;
    for (std::string inputStr : input)
    {
        std::vector<std::string> splittedInput = StringOperations::splitString(inputStr, ",");
        std::string part1Str = splittedInput[0];
        std::string part2Str = splittedInput[1];

        std::vector<int> part1(std::stoi(part1Str.substr(part1Str.find('-') + 1)) - std::stoi(part1Str.substr(0, part1Str.find('-'))) + 1);
        std::iota(part1.begin(), part1.end(), std::stoi(part1Str.substr(0, part1Str.find('-'))));
        std::vector<int> part2(std::stoi(part2Str.substr(part2Str.find('-') + 1)) - std::stoi(part2Str.substr(0, part2Str.find('-'))) + 1);
        std::iota(part2.begin(), part2.end(), std::stoi(part2Str.substr(0, part2Str.find('-'))));
        
        bool part1ContainsPart2 = std::any_of(part2.begin(), part2.end(), [&part1](int value){ return std::find(part1.begin(), part1.end(), value) != part1.end(); });
        bool part2ContainsPart1 = std::any_of(part1.begin(), part1.end(), [&part2](int value){ return std::find(part2.begin(), part2.end(), value) != part2.end(); });
        if (part1ContainsPart2 || part2ContainsPart1)
        {
            amountThatContains++;
        }
    }
    
    return amountThatContains;
}

int main(void) 
{
    std::vector<std::string> testInput {"2-4,6-8", "2-3,4-5", "5-7,7-9", "2-8,3-7", "6-6,4-6", "2-6,4-8"};
    assert(part1(testInput) == 2);

    InputFile inputFile("AdventOfCodeInputFiles/2022/day04.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 4, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 4);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 4, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}