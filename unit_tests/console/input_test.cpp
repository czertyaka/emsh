#include <gtest/gtest.h>

#include "console/input.h"

using emsh::console::Input;

namespace {

TEST(InputTest, BasicTest) {
    Input input;
    EXPECT_EQ(input.GetCursor(), 0u);
    EXPECT_EQ(input.GetTextLength(), 0u);
    EXPECT_EQ(input.GetText(), "");

    ASSERT_TRUE(input.Add("test"));
    EXPECT_EQ(input.GetCursor(), 3u);
    EXPECT_EQ(input.GetTextLength(), 4u);
    EXPECT_EQ(input.GetText(), "test");
}

} // namespace
