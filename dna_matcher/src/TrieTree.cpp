#include <queue>
#include "TrieTree.hpp"

Node::Node() {
    this->key = 0;
    this->failureLink = nullptr;
    this->children = std::vector<Node *>{};
    this->outputs = std::set<std::string>{};
}

Node::Node(char key) : Node() {
    this->key = key;
}

bool Node::hasChild(char key) {
    for (auto child : children) {
        if (child->key == key)
            return true;
    }
    return false;
}

Node *Node::getChild(char key) const {
    for (auto child : children) {
        if (child->key == key)
            return child;
    }
    return nullptr;
}

void Node::addChild(char key) {
    children.push_back(new Node(key));
}

void Node::addOutput(const std::string& output) {
    outputs.insert(output);
}

void Node::copyOutputs(Node *node) {
    outputs.insert(node->outputs.begin(), node->outputs.end());
}

Node* Node::getFailureLink() const {
    return failureLink;
}

const std::set<std::string>& Node::getOutputs() const {
    return outputs;
}

Node *TrieTree::getRoot() const {
    return root;
}

TrieTree::TrieTree(const std::set<std::string> &patterns) {

    this->root = new Node();
    Node *currentNode = this->root;

    for (const auto &pattern: patterns) {
        for (int i = 0; i < pattern.length(); i++) {
            char key = pattern[i];
            if (!currentNode->hasChild(key))
                currentNode->addChild(key);
            // Move down the tree
            currentNode = currentNode->getChild(key);
        }

        // By the end of the for loop,
        //  the whole pattern string has been processed
        //  and the currentNode is at the
        //  last character of the pattern
        //  we must add the pattern to the outputs of the node
        //  to indicate that this node is the end of a pattern
        currentNode->addOutput(pattern);

        // Reset the currentNode to the root
        currentNode = this->root;
    }

    // Construct failure links
    updateFailureLinks();

    /*
    for (const auto& pattern : patterns) {
        Node* current = root;
        for (char c : pattern) {
            if (!current->hasChild(c))
                current->addChild(c);
            current = current->getChild(c);
        }
        current->addOutput(pattern);
    }
    root->failureLink = root;
    std::queue<Node*> queue;
    for (auto child : root->children) {
        child->failureLink = root;
        queue.push(child);
    }
    while (!queue.empty()) {
        Node* current = queue.front();
        queue.pop();
        for (auto child : current->children) {
            Node* state = current->failureLink;
            while (!state->hasChild(child->key) && state != root)
                state = state->failureLink;
            if (state->hasChild(child->key))
                child->failureLink = state->getChild(child->key);
            else
                child->failureLink = root;
            child->copyOutputs(child->failureLink);
            queue.push(child);
        }
    }
    */

}

void TrieTree::updateFailureLinks() {
    // The root's failure link is the root itself
    this->root->failureLink = this->root;

    // Create a queue to perform a breadth-first search
    std::queue<Node*> queue;

    // Add the root's children to the queue
    for (auto child: this->root->children) {
        // The root's children have the root as their failure link
        child->failureLink = this->root;
        queue.push(child);
    }

    // While there are still nodes to be processed
    while (queue.size() != 0) {
        // Extract (get and pop) the first node in the queue
        Node* currentNode = queue.front();
        queue.pop();

        // Add the current node's children to the queue
        for (auto child: currentNode->children) {
            queue.push(child);
            Node* currentFailureLink = currentNode->failureLink;

            // Follow the failure links
            // until we find a node that either has a transition with the child's key
            // or until we reach the root
            while (!currentFailureLink->hasChild(child->key)
                   && currentFailureLink != this->root) {
                currentFailureLink = currentFailureLink->failureLink;
            }

            // Found the target of the failure link
            //  (i.e. when we kept going through the failure links,
            //  we eventually found one that does something when reading the child's key,
            //  or we reached the root)
            // Set the failure link accordingly
            child->failureLink =
                    currentFailureLink->getChild(child->key) != nullptr ?
                    currentFailureLink->getChild(child->key) : this->root;

            // Copy the outputs of the failure link to the current node
            child->copyOutputs(child->failureLink);
        }
    }
}
