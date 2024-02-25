#include <iostream>

#include "emsh/console/console.h"

namespace emsh {
namespace console {

Console::Console() : is_(std::cin), os_(std::cout), prompt_("emsh > ") {}

// explicit
Console::Console(const Prompt& prompt) : is_(std::cin), os_(std::cout), prompt_(prompt) {}

Console::Console(std::istream& is, std::ostream& os) : is_(is), os_(os), prompt_("emsh > ") {}

Console::Console(std::istream& is, std::ostream& os, const Prompt& prompt)
    : is_(is), os_(os), prompt_(prompt) {}

void Console::UpdatePrompt(const Prompt& prompt) {
    prompt_ = prompt;
}

void Console::UpdateInput(const Input& input) {
    input_ = input;
}

void Console::Refresh() {
    os_ << "\r"
           "\x1b"
           "[2K"
        << prompt_.Text() << input_.GetText();
}

const Input& Console::GetInput() const {
    return input_;
}

void Console::Newline() {
    os_ << "\r\n" << prompt_.Text();
}

bool Console::ReadInput() {
    while (true) {
        char c = 0;
        is_.get(c);
        switch (c) {
        case '\n':
            return true;
        case 'q':
            return false;
        default: {
            if (input_.InsertChars(c)) {
                os_ << c;
            }
        }
        }
    }
    return true;
}

} // namespace console
} // namespace emsh
