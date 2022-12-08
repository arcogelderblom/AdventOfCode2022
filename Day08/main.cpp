#include <iostream>
#include <cassert>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <map>
#include <utility>

#include "inputfile.hpp"
#include "stringoperations.hpp"

bool isViewUnblocked(const std::vector<std::vector<int>> & forest, int x, int y)
{
    // top
    bool visibleTop = true;
    for (int checkY = 0; checkY < y; checkY++)
    {
        if (forest[x][checkY] >= forest[x][y])
        {
            visibleTop = false;
            break;
        }
    }
    if (visibleTop)
    {
        return true;
    }

    // bottom
    bool visibleBottom = true;
    for (int checkY = y + 1; checkY < forest[x].size(); checkY++)
    {
        if (forest[x][checkY] >= forest[x][y])
        {
            visibleBottom = false;
            break;
        }
    }
    if (visibleBottom)
    {
        return true;
    }
    
    // left
    bool visibleLeft = true;
    for (int checkX = 0; checkX < x; checkX++)
    {
        if (forest[checkX][y] >= forest[x][y])
        {
            visibleLeft = false;
            break;
        }
    }
    if (visibleLeft)
    {
        return true;
    }

    // right
    bool visibleRight = true;
    for (int checkX = x + 1; checkX < forest.size(); checkX++)
    {
        if (forest[checkX][y] >= forest[x][y])
        {
            visibleRight = false;
            break;
        }
    }
    if (visibleRight)
    {
        return true;
    }
    return false;
}

int part1(std::vector<std::string> input) 
{
    std::vector<std::vector<int>> forest;

    for (int x = 0; x < input[0].size(); x++)
    {
        std::vector<int> columnTrees;
        for (std::string line : input)
        {
            columnTrees.push_back(line[x] - '0');
        }
        forest.push_back(columnTrees);
    }

    int edgeTrees = (forest.size() * 2) + ((forest[0].size() - 2) * 2);
    int amountTreesVisible = edgeTrees;
    for (int x = 1; x < forest.size() - 1; x++)
    {
        for (int y = 1; y < forest[x].size() - 1; y++)
        {
            if (isViewUnblocked(forest, x, y))
            {
                amountTreesVisible++;
            }
        }
    }
    
    return amountTreesVisible;
}

int getScenicScore(const std::vector<std::vector<int>> & forest, int x, int y)
{
    // top
    int visibleTop = 0;
    for (int checkY = y - 1; checkY >= 0; checkY--)
    {
        visibleTop++;
        if (forest[x][checkY] >= forest[x][y])
        {
            break;
        }
    }

    // bottom
    int visibleBottom = 0;
    for (int checkY = y + 1; checkY < forest[x].size(); checkY++)
    {
        visibleBottom++;
        if (forest[x][checkY] >= forest[x][y])
        {
            break;
        }
    }

    // left
    int visibleLeft = 0;
    for (int checkX = x - 1; checkX >= 0; checkX--)
    {
        visibleLeft++;
        if (forest[checkX][y] >= forest[x][y])
        {
            break;
        }
    }

    // right
    int visibleRight = 0;
    for (int checkX = x + 1; checkX < forest.size(); checkX++)
    {
        visibleRight++;
        if (forest[checkX][y] >= forest[x][y])
        {
            break;
        }
    }
    return visibleTop * visibleBottom * visibleLeft * visibleRight;
}

int part2(std::vector<std::string> input) 
{
    std::vector<std::vector<int>> forest;

    for (int x = 0; x < input[0].size(); x++)
    {
        std::vector<int> columnTrees;
        for (std::string line : input)
        {
            columnTrees.push_back(line[x] - '0');
        }
        forest.push_back(columnTrees);
    }

    int highestScenicScore;
    for (int x = 1; x < forest.size() - 1; x++)
    {
        for (int y = 1; y < forest[x].size() - 1; y++)
        {
            int currentScenicScore = getScenicScore(forest, x, y);
            if (currentScenicScore > highestScenicScore)
            {
                highestScenicScore = currentScenicScore;
            }
        }
    }
    
    return highestScenicScore;
}

int main(void) 
{
    std::vector<std::string> testInput = {"30373", "25512", "65332", "33549", "35390"};
    assert(part1(testInput) == 21);

    InputFile inputFile("InputFiles/day08.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 8, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 8);  
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 8, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}