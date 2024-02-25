#include <algorithm>
#include <stdexcept>

#include "emsh/console/character_sequence.h"

namespace emsh {
namespace console {
namespace charseq {

static bool operator==(const Node& node, const char c) {
    return node.value == c;
}

SequencesCollection::SequencesCollection() {
    root_.value = 0;
}

void SequencesCollection::Add(const char* sequence, const std::size_t length) {
    if (!sequence) {
        throw std::invalid_argument("can't add NULL sequence");
    }

    Node::Children* children = &root_.childNodes;
    for (std::size_t i = 0; i < length; ++i) {
        Node::Children::iterator it = std::find(children->begin(), children->end(), sequence[i]);
        if (it != children->end()) {
            children = &it->childNodes;
        }
        else {
            Node node;
            node.value = sequence[i];
            children->push_back(node);
            children = &children->back().childNodes;
        }
    }
}

void SequencesCollection::Add(const std::string& sequence) {
    Add(sequence.c_str(), sequence.size());
}

const Node& SequencesCollection::Root() {
    return root_;
}

SearchByChar::SearchByChar(const Node& root) : currentNode_(&root) {}

bool SearchByChar::Search(const char c) {
    const Node::Children& children = currentNode_->childNodes;
    Node::Children::const_iterator it = std::find(children.begin(), children.end(), c);
    if (it == children.end()) {
        return false;
    }
    currentNode_ = &(*it);
    return true;
}

bool SearchByChar::End() const {
    return currentNode_->childNodes.empty();
}

} // namespace charseq
} // namespace console
} // namespace emsh
