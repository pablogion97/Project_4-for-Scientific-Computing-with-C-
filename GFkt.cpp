#include "GFkt.h"

GFkt& GFkt::operator=(const GFkt& U)
{
	if (this != &U) {
		if (this->grid != U.grid) {
			std::cerr << "Error: Dimension missmatch at equal sign.";
			exit(EXIT_FAILURE);
		}

		u = U.u;
		grid = U.grid;
	}

	return *this;
}

GFkt GFkt::operator+(const GFkt& U) const
{
	if (grid != U.grid) {
		std::cerr << "Error: Dimension missmatch at addition.";
		exit(EXIT_FAILURE);
	}

	GFkt tmp(*this);
	tmp.u += U.u;
	return tmp;
}

GFkt GFkt::operator*(const GFkt& U) const
{
	if (grid != U.grid) {
		std::cerr << "Error: Dimension missmatch at multiplication.";
		exit(EXIT_FAILURE);
	}

	GFkt tmp(*this);
	tmp.u *= U.u;
	return tmp;
}

GFkt GFkt::operator*(const double& c) const
{
	if (grid == nullptr) {
		std::cerr << "Error: Grid is not initialized.";
		exit(EXIT_FAILURE);
	}

	GFkt tmp(*this);
	tmp.u *= c;
	return tmp;
}

GFkt operator*(const double& c, const GFkt& U)
{
	return U*c;
}

GFkt GFkt::D0x() const {

	GFkt tmp(grid);

	if (grid->grid_valid()) {

		double nx = (double)grid->xsize();
		double ny = (double)grid->ysize();
		double dUdXi, dUdEta, dPhiXdXi, dPhiXdEta, dPhiYdXi, dPhiYdEta;

		for (size_t i = 0; i <= nx; i++) {
			for (size_t j = 0; j <= ny; j++) {

				if (i > 0 && i < nx) {
					dPhiXdXi = 0.5 * nx * ((*grid)(i + 1, j).x - (*grid)(i - 1, j).x);
					dPhiYdXi = 0.5 * nx * ((*grid)(i + 1, j).y - (*grid)(i - 1, j).y);
					dUdXi = 0.5 * nx * (u(i + 1, j) - u(i - 1, j));
				}
				else if (i == 0) {
					dPhiXdXi = 0.5 * nx * (-(*grid)(2, j).x + 4 * (*grid)(1, j).x - 3 * (*grid)(0, j).x);
					dPhiYdXi = 0.5 * nx * (-(*grid)(2, j).y + 4 * (*grid)(1, j).y - 3 * (*grid)(0, j).y);
					dUdXi = 0.5 * nx * (-u(2, j) + 4 * u(1, j) - 3 * u(0, j));
				}
				else {
					dPhiXdXi = 0.5 * nx * (3 * (*grid)(i, j).x - 4 * (*grid)(i - 1, j).x + (*grid)(i - 2, j).x);
					dPhiYdXi = 0.5 * nx * (3 * (*grid)(i, j).y - 4 * (*grid)(i - 1, j).y + (*grid)(i - 2, j).y);
					dUdXi = 0.5 * nx * (3 * u(i, j) - 4 * u(i - 1, j) + u(i - 2, j));
				}

				if (j > 0 && j < ny) {
					dPhiXdEta = 0.5 * ny * ((*grid)(i, j + 1).x - (*grid)(i, j - 1).x);
					dPhiYdEta = 0.5 * ny * ((*grid)(i, j + 1).y - (*grid)(i, j - 1).y);
					dUdEta = 0.5 * ny * (u(i, j + 1) - u(i, j - 1));
				}
				else if (j == 0) {
					dPhiXdEta = 0.5 * ny * (-(*grid)(i, 2).x + 4 * (*grid)(i, 1).x - 3 * (*grid)(i, 0).x);
					dPhiYdEta = 0.5 * ny * (-(*grid)(i, 2).y + 4 * (*grid)(i, 1).y - 3 * (*grid)(i, 0).y);
					dUdEta = 0.5 * ny * (-u(i, 2) + 4 * u(i, 1) - 3 * u(i, 0));
				}
				else {
					dPhiXdEta = 0.5 * ny * (3 * (*grid)(i, j).x - 4 * (*grid)(i, j - 1).x + (*grid)(i, j - 2).x);
					dPhiYdEta = 0.5 * ny * (3 * (*grid)(i, j).y - 4 * (*grid)(i, j - 1).y + (*grid)(i, j - 2).y);
					dUdEta = 0.5 * ny * (3 * u(i, j) - 4 * u(i, j - 1) + u(i, j - 2));
				}

				tmp.u(i, j) = (dUdXi * dPhiYdEta - dUdEta * dPhiYdXi)
					/ (dPhiXdXi * dPhiYdEta - dPhiXdEta * dPhiYdXi);
			}
		}
		
	}
	else {
		std::cerr << "Error: Grid is not available.";
		exit(EXIT_FAILURE);
	}
		return tmp;
}


