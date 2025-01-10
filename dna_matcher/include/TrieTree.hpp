#pragma once
#include <vector>
#include <set>
#include <string>

class Node {
    friend class TrieTree;
private:
    char key;
    std::vector<Node*> children;
    Node* failureLink;
    std::set<std::string> outputs;
public:
    /**
     * Constructs a node without a key (used to construct the root node of the trie, which does not contain a
     * key).
     */
    Node();

    /**
     * Constructs a node containing the given <b>key</b>.
     */
    Node(char key);

    /**
     * Checks if the node has a child with the given <b>key</b>.
     * @return True if the node has a child with the given <b>key</b>, false otherwise.
     */
    bool hasChild(char key);

    /**
     * Returns the child node with the given <b>key</b>.
     * @return The child node with the given <b>key</b>, or null if no such child exists.
     */
    Node* getChild(char key) const;

    /**
     * Adds a child node to the calling object, with the given <b>key</b>.
     */
    void addChild(char key);

    /**
     * Adds an output string to the calling object.
     * If a node contains an output string, it is the end of a pattern
     * (i.e. when traversed to from the node, the string <b>output</b>  is formed).
     */
    void addOutput(const std::string& output);

    /**
     * Copies the outputs of the given <b>node</b> to the calling object.
     */
    void copyOutputs(Node* node);

    /**
     * Returns the failure link of the calling object.
     * The failure link is transitioned to when a non-matching character is met in the text.
     */
    Node* getFailureLink() const;

    /**
     * Returns the set of output strings that the node contains.
     */
    const std::set<std::string>& getOutputs() const;
};

class TrieTree {

private:
    Node* root;
public:
    /**
     * Constructs a trie tree with the given set of <b>patterns</b>.
     */
    TrieTree(const std::set<std::string> &patterns);

    /**
     * Updates the failure links of the trie tree for all the nodes currently inserted in it.
     */
    void updateFailureLinks();

    /**
     * Returns the root node of the trie tree.
     */
    Node* getRoot() const;
};
