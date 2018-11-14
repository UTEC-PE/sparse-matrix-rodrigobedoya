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

    Matrix<int> B;
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

    Matrix<int> D;
    D = B+a;
    cout << endl;
    cout << D(0,0) << endl;
    cout << D(1,1) << endl;
    cout << D(2,1) << endl;
    cout << D(1,3) << endl;
    cout << D(2,3) << endl;
    cout << D(2,2) << endl;
    cout << D(0,2) << endl;
    cout << D(1,2) << endl;
    cout << D(0,1) << endl;
    cout << (D*2)(0,1) << endl;
    cout << D.transposed()(1,0) << endl;




    Matrix<int> m1(2,1);
    Matrix<int> m2(1,2);

    m1.set(0,0,2);
    m1.set(1,0,1);
    m2.set(0,0,3);
    m2.set(0,1,4);

    cout << m1(0,0) << endl;
    cout << m1(1,0) << endl;
    cout << m2(0,0) << m2(0,1) << endl;

    Matrix<int> C(2,2);
    C = (m1*m2);
    C.remove(1,0);
    cout << C(0,0) << "," << C(0,1) << endl;
    cout << C(1,0) << "," << C(1,1) << endl;
      
    return EXIT_SUCCESS;
}