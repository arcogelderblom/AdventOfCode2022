#include <iostream>
#include <cassert>
#include <chrono>

#include "inputfile.hpp"
#include "stringoperations.hpp"

std::vector<std::string> create2DPlane(const std::vector<std::string> & input)
{
    // create a large enough 2D scan plane
    std::string row(1000, '.');
    std::vector<std::string> scan(200, row);
    
    for (std::string line : input)
    {
        std::string separator = " -> ";
        while (line.find(separator) != std::string::npos)
        {
            int separatorIndex = line.find(" -> ");
            std::string start = line.substr(0, separatorIndex);
            std::string finish = line.substr(separatorIndex + separator.size(), line.find(separator, separatorIndex + separator.size()) - (separatorIndex + separator.size()));


            // brute force adding in all possible ways, l->r r->l u->d d->u
            for (int row = std::stoi(start.substr(start.find(",") + 1)); row <= std::stoi(finish.substr(finish.find(",") + 1)); row++)
            {
                for (int column = std::stoi(start.substr(0, start.find(","))); column >= std::stoi(finish.substr(0, finish.find(","))); column--)
                {
                    scan[row][column] = '#';
                }
            }
            for (int row = std::stoi(start.substr(start.find(",") + 1)); row <= std::stoi(finish.substr(finish.find(",") + 1)); row++)
            {
                for (int column = std::stoi(start.substr(0, start.find(","))); column <= std::stoi(finish.substr(0, finish.find(","))); column++)
                {
                    scan[row][column] = '#';
                }
            }

            for (int row = std::stoi(start.substr(start.find(",") + 1)); row >= std::stoi(finish.substr(finish.find(",") + 1)); row--)
            {
                for (int column = std::stoi(start.substr(0, start.find(","))); column <= std::stoi(finish.substr(0, finish.find(","))); column++)
                {
                    scan[row][column] = '#';
                }
            }

            for (int row = std::stoi(start.substr(start.find(",") + 1)); row >= std::stoi(finish.substr(finish.find(",") + 1)); row--)
            {
                for (int column = std::stoi(start.substr(0, start.find(","))); column >= std::stoi(finish.substr(0, finish.find(","))); column--)
                {
                    scan[row][column] = '#';
                }
            }
            line = line.substr(separatorIndex + separator.size());
        }
    }
    return scan;
}

int getHighestY(const std::vector<std::string> & input)
{
    int result = 0;
    for (std::string line : input)
    {
        std::string separator = " -> ";
        while (line.find(separator) != std::string::npos)
        {
            int separatorIndex = line.find(" -> ");
            std::string start = line.substr(0, separatorIndex);
            std::string finish = line.substr(separatorIndex + separator.size(), line.find(separator, separatorIndex + separator.size()) - (separatorIndex + separator.size()));

            if (std::stoi(start.substr(start.find(",") + 1)) > result)
            {
                result = std::stoi(start.substr(start.find(",") + 1));
            }
            if (std::stoi(start.substr(start.find(",") + 1)) > result)
            {
                result = std::stoi(finish.substr(finish.find(",") + 1));
            }

            line = line.substr(separatorIndex + separator.size());
        }
    }
    return result;
}

int part1(std::vector<std::string> input) 
{
    std::vector<std::string> scan = create2DPlane(input);

    int currentSandUnit = 0;
    while (true)
    {
        currentSandUnit++;
        bool falling = true;
        int sandRow = 0;
        int sandColumn = 500;
        while (falling)
        {
            if (scan[sandRow+1][sandColumn] == '#' || scan[sandRow+1][sandColumn] == 'o')
            {
                if (scan[sandRow+1][sandColumn-1] == '.')
                {
                    sandColumn--;
                }
                else if (scan[sandRow+1][sandColumn+1] == '.')
                {
                    sandColumn++;
                }
                else 
                {
                    falling = false;
                    scan[sandRow][sandColumn] = 'o';
                }
            }
            
            sandRow++;
            if (sandRow >= scan.size())
            {
                // current keeps falling so value we want is 1 before
                return currentSandUnit - 1;
            }
        }
    }

    return 0;
}

long long part2(const std::vector<std::string> & input) 
{
    std::vector<std::string> scan = create2DPlane(input);
    std::string floor(1000, '#');
    std::cout << getHighestY(input) + 2 << std::endl;
    scan[getHighestY(input) + 2] = floor;

    int currentSandUnit = 0;
    while (scan[0][500] != 'o')
    {
        std::cout << currentSandUnit << std::endl;
        currentSandUnit++;
        bool falling = true;
        int sandRow = 0;
        int sandColumn = 500;
        while (falling)
        {
            if (scan[sandRow+1][sandColumn] == '#' || scan[sandRow+1][sandColumn] == 'o')
            {
                if (scan[sandRow+1][sandColumn-1] == '.')
                {
                    sandColumn--;
                }
                else if (scan[sandRow+1][sandColumn+1] == '.')
                {
                    sandColumn++;
                }
                else 
                {
                    falling = false;
                    scan[sandRow][sandColumn] = 'o';
                }
            }
            sandRow++;
        }
    }
    std::cout << currentSandUnit << std::endl;
    return currentSandUnit;
}

int main(void) 
{
    std::vector<std::string> testInput = {"498,4 -> 498,6 -> 496,6", "503,4 -> 502,4 -> 502,9 -> 494,9"};
    assert(part1(testInput) == 24);

    InputFile inputFile("InputFiles/day14.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 14, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 93);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 14, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}