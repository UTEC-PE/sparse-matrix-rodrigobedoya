#include <iostream>
#include "matrix.h"
#define EXIT_SUCCESS 0

using namespace std;

int main(int argc, char *argv[]) {
    Matrix<int> a(5, 5);
	a.set(0,0,2);
    a.set(1,1,2);
    a.set(2,1,3);
    a.set(1,1,4);
    a.set(1,3,5);
    a.set(2,3,8);
    a.set(2,2,9);
    a.set(0,2,5);
    a.set(1,2,9);
    a.set(0,1,10);           

    cout << a(0,0) << endl;
    cout << a(1,1) << endl;
    cout << a(2,1) << endl;
    cout << a(1,3) << endl;
    cout << a(2,3) << endl;
    cout << a(2,2) << endl;
    cout << a(0,2) << endl;
    cout << a(1,2) << endl;
    cout << a(0,1) << endl;
    cout << (a*2)(0,1) << endl;
    cout << a.transposed()(1,0) << endl;

    Matrix<int> B(5, 5);
    B = a;
    cout << endl;
    cout << B(0,0) << endl;
    cout << B(1,1) << endl;
    cout << B(2,1) << endl;
    cout << B(1,3) << endl;
    cout << B(2,3) << endl;
    cout << B(2,2) << endl;
    cout << B(0,2) << endl;
    cout << B(1,2) << endl;
    cout << B(0,1) << endl;
    cout << (B*2)(0,1) << endl;
    cout << B.transposed()(1,0) << endl;

    return EXIT_SUCCESS;
}