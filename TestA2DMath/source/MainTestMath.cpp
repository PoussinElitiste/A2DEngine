// external include
#include <iostream>
#include <iomanip>
using namespace std;

// Engine include
#include <A2DMath.hpp>
#include <A2DTypes.hpp>
using namespace Advanced2D;

int32 main(int32 argc, char8* argv[])
{
    A2DMath math;
    float32 angle, x, y;
    cout << "MATH TEST" << endl << endl;
    cout.setf(ios::fixed);
    cout << setprecision(2);

    A2DVector3 vectA(5, 5, 1);
    cout << "vectA = " << vectA(X) << ", " << vectA(Y) << ", " << vectA(Z) << endl;
    A2DVector3 vectB(90, 80 ,1);
    cout << "vectB = " << vectB(X) << ", " << vectB(Y) << ", " << vectB(Z) << endl;

    cout << endl <<"Distance : " << math.Distance(vectA, vectB) << endl;
    cout << "Dot Product : " << math.DotProduct(vectA, vectB) << endl;

    A2DVector3 vectD =  math.CrossProduct(vectA, vectB);
    cout << "Cross Product : " << vectD(X) << ", " << vectD(Y) << ", " << vectD(Z) << endl;

    vectD = math.Normal(vectA);
    cout << "Normalized vectA: " << vectD(X) << ", " << vectD(Y) << ", " << vectD(Z) << endl;
    vectD = math.Normal(vectB);
    cout << "Normalized vectB: " << vectD(X) << ", " << vectD(Y) << ", " << vectD(Z) << endl;

    angle = (float32)(math.AngleToTarget( vectA, vectB ));
    cout << "Angle to target: " << angle << " radians (";
    cout << math.ToDegrees(angle) << " degrees)" << endl << endl;
    for (angle = 0; angle < 360; angle += 45) 
    {
        x = (float32)(math.LinearVelocityX(angle));
        y = (float32)(math.LinearVelocityY(angle));
        cout << "Linear velocity (" << setprecision(0) << angle << " degrees): ";
        cout << setprecision(2) << x << ", " << y << endl;
    }

    system("pause");

    return 0;
}