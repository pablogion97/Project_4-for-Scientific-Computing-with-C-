#pragma once
#ifndef GFKT
#define GFKT
#include "Domain.h"
#include "Matrix.h"

class GFkt {

private:
	Matrix u;
	std::shared_ptr<Domain> grid;

public:
	GFkt(std::shared_ptr<Domain> grid_) : u(grid_->xsize() + 1, grid_->ysize() + 1), grid(grid_) {}
	GFkt(const GFkt& U) : u(U.u), grid(U.grid) {}

	GFkt& operator=(const GFkt & U);
	GFkt operator+(const GFkt& U) const;
	GFkt operator*(const GFkt& U) const;
	GFkt operator*(const double& c) const;
	friend GFkt operator*(const double& c, const GFkt& U);

	GFkt D0x() const;
	GFkt D0y() const;
	void D0xy(GFkt& dx, GFkt& dy) const;
	GFkt DD0() const;

	void setFunction(double (*func) (Point));
	void print(std::string name);
	size_t xsize() { return grid->xsize(); }
	size_t ysize() { return grid->ysize(); }
};

#endif // !GFKT