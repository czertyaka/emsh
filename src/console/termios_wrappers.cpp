#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <unistd.h>

#include "emsh/console/termios_wrappers.h"

namespace emsh {
namespace console {
namespace termios_wrap {

Mask::Mask() : or_(0), and_(~tcflag_t(0)) {}

void Mask::AddFlag(const tcflag_t flag) {
    or_ |= flag;
    and_ |= flag;
}

void Mask::RemoveFlag(const tcflag_t flag) {
    or_ &= ~flag;
    and_ &= ~flag;
}

bool Mask::Apply(tcflag_t& flags) const {
    const tcflag_t prev = flags;
    flags |= or_;
    flags &= and_;
    return flags != prev;
}

MasksSet::MasksSet() {}

// static
const MasksSet& MasksSet::enable_raw_mode() {
    static MasksSet set;
    static bool init = false;
    if (!init) {
        set.localMask.RemoveFlag(ICANON);
        set.localMask.RemoveFlag(ECHO);
        init = true;
    }
    return set;
}

// static
const MasksSet& disable_echo() {
    static MasksSet set;
    static bool init = false;
    if (!init) {
        set.localMask.RemoveFlag(ECHO);
        init = true;
    }
    return set;
}

StdinFlagsSetter::StdinFlagsSetter(const MasksSet& masks) {
    termios _termios;
    get_current_termios(_termios);
    std::memcpy(&previous_, &_termios, sizeof(previous_));

    if (masks.inputMask.Apply(_termios.c_iflag) || masks.outputMask.Apply(_termios.c_oflag) ||
        masks.controlMask.Apply(_termios.c_cflag) || masks.localMask.Apply(_termios.c_lflag)) {
        set_termios(_termios);
        applied_ = true;
    }
}

StdinFlagsSetter::~StdinFlagsSetter() {
    try {
        if (applied_) {
            set_termios(previous_);
        }
    }
    catch (const std::exception& err) {
    }
}

// static
void StdinFlagsSetter::get_current_termios(termios& termios) {
    if (tcgetattr(STDIN_FILENO, &termios) != 0) {
        throw std::runtime_error(std::strerror(errno));
    }
}

// static
void StdinFlagsSetter::set_termios(const termios& termios) {
    if (tcsetattr(STDERR_FILENO, TCSAFLUSH, &termios) != 0) {
        throw std::runtime_error(std::strerror(errno));
    }
}

} // namespace termios_wrap
} // namespace console
} // namespace emsh
