#include <cctype>
#include <limits>
#include <string>

#include <gtest/gtest.h>

#include "emsh/console/input.h"

using emsh::console::Input;

namespace {

TEST(InputTest, DefaultInputIsEmpty) {
    Input input;
    EXPECT_EQ(input.GetCursor(), 0u);
    EXPECT_EQ(input.GetTextLength(), 0u);
    EXPECT_EQ(input.GetText(), "");
}

TEST(InputTest, ClearUpdatesCursorAndText) {
    Input input;

    ASSERT_TRUE(input.SetText("FizzBuzz"));
    ASSERT_EQ(input.GetCursor(), 8u);
    ASSERT_EQ(input.GetTextLength(), 8u);
    ASSERT_EQ(input.GetText(), "FizzBuzz");

    input.Clear();
    EXPECT_EQ(input.GetCursor(), 0u);
    EXPECT_EQ(input.GetTextLength(), 0u);
    EXPECT_EQ(input.GetText(), "");
}

template <typename T> class InputTextTypedTest : public testing::Test {};

using TextTypes = testing::Types<const char*, std::string>;
TYPED_TEST_SUITE(InputTextTypedTest, TextTypes);

TYPED_TEST(InputTextTypedTest, SetTextUpdatesCursorAndText) {
    Input input;

    TypeParam text = "Fizz";
    EXPECT_TRUE(input.SetText(text));
    EXPECT_EQ(input.GetCursor(), 4u);
    EXPECT_EQ(input.GetTextLength(), 4u);
    EXPECT_EQ(input.GetText(), "Fizz");

    text = "Buzz";
    EXPECT_TRUE(input.SetText(text));
    EXPECT_EQ(input.GetCursor(), 4u);
    EXPECT_EQ(input.GetTextLength(), 4u);
    EXPECT_EQ(input.GetText(), "Buzz");
}

TYPED_TEST(InputTextTypedTest, SetTextErasesPreviousText) {
    const TypeParam text = "FizzBuzz";

    Input input;
    ASSERT_TRUE(input.SetText("replace me"));

    EXPECT_TRUE(input.SetText(text));
    EXPECT_EQ(input.GetCursor(), 8u);
    EXPECT_EQ(input.GetTextLength(), 8u);
    EXPECT_EQ(input.GetText(), "FizzBuzz");
}

TYPED_TEST(InputTextTypedTest, ResetInputWithSetText) {
    const TypeParam text = "";

    Input input;
    ASSERT_TRUE(input.SetText("erase me"));

    EXPECT_TRUE(input.SetText(text));
    EXPECT_EQ(input.GetCursor(), 0u);
    EXPECT_EQ(input.GetTextLength(), 0u);
    EXPECT_EQ(input.GetText(), "");
}

TYPED_TEST(InputTextTypedTest, CanNotSetUnprintableText) {
    using limits = std::numeric_limits<char>;
    for (char c = limits::min(); c < limits::max(); ++c) {
        if (std::isprint(c) != 0 || c == '\0' || c == '\n') {
            continue;
        }

        char buffer[] = "FizzBuzz";
        buffer[2] = c;
        const TypeParam text = buffer;

        Input input;
        ASSERT_TRUE(input.SetText("BuzzFizz"));

        EXPECT_FALSE(input.SetText(text));
        EXPECT_EQ(input.GetCursor(), 8u);
        EXPECT_EQ(input.GetTextLength(), 8u);
        EXPECT_EQ(input.GetText(), "BuzzFizz");
    }
}

TYPED_TEST(InputTextTypedTest, InsertCharsUpdatesCursorAndText) {
    Input input;
    const TypeParam chars = "FizzBuzz";

    ASSERT_TRUE(input.InsertChars(chars));
    EXPECT_EQ(input.GetCursor(), std::string(chars).size());
    EXPECT_EQ(input.GetTextLength(), std::string(chars).size());
    EXPECT_EQ(input.GetText(), chars);
}

TEST(InputTest, InsertCharUpdatesCursorAndText) {
    Input input;

    ASSERT_TRUE(input.InsertChars('c'));
    EXPECT_EQ(input.GetCursor(), 1u);
    EXPECT_EQ(input.GetTextLength(), 1u);
    EXPECT_EQ(input.GetText(), "c");
}

TYPED_TEST(InputTextTypedTest, CanNotInsertUnprintableCharacters) {
    using limits = std::numeric_limits<char>;
    for (char c = limits::min(); c < limits::max(); ++c) {
        if (std::isprint(c) != 0 || c == '\0' || c == '\n') {
            continue;
        }

        char buffer[] = "FizzBuzz";
        buffer[2] = c;
        const TypeParam chars = buffer;

        Input input;
        ASSERT_TRUE(input.SetText("BuzzFizz"));

        EXPECT_FALSE(input.InsertChars(chars)) << "c = " << c;
        EXPECT_EQ(input.GetCursor(), 8u);
        EXPECT_EQ(input.GetTextLength(), 8u);
        EXPECT_EQ(input.GetText(), "BuzzFizz");
    }
}

TEST(InputTest, CanNotInsertUnprintableCharacter) {
    using limits = std::numeric_limits<char>;
    for (char c = limits::min(); c < limits::max(); ++c) {
        if (std::isprint(c) != 0) {
            continue;
        }

        Input input;
        ASSERT_TRUE(input.SetText("BuzzFizz"));

        EXPECT_FALSE(input.InsertChars(c));
        EXPECT_EQ(input.GetCursor(), 8u);
        EXPECT_EQ(input.GetTextLength(), 8u);
        EXPECT_EQ(input.GetText(), "BuzzFizz");
    }
}

TYPED_TEST(InputTextTypedTest, InsertCharsInTheMiddleOfText) {
    Input input;
    ASSERT_TRUE(input.SetText("FizzFuzz"));
    ASSERT_TRUE(input.SetCursor(4));

    const TypeParam chars = " Buzz ";
    EXPECT_TRUE(input.InsertChars(chars));
    EXPECT_EQ(input.GetCursor(), 10u);
    EXPECT_EQ(input.GetTextLength(), 14u);
    EXPECT_EQ(input.GetText(), "Fizz Buzz Fuzz");
}

TEST(InputTest, InsertCharInTheMiddleOfText) {
    Input input;
    ASSERT_TRUE(input.SetText("FizzFuzz"));
    ASSERT_TRUE(input.SetCursor(4));

    EXPECT_TRUE(input.InsertChars('c'));
    EXPECT_EQ(input.GetCursor(), 5u);
    EXPECT_EQ(input.GetTextLength(), 9u);
    EXPECT_EQ(input.GetText(), "FizzcFuzz");
}

TYPED_TEST(InputTextTypedTest, InsertCharsBeforeText) {
    Input input;
    ASSERT_TRUE(input.SetText("Buzz"));
    ASSERT_TRUE(input.SetCursor(0));

    const TypeParam chars = "Fizz";
    EXPECT_TRUE(input.InsertChars(chars));
    EXPECT_EQ(input.GetCursor(), 4u);
    EXPECT_EQ(input.GetTextLength(), 8u);
    EXPECT_EQ(input.GetText(), "FizzBuzz");
}

TEST(InputTest, InsertCharBeforeText) {
    Input input;
    ASSERT_TRUE(input.SetText("Buzz"));
    ASSERT_TRUE(input.SetCursor(0));

    EXPECT_TRUE(input.InsertChars('c'));
    EXPECT_EQ(input.GetCursor(), 1u);
    EXPECT_EQ(input.GetTextLength(), 5u);
    EXPECT_EQ(input.GetText(), "cBuzz");
}

class InputCursorTest : public testing::Test {
public:
    void SetUp() {
        ASSERT_TRUE(input.SetText("FizzBuzz"));
        ASSERT_TRUE(input.SetCursor(4));
    }

