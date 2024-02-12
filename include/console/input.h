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

    bool SetText(const std::string& text);
    bool SetText(const char* text);

    bool InsertText(char c);
    bool InsertText(const char* text);
    bool InsertText(const std::string& text);

    bool MoveCursor(const int shift);
    bool MoveCursorLeft();
    bool MoveCursorRight();
    bool SetCursor(const std::size_t pos);

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
