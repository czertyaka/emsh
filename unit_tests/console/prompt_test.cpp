#include <gtest/gtest.h>

#include "emsh/console/prompt.h"

using emsh::console::Prompt;

namespace {

TEST(PromptTest, DefaultConstructorAddsNoText) {
    Prompt prompt;
    EXPECT_TRUE(prompt.Text().empty());
}

TEST(Prompt, ConstructorWithStringAddsText) {
    Prompt prompt("test > ");
    EXPECT_EQ(prompt.Text(), "test > ");
}

TEST(Prompt, CopyConstructorDoesItsThing) {
    Prompt prompt1("test > ");
    Prompt prompt2(prompt1);
    EXPECT_EQ(prompt2.Text(), "test > ");
}

TEST(PromptTest, AssignmentOperatorDoesItsThing) {
    Prompt prompt1("test > ");
    Prompt prompt2(" < test");
    prompt1 = prompt2;
    EXPECT_EQ(prompt2.Text(), " < test");
}

} // namespace
