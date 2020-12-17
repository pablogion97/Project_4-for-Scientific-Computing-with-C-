// Project_4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <cmath>
#include "GFkt.h"

double f(Point p) {
    return sin((0.01 * p.x * p.x)) * cos(0.1 * p.x) + p.y;
}

int main(int argc, char* argv[])
{
    // Generate curves
    std::shared_ptr<Curve> bottomCurve = std::make_shared<Curve>(-10, 5, 0, true, -3);
    std::shared_ptr<VLine> rightCurve = std::make_shared<VLine>(0, 3, 5, true);
    std::shared_ptr<HLine> topCurve = std::make_shared<HLine>(-10, 5, 3, false);
    std::shared_ptr<VLine> leftCurve = std::make_shared<VLine>(0, 3, -10, false);

    // Set grid spacings
    const size_t NX = 49;
    const size_t NY = 19;

    // Generate domain
    std::shared_ptr<Domain> domain = std::make_shared<Domain>(bottomCurve, rightCurve, topCurve, leftCurve);

    // Generate grid
    domain->generate_grid(NX, NY);

    // Export grid to csv file
    domain->print();

    // Initialize domain
    GFkt u(domain);
    GFkt dudx(domain);
    GFkt dudy(domain);
    GFkt d2u(domain);

    // Set the function values according to the function above
    u.setFunction(&f);

    // Compute derivatives in x and y
    u.D0xy(dudx, dudy);

    // String to denote the name of the output csv files
    std::string name = "u";

    // u
    u.print(name);
    
    // dudx
    name = "dudx";
    dudx.print(name);

    // dudy
    name = "dudy";
    dudy.print(name);

    // Laplace u
    name = "d2u";
    u.DD0().print(name);
}