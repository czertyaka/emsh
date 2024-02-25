#ifndef EMSH_ESCAPE_SEQUENCES_H
#define EMSH_ESCAPE_SEQUENCES_H

#include <cstddef>
#include <string>

namespace emsh {
namespace console {
namespace escape_sequences {

namespace ASCII {

extern const std::string backspace;
extern const std::string tab;
extern const std::string new_line;
extern const std::string carriage_return;
extern const std::string escape;
extern const std::string del;

} // namespace ASCII

namespace VT100 {

extern const std::string cursor_up_1;
extern const std::string cursor_down_1;
extern const std::string cursor_right_1;
extern const std::string cursor_left_1;

std::string cursor_up(const std::size_t times);
std::string cursor_down(const std::size_t times);
std::string cursor_right(const std::size_t times);
std::string cursor_left(const std::size_t times);

extern const std::string home;
extern const std::string end;
extern const std::string insert;
extern const std::string del;
extern const std::string pgup;
extern const std::string pgdn;

extern const std::string clear_eol;
extern const std::string clear_bol;
extern const std::string clear_line;

} // namespace VT100

} // namespace escape_sequences
} // namespace console
} // namespace emsh

#endif // EMSH_ESCAPE_SEQUENCES_H
