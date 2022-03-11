#include "Matrix.h"


Matrix::Matrix(std::initializer_list<REAL> list,std::initializer_list<int> size)
{
	int dim=static_cast<int>(size.size());
	assert(dim==2);
	
	auto it=size.begin();
	this->m=*it;it++;
	this->n=*it;
	
	this->data=new REAL[this->m*this->n]{};
	int i=0;
	for (auto element : list)
	{
		this->data[i] = element;
		i++;
	}
}

Matrix::Matrix(std::initializer_list<int> size)
{
	int dim=static_cast<int>(size.size());
	assert(dim==2);
	
	auto it=size.begin();
	this->m=*it;it++;
	this->n=*it;
	
	this->data=new REAL[this->m*this->n]{};
}

Matrix::~Matrix()
{
	this->m=0;
	this->n=0;
	delete[] this->data;
}

Matrix Matrix::Transpose()
{
	Matrix res({n,m});
	for(int i=0;i<m;i++) //#of rows
	{
		for(int j=0;j<n;j++)//#of cols
		{
			res.data[i+j*m]=data[j+i*n];
		}
	}
	return res;
}

void Matrix::setValueAt(int x, int y, REAL value) {
	if (x >= this->m || y >= this->n) return;
	this->data[this->n * x + y] = value;
}

REAL Matrix::getValueAt(int x, int y) {
	if (x >= this->m || y >= this->n) return - 1;
	return this->data[this->n * x + y];
}

Matrix Matrix::Identity(int n)
{
	Matrix res({n,n});
	for(int i=0;i<n;i++) //#of rows
	{
		res.data[i+i*n]=1;
	}
	return res;
}

Matrix Matrix::Ones(std::initializer_list<int> size)
{
	int dim=static_cast<int>(size.size());
	assert(dim==2);
	
	auto it=size.begin();
	int m=*it;it++;
	int n=*it;
	
	Matrix res({m,n});
	for(int i=0;i<m;i++) //#of rows
	{
		for(int j=0;j<n;j++)//#of cols
		{
			res.data[i+j*m]=1.0;
		}
	}
	return res;
}
Matrix Matrix::Zeros(std::initializer_list<int> size)
{
	int dim=static_cast<int>(size.size());
	assert(dim==2);
	
	auto it=size.begin();
	int m=*it;it++;
	int n=*it;
	
	Matrix res({m,n});
	return res;
}