GFkt GFkt::D0y() const {

	GFkt tmp(grid);

	if (grid->grid_valid()) {

		double nx = (double)grid->xsize();
		double ny = (double)grid->ysize();
		double dUdXi, dUdEta, dPhiXdXi, dPhiXdEta, dPhiYdXi, dPhiYdEta;

		for (size_t i = 0; i <= nx; i++) {
			for (size_t j = 0; j <= ny; j++) {

				if (i > 0 && i < nx) {
					dPhiXdXi = 0.5 * nx * ( (*grid)(i + 1, j).x - (*grid)(i - 1, j).x);
					dPhiYdXi = 0.5 * nx * ( (*grid)(i + 1, j).y - (*grid)(i - 1, j).y);
					dUdXi = 0.5 * nx * ( u(i + 1, j) - u(i - 1, j));
				}
				else if (i == 0) {
					dPhiXdXi = 0.5 * nx * ( -(*grid)(2, j).x + 4 * (*grid)(1, j).x - 3 * (*grid)(0, j).x);
					dPhiYdXi = 0.5 * nx * ( -(*grid)(2, j).y + 4 * (*grid)(1, j).y - 3 * (*grid)(0, j).y);
					dUdXi = 0.5 * nx * ( -u(2, j) + 4 * u(1, j) - 3 * u(0, j));
				}
				else {
					dPhiXdXi = 0.5 * nx * (3 * (*grid)(nx, j).x - 4 * (*grid)(nx - 1, j).x + (*grid)(nx - 2, j).x);
					dPhiYdXi = 0.5 * nx * (3 * (*grid)(nx, j).y - 4 * (*grid)(nx - 1, j).y + (*grid)(nx - 2, j).y);
					dUdXi = 0.5 * nx * (3 * u(nx, j) - 4 * u(nx - 1, j) + u(nx - 2, j));
				}

				if (j > 0 && j < ny) {
					dPhiXdEta = 0.5 * ny * ((*grid)(i, j + 1).x - (*grid)(i, j - 1).x);
					dPhiYdEta = 0.5 * ny * ((*grid)(i, j + 1).y - (*grid)(i, j - 1).y);
					dUdEta = 0.5 * ny * (u(i, j + 1) - u(i, j - 1));
				}
				else if (j == 0) {
					dPhiXdEta = 0.5 * ny * (-(*grid)(i, 2).x + 4 * (*grid)(i, 1).x - 3 * (*grid)(i, 0).x);
					dPhiYdEta = 0.5 * ny * (-(*grid)(i, 2).y + 4 * (*grid)(i, 1).y - 3 * (*grid)(i, 0).y);
					dUdEta = 0.5 * ny * (-u(i, 2) + 4 * u(i, 1) - 3 * u(i, 0));
				}
				else {
					dPhiXdEta = 0.5 * ny * (3 * (*grid)(i, ny).x - 4 * (*grid)(i, ny - 1).x + (*grid)(i, ny - 2).x);
					dPhiYdEta = 0.5 * ny * (3 * (*grid)(i, ny).y - 4 * (*grid)(i, ny - 1).y + (*grid)(i, ny - 2).y);
					dUdEta = 0.5 * ny * (3 * u(i, ny) - 4 * u(i, ny - 1) + u(i, ny - 2));
				}

				tmp.u(i, j) = (-dUdXi * dPhiXdEta + dUdEta * dPhiXdXi)
					/ (dPhiXdXi * dPhiYdEta - dPhiXdEta * dPhiYdXi);
			}
		}

	}
	else {
		std::cerr << "Error: Grid is not available.";
		exit(EXIT_FAILURE);
	}
	return tmp;
}

