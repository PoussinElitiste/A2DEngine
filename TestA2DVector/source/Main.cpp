// external include
#include <iostream>
using namespace std;

// Engine include
#include <A2DEngine.hpp>
using namespace Advanced2D;

int main(int argc, char *argv[])
{
    cout << "VECTOR TEST" << endl;
    A2DVector3 vectA(5, 5, 1);
    cout << "vectA = " << vectA(X) << ","
    << vectA(Y) << "," << vectA(Z) << endl;

    A2DVector3 vectB(90, 80 ,1);
    cout << "vectB = " << vectB(X) << ","
    << vectB(Y) << "," << vectB(Z) << endl;

    cout << "Distance A to B: "
    << vectA.Distance2D( vectB ) << endl;
    cout << "Length of A: " << vectA.Length() << endl;
    cout << "Length of B: " << vectB.Length() << endl;

    vectA.Move(A2DVector3(5, 0, 0));
    cout << "A moved: " << vectA(X) << ","
    << vectA(Y) << "," << vectA(Z) << endl;

    A2DVector3 vectC = vectA;
    cout << "vectC = " << vectC(X) << ","
    << vectC(Y) << "," << vectC(Z) << endl;

    cout << "Dot Product of A and B: " << vectA.DotProduct(vectB) << endl;
    A2DVector3 vectD = vectA.CrossProduct(vectB);
    cout << "Cross Product of A and B: " << vectD(X) << ","
    << vectD(Y) << "," << vectD(Z) << endl;

    vectD = vectA.Normal();
    cout << "Normal of A: " << vectD(X) << ","
    << vectD(Y) << "," << vectD(Z) << endl;

    vectA.Set(2.1,2.2,2.3);
    vectB.Set(3.1,3.2,3.3);
    cout << "A = " << vectA(X) << ","
    << vectA(Y) << "," << vectA(Z) << endl;
    cout << "B = " << vectB(X) << ","
    << vectB(Y) << "," << vectB(Z) << endl;

    vectA += vectB;
    cout << "A + B: " << vectA(X) << ","
    << vectA(Y) << "," << vectA(Z) << endl;
    vectA -= vectB;
    cout << "A - B: " << vectA(X) << ","
    << vectA(Y) << "," << vectA(Z) << endl;
    vectA *= vectB;
    cout << "A * B: " << vectA(X) << ","
    << vectA(Y) << "," << vectA(Z) << endl;
    vectA /= vectB;
    cout << "A / B: " << vectA(X) << ","
    << vectA(Y) << "," << vectA(Z) << endl;
    cout << "A == B: " << (vectA == vectB) << endl; 

    system("pause");

    return 0;
}