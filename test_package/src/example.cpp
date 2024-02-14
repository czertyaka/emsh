#include "emsh/console/console.h"
#include "emsh/console/termios_wrappers.h"

using namespace emsh;

int main() {
    using namespace console::termios_wrap;
    StdinFlagsSetter rawMode(MasksSet::enable_raw_mode());
    console::Console console;
    console.Newline();
    while (console.ReadInput()) {
        const console::Prompt prompt(console.GetInput().GetText() + " > ");
        console.UpdatePrompt(prompt);
        console.UpdateInput(console::Input());
        console.Refresh();
    }
}