void GFkt::D0xy(GFkt& dx, GFkt& dy) const
{
	if (grid->grid_valid() && grid == dx.grid && grid == dy.grid) {

		double nx = (double)grid->xsize();
		double ny = (double)grid->ysize();
		double dUdXi, dUdEta, dPhiXdXi, dPhiXdEta, dPhiYdXi, dPhiYdEta;

		for (size_t i = 0; i <= nx; i++) {
			for (size_t j = 0; j <= ny; j++) {

				if (i > 0 && i < nx) {
					dPhiXdXi = 0.5 * nx * ((*grid)(i + 1, j).x - (*grid)(i - 1, j).x);
					dPhiYdXi = 0.5 * nx * ((*grid)(i + 1, j).y - (*grid)(i - 1, j).y);
					dUdXi = 0.5 * nx * (u(i + 1, j) - u(i - 1, j));
				}
				else if (i == 0) {
					dPhiXdXi = 0.5 * nx * (-(*grid)(2, j).x + 4 * (*grid)(1, j).x - 3 * (*grid)(0, j).x);
					dPhiYdXi = 0.5 * nx * (-(*grid)(2, j).y + 4 * (*grid)(1, j).y - 3 * (*grid)(0, j).y);
					dUdXi = 0.5 * nx * (-u(2, j) + 4 * u(1, j) - 3 * u(0, j));
				}
				else {
					dPhiXdXi = 0.5 * nx * (3 * (*grid)(i, j).x - 4 * (*grid)(i - 1, j).x + (*grid)(i - 2, j).x);
					dPhiYdXi = 0.5 * nx * (3 * (*grid)(i, j).y - 4 * (*grid)(i - 1, j).y + (*grid)(i - 2, j).y);
					dUdXi = 0.5 * nx * (3 * u(i, j) - 4 * u(i - 1, j) + u(i - 2, j));
				}

				if (j > 0 && j < ny) {
					dPhiXdEta = 0.5 * ny * ((*grid)(i, j + 1).x - (*grid)(i, j - 1).x);
					dPhiYdEta = 0.5 * ny * ((*grid)(i, j + 1).y - (*grid)(i, j - 1).y);
					dUdEta = 0.5 * ny * (u(i, j + 1) - u(i, j - 1));
				}
				else if (j == 0) {
					dPhiXdEta = 0.5 * ny * (-(*grid)(i, 2).x + 4 * (*grid)(i, 1).x - 3 * (*grid)(i, 0).x);
					dPhiYdEta = 0.5 * ny * (-(*grid)(i, 2).y + 4 * (*grid)(i, 1).y - 3 * (*grid)(i, 0).y);
					dUdEta = 0.5 * ny * (-u(i, 2) + 4 * u(i, 1) - 3 * u(i, 0));
				}
				else {
					dPhiXdEta = 0.5 * ny * (3 * (*grid)(i, j).x - 4 * (*grid)(i, j - 1).x + (*grid)(i, j - 2).x);
					dPhiYdEta = 0.5 * ny * (3 * (*grid)(i, j).y - 4 * (*grid)(i, j - 1).y + (*grid)(i, j - 2).y);
					dUdEta = 0.5 * ny * (3 * u(i, j) - 4 * u(i, j - 1) + u(i, j - 2));
				}

				dx.u(i, j) = (dUdXi * dPhiYdEta - dUdEta * dPhiYdXi)
					/ (dPhiXdXi * dPhiYdEta - dPhiXdEta * dPhiYdXi);

				dy.u(i, j) = (-dUdXi * dPhiXdEta + dUdEta * dPhiXdXi)
					/ (dPhiXdXi * dPhiYdEta - dPhiXdEta * dPhiYdXi);
			}
		}
	}
	else {
		std::cerr << "Error: Grid is not available.";
		exit(EXIT_FAILURE);
	}
}

GFkt GFkt::DD0() const
{
	GFkt dx(grid);
	GFkt dy(grid);
	D0xy(dx, dy);
	return GFkt(dx.D0x() + dy.D0y());
}

void GFkt::setFunction(double (*func)(Point))
{
	for (int j = 0; j <= grid->ysize(); j++)
		for (int i = 0; i <= grid->xsize(); i++)
			u(i, j) = func((*grid)(i, j));
}

void GFkt::print(std::string name)
{
	// Write grid to file as a csv table
	std::ofstream gridFile;
	gridFile.precision(15);
	gridFile.open(name + ".csv");

	int nx = grid->xsize();
	int ny = grid->ysize();

	for (int j = 0; j <= ny; j++)
		for (int i = 0; i <= nx; i++)
			gridFile << u(i,j) << std::endl;

	gridFile.close();
}
