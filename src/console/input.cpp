#include <cctype>
#include <cstring>
#include <exception>

#include "emsh/console/input.h"

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

void Input::Clear() {
    text_.clear();
    cursor_ = 0;
}

bool Input::SetText(const char* text) {
    if (!text_printable(text)) {
        return false;
    }
    text_ = text;
    cursor_ = text_.size();
    return true;
}

bool Input::SetText(const std::string& text) {
    if (!text_printable(text)) {
        return false;
    }
    text_ = text;
    cursor_ = text_.size();
    return true;
}

bool Input::InsertChars(const char c) {
    try {
        if (std::isprint(c) == 0) {
            return false;
        }
        text_.insert(cursor_++, 1, c);
        return true;
    }
    catch (const std::exception&) {
    }
    return false;
}

bool Input::InsertChars(const char* chars) {
    try {
        if (!text_printable(chars)) {
            return false;
        }
        const std::size_t length = std::strlen(chars);
        text_.insert(cursor_, chars, length);
        cursor_ += length;
        return true;
    }
    catch (const std::exception&) {
    }
    return false;
}

bool Input::InsertChars(const std::string& chars) {
    try {
        if (!text_printable(chars)) {
            return false;
        }
        text_.insert(cursor_, chars);
        cursor_ += chars.length();
        return true;
    }
    catch (const std::exception&) {
    }
    return false;
}

bool Input::MoveCursor(const int shift) {
    const int pos = static_cast<int>(cursor_) + shift;
    if (pos < 0 || pos > text_.size()) {
        return false;
    }
    cursor_ = static_cast<std::size_t>(pos);
    return true;
}

bool Input::MoveCursorLeft() {
    if (cursor_ == 0) {
        return false;
    }
    --cursor_;
    return true;
}

bool Input::MoveCursorRight() {
    if (cursor_ == text_.size()) {
        return false;
    }
    ++cursor_;
    return true;
}

bool Input::SetCursor(const std::size_t pos) {
    if (pos > text_.size()) {
        return false;
    }
    cursor_ = pos;
    return true;
}

std::size_t Input::GetCursor() const { return cursor_; }

std::size_t Input::GetTextLength() const { return text_.size(); }

const std::string& Input::GetText() const { return text_; }

bool Input::text_printable(const std::string& text) {
    for (std::string::const_iterator it = text.begin(); it != text.end(); ++it) {
        if (std::isprint(*it) == 0) {
            return false;
        }
    }
    return true;
}

} // namespace console
} // namespace emsh
