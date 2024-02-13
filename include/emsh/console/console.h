#ifndef EMSH_CONSOLE_H
#define EMSH_CONSOLE_H

#include "emsh/console/input.h"
#include "emsh/console/prompt.h"
#include "emsh/console/termios_raw_mode.h"

namespace emsh {
namespace console {

enum ControlSequence { CS_ENTER, CS_TAB, CS_ARROW_UP, CS_ARROW_DOWN };

class Console {
public:
    Console();
    explicit Console(const Prompt& prompt);

    void UpdatePrompt(const Prompt& prompt);
    void UpdateInput(const Input& input);
    void Refresh();

    const Input& GetInput() const;

    bool Newline();
    ControlSequence ReadInput();

private:
    TermiosRawMode termiosRawMode_;
    Input input_;
    Prompt prompt_;
};

} // namespace console
} // namespace emsh

#endif // EMSH_CONSOLE_H
