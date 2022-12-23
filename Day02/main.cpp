#include <iostream>
#include <cassert>
#include <chrono>

#include "inputfile.hpp"
#include "stringoperations.hpp"

int part1(std::vector<std::string> input) 
{
    int score = 0;
    for (std::string round : input)
    {
        std::vector<std::string> splitted = StringOperations::splitString(round, " ");
        std::string opponent = splitted[0];
        std::string response = splitted[1];
        if (response == "X") // rock
        {
            score += 1;
            if (opponent == "A")
            {
                score += 3;
            }
            else if (opponent == "C")
            {
                score += 6;
            }

        }
        else if (response == "Y") // paper
        {
            score += 2;
            if (opponent == "B")
            {
                score += 3;
            }
            else if (opponent == "A")
            {
                score += 6;
            }
        }
        else if (response == "Z") // scissors
        {
            score += 3;
            if (opponent == "C")
            {
                score += 3;
            }
            else if (opponent == "B")
            {
                score += 6;
            }
        }
    }
    return score;
}

int part2(std::vector<std::string> input) 
{
   int score = 0;
    for (std::string round : input)
    {
        std::vector<std::string> splitted = StringOperations::splitString(round, " ");
        std::string opponent = splitted[0];
        std::string outcome = splitted[1];
        if (outcome == "X") // lose
        {
            if (opponent == "A") // rock
            {
                score += 3; // scissors
            }
            else if (opponent == "B") // paper
            {
                score += 1; // rock
            }
            else // scissors
            {
                score += 2; // paper
            }
        }
        else if (outcome == "Y") // draw
        {
            score += 3;
            if (opponent == "A") // rock
            {
                score += 1; // rock
            }
            else if (opponent == "B") // paper
            {
                score += 2; // paper
            }
            else // scissors
            {
                score += 3; // scissors
            }
        }
        else if (outcome == "Z") // win
        {
            score += 6;
            if (opponent == "A") // rock
            {
                score += 2; // paper
            }
            else if (opponent == "B") // paper
            {
                score += 3; // scissors
            }
            else // scissors
            {
                score += 1; // rock
            }
        }
    }
    return score;
}

int main(void) 
{
    std::vector<std::string> testInput {"A Y", "B X", "C Z"};
    assert(part1(testInput) == 15);

    InputFile inputFile("AdventOfCodeInputFiles/2022/day02.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 2, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 12);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 2, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}