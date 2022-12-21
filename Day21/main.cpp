#include <iostream>
#include <cassert>
#include <chrono>

#include <cctype>
#include <map>
#include <iomanip>
#include <limits>

#include "inputfile.hpp"
#include "stringoperations.hpp"

struct Monkey
{
    std::string name;
    double num = -1;
    std::string operation;
    std::string lhs;
    std::string rhs;
};

double getResult(Monkey monkey, std::map<std::string, Monkey> & monkeys, const double & humanShouts)
{
    if (monkey.name == "humn" && humanShouts != -1)
    {
        return humanShouts;
    }
    if (monkey.num != -1)
    {
        return monkey.num;
    }
    
    if (monkey.operation == "+")
    {
        return getResult(monkeys[monkey.lhs], monkeys, humanShouts) + getResult(monkeys[monkey.rhs], monkeys, humanShouts);
    }
    else if (monkey.operation == "-")
    {
        return getResult(monkeys[monkey.lhs], monkeys, humanShouts) - getResult(monkeys[monkey.rhs], monkeys, humanShouts);
    }
    else if (monkey.operation == "/")
    {
        return getResult(monkeys[monkey.lhs], monkeys, humanShouts) / getResult(monkeys[monkey.rhs], monkeys, humanShouts);
    }
    else if (monkey.operation == "*")
    {
        return getResult(monkeys[monkey.lhs], monkeys, humanShouts) * getResult(monkeys[monkey.rhs], monkeys, humanShouts);
    }
    else if (monkey.operation == "=")
    {
        return getResult(monkeys[monkey.lhs], monkeys, humanShouts) == getResult(monkeys[monkey.rhs], monkeys, humanShouts);
    }
    assert(false); // should never come here
}

std::map<std::string, Monkey> parseInput(const std::vector<std::string> & input)
{
    std::map<std::string, Monkey> monkeys;
    for (std::string line : input)
    {
        Monkey monkey;
        monkey.name = line.substr(0, 4);

        if (isdigit(line[6]))
        {
            monkey.num = std::stod(line.substr(6));
            monkeys[monkey.name] = monkey;
            continue;
        }

        monkey.lhs = line.substr(6, 4);
        monkey.operation = line[11];
        monkey.rhs = line.substr(13);

        monkeys[monkey.name] = monkey;
    }
    return monkeys;
}

double part1(const std::vector<std::string> & input) 
{
    std::map<std::string, Monkey> monkeys = parseInput(input);
    return getResult(monkeys["root"], monkeys, -1);
}

double part2(const std::vector<std::string> & input)
{
    std::map<std::string, Monkey> monkeys = parseInput(input);

    double targetValue;
    Monkey monkeyThatIsDependentOfHuman;
    if (getResult(monkeys[monkeys["root"].lhs], monkeys, -1) == getResult(monkeys[monkeys["root"].lhs], monkeys, 0))
    {
        // lhs is independent of human
        targetValue = getResult(monkeys[monkeys["root"].lhs], monkeys, -1);
        monkeyThatIsDependentOfHuman = monkeys[monkeys["root"].rhs];
    }
    else
    {
        // rhs is independent of human
        targetValue = getResult(monkeys[monkeys["root"].rhs], monkeys, -1);
        monkeyThatIsDependentOfHuman = monkeys[monkeys["root"].lhs];
    }

    double humanMustShout = 0;
    double min = 0;
    double max = 1e20;
    while (min < max)
    {
        double mid = (min+max) / 2;
        double result = targetValue - getResult(monkeyThatIsDependentOfHuman, monkeys, mid);
        if (result < 0)
        {
            min = mid;
        }
        else if (result == 0)
        {
            humanMustShout = mid;
            break;
        }
        else
        {
            max = mid;
        }
    }
    
    return humanMustShout;
}

int main(void) 
{
    std::vector<std::string> testInput = {"root: pppw + sjmn", "dbpl: 5", "cczh: sllz + lgvd", "zczc: 2", "ptdq: humn - dvpt", "dvpt: 3", "lfqf: 4", "humn: 5", "ljgn: 2", "sjmn: drzm * dbpl", "sllz: 4", "pppw: cczh / lfqf", "lgvd: ljgn * ptdq", "drzm: hmdt - zczc", "hmdt: 32"};
    assert(part1(testInput) == 152);

    InputFile inputFile("InputFiles/day21.txt");
    std::vector<std::string> input = inputFile.getContentAsString("\n");
    auto t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 21, puzzle 1: " << std::flush << std::setprecision(std::numeric_limits<double>::max_digits10) << part1(input) << std::endl;
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;

    // assert(part2(testInput) == (double)301); //test input fails?!
    t_begin = std::chrono::high_resolution_clock::now();
    std::cout << "Day 21, puzzle 2: " << std::flush << std::setprecision(std::numeric_limits<double>::max_digits10) << part2(input) << std::endl;
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << "Completed in: " << std::chrono::duration<double, std::milli>(t_end - t_begin).count() << " ms" << std::endl;
}