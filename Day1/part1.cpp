// iterate array of instructions
// take substring of instruction
// L22 -> direction L, value 22
// increment password when position on dial == 0

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int day_one(std::vector<std::string> instructions) {
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

    std::cout << day_one(instructions) << '\n';
    return 0;
}
