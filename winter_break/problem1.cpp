#include <iostream>
#include <cmath>
using namespace std;

int a = 3;  
int b = 3;  
int c = a++;  
int d = ++b;  
// intermediate point  
int the_answer = (--c + b++) * (--a + d);
int y = abs(3.14);


int main(){
    cout << "a is:" << a << endl;
    cout << "b is:" << b << endl;
    cout << "c is:" << c << endl;
    cout << "d is:" << d << endl;
    cout << "y is:" << y << endl;
    int i;  
    float f;  
    char j, k;  
    cin >> i >> f >> j >> k;  
    return 0;
}
