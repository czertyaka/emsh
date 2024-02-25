#include <sstream>
#include <stdexcept>

#include "emsh/console/escape_sequences.h"

#define ESC "\x1b"

namespace emsh {
namespace console {
namespace escape_sequences {

namespace ASCII {

const std::string backspace = "\x08";
const std::string tab = "\x09";
const std::string new_line = "\x0A";
const std::string carriage_return = "\x0D";
const std::string escape = ESC;
const std::string del = "\x7f";

} // namespace ASCII

namespace VT100 {

const std::string cursor_up_1 = ESC "[A";
const std::string cursor_down_1 = ESC "[B";
const std::string cursor_right_1 = ESC "[C";
const std::string cursor_left_1 = ESC "[D";

namespace {

enum Direction { UP, DOWN, RIGHT, LEFT, COUNT };

std::string move_cursor(const Direction direction, const std::size_t times) {
    if (direction >= COUNT) {
        std::ostringstream error;
        error << "invalid direction: " << static_cast<int>(direction);
        throw std::invalid_argument(error.str());
    }
    static const char literals[COUNT] = {'A', 'B', 'C', 'D'};
    std::ostringstream sequence;
    sequence << ESC << '[' << times << literals[direction];
    return sequence.str();
}

} // namespace

std::string cursor_up(const std::size_t times) { return move_cursor(UP, times); }

std::string cursor_down(const std::size_t times) { return move_cursor(DOWN, times); }

std::string cursor_right(const std::size_t times) { return move_cursor(RIGHT, times); }

std::string cursor_left(const std::size_t times) { return move_cursor(LEFT, times); }

const std::string home = ESC "[1~";
const std::string end = ESC "[F";
const std::string insert = ESC "[2~";
const std::string delete_ = ESC "[3~";
const std::string pgup = ESC "[5~";
const std::string pgdn = ESC "6[~";

const std::string cleareol = ESC "[0K";
const std::string clearbol = ESC "[1K";
const std::string clearline = ESC "[2K";

} // namespace VT100

} // namespace escape_sequences
} // namespace console
} // namespace emsh
