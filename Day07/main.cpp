#include <iostream>
#include <cassert>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <map>
#include <utility>

#include "inputfile.hpp"
#include "stringoperations.hpp"

int part1(std::vector<std::string> input) 
{
    std::map<std::string, std::vector<std::string>> dirsWithContents;
    std::string curDir;
    std::vector<std::string> lastDirs;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].find("$ cd") == 0)
        {
            std::string argument = input[i].substr(std::string("$ cd ").size());
            if (argument == "..")
            {
                curDir = curDir.substr(0, curDir.size() - (lastDirs.back().size() + 1));
                lastDirs.pop_back();
            }
            else if (argument == "/")
            {   
                curDir = argument;
                lastDirs = { argument };
            }
            else
            {
                curDir += argument + "/";
                lastDirs.push_back(argument);
            }
        }
        else if (input[i].find("$ ls") == 0)
        {
            while (input[++i].find("$") != 0 && i < input.size())
            {
                dirsWithContents[curDir].push_back(input[i]);
            }
            i--;
        }
    }
    
    std::map<std::string, int> dirsWithSize;
    while (dirsWithSize.size() < dirsWithContents.size())
    {
        for (std::pair<std::string, std::vector<std::string>> dirWithContents : dirsWithContents)
        {
            if (dirsWithSize.find(dirWithContents.first) == dirsWithSize.end())
            {
                bool allContentsKnown = true;
                int total = 0;
                for (std::string content : dirWithContents.second)
                {
                    if (content.find("dir") == 0)
                    {
                        std::string dir = content.substr(std::string("dir ").size());
                        std::string fullDirPath = dirWithContents.first + dir + "/";
                        if (dirsWithSize.find(fullDirPath) != dirsWithSize.end())
                        {
                            total += dirsWithSize[fullDirPath];
                        }
                        else
                        {
                            allContentsKnown = false;
                            break;
                        }
                    }
                    else 
                    {
                        int fileSize = std::stoi(content.substr(0, content.find(" ")));
                        total += fileSize;
                    }
                }
                if (allContentsKnown)
                {
                    dirsWithSize[dirWithContents.first] = total;
                }
            }
        }
    }

    int result = 0;
    for (std::pair<std::string, int> dirWithSize : dirsWithSize)
    {
        if (dirWithSize.second < 100000)
        {
            result += dirWithSize.second;
        }
    }
    return result;
}

int part2(std::vector<std::string> input) 
{
    std::map<std::string, std::vector<std::string>> dirsWithContents;
    std::string curDir;
    std::vector<std::string> lastDirs;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].find("$ cd") == 0)
        {
            std::string argument = input[i].substr(std::string("$ cd ").size());
            if (argument == "..")
            {
                curDir = curDir.substr(0, curDir.size() - (lastDirs.back().size() + 1));
                lastDirs.pop_back();
            }
            else if (argument == "/")
            {   
                curDir = argument;
                lastDirs = { argument };
            }
            else
            {
                curDir += argument + "/";
                lastDirs.push_back(argument);
            }
        }
        else if (input[i].find("$ ls") == 0)
        {
            while (input[++i].find("$") != 0 && i < input.size())
            {
                dirsWithContents[curDir].push_back(input[i]);
            }
            i--;
        }
    }

    std::map<std::string, int> dirsWithSize;
    while (dirsWithSize.size() < dirsWithContents.size())
    {
        for (std::pair<std::string, std::vector<std::string>> dirWithContents : dirsWithContents)
        {
            if (dirsWithSize.find(dirWithContents.first) == dirsWithSize.end())
            {
                bool allContentsKnown = true;
                int total = 0;
                for (std::string content : dirWithContents.second)
                {
                    if (content.find("dir") == 0)
                    {
                        std::string dir = content.substr(std::string("dir ").size());
                        std::string fullDirPath = dirWithContents.first + dir + "/";
                        if (dirsWithSize.find(fullDirPath) != dirsWithSize.end())
                        {
                            total += dirsWithSize[fullDirPath];
                        }
                        else
                        {
                            allContentsKnown = false;
                            break;
                        }
                    }
                    else 
                    {
                        int fileSize = std::stoi(content.substr(0, content.find(" ")));
                        total += fileSize;
                    }
                }
                if (allContentsKnown)
                {
                    dirsWithSize[dirWithContents.first] = total;
                }
            }
        }
    }

    int totalSpace = 70000000;
    int usedSpace = dirsWithSize["/"];
    int unusedSpace = totalSpace - usedSpace;
    int spaceNeeded = 30000000;
    int spaceToFreeUp = spaceNeeded - unusedSpace;

    int result = usedSpace;
    for (std::pair<std::string, int> dirWithSize : dirsWithSize)
    {
        if (dirWithSize.second > spaceToFreeUp && dirWithSize.second < result)
        {
            result = dirWithSize.second;
        }
    }
    return result;
}

int main(void) 
{
    std::vector<std::string> testInput = {"$ cd /", "$ ls", "dir a", "14848514 b.txt", "8504156 c.dat", "dir d", "$ cd a", "$ ls", "dir e", "29116 f", "2557 g", "62596 h.lst", "$ cd e", "$ ls", "584 i", "$ cd ..", "$ cd ..", "$ cd d", "$ ls", "4060174 j", "8033020 d.log", "5626152 d.ext", "7214296 k"};
    assert(part1(testInput) == 95437);

    InputFile inputFile("InputFiles/day07.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 7, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 24933642);  
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 7, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}