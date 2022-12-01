#include <iostream>
#include <cassert>
#include <chrono>

#include "inputfile.hpp"
#include "stringoperations.hpp"

int part1(std::vector<std::string> input) 
{
    int max = 0;
    for (std::string elf : input)
    {
        std::vector<std::string> inventory = StringOperations::splitString(elf, "\n");
        int total = 0;
        for (std::string item : inventory)
        {
            total += std::stoi(item);
        }
        
        if (total > max)
        {
            max = total;
        }
    }
    return max;
}

int part2(std::vector<std::string> input) 
{
    int max1 = 0;
    int max2 = 0;
    int max3 = 0;
    for (std::string elf : input)
    {
        std::vector<std::string> inventory = StringOperations::splitString(elf, "\n");
        int total = 0;
        for (std::string item : inventory)
        {
            total += std::stoi(item);
        }

        if (total > max1)
        {
            max3 = max2;
            max2 = max1;
            max1 = total;
        }
        else if (total > max2)
        {
            max3 = max2;
            max2 = total;
        }
        else if (total > max3)
        {
            max3 = total;
        }
    }
    
    return max1 + max2 + max3;
}

int main(void) 
{
    std::vector<std::string> testInput {"1000\n2000\n3000", "4000", "5000\n6000", "7000\n8000\n9000", "10000"};
    assert(part1(testInput) == 24000);

    InputFile inputFile("InputFiles/day01.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 1, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 45000);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 1, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}