    Input input;
};

TEST_F(InputCursorTest, MoveCursorPositiveShift) {
    ASSERT_TRUE(input.MoveCursor(2));

    EXPECT_EQ(input.GetCursor(), 6u);
    EXPECT_EQ(input.GetTextLength(), 8u);
    EXPECT_EQ(input.GetText(), "FizzBuzz");
}

TEST_F(InputCursorTest, MoveCursorNegativeShift) {
    ASSERT_TRUE(input.MoveCursor(-2));

    EXPECT_EQ(input.GetCursor(), 2u);
    EXPECT_EQ(input.GetTextLength(), 8u);
    EXPECT_EQ(input.GetText(), "FizzBuzz");
}

TEST_F(InputCursorTest, CanNotMoveCursorTooMuchRight) {
    ASSERT_FALSE(input.MoveCursor(5));

    EXPECT_EQ(input.GetCursor(), 4u);
    EXPECT_EQ(input.GetTextLength(), 8u);
    EXPECT_EQ(input.GetText(), "FizzBuzz");
}

TEST_F(InputCursorTest, CanNotMoveCursorTooMuchLeft) {
    ASSERT_FALSE(input.MoveCursor(-5));

    EXPECT_EQ(input.GetCursor(), 4u);
    EXPECT_EQ(input.GetTextLength(), 8u);
    EXPECT_EQ(input.GetText(), "FizzBuzz");
}

TEST_F(InputCursorTest, MoveCursorLeftUpdatesCursor) {
    ASSERT_TRUE(input.MoveCursorLeft());

    EXPECT_EQ(input.GetCursor(), 3u);
    EXPECT_EQ(input.GetTextLength(), 8u);
    EXPECT_EQ(input.GetText(), "FizzBuzz");

    while (input.MoveCursorLeft()) {
    }

    EXPECT_EQ(input.GetCursor(), 0u);
    EXPECT_EQ(input.GetTextLength(), 8u);
    EXPECT_EQ(input.GetText(), "FizzBuzz");
}

TEST_F(InputCursorTest, MoveCursorRightUpdatesCursor) {
    ASSERT_TRUE(input.MoveCursorRight());

    EXPECT_EQ(input.GetCursor(), 5u);
    EXPECT_EQ(input.GetTextLength(), 8u);
    EXPECT_EQ(input.GetText(), "FizzBuzz");

    while (input.MoveCursorRight()) {
    }

    EXPECT_EQ(input.GetCursor(), 8u);
    EXPECT_EQ(input.GetTextLength(), 8u);
    EXPECT_EQ(input.GetText(), "FizzBuzz");
}

TEST_F(InputCursorTest, SetCursorUpdatesCursor) {
    ASSERT_TRUE(input.SetCursor(0));
    EXPECT_EQ(input.GetCursor(), 0u);
    EXPECT_EQ(input.GetTextLength(), 8u);
    EXPECT_EQ(input.GetText(), "FizzBuzz");
}

TEST_F(InputCursorTest, CanNotSetCursorOutsideOfText) {
    ASSERT_FALSE(input.SetCursor(9));
    EXPECT_EQ(input.GetCursor(), 4u);
    EXPECT_EQ(input.GetTextLength(), 8u);
    EXPECT_EQ(input.GetText(), "FizzBuzz");
}

} // namespace
