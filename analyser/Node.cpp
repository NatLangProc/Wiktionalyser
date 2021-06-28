#include "Node.h"

int countLeftEq(const std::string& line) {
    int leftCnt = 0;
    while (line[leftCnt]=='=') leftCnt++;
    return leftCnt;
}

int countRightEq(const std::string& line) {
    int rightCnt = 0;
    int pos = line.length()-1;
    while (pos>=0 && line[pos]=='+') {
        pos--;
        rightCnt++;
    }
    while (pos>=0 && line[pos]=='=') {
        pos--;
        rightCnt++;
    }
    return rightCnt;
}

Node::Node() {
    level = 0;
    eqCnt = 1;
}

Node::Node(const std::string& line) {
    int leftCnt = countLeftEq(line);
    int rightCnt = countRightEq(line);
    eqCnt = std::max(leftCnt, rightCnt);
    level = 0;
    name = line.substr(leftCnt, line.length()-leftCnt-rightCnt);
}

void Node::link(Node* node) {
    Node* ancestor = node;
    while (ancestor && ancestor->eqCnt >= eqCnt) ancestor = ancestor->parent;
    parent = ancestor;
    ancestor->childs.push_back(this);
}

Node::~Node() {
    for (Node* child: childs)
        delete child;
}