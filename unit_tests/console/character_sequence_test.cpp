#include <algorithm>
#include <ostream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "emsh/console/character_sequence.h"

using emsh::console::charseq::Node;
using emsh::console::charseq::SequencesCollection;

using testing::UnorderedElementsAre;

namespace emsh {
namespace console {
namespace charseq {

bool operator==(const Node& node, const char c) {
    return node.value == c;
}

} // namespace charseq
} // namespace console
} // namespace emsh

namespace {

struct SequencesCollectionTest : testing::Test {
    SequencesCollection collection;

    void FindChild(const char c, const Node& parent, Node& child) {
        const auto& children = parent.childNodes;
        auto it = std::find(children.cbegin(), children.cend(), c);
        ASSERT_NE(it, children.cend());
        child = *it;
    }
};

TEST_F(SequencesCollectionTest, CollectionIsEmptyByDefault) {
    EXPECT_TRUE(collection.Root().childNodes.empty());
}

TEST_F(SequencesCollectionTest, AddNullThrows) {
    EXPECT_ANY_THROW(collection.Add(NULL, 0));
}

TEST_F(SequencesCollectionTest, AddEmptyStringSequence) {
    ASSERT_NO_THROW(collection.Add(""));
    EXPECT_TRUE(collection.Root().childNodes.empty());
}

TEST_F(SequencesCollectionTest, AddEmptyCStringSequence) {
    ASSERT_NO_THROW(collection.Add("", 0));
    EXPECT_TRUE(collection.Root().childNodes.empty());
}

TEST_F(SequencesCollectionTest, AddZeroSizeCStringSequence) {
    ASSERT_NO_THROW(collection.Add("fizzbuzz", 0));
    EXPECT_TRUE(collection.Root().childNodes.empty());
}

TEST_F(SequencesCollectionTest, AddSingleSequence) {
    ASSERT_NO_THROW(collection.Add("\xff"
                                   "c\r"));
    ASSERT_THAT(collection.Root().childNodes, UnorderedElementsAre('\xff'));
    ASSERT_THAT(collection.Root().childNodes[0].childNodes, UnorderedElementsAre('c'));
    ASSERT_THAT(collection.Root().childNodes[0].childNodes[0].childNodes,
                UnorderedElementsAre('\r'));
}

TEST_F(SequencesCollectionTest, AddSeveralSequences) {
    ASSERT_NO_THROW(collection.Add("abc"));
    ASSERT_NO_THROW(collection.Add("acb"));
    ASSERT_NO_THROW(collection.Add("az"));
    ASSERT_NO_THROW(collection.Add("bz"));
    ASSERT_THAT(collection.Root().childNodes, UnorderedElementsAre('a', 'b'));
    {
        Node node;
        FindChild('b', collection.Root(), node);
        ASSERT_THAT(node.childNodes, UnorderedElementsAre('z'));
        ASSERT_TRUE(node.childNodes[0].childNodes.empty());
    }
    {
        Node node;
        FindChild('a', collection.Root(), node);
        ASSERT_THAT(node.childNodes, UnorderedElementsAre('b', 'c', 'z'));

        const Node parent = node;

        FindChild('b', parent, node);
        ASSERT_THAT(node.childNodes, UnorderedElementsAre('c'));
        ASSERT_TRUE(node.childNodes[0].childNodes.empty());

        FindChild('c', parent, node);
        ASSERT_THAT(node.childNodes, UnorderedElementsAre('b'));
        ASSERT_TRUE(node.childNodes[0].childNodes.empty());

        FindChild('z', parent, node);
        ASSERT_TRUE(node.childNodes.empty());
    }
}

} // namespace
