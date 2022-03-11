#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#endif

#include <initializer_list>
#include <iostream>
#include <cassert> 

#define REAL float

class Matrix
{

public:
	int m;          // #of rows
	int n;          // #of cols
	REAL* data;

	Matrix(std::initializer_list<REAL> list,std::initializer_list<int> size);
	Matrix(std::initializer_list<int> size);
	~Matrix();
	Matrix Transpose();
	void setValueAt(int x, int y, REAL value);
	REAL getValueAt(int x, int y);
	static Matrix Identity(int n);
	static Matrix Ones(std::initializer_list<int> size);
	static Matrix Zeros(std::initializer_list<int> size);
	
	friend std::ostream & operator<<(std::ostream & os, const Matrix & mat)
	{   
		for (int row = 0; row < mat.m; row++)
		{
			for (int col = 0; col < mat.n; col++)
			{
				REAL elem=mat.data[col+row*mat.n];
				os<<elem<<" ";
			}
			os<<"\n";
		}
		os<<"\n";
		return os;
	}
	
	REAL operator()(int i,int j)
	{
		return data[(j-1)+(i-1)*n];
	}

	
	Matrix operator +(Matrix const &obj) 
	{ 
		assert(m==obj.m && n==obj.n);
        Matrix res({m,n}); 
		for (int i=0;i<m*n;i++)
		{
			res.data[i]=data[i]+obj.data[i];
		}
        return res; 
    }
	
	Matrix operator -(Matrix const &obj) 
	{ 
		assert(m==obj.m && n==obj.n);
        Matrix res({m,n}); 
		for (int i=0;i<m*n;i++)
		{
			res.data[i]=data[i]-obj.data[i];
		}
        return res; 
    }
	
	Matrix operator *(Matrix const &obj) 
	{ 
		assert(n==obj.m);
        Matrix res({m,obj.n}); 
				
		for (int row = 0; row < m; row++)
		{
			for (int col = 0; col < obj.n; col++)
			{
				REAL sum = 0;
				for (int k = 0; k < n; k++)
				{
					int indx1 = k + row * n;
					int indx2 = col + k * obj.n;
					sum += data[indx1] * obj.data[indx2];
				}
				res.data[col + row * obj.n] = sum;
				
			}
		}		
		
        return res; 
    }
	
	Matrix operator*(REAL x)
	{
		Matrix res({m,n});
		for (int i=0;i<m*n;i++)
		{
			res.data[i]=data[i]*x;
		}
        return res;
	}
};