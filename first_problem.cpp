#include <iostream>
#include "tester_for_first.h"

class Vector : public vector < int >
{
public:
    const Vector operator * (const Vector& v) const {
        Vector::const_iterator it;
        Vector::const_iterator it2;
        Vector result;
        for(it = v.begin(), it2 = this->begin(); it != v.end(); it++, it2++) {
            result.push_back((*it)*(*it2));
        }
        return result;
    }

    const Vector operator + (const Vector& v) const {
        Vector::const_iterator it;
        Vector::const_iterator it2;
        Vector result;
        for(it = v.begin(), it2 = this->begin(); it != v.end(); it++, it2++) {
            result.push_back((*it)+(*it2));
        }
        return result;
    }
    
    const Vector operator - (const Vector& v) const {
        Vector::const_iterator it;
        Vector::const_iterator it2;
        Vector result;
        for(it = v.begin(), it2 = this->begin(); it != v.end(); it++, it2++) {
            result.push_back((*it)-(*it2));
        }
        return result;
    }

    const Vector operator + (const int a) const {
        Vector::const_iterator it;
        Vector result;
        for(it = this->begin(); it != this->end(); it++) {
            result.push_back((*it) + a);
        }
        return result;
    }

    const Vector operator * (const int a) const {
        Vector::const_iterator it;
        Vector result;
        for(it = this->begin(); it != this->end(); it++) {
            result.push_back((*it) * a);
        }
        return result;
    }

    const Vector operator % (const int a) const {
        Vector::const_iterator it;
        Vector result;
        for(it = this->begin(); it != this->end(); it++) {
            result.push_back((*it) % a);
        }
        return result;
    }

    const Vector operator - (const int a) const {
        Vector::const_iterator it;
        Vector result;
        for(it = this->begin(); it != this->end(); it++) {
            result.push_back((*it) - a);
        }
        return result;
    }

};

ostream& operator << (ostream& out , const vector < int > &v) {
        vector < int >::const_iterator it;
        for (it = v.begin(); it != v.end(); it++) {
                out << (*it) << " ";
        }
        out << endl;
        return out;
}

template <class T1>
class Transformation : public GlobalFunctor <T1>
{    
public:
    Transformation(const int n_): n(n_) { }
    T1 operator() (const T1 element) const {
        return (element*element*3+element+3)%n;
    }
    int getN() const
    {
        return n;       
    }
private:
    int n;
};

template < class T1,  class D>
int solve(const D &t, T1 x0)
{
	T1 temp;
    int cnt;
	temp = x0;
	for (int i = 0; i < t.getN(); i++) 
    {
        temp = t(temp);
    }
	T1 buff = temp;
	int cycle = 1;
	while (t(buff)!=temp) 
    { 
        cycle++; 
        buff = t(buff); 
    }
	buff = x0;
	for (int i = 0; i < cycle; i++) 
    { 
        buff = t(buff);
    }
	temp = x0;
	cnt = 0;
	while (temp != buff)
	{
		temp = t(temp);
		buff = t(buff);
		cnt++;
	}
	return cnt;
}

int main() {
    Vector a;
    a.push_back(45);
    a.push_back(32);
    a.push_back(12);
    Vector b;
    a.push_back(9);
    a.push_back(10);
    a.push_back(2);
    a.push_back(13);
    GraphFunctor < Vector > f(5, 3, a);
    REQUIRE(solve(f, a) == 3, "solution does not accept, should be " << 3);
    forn (i, GenerateAmountOfTests()) {
        int pl = GeneratePreCycleLength(i);
        int cl = GenerateCycleLength(i);
        Vector a;
        a.push_back(90);
        a.push_back(43);
        GraphFunctor < Vector > f(cl, pl, a);
        REQUIRE(solve(f, a) == pl, "solution does not accept, should be " << pl);
    }
    Vector d;
    d.push_back(3);
    d.push_back(2);
    d.push_back(7);
    d.push_back(54);
    Transformation < Vector > tr(6);
    REQUIRE(solve(tr, d) == 1, "solution does not accept, should be " << 1);
    return 0;
}
