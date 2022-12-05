#include <iostream>
#include <cassert>
#include <chrono>
#include <algorithm>

#include "inputfile.hpp"
#include "stringoperations.hpp"

int part1(std::vector<std::string> input) 
{
    std::string priorities = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int total = 0;
    for (std::string rucksack : input)
    {
        std::string firstHalf = rucksack.substr(0, rucksack.size() / 2);
        std::string secondHalf = rucksack.substr(rucksack.size() / 2);

        for (char c : firstHalf)
        {
            if (std::find(secondHalf.begin(), secondHalf.end(), c) != secondHalf.end())
            {
                total += priorities.find(c) + 1;
                break;
            }
        }
        
    }
    
    return total;
}

int part2(std::vector<std::string> input) 
{
    std::string priorities = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int total = 0;

    for (int i = 0; i < input.size(); i+=3)
    {
        for (char c : input[i])
        {
            if (input[i+1].find(c) != std::string::npos && input[i+2].find(c) != std::string::npos)
            {
                total += priorities.find(c) + 1;
                break;
            }
        }
    }  
    
    return total;
}

int main(void) 
{
    std::vector<std::string> testInput {"vJrwpWtwJgWrhcsFMMfFFhFp", "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL", "PmmdzqPrVvPwwTWBwg", "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn", "ttgJtRGJQctTZtZT", "CrZsJsPPZsGzwwsLwLmpwMDw"};
    assert(part1(testInput) == 157);

    InputFile inputFile("InputFiles/day03.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 3, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 70);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 3, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}