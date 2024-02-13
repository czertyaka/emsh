#include "emsh/console/console.h"

namespace emsh {
namespace console {

Console::Console() : prompt_("emsh > ") {}

// explicit
Console::Console(const Prompt& prompt) : prompt_(prompt) {}

void Console::UpdatePrompt(const Prompt& prompt) { prompt_ = prompt; }

void Console::UpdateInput(const Input& input) { input_ = input; }

void Refresh() {
    // @TODO: implement
}

const Input& Console::GetInput() const { return input_; }

bool Console::Newline() {
    // @TODO: implement
    return false;
}

ControlSequence Console::ReadInput() {
    // @TODO: implement
    return CS_ENTER;
}

} // namespace console
} // namespace emsh
