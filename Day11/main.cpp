#include <iostream>
#include <cassert>
#include <chrono>

#include "inputfile.hpp"
#include "stringoperations.hpp"

struct Monkey
{
    std::vector<int> items;
    std::function<long long(long long)> operation;
    int testDivision;
    int ifTrueToMonkey;
    int ifFalseToMonkey;
    int inspectedTimes = 0;
};

std::vector<Monkey> parseToMonkeys(const std::vector<std::string> & input)
{
    std::vector<Monkey> monkeys;
    for (std::string line : input)
    {
        Monkey monkey;
        
        std::vector<std::string> splitted = StringOperations::splitString(line, "\n");

        // starting items
        std::vector<std::string> itemsStr = StringOperations::splitString(splitted[1].substr(std::string("  Starting items: ").size()), ", ");
        for (std::string item : itemsStr)
        {
            monkey.items.push_back(std::stoi(item));
        }

        // operation
        std::string operationStr = splitted[2].substr(std::string("  Operation: new = old ").size());
        std::function<long long(long long)> operation;

        std::string operatorStr = operationStr.substr(0, 1);
        std::string rhs = operationStr.substr(2);
        if (operatorStr == "*")
        {
            if (rhs != "old")
            {
                long long rhsVal = std::stoi(rhs);
                operation = [rhsVal](long long value) { return value * rhsVal; };
            }
            else
            {
                operation = [](long long value) { return value * value; };
            }
        }
        else if (operatorStr == "+")
        {
            if (rhs != "old")
            {
                long long rhsVal = std::stoi(rhs);
                operation = [rhsVal](long long value) { return value + rhsVal; };
            }
            else
            {
                operation = [](long long value) { return value + value; };
            }
        }
        monkey.operation = operation;

        // test
        monkey.testDivision =  std::stoi(splitted[3].substr(std::string("  Test: divisible by ").size()));

        // if true
        monkey.ifTrueToMonkey = std::stoi(splitted[4].substr(std::string("    If true: throw to monkey ").size()));

        // if false
        monkey.ifFalseToMonkey = std::stoi(splitted[5].substr(std::string("    If false: throw to monkey ").size()));

        // add monkey to vector
        monkeys.push_back(monkey);
    }
    return monkeys;
}

long long getResult(const std::vector<Monkey> & monkeys)
{
    long long mostInspectedTimes = 0;
    long long secondMostInspectedTimes = 0;
    for (Monkey monkey : monkeys)
    {
        if (monkey.inspectedTimes > mostInspectedTimes)
        {
            secondMostInspectedTimes = mostInspectedTimes;
            mostInspectedTimes = monkey.inspectedTimes;
        }
        else if (monkey.inspectedTimes > secondMostInspectedTimes)
        {
            secondMostInspectedTimes = monkey.inspectedTimes;
        }
    }
    return mostInspectedTimes * secondMostInspectedTimes;
} 

int part1(const std::vector<std::string> & input) 
{
    std::vector<Monkey> monkeys = parseToMonkeys(input);
    for (int round = 1; round <= 20; round++)
    {
        for (Monkey & monkey : monkeys)
        {
            for (int item : monkey.items)
            {
                monkey.inspectedTimes++;
                item = monkey.operation(item);
                item /= 3;
                if (item % monkey.testDivision == 0)
                {
                    monkeys[monkey.ifTrueToMonkey].items.push_back(item);
                }
                else 
                {
                    monkeys[monkey.ifFalseToMonkey].items.push_back(item);
                }
            }
            monkey.items.clear();
        }
    }

    return getResult(monkeys);
}

long long part2(const std::vector<std::string> & input) 
{
    std::vector<Monkey> monkeys = parseToMonkeys(input);

    int supermod = 1;
    for (const Monkey & monkey : monkeys)
    {
        supermod *= monkey.testDivision;
    }

    for (int round = 1; round <= 10000; round++)
    {
        for (Monkey & monkey : monkeys)
        {
            for (int item : monkey.items)
            {
                monkey.inspectedTimes++;
                item = monkey.operation(item) % supermod;
                if (item % monkey.testDivision == 0)
                {
                    monkeys[monkey.ifTrueToMonkey].items.push_back(item);
                }
                else 
                {
                    monkeys[monkey.ifFalseToMonkey].items.push_back(item);
                }
            }
            monkey.items.clear();
        }
    }
    return getResult(monkeys);
}

int main(void) 
{
    std::vector<std::string> testInput = {"Monkey 0:\n  Starting items: 79, 98\n  Operation: new = old * 19\n  Test: divisible by 23\n    If true: throw to monkey 2\n    If false: throw to monkey 3\n", 
                                          "Monkey 1:\n  Starting items: 54, 65, 75, 74\n  Operation: new = old + 6\n  Test: divisible by 19\n    If true: throw to monkey 2\n    If false: throw to monkey 0\n",
                                          "Monkey 2:\n  Starting items: 79, 60, 97\n  Operation: new = old * old\n  Test: divisible by 13\n    If true: throw to monkey 1\n    If false: throw to monkey 3", 
                                          "Monkey 3:\n  Starting items: 74\n  Operation: new = old + 3\n  Test: divisible by 17\n    If true: throw to monkey 0\n    If false: throw to monkey 1\n"};
    assert(part1(testInput) == 10605);

    InputFile inputFile("InputFiles/day11.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 11, puzzle 1: " << std::flush << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    assert(part2(testInput) == 2713310158);
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 11, puzzle 2: " << std::flush << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}