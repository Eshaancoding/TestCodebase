#include "Bezier.h"
#include <cmath>
#include <vector>

long Bezier::factorial (int n) {
    if (n == 1) return 1;
    if (factorial_m.find(n) != factorial_m.end()) {
        return factorial_m[n];
    }
    else {
        long ret = n * factorial(n - 1);
        factorial_m.insert({n, ret});
        return ret;
    }
}

double Bezier::b (int n, int i, double u) {
    long ret = factorial(n) / (factorial(i) * factorial(n - i));
    return (float)ret * pow(u, i) * pow(1 - u, n - i);
}

void Bezier::calc () {
    // bezier curve
    double u = 0.0;
    while (u < 1.0) {
        okapi::Point finalPoint ({0_in, 0_in});

        // calculate bezier
        int i = 0;
        for (auto p : this->points) {
            double b_out = b((int)this->points.size(), i, u);
            finalPoint = {finalPoint.x + p.x * b_out, finalPoint.y + p.y * b_out};
            i += 1;
        }

        this->curve.push_back(finalPoint);

        u += 1.0 / this->numPoints;
    }

    // derivative
    u = 0.0;
    while (u < 1.0) {
        okapi::Point finalPoint ({0_in, 0_in});

        for (int i = 0; i < this->points.size() - 1; i++) {
            double b_out = b((int)this->points.size() - 1, i, u);
            finalPoint = {
                finalPoint.x + b_out * this->points.size() * (this->points[i + 1].x - this->points[i].x),
                finalPoint.y + b_out * this->points.size() * (this->points[i + 1].y - this->points[i].y),
            };
        }

        this->dCurve.push_back(finalPoint);

        u += 1.0 / this->numPoints;
    }

    // derivative of derivative
    u = 0.0;
    while (u < 1.0) {
        okapi::Point finalPoint ({0_in, 0_in});

        for (int i = 0; i < this->points.size() - 2; i++) {
            double b_out = b((int)this->points.size() - 2, i, u);
            finalPoint = {
                finalPoint.x + b_out * this->points.size() * (this->points.size() - 1) * (this->points[i + 2].x - 2 * this->points[i + 1].x + this->points[i].x),
                finalPoint.y + b_out * this->points.size() * (this->points.size() - 1) * (this->points[i + 2].y - 2 * this->points[i + 1].y + this->points[i].y),
            };
        }

        this->ddCurve.push_back(finalPoint);

        u += 1.0 / this->numPoints;
    }

    
}

std::vector<double> Bezier::d () {
    std::vector<double> res;
    for (auto p : this->dCurve) {
        res.push_back(sqrt(pow(p.x.convert(okapi::inch), 2) + pow(p.y.convert(okapi::inch), 2)));
    }
    return res; 
}

std::vector<double> Bezier::dd () {
    std::vector<double> res;
    for (auto p : this->ddCurve) {
        res.push_back(sqrt(pow(p.x.convert(okapi::inch), 2) + pow(p.y.convert(okapi::inch), 2)));
    }
    return res;
}

std::vector<double> Bezier::k () {
    std::vector<double> d_out = d();
    std::vector<double> dd_out = dd();

    std::vector<double> k;

    for (int i = 0; i < d_out.size(); i++) { 
        k.push_back( dd_out[i] / pow(1 + pow(d_out[i], 2), 1.5) );
    }

    return k;
}