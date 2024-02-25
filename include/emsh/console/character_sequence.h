#ifndef CHARACTER_SEQUENCE_H
#define CHARACTER_SEQUENCE_H

#include <cstddef>
#include <string>
#include <vector>

namespace emsh {
namespace console {
namespace charseq {

struct Node {
    typedef std::vector<Node> Children;

    char value;
    std::vector<Node> childNodes;
};

class SequencesCollection {
public:
    SequencesCollection();
    void Add(const char* sequence, const std::size_t length);
    void Add(const std::string& sequence);
    const Node& Root();

private:
    Node root_;
};

class SearchByChar {
public:
    SearchByChar(const Node& root);
    bool Search(const char c);
    bool End() const;

private:
    const Node* currentNode_;
};

} // namespace charseq
} // namespace console
} // namespace emsh

#endif // CHARACTER_SEQUENCE_H
