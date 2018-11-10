#ifndef NODE_H
#define NODE_H

using namespace std;

template <class T>
class Node {
public:

	Node(T data,Node* next = NULL, Node* down = NULL):
		data(data),next(next),down(down) {}

	Node(int x,int y,T data = 0,Node* next = NULL, Node* down = NULL):
		x(x),y(y),data(data),next(next),down(down) {}
    
    int x, y;
    T data;
    Node* next;
    Node* down;

};

#endif