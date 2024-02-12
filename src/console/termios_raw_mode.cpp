#include "console/termios_raw_mode.h"

#include <cerrno>
#include <cstring>
#include <stdexcept>

#include <unistd.h>

namespace emsh {
namespace console {

TermiosRawMode::TermiosRawMode() : applied_(false) {
    termios raw;
    get_current_termios(raw);
    const tcflag_t mask = ICANON | ISIG | ECHO;
    if ((raw.c_lflag & mask) > 0) {
        std::memcpy(&prev_, &raw, sizeof(prev_));
        raw.c_lflag &= ~mask;
        set_termios(raw);
        applied_ = true;
    }
}

TermiosRawMode::~TermiosRawMode() {
    try {
        if (applied_) {
            set_termios(prev_);
        }
    }
    catch (const std::exception &err) {
    }
}

// static
void TermiosRawMode::get_current_termios(termios &_termios) {
    if (tcgetattr(STDIN_FILENO, &_termios) != 0) {
        throw std::runtime_error(std::strerror(errno));
    }
}

// static
void TermiosRawMode::set_termios(const termios &_termios) {
    if (tcsetattr(STDERR_FILENO, TCSAFLUSH, &_termios) != 0) {
        throw std::runtime_error(std::strerror(errno));
    }
}

} // namespace console
} // namespace emsh
