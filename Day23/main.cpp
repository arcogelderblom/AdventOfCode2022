#include <iostream>
#include <cassert>
#include <chrono>

#include <map>
#include <utility>
#include <list>
#include <limits>
#include <algorithm>

#include "inputfile.hpp"
#include "stringoperations.hpp"

enum Direction
{
    North = 0,
    South,
    West,
    East
};

// row, column
typedef std::pair<int, int> Coordinate;

void getProposedLocation(std::map<Coordinate, Coordinate> & elvesWithProposedLocation, const Coordinate & elf, const std::list<Direction> & directionPriorities, const std::vector<std::string> & groveScan)
{
    if (groveScan[elf.first-1][elf.second-1] == '.' &&
        groveScan[elf.first-1][elf.second] == '.' &&
        groveScan[elf.first-1][elf.second+1] == '.' && 
        groveScan[elf.first][elf.second-1] == '.' &&
        groveScan[elf.first][elf.second+1] == '.' &&
        groveScan[elf.first+1][elf.second-1] == '.' &&
        groveScan[elf.first+1][elf.second] == '.' &&
        groveScan[elf.first+1][elf.second+1] == '.')
    {
        return;
    }

    for (const Direction & priority : directionPriorities)
    {
        switch (priority)
        {
            case (North):
            {
                if (groveScan[elf.first-1][elf.second-1] == '.' &&
                    groveScan[elf.first-1][elf.second] == '.' &&
                    groveScan[elf.first-1][elf.second+1] == '.')
                {
                    elvesWithProposedLocation[elf] = std::make_pair(elf.first - 1, elf.second);
                    return;
                }
                break;
            }
            case (South):
            {
                if (groveScan[elf.first+1][elf.second-1] == '.' &&
                    groveScan[elf.first+1][elf.second] == '.' &&
                    groveScan[elf.first+1][elf.second+1] == '.')
                {
                    elvesWithProposedLocation[elf] = std::make_pair(elf.first + 1, elf.second);
                    return;
                }
                break;
            }
            case (West):
            {
                if (groveScan[elf.first-1][elf.second-1] == '.' &&
                    groveScan[elf.first][elf.second-1] == '.' &&
                    groveScan[elf.first+1][elf.second-1] == '.')
                {
                    elvesWithProposedLocation[elf] = std::make_pair(elf.first, elf.second - 1);
                    return;
                }
                break;
            }
            case (East):
            {
                if (groveScan[elf.first-1][elf.second+1] == '.' &&
                    groveScan[elf.first][elf.second+1] == '.' &&
                    groveScan[elf.first+1][elf.second+1] == '.')
                {
                    elvesWithProposedLocation[elf] = std::make_pair(elf.first, elf.second + 1);
                    return;
                }
                break;
            }
        }
    }
}

void moveElves(std::map<Coordinate, Coordinate> & elvesWithProposedLocation, std::vector<Coordinate> & elfCoordinates, std::vector<std::string> & groveScan)
{
    // move elves
    while (elvesWithProposedLocation.size() > 0)
    {
        std::pair<Coordinate, Coordinate> current = *elvesWithProposedLocation.begin();
        std::vector<Coordinate> duplicates;
        for (std::pair<Coordinate, Coordinate> other : elvesWithProposedLocation)
        {
            if (current.first == other.first)
            {
                continue;
            }
            if (current.second == other.second)
            {
                duplicates.push_back(other.first);
            }    
        }

        if (duplicates.size() > 0)
        {
            elvesWithProposedLocation.erase(current.first);
            for (Coordinate duplicate : duplicates)
            {
                elvesWithProposedLocation.erase(duplicate);
            }
        }
        else
        {
            groveScan[current.first.first][current.first.second] = '.';
            groveScan[current.second.first][current.second.second] = '#';
            elfCoordinates.push_back(current.second);
            elfCoordinates.erase(std::find(elfCoordinates.begin(), elfCoordinates.end(), current.first));
            elvesWithProposedLocation.erase(current.first);
        }
    }
}

