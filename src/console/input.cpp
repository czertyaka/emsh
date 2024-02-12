#include "console/input.h"

namespace emsh {
namespace console {

Input::Input() : cursor_(0) {}

Input::Input(const Input& other) : text_(other.text_), cursor_(other.cursor_) {}

Input& Input::operator=(const Input& other) {
    if (this != &other) {
        text_ = other.text_;
        cursor_ = other.cursor_;
    }
    return *this;
}

bool Input::SetText(const char* text) { return false; }

bool Input::SetText(const std::string& text) { return false; }

bool Input::InsertChars(const char c) { return false; }

bool Input::InsertChars(const char* chars) { return false; }

bool Input::InsertChars(const std::string& chars) { return false; }

bool Input::MoveCursor(const int shift) { return false; }

bool Input::MoveCursorLeft() { return false; }

bool Input::MoveCursorRight() { return false; }

bool Input::SetCursor(const std::size_t pos) { return false; }

std::size_t Input::GetCursor() const { return cursor_; }

std::size_t Input::GetTextLength() const { return text_.size(); }

const std::string& Input::GetText() const { return text_; }

} // namespace console
} // namespace emsh
