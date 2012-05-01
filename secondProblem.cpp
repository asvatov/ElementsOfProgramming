#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

#define REQUIRE(condition, message) \
        if (!(condition)) cerr << message << endl; \
        else cout << "accept" << endl;

/**/

class matrix
{
private:
	vector < vector < int > > a;
public:
	matrix (int n) 
	{ 
		a.resize(n); 
		for (int i = 0; i < n; i++)
		{
			a[i].resize(n);
		}
	}
	matrix (const vector < vector < int > > values)
	{
        a = values;
	}
	matrix getIdentityMatrix()
	{
		matrix res(getMatrixSize());
        for (int i = 0; i < getMatrixSize(); i++) res.fillMatrix(i, i, 1);
        return res;
	}
    matrix getNullMatrix()
	{
        matrix res(getMatrixSize());
		return res; 
	}
	void fillMatrix (int i, int j, int value)
	{
		a[i][j] = value;
	}
	int getMatrixSize()
	{
		return a.size();
	}
	int getValue(int i, int j)
	{
		return a[i][j];
	}
	matrix operator = (matrix COPIED) {
		for (int i = 0; i < getMatrixSize(); i++)
			for (int j = 0; j < getMatrixSize(); j++)
				a[i][j] = COPIED.getValue(i, j);
		return *this;
	}
    bool operator == (matrix& b) {
        if (getMatrixSize() != b.getMatrixSize()) return false;
        for (int i = 0; i < getMatrixSize(); i++) {
            for (int j = 0; j < getMatrixSize(); j++)
                if (a[i][j] != b.getValue(i, j)) return false;
        }
        return true;
    }
	void print()
	{
		for (int i = 0; i < getMatrixSize(); i++)
		{
			for (int j = 0; j < getMatrixSize(); j++)
				cout << a[i][j] << " ";
			cout << endl;
		}
	}
};

template < class T >
class binop
{
public:
	T operator () (T a, T b) {
		matrix result(a.getMatrixSize());
	    for (int i = 0; i < a.getMatrixSize(); i++)
            for (int j = 0; j < a.getMatrixSize(); j++) {
                int buff = 0;
                int aj = 0; 
                int bi = 0;
                for (; aj < a.getMatrixSize(); aj++, bi++) {
                     buff += a.getValue(i, aj)*b.getValue(bi, j); 
                }
                result.fillMatrix(i, j, buff);
            }
		return result; 
	}; 
};

template < class T, template < class > class binop >
T poww(T a, size_t n, binop <T> f)
{
	T powA = a;
	int pos = 0;
	T res = a.getIdentityMatrix();
	while ((1 << pos) <= n)
	{
		if (n & (1 << pos))
		{
			res = f(res, powA);
		}
		++pos;
		powA = f(powA, powA);
	}
	return res;
}



int OneOrZero(int x, int i) {
    if (i < 0) return 0; 
    else {
        if ((x & (1 << i)) == 0) return 0;
        else return 1;
    }
}
void count(vector < vector < int > >& d, int n, int p, int profile, int len) {
    if (len == n) { d[p][profile] = 1; return; }
    if (!OneOrZero(p, len)) {
        count(d, n, p, profile + (1 << len), len + 1);
        if (len < n - 1) {
            if (!OneOrZero(p, len + 1)) count(d, n, p, profile, len + 2);
        }
    }
    else {
        count(d, n, p, profile, len + 1);
    }
}
void solve(vector < vector < int > >& d, int n) {
    for (int p = 0; p < (1 << n); p++) {
       count(d, n, p, 0, 0);
    }
}

matrix GenerateMatrix(int i) {
    srand(time(NULL)+i);
    matrix res(2+rand()%10);
    for (int t = 0; t < res.getMatrixSize(); t++)
        for (int j = 0; j < res.getMatrixSize(); j++) {
            srand(time(NULL)+i*t*j);
            res.fillMatrix(t, j, rand()%10);
        }
    return res;
}

matrix Grad(matrix a, int n, binop <matrix> f) {
    matrix res = a.getIdentityMatrix();
    for (int i = 0; i < n; i++) {
        res = f(res, a);
    }
    return res;
}

int solveDynamic(int n, int m, vector < vector < int > >& d, binop <matrix> f) {
    int grad = (1 << n);
    d.resize(grad);
    for (int i = 0; i < grad; i++) {
        d[i].resize(grad);
    }
    solve(d, n);
    matrix tr(d);
    matrix res = poww(tr, m, f);
    return res.getValue(0, 0);
}

int main()
{
	binop <matrix> f;
    vector < vector < int > > d;
    if (solveDynamic(2, 4, d, f) == 5) cout << "accept\n";
    else cout << "should be 5\n";
    if (solveDynamic(2, 2, d, f) == 2) cout << "accept\n";
    else cout << "should be 2\n";
    srand(time(NULL));
    for (int i = 0; i < 10+rand()%10; i++) {
        matrix g = GenerateMatrix(i);
        int in = rand()%5;
        matrix _poww = poww(g, in, f);
        matrix _Grad = Grad(g, in, f);
        REQUIRE(_poww == _Grad, "wrong");
    }
	return 0;
}
