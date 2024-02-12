#ifndef EMSH_INPUT_H
#define EMSH_INPUT_H

#include <cstddef>
#include <string>

namespace emsh {
namespace console {

class Input {
public:
    Input();
    Input(const Input& other);
    Input& operator=(const Input& other);

    bool Add(char c);
    bool Add(const char* text);
    bool Add(const std::string& text);

    bool MoveCursor(const int shift);
    bool MoveCursorLeft();
    bool MoveCursorRight();
    bool SetCursor(const std::size_t pos);

    bool SetText(const std::string& text);
    bool SetText(const char* text);

    std::size_t GetCursor() const;
    std::size_t GetTextLength() const;
    const std::string& GetText() const;

private:
    std::string text_;
    std::size_t cursor_;
};

} // namespace console
} // namespace emsh

#endif // EMSH_INPUT_H
