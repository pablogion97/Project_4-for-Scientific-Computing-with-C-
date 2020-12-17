#pragma once

#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <iomanip>

class Matrix {

private:
	size_t nx, ny;  // Use 
	double *A;

public:

	// Constructor
	Matrix(size_t m_ = 0, size_t n_ = 0) : nx(m_), ny(n_), A(nullptr) {
		if (nx*ny > 0) {
			A = new double[nx*ny];
			std::fill(A, A + nx*ny, 0.0);
		}
	}
	
	// Copy constructor
	Matrix(const Matrix& B) : nx(B.nx), ny(B.ny), A(nullptr) {
		if (ny * nx > 0) {
			A = new double[ny * nx];
			std::copy(B.A, B.A + nx * ny, A);
		}
	}

	// Move constructor
	Matrix(Matrix&& B) noexcept : nx(B.nx), ny(B.ny), A(B.A) {
		B.nx = 0;
		B.ny = 0;
		B.A = nullptr;
	}

	// Operators
	// =
	Matrix& operator=(const Matrix& B) {
		if (this != &B) {
			if (nx * ny != B.nx * B.ny) {

				if (A != nullptr)
					delete[] A;

				if (B.A != nullptr)
					A = new double[B.nx * B.ny];
			}

			nx = B.nx;
			ny = B.ny;
			std::copy(B.A, B.A + nx * ny, A);
		}

		return *this;
	}
	

	Matrix& operator=(Matrix&& B) noexcept {

		if (this != &B) {
			nx = B.nx;
			ny = B.ny;

			if (A != nullptr)
				delete[] A;

			A = B.A;
			B.nx = B.ny = 0;
			B.A = nullptr;
		}
		
		return *this;
	}


	// Selection operator
	double& operator()(size_t i, size_t j) {

		if (i >= 0 && i < nx && j >= 0 && j < ny) {
			return A[j * nx + i];
		}
		else {
			std::cerr << "Error: Invalid matrix index.";
			exit(EXIT_FAILURE);
		}
	}

	double operator()(size_t i, size_t j) const {

		if (i >= 0 && i < nx && j >= 0 && j < ny) {
			return A[j * nx + i];
		}
		else {
			std::cerr << "Error: Invalid matrix index.";
			exit(EXIT_FAILURE);
		}
		
	}

	// Matrix addition
	Matrix& operator+=(const Matrix& B) {
		for (int i = 0; i < ny * nx; i++)
			A[i] += B.A[i];

		return *this;
	}

	// Matrix addition
	Matrix operator+(const Matrix& B) const
	{
		Matrix sum(B);
		sum += *this;
		return sum;
	}

	// Implementation for A = c + B;
	friend Matrix operator+(const double c, const Matrix& B);

	// Matrix multiplication
	Matrix& operator*=(const Matrix& B) {
		for (int i = 0; i < ny * nx; i++)
			A[i] *= B.A[i];

		return *this;
	}

	// Matrix multiplication
	Matrix operator*(const Matrix& B) const
	{
		Matrix sum(B);
		sum *= *this;
		return sum;
	}

	// Implementation for A = c * B;
	friend Matrix operator*(const double c, const Matrix& B);

	// Matrix scalar multplication
	Matrix& operator*=(const double c)
	{
		for (int i = 0; i < ny * nx; i++)
			A[i] *= c;

		return *this;
	}

	// Matrix scalar multiplication
	Matrix operator*(const double c) const
	{
		Matrix sum(*this);
		sum *= c;
		return sum;
	}

	friend std::ostream& operator<<(std::ostream& os, const Matrix& B);
};

// Defined << operator for a more simple matrix printout and debugging
inline std::ostream& operator<<(std::ostream& os, const Matrix& B) {
	os << std::setprecision(4);
	os << std::showpoint;

	for (int i = 0; i < B.nx; i++)
	{
		os << "|";

		for (int j = 0; j < B.ny; j++)
			os << B.A[i * B.nx + j] << "\t";

		os << "|" << "\ny";
	}
	os << std::endl;

	return os;
}


// Added c */+ A operation with inlined friend functions
inline Matrix operator*(const double c, const Matrix& B) {
	return B * c;
}

inline Matrix operator+(const double c, const Matrix& B) {
	return B + c;
}

#endif