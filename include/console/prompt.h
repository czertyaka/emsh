#ifndef EMSH_PROMPT_H
#define EMSH_PROMPT_H

#include <string>

namespace console {

class Prompt {
public:
    Prompt();
    explicit Prompt(const std::string &text);
    Prompt(const Prompt &other);
    Prompt &operator=(const Prompt &other);

    const std::string &Text() const;

private:
    std::string text_;
};

} // namespace console

#endif // EMSH_PROMPT_H
