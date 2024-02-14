#include <gtest/gtest.h>

#include "emsh/console/termios_wrappers.h"

using emsh::console::termios_wrap::Mask;

namespace {

struct MaskTest : testing::Test {
    tcflag_t flag = 0b1010;
    Mask mask;
};

TEST_F(MaskTest, DefaultMaskDoesNotApply) {
    EXPECT_FALSE(mask.Apply(flag));
    EXPECT_EQ(flag, 0b1010);
}

TEST_F(MaskTest, MaskWithAddedFlagApply) {
    mask.AddFlag(0b0100);

    EXPECT_TRUE(mask.Apply(flag));
    EXPECT_EQ(flag, 0b1110);
}

TEST_F(MaskTest, MaskWithAddedFlagDoesNotApply) {
    mask.AddFlag(0b1000);

    EXPECT_FALSE(mask.Apply(flag));
    EXPECT_EQ(flag, 0b1010);
}

TEST_F(MaskTest, MaskWithRemovedFlagApply) {
    mask.RemoveFlag(0b1000);

    EXPECT_TRUE(mask.Apply(flag));
    EXPECT_EQ(flag, 0b0010);
}

TEST_F(MaskTest, MaskWithRemovedFlagDoesNotApply) {
    mask.RemoveFlag(0b0100);

    EXPECT_FALSE(mask.Apply(flag));
    EXPECT_EQ(flag, 0b1010);
}

TEST_F(MaskTest, MasksWithAddedAndRemovedFlagsApply) {
    mask.AddFlag(0b0101);
    mask.RemoveFlag(0b1010);

    EXPECT_TRUE(mask.Apply(flag));
    EXPECT_EQ(flag, 0b0101);
}

TEST_F(MaskTest, MasksWithAddedAndRemovedFlagsDoesNotApply) {
    mask.AddFlag(0b1010);
    mask.RemoveFlag(0b0101);

    EXPECT_FALSE(mask.Apply(flag));
    EXPECT_EQ(flag, 0b1010);
}

} // namespace
