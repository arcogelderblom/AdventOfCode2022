#include <iostream>
#include <cassert>
#include <chrono>

#include <thread>

#include "inputfile.hpp"
#include "stringoperations.hpp"

int part1(std::vector<std::string> input) 
{
    int reg = 1;
    int cycle = 1;
    int result = 0;
    
    for (std::string instruction : input)
    {
        if (instruction == "noop")
        {
            cycle += 1;
            if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220) 
            {
                result+=cycle*reg; 
            }
        }
        else if (instruction.find("addx") == 0)
        {
            cycle += 1;
            if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220) 
            {
                result+=cycle*reg; 
            }
            reg += std::stoi(instruction.substr(std::string("addx ").size()));
            cycle += 1;
            
            if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220) 
            {
                result+=cycle*reg; 
            }
        }
    }
    
    return result;
}

void draw(std::string & curCrtRow, int & crt, const int reg)
{
    if (std::abs(crt - reg) <= 1)
    {
        curCrtRow += '#';
    }
    else 
    {
        curCrtRow += '.';
    }
    crt++;
}

std::string part2(std::vector<std::string> input) 
{
    int reg = 1;
    int crt = 0;
    std::vector<std::string> allCrtRows;
    std::string curCrtRow;
    
    for (std::string instruction : input)
    {
        if (instruction == "noop")
        {
            draw(curCrtRow, crt, reg);
        }
        else if (instruction.find("addx") == 0)
        {
            draw(curCrtRow, crt, reg);
            draw(curCrtRow, crt, reg);
            reg += std::stoi(instruction.substr(std::string("addx ").size()));
        }
        
        if (curCrtRow.size() % 40 == 0)
        {
            allCrtRows.push_back(curCrtRow);
            crt = 0;
            curCrtRow = "";
        }

    }
    
    std::string result;
    for (std::string crtRow : allCrtRows)
    {
        result += crtRow + '\n';
    }
    return result;
}

int main(void) 
{
    std::vector<std::string> testInput = {"addx 15", "addx -11", "addx 6", "addx -3", "addx 5", "addx -1", "addx -8", "addx 13", "addx 4", "noop", "addx -1", "addx 5", "addx -1", "addx 5", "addx -1", "addx 5", "addx -1", "addx 5", "addx -1", "addx -35", "addx 1", "addx 24", "addx -19", "addx 1", "addx 16", "addx -11", "noop", "noop", "addx 21", "addx -15", "noop", "noop", "addx -3", "addx 9", "addx 1", "addx -3", "addx 8", "addx 1", "addx 5", "noop", "noop", "noop", "noop", "noop", "addx -36", "noop", "addx 1", "addx 7", "noop", "noop", "noop", "addx 2", "addx 6", "noop", "noop", "noop", "noop", "noop", "addx 1", "noop", "noop", "addx 7", "addx 1", "noop", "addx -13", "addx 13", "addx 7", "noop", "addx 1", "addx -33", "noop", "noop", "noop", "addx 2", "noop", "noop", "noop", "addx 8", "noop", "addx -1", "addx 2", "addx 1", "noop", "addx 17", "addx -9", "addx 1", "addx 1", "addx -3", "addx 11", "noop", "noop", "addx 1", "noop", "addx 1", "noop", "noop", "addx -13", "addx -19", "addx 1", "addx 3", "addx 26", "addx -30", "addx 12", "addx -1", "addx 3", "addx 1", "noop", "noop", "noop", "addx -9", "addx 18", "addx 1", "addx 2", "noop", "noop", "addx 9", "noop", "noop", "noop", "addx -1", "addx 2", "addx -37", "addx 1", "addx 3", "noop", "addx 15", "addx -21", "addx 22", "addx -6", "addx 1", "noop", "addx 2", "addx 1", "noop", "addx -10", "noop", "noop", "addx 20", "addx 1", "addx 2", "addx 2", "addx -6", "addx -11", "noop", "noop", "noop"};
    assert(part1(testInput) == 13140);

    InputFile inputFile("AdventOfCodeInputFiles/2022/day10.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 10, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 10, puzzle 2:" << std::endl << std::flush << part2(input);
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}