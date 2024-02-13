#ifndef EMSH_TERMIOS_RAW_MODE_H
#define EMSH_TERMIOS_RAW_MODE_H

#include <termios.h>

namespace emsh {
namespace console {

class TermiosRawMode {
public:
    TermiosRawMode();
    ~TermiosRawMode();

private:
    static void get_current_termios(termios &_termios);
    static void set_termios(const termios &_termios);

private:
    termios prev_;
    bool applied_;
};

} // namespace console
} // namespace emsh

#endif // EMSH_TERMIOS_RAW_MODE_H
