// iterate array of instructions
// take substring of instruction
// L22 -> direction L, value 22
// increment password when position on dial == 0

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> example = {"L68", "L30", "R48", "L5", "R60", "L55",
    "L1", "L99", "R14", "L82"};

int part_one(std::vector<std::string> instructions) {
    int password = 0;   // initial password
    int position = 50;  // starting point

    for (std::string instruction: instructions) {
        char dir = instruction[0];
        int val = stoi(instruction.substr(1));

        if (dir == 'L') {
            position = (position - val + 100) % 100;
        } else if (dir == 'R') {
            position = (position + val) % 100;
        }

        if (position == 0) { ++password; }
    }

    return password;
}

int part_two(const std::vector<std::string>& instructions) {
    long long password = 0;
    int position = 50;

    for (const auto& instruction : instructions) {
        char dir = instruction[0];
        int val = std::stoi(instruction.substr(1));

        if (dir == 'L') {
            // distance to 0 going left
            int dist = position == 0 ? 100 : position;

            if (val >= dist) {
                password += 1 + (val - dist) / 100;
            }

            position = ((position - val) % 100 + 100) % 100;
        } else if (dir == 'R') {
            // distance to 0 going right
            int dist = (100 - position) % 100;
            if (dist == 0) dist = 100;

            if (val >= dist) {
                password += 1 + (val - dist) / 100;
            }

            position = (position + val) % 100;
        }
    }

    return password;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "error" << std::endl;
        return 1;
    }

    std::vector<std::string> instructions;
    std::string line;

    while (std::getline(inputFile, line)) {
        instructions.push_back(line);
    }

    inputFile.close();

    std::cout << "part1 example: " << part_one(example) << '\n';
    std::cout << "part2 example: " << part_two(example) << '\n';

    std::cout << "part1 input: " << part_one(instructions) << '\n';
    std::cout << "part2 input: " << part_two(instructions) << '\n';
    return 0;
}
