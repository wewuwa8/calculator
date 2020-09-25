#include <string>
#include <sstream>
#include <iostream>

#include <tokenizer.h>
#include <parser.h>

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        try {
            Tokenizer tokenizer{&ss};
            Parser parser{&tokenizer};
            std::cout << parser.Evaluate() << std::endl;
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;    
}