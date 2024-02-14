#ifndef EMSH_TERMIOS_WRAPPERS_H
#define EMSH_TERMIOS_WRAPPERS_H

#include <termios.h>

namespace emsh {
namespace console {
namespace termios_wrap {

class Mask {
public:
    Mask();
    void AddFlag(const tcflag_t flag);
    void RemoveFlag(const tcflag_t flag);
    bool Apply(tcflag_t& flags);

private:
    tcflag_t or_;
    tcflag_t and_;
};

struct MasksSet {
    MasksSet();

    static const MasksSet& enable_raw_mode();
    static const MasksSet& disable_echo();

    Mask inputMask;   // applies to c_iflag
    Mask outputMask;  // applies to c_oflag
    Mask controlMask; // applies to c_cflag
    Mask localMask;   // applies to c_lflag
};

class StdinFlagsSetter {
public:
    StdinFlagsSetter(const MasksSet& masks);
    ~StdinFlagsSetter();

private:
    StdinFlagsSetter(const StdinFlagsSetter& other);
    static void get_current_termios(termios& termios);
    static void set_termios(const termios& termios);

private:
    termios previous_;
    bool applied_;
};

} // namespace termios_wrap
} // namespace console
} // namespace emsh

#endif // EMSH_TERMIOS_WRAPPERS_H
