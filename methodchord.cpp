#include "methodchord.h"

double MethodChord::chordMethod(double x1, double x2) {
    double y1 = function(x1);
    double y2 = function(x2);
    double x0, y0;
    double epsilon = 0.0001;

    while (true) {
        // Compute the new approximation
        x0 = x1 - y1 * (x2 - x1) / (y2 - y1);
        y0 = function(x0);

        // Check for convergence
        if (fabs(y0) < epsilon) {
            return x0;
        }

        // Update points
        if (y0 > 0) {
            x1 = x0;
            y1 = y0;
        }
        else {
            x2 = x0;
            y2 = y0;
        }
    }
}

double MethodChord::function(double x) {
    return x * x + 5*x - 2;
}
