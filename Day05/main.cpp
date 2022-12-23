#include <iostream>
#include <cassert>
#include <chrono>
#include <numeric>
#include <algorithm>

#include "inputfile.hpp"
#include "stringoperations.hpp"

std::string part1(std::vector<std::string> input) 
{
    std::vector<std::string> startStacksStr = StringOperations::splitString(input[0], "\n");
    
    std::vector<std::string> stacks(std::stoi(startStacksStr[startStacksStr.size() - 1].substr(startStacksStr[startStacksStr.size() - 1].find_last_not_of(" "))));
    for (int i = 0; i < startStacksStr.size() - 1; i++)
    {
        for (int j = 0; (j*4)+1 < startStacksStr[i].size(); j++)
        {
            if (startStacksStr[i][(j*4)+1] != ' ')
            {
                stacks[j] = startStacksStr[i][(j*4)+1] + stacks[j];
            }
        }
    }

    std::vector<std::string> instructions = StringOperations::splitString(input[1], "\n");
    for (std::string instruction : instructions)
    {
        std::vector<std::string> splittedInstruction = StringOperations::splitString(instruction, " ");
        int amount = std::stoi(splittedInstruction[1]);
        int source = std::stoi(splittedInstruction[3]) - 1; // correct index
        int destination = std::stoi(splittedInstruction[5]) - 1; // correct index

        std::string toMove = stacks[source].substr(stacks[source].size() - amount);
        std::reverse(toMove.begin(), toMove.end());
        stacks[destination] = stacks[destination] + toMove;
        stacks[source] = stacks[source].substr(0, stacks[source].size() - amount);
    }
    
    std::string result;
    for (std::string stack : stacks)
    {
        result += stack[stack.size() - 1];
    }
    
    return result;
}

std::string part2(std::vector<std::string> input) 
{
    std::vector<std::string> startStacksStr = StringOperations::splitString(input[0], "\n");
    
    std::vector<std::string> stacks(std::stoi(startStacksStr[startStacksStr.size() - 1].substr(startStacksStr[startStacksStr.size() - 1].find_last_not_of(" "))));
    for (int i = 0; i < startStacksStr.size() - 1; i++)
    {
        for (int j = 0; (j*4)+1 < startStacksStr[i].size(); j++)
        {
            if (startStacksStr[i][(j*4)+1] != ' ')
            {
                stacks[j] = startStacksStr[i][(j*4)+1] + stacks[j];
            }
        }
    }

    std::vector<std::string> instructions = StringOperations::splitString(input[1], "\n");
    for (std::string instruction : instructions)
    {
        std::vector<std::string> splittedInstruction = StringOperations::splitString(instruction, " ");
        int amount = std::stoi(splittedInstruction[1]);
        int source = std::stoi(splittedInstruction[3]) - 1; // correct index
        int destination = std::stoi(splittedInstruction[5]) - 1; // correct index

        std::string toMove = stacks[source].substr(stacks[source].size() - amount);
        stacks[destination] = stacks[destination] + toMove;
        stacks[source] = stacks[source].substr(0, stacks[source].size() - amount);
    }
    
    std::string result;
    for (std::string stack : stacks)
    {
        result += stack[stack.size() - 1];
    }
    
    return result;
}

int main(void) 
{
    std::vector<std::string> testInput {"    [D]\n[N] [C]\n[Z] [M] [P]\n 1   2   3 ","move 1 from 2 to 1\nmove 3 from 1 to 3\nmove 2 from 2 to 1\nmove 1 from 1 to 2"};
    assert(part1(testInput) == "CMZ");

    InputFile inputFile("AdventOfCodeInputFiles/2022/day05.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 5, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == "MCD");
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 5, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}