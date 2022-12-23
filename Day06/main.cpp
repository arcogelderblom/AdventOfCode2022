#include <iostream>
#include <cassert>
#include <chrono>
#include <numeric>
#include <algorithm>

#include "inputfile.hpp"
#include "stringoperations.hpp"

int part1(std::string input) 
{
    for (int i = 0; i + 4 < input.size(); i++)
    {
        std::string lastFourChars = input.substr(i, 4);
        std::sort(lastFourChars.begin(), lastFourChars.end());
        if (std::unique(lastFourChars.begin(), lastFourChars.end()) == lastFourChars.end())
        {
            return i + 4;
        }
    }
    return 0;
}

int part2(std::string input) 
{
    for (int i = 0; i + 14 < input.size(); i++)
    {
        std::string lastFourChars = input.substr(i, 14);
        std::sort(lastFourChars.begin(), lastFourChars.end());
        if (std::unique(lastFourChars.begin(), lastFourChars.end()) == lastFourChars.end())
        {
            return i + 14;
        }
    }
    return 0;
}

int main(void) 
{
    std::string testInput1 = "mjqjpqmgbljsphdztnvjfqwrcgsmlb";
    std::string testInput2 = "bvwbjplbgvbhsrlpgdmjqwftvncz";
    std::string testInput3 = "nppdvjthqldpwncqszvftbrmjlhg";
    std::string testInput4 = "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg";
    std::string testInput5 = "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw";
    assert(part1(testInput1) == 7);
    assert(part1(testInput2) == 5);
    assert(part1(testInput3) == 6);
    assert(part1(testInput4) == 10);
    assert(part1(testInput5) == 11);

    InputFile inputFile("AdventOfCodeInputFiles/2022/day06.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 6, puzzle 1: " << std::flush << part1(input[0]) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;


    assert(part2(testInput1) == 19);
    assert(part2(testInput2) == 23);
    assert(part2(testInput3) == 23);
    assert(part2(testInput4) == 29);
    assert(part2(testInput5) == 26);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 6, puzzle 2: " << std::flush << part2(input[0]) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}