int part1(const std::vector<std::string> & input)
{
    std::string row(input[0].size() * 5, '.');
    std::vector<std::string> emptyRows(input.size(), row);

    std::vector<std::string> groveScan(emptyRows);
    for (std::string line : input)
    {
        line = std::string(input[0].size() * 2, '.') + line + std::string(input[0].size() * 2, '.');
        groveScan.push_back(line);
    }
    groveScan.insert(groveScan.end(), emptyRows.begin(), emptyRows.end());

    std::vector<Coordinate> elfCoordinates;
    for (int row = 0; row < groveScan.size(); row++)
    {
        for (int column = 0; column < groveScan[row].size(); column++)
        {
            if (groveScan[row][column] == '#')
            {
                elfCoordinates.push_back(std::make_pair(row, column));
            }
        }
    }

    std::list<Direction> priorities = { North, South, West, East};
    for (int round = 0; round < 10; round++)
    {
        std::map<Coordinate, Coordinate> elvesWithProposedLocation;
        for (const Coordinate & elf : elfCoordinates)
        {
            getProposedLocation(elvesWithProposedLocation, elf, priorities, groveScan);
        }
        moveElves(elvesWithProposedLocation, elfCoordinates, groveScan);

        // change priorities
        priorities.emplace_back(*priorities.begin());
        priorities.pop_front();
    }

    int minRow = std::distance(groveScan.begin(), std::find_if(groveScan.begin(), groveScan.end(), [](std::string row){ return row.find_first_of('#') != std::string::npos; }));
    int maxRow = groveScan.size() - 1 - std::distance(groveScan.rbegin(), std::find_if(groveScan.rbegin(), groveScan.rend(), [](std::string row){ return row.find_first_of('#') != std::string::npos; }));
    int minColumn = std::numeric_limits<int>::max();
    int maxColumn = 0;
    for (int row = minRow; row <= maxRow; row++)
    {
        int first = groveScan[row].find_first_of('#');
        int last = groveScan[row].find_last_of('#');
        if (first != -1 && first < minColumn) minColumn = first;
        if (last > maxColumn) maxColumn = last;
    }
    
    int result = 0;
    for (int row = minRow; row <= maxRow; row++)
    {
        for (int column = minColumn; column <= maxColumn; column++)
        {
            if (groveScan[row][column] == '.')
            {
                result++;
            }
        }
    }

    return result;
}

int part2(const std::vector<std::string> & input)
{
    std::string row(input[0].size() * 5, '.');
    std::vector<std::string> emptyRows(input.size(), row);

    std::vector<std::string> groveScan(emptyRows);
    for (std::string line : input)
    {
        line = std::string(input[0].size() * 2, '.') + line + std::string(input[0].size() * 2, '.');
        groveScan.push_back(line);
    }
    groveScan.insert(groveScan.end(), emptyRows.begin(), emptyRows.end());

    std::vector<Coordinate> elfCoordinates;
    for (int row = 0; row < groveScan.size(); row++)
    {
        for (int column = 0; column < groveScan[row].size(); column++)
        {
            if (groveScan[row][column] == '#')
            {
                elfCoordinates.push_back(std::make_pair(row, column));
            }
        }
    }

    std::list<Direction> priorities = { North, South, West, East};
    bool elvesMoved = true;
    int round = 0;
    while (elvesMoved)
    {
        elvesMoved = false;
        std::map<Coordinate, Coordinate> elvesWithProposedLocation;
        for (const Coordinate & elf : elfCoordinates)
        {
            getProposedLocation(elvesWithProposedLocation, elf, priorities, groveScan);
        }
        if (elvesWithProposedLocation.size() > 0)
        {
            moveElves(elvesWithProposedLocation, elfCoordinates, groveScan);
            elvesMoved = true;
        }

        // change priorities
        priorities.emplace_back(*priorities.begin());
        priorities.pop_front();

        round++;
    }
    
    return round;
}

int main(void) 
{
    std::vector<std::string> testInput = {"....#..", "..###.#", "#...#.#", ".#...##", "#.###..", "##.#.##", ".#..#.."};
    assert(part1(testInput) == 110);

    InputFile inputFile("AdventOfCodeInputFiles/2022/day23.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 23, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 20);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 23, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}