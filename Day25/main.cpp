#include <iostream>
#include <cassert>
#include <chrono>

#include <cmath>

#include "inputfile.hpp"
#include "stringoperations.hpp"

int64_t getDecimal(const std::string & SNAFUnum)
{
    int64_t result = 0;
    for (int i = 0; i < SNAFUnum.size(); i++)
    {
        if (isdigit(SNAFUnum[i]))
        {
            if (std::pow((double)5, (SNAFUnum.size() - 1 - i)) == 0)
            {
                result += (SNAFUnum[i] - '0');
            }
            else
            {
                result += (SNAFUnum[i] - '0') * std::pow((double)5, (SNAFUnum.size() - 1 - i));
            }
        }
        else if (SNAFUnum[i] == '-')
        {
            if (std::pow((double)5, (SNAFUnum.size() - 1 - i)) == 0)
            {
                result -= 1;
            }
            else
            {
                result -= std::pow((double)5, (SNAFUnum.size() - 1 - i));
            }
        }
        else if (SNAFUnum[i] == '=')
        {
            if (std::pow((double)5, (SNAFUnum.size() - 1 - i)) == 0)
            {
                result -= 2;
            }
            else
            {
                result -= 2 * (std::pow((double)5, (SNAFUnum.size() - 1 - i)));
            }
        }
    }
    
    return result;
}

std::string getSNAFU(int64_t decimal)
{
    std::string result;
    
    while (decimal > 0)
    {
        int64_t value = decimal % 5;
        switch (value)
        {
            case 0:
            {
                result = "0" + result;
                break;
            }
            case 1:
            {
                result = "1" + result;
                break;
            }
            case 2:
            {
                result = "2" + result;
                break;
            }
            case 3:
            {
                result = "=" + result;
                value -= 5;
                break;
            }
            case 4:
            {
                result = "-" + result;
                value -= 5;
                break;
            }
        }
        decimal -= value;
        decimal /= 5;
    }

    return result;
}

std::string part1(const std::vector<std::string> & input)
{
    int64_t result = 0;
    for (const std::string & SNAFUnum : input)
    {
        result += getDecimal(SNAFUnum);
        std::cout << result << std::endl;
    }
    return getSNAFU(result);
}

int part2(const std::vector<std::string> & input)
{
    return 0;
}

int main(void) 
{
    assert(getDecimal("1") == 1);
    assert(getDecimal("2") == 2);
    assert(getDecimal("1=") == 3);
    assert(getDecimal("1-") == 4);
    assert(getDecimal("10") == 5);
    assert(getDecimal("11") == 6);
    assert(getDecimal("12") == 7);
    assert(getDecimal("2=") == 8);
    assert(getDecimal("2-") == 9);
    assert(getDecimal("20") == 10);
    assert(getDecimal("1=0") == 15);
    assert(getDecimal("1-0") == 20);
    assert(getDecimal("1=11-2") == 2022);

    std::vector<std::string> testInput = {"1=-0-2", "12111", "2=0=", "21", "2=01", "111", "20012", "112", "1=-1=", "1-12", "12", "1=", "122"};
    assert(getDecimal("2=-1=0") == 4890);
    assert(part1(testInput) == "2=-1=0");

    InputFile inputFile("AdventOfCodeInputFiles/2022/day25.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 25, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 20);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 25, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}