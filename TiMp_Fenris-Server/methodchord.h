#ifndef METHODCHORD_H
#define METHODCHORD_H
#include <cmath>

class MethodChord
{
public:

    // Chord method implementation
    double chordMethod(double x1, double x2);

private:

    // Define the function whose root we want to find
    double function(double x);
};

#endif // METHODCHORD_H
