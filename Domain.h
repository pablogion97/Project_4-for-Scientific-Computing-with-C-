#pragma once
#ifndef DOMAIN_H
#define DOMAIN_H
#include "Curve.h"
#include "HLine.h"
#include "VLine.h"
#include <fstream>

struct Point {
	double x, y;
};

class Domain {
private:
	size_t nx, ny;
	double* x_, * y_;

	std::shared_ptr<Curvebase> sides[4];
	bool check_consistency() const;

public:
	Domain(std::shared_ptr<Curvebase> bottom,
		   std::shared_ptr<Curvebase> right,
		   std::shared_ptr<Curvebase> top,
		   std::shared_ptr<Curvebase> left);

	Domain(const Domain& other);
	~Domain();

	Domain& operator=(const Domain& other);

	void generate_grid(const size_t& nX, const size_t& nY);
	void print() const;
	bool grid_valid() { return nx != 0; }
	size_t xsize() { return nx; }
	size_t ysize() { return ny; }
	Point operator()(int i, int j) const;
};

#endif // !DOMAIN_H