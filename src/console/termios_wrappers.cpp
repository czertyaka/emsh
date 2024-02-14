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

bool Mask::Apply(tcflag_t& flags) {
    const tcflag_t prev = flags;
    flags |= or_;
    flags &= and_;
    return flags != prev;
}

MasksSet::MasksSet() {}

} // namespace termios_wrap
} // namespace console
} // namespace emsh
