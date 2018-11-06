#ifndef NODE_H
#define NODE_H

using namespace std;

template <class T>
class Node {
    int x, y;
    T data;
    Node* next;
    Node* down;
};

#endif