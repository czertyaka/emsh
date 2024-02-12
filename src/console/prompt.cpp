#include <console/prompt.h>

namespace emsh {
namespace console {

Prompt::Prompt() : text_("emsh > ") {}

// explicit
Prompt::Prompt(const std::string& text) : text_(text) {}

Prompt::Prompt(const Prompt& other) : text_(other.text_) {}

Prompt& Prompt::operator=(const Prompt& other) {
    if (this != &other) {
        text_ = other.text_;
    }
    return *this;
}

const std::string& Prompt::Text() const { return text_; }

} // namespace console
} // namespace emsh
