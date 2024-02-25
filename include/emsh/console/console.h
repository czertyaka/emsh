#ifndef EMSH_CONSOLE_H
#define EMSH_CONSOLE_H

#include <istream>
#include <ostream>

#include "emsh/console/input.h"
#include "emsh/console/prompt.h"

namespace emsh {
namespace console {

class Console {
public:
    Console();
    explicit Console(const Prompt& prompt);
    Console(std::istream& is, std::ostream& os);
    Console(std::istream& is, std::ostream& os, const Prompt& prompt);

    void UpdatePrompt(const Prompt& prompt);
    void UpdateInput(const Input& input);
    void Refresh();

    const Input& GetInput() const;

    void Newline();
    bool ReadInput();

private:
    std::istream& is_;
    std::ostream& os_;

    Input input_;
    Prompt prompt_;
};

} // namespace console
} // namespace emsh

#endif // EMSH_CONSOLE_H
