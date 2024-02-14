#include <cctype>
#include <iostream>

#include "emsh/console/termios_wrappers.h"

using namespace emsh;

int main() {
    using namespace console::termios_wrap;
    StdinFlagsSetter rawMode(MasksSet::enable_raw_mode());
    char c = 0;
    bool escape_sequence = false;
    while (c != '\n') {
        c = std::cin.get();
        if (escape_sequence) {
            escape_sequence = false;
            std::cout << "\n\r" << std::hex << static_cast<int>(c) << std::hex << "\n\r";
        }
        else {
            if (c == 0x1B) {
                escape_sequence = true;
                std::cout << "\n\rescape sequence\n\r";
            }
            else if (std::isalpha(c)) {
                std::cout << c;
            }
            else if (c == '\t') {
                std::cout << "\n\rcompletion requested\n\r";
            }
        }
    }
}
