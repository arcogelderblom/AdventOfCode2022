#include <iostream>
#include <cassert>
#include <chrono>

#include "inputfile.hpp"

int part1() 
{
    return 0;
}

int part2() 
{
    return 0;
}

int main(void) 
{
    //std::vector<int> testInput {};
    //assert(getIncreaseCount(testInput) == 7);

    InputFile inputFile("InputFiles/day01.txt");
    //std::vector<int> measurements = inputFile.getContentAsInt("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 1, puzzle 1: " << std::flush << part1() << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    //assert(getIncreaseCountSum(testInput) == 5);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 1, puzzle 2: " << std::flush << part2() << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}