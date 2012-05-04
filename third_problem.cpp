#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <cstdlib>
#define IsThisSymbolANumber(j) \
        (poly[j] >= '0' && poly[j] <= '9') 
#define TheLeadingCoeffOfResultMoreThanOfB \
        (*ita2).first >= (*itb2).first
#define ThereWasNoIterations \
        ita == ita2
#define CurrentCoeffOfResultMoreThanOfBInAbsolute \
        abs((*ita).second) >= abs((*itb).second)
#define ThereAreGCD \
        abs(_gcd((*ita).second, (*itb).second)) != 1 && abs((*itb).second) != 1
using namespace std;
/*
template <class T>
T _gcd(T a, T b)
{
    if (a == 0) return b;
    else if (b == 0) return a;
    if (a == 1 || b == 1) return 1;
    if (a >= b) return _gcd(a%b, b);
    else return _gcd(b, a);
}
*/
/*
class fraction {
private:
    int value1;
    int value2;
public:
    fraction (int v1, int v2) { value1 = v1; value2 = v2; }
    bool operator == (const fraction& b) {
        int v1 = value1/_gcd<int>(value1, value2);
        int v2 = value2/_gcd<int>(value1, value2);
        int bv1 = b.value1/_gcd<int>(b.value1, b.value2);
        int bv2 = b.value2/_gcd<int>(b.value1, b.value2);
        if (v1 == bv1 && v2 == bv2) return true;
        else return false;
    }
    bool operator >= (const fraction& b)
    {
        int v1 = value1/_gcd<int>(value1, value2);
        int v2 = value2/_gcd<int>(value1, value2);
        int bv1 = b.value1/_gcd<int>(b.value1, b.value2);
        int bv2 = b.value2/_gcd<int>(b.value1, b.value2);
        if (v1*bv2 >= bv1*v2) return true;
        else return false;
    }
 /*   const fraction operator % (const fraction a) const 
    {
        double gavno;
        gavno = 
        Double result(gavno);
        return result;
    }
};*/

class polynom {
private:
    int _gcd(int a, int b) const
    {
        if (a == 0) return b;
        else if (b == 0) return a;
        if (a == 1 || b == 1) return 1;
        if (a >= b) return _gcd(a%b, b);
        else return _gcd(b, a);
    }
    map < int, int > grad;
    void IfPlusOrMinus(int i, const string& poly) {
        int j = i - 1;
        int coeff = 0;
        int ten = 1;
        while (j >= 0 && IsThisSymbolANumber(j)) {
            coeff = coeff + (poly[j] - '0')*ten;
            ten *= 10;
            j--;
        }
        if (j>=0 && poly[j] == '-') coeff *= -1;
        grad[0] += coeff;
    }
    void IfX(int i, const string& poly) {
        int number = 1;
        int coeff = 1;
        if (i > 0) {
            if (!IsThisSymbolANumber(i-1)) {
                if (poly[i - 1] == '-') coeff = -1;   
            }
            else {
                int j = i - 1;
                coeff = 0;
                int ten = 1;
                while (j >= 0 && IsThisSymbolANumber(j)) {
                    coeff = coeff + (poly[j] - '0')*ten;
                    ten *= 10;
                    j--;
                }
                if (j>=0 && poly[j] == '-') coeff *= -1; 
            }
        }
        if (i+1 <= poly.length()-1) {
            if (poly[i+1] == '^') {
                int j = i + 2;
                number = 0;
                while (j < poly.length() && IsThisSymbolANumber(j)) {
                    number = number*10 + (poly[j] - '0');
                    j++;
                }
            }
        }
        grad[number] += coeff;
    }
    void parsePoly(const string& poly) {
        int i = 0;
        bool flag = true;
        while (i < poly.length()) {
            if (poly[i] == '+' || poly[i] == '-') {
                if (flag) IfPlusOrMinus(i, poly);
                flag = true;
            }
            if (poly[i] == 'x') {
                flag = false;
                IfX(i, poly);
            }
            i++;
        }
        if (flag) {
            int j = i - 1;
            int coeff = 0;        
            int ten = 1;
            while (j >= 0 && IsThisSymbolANumber(j)) {
                coeff = coeff + (poly[j] - '0')*ten;
                ten *= 10;
                j--;
            }
            if (j>=0 && poly[j] == '-') coeff *= -1;
            grad[0] += coeff;
        }
    }
public:
    polynom() {}
    polynom(int wannaBePolynom) {
        grad[0] = wannaBePolynom;
    }
    polynom(string poly) { parsePoly(poly); }
    void inputPoly() {
        string ab;
        char buff;
        while (1) {
            buff = getchar();
            if (buff == '\n') break;
            ab = ab + buff;
        }
        parsePoly(ab);
    }
    int get(int key){// const {
        return grad[key];
    }
    map < int, int >::const_iterator getbit() const {
        return grad.begin();
    }
    map < int, int >::const_iterator geteit() const {
        return grad.end();
    }
    bool empty() {
        return grad.empty();
    }
    void change(int key, int value) {
        grad[key] = value;
    }
    int getGradOfLeadingCoeff() const {
        map < int, int >::const_iterator ita = grad.end();
        ita--;
        while (!ita->second) {ita--;}
        return ita->first;
    }
    int getLeadingCoeff() {
        return grad[getGradOfLeadingCoeff()];
    }
    bool IsMyLeadingCoeffMoreThan(const polynom& b) const {
        map < int, int >::const_iterator ita = grad.end();
        map < int, int >::const_iterator itb = b.geteit();
        ita--;
        itb--;
        while (!ita->second) {ita--;}
        while (!itb->second) {itb--;}
        if (ita->first > itb->first) return true;
        else return false;
    }
    bool IsMyLeadingCoeffEqWith(const polynom& b) const {
        map < int, int >::const_iterator ita = grad.end();
        map < int, int >::const_iterator itb = b.geteit();
        ita--;
        itb--;
        while (!ita->second) {ita--;}
        while (!itb->second) {itb--;}
        if (ita->first == itb->first) return true;
        else return false;
    }
    void erase(int key) {
        grad.erase(grad.find(key));
    }
    void eraseAllZeros() {
        map < int, int >::iterator ita = grad.begin();
        for (; ita != grad.end(); ita++) {
            if (!ita->second) { grad.erase(ita); ita--; }
        }
    }
    bool zero() {
        map < int, int >::iterator ita = grad.begin();
        for (; ita != grad.end(); ita++) {
            if (ita->second) return false;
        }
        return true;
    }
    bool AmIJustANumber() {
        map < int, int >::iterator it;
        for (it = grad.begin(); it != grad.end(); it++) {
            if (it->first && it->second) return false;        
        }
        return true;
    }
    void printPoly() {
        map < int, int >::iterator it = grad.end();
        it--;
        for (; it != grad.begin(); it--) {
            if (!((*it).second)) continue;
            if ((*it).first > 1) {
                if ((*it).second != 1) cout << (*it).second;
                cout << "x^" << (*it).first;
            }
            if ((*it).first == 1 || (*it).first == -1) {
                if ((*it).second != 1) cout << (*it).second;
                cout << "x";
            }
            if (!((*it).first)) cout << (*it).second;
            if ((*it).second > 0) cout << "+";
        }
        if ((*it).second) {
            if ((*it).first > 1) {
                if ((*it).second != 1) cout << (*it).second;
                cout << "x^" << (*it).first;
            }
            if ((*it).first == 1) {
                if ((*it).second != 1) cout << (*it).second;
                cout << "x";
            }
            if (!((*it).first))
                cout << (*it).second;
        }
        cout << endl;
    }
     bool operator == (/*const */polynom& b) {
        map < int, int >::const_iterator it;
        bool flag = true;
        for (it = grad.begin(); it != grad.end(); it++)
            if ((*it).second != b.get((*it).first)) flag = false;
        for (it = b.getbit(); it != b.geteit(); it++)
            if (b.get((*it).first) != grad[(*it).first]) flag = false;
        return flag;
    }
    bool operator >= (const polynom& b) const {
        map < int, int >::const_iterator ita = grad.end();
        map < int, int >::const_iterator itb = b.geteit();
        ita--;
        itb--;
        while (!((*itb).second)) itb--;
        while (!((*ita).second)) ita--;
        if ((*ita).first > (*itb).first) return true;
        else if ((*ita).first == (*itb).first) {
            if (abs((*ita).second) >= abs((*itb).second)) return true;
            else return false;
        }
        else return false; 
    }
    polynom& operator = (polynom b) {
		for (map < int, int>::const_iterator it = b.getbit(); it != b.geteit(); it++) 
            grad[(*it).first] = (*it).second;
		return *this;
	}
    polynom operator % (polynom& b) {
        polynom result = *this;
        polynom reservresult = *this;
        map < int, int >::const_iterator ita;
        map < int, int >::const_iterator itb;
        if (IsMyLeadingCoeffMoreThan(b)) {
            if (b.AmIJustANumber()) {
                int resGCD = b.get(0);
                eraseAllZeros();
                for (ita = grad.begin(); ita != grad.end(); ita++) {
                    if (!ita->second) { cerr << "WHat Is That?\n"; exit(1); }
                    resGCD = _gcd(abs(resGCD), abs(ita->second));
                } 
                polynom st(resGCD);
                return st;
            }
            else { 
                polynom copya = *this;
                int resGCDb = b.get(0);
                int resGCDa = get(0);
                eraseAllZeros();
                b.eraseAllZeros();
                for (itb = b.getbit(); itb != b.geteit(); itb++) {
                    if (!itb->second) continue;
                    resGCDb = _gcd(abs(resGCDb), abs(itb->second));
                }
                for (ita = grad.begin(); ita != grad.end(); ita++) {
                    if (!ita->second) continue;
                    resGCDa = _gcd(abs(resGCDa), abs(ita->second));
                }
                int inMind;
                inMind = _gcd(resGCDa, resGCDb);
                for (itb = b.getbit(); itb != b.geteit(); itb++) {
                    b.change(itb->first, b.get(itb->first) / resGCDb);
                }
                for (ita = grad.begin(); ita != grad.end(); ita++) {
                    copya.change(ita->first, copya.get(ita->first) / resGCDa);
                }
                    while (b.getGradOfLeadingCoeff() <= copya.getGradOfLeadingCoeff()) {
                        copya.eraseAllZeros();
                        b.eraseAllZeros();
                        if (_gcd(abs(copya.getLeadingCoeff()), abs(b.getLeadingCoeff())) != abs(b.getLeadingCoeff())) return polynom(1);
                        int multg = copya.getGradOfLeadingCoeff() - b.getGradOfLeadingCoeff();
                        int multc = copya.getLeadingCoeff()/b.getLeadingCoeff();
                        itb = b.geteit(); itb--;
                        for (; itb != b.getbit(); itb--) {
                            int gr = itb->first + multg;
                            int vl = itb->second * multc;
                            copya.change(gr, copya.get(gr) - vl);
                        }
                        int gr = itb->first + multg;
                        int vl = itb->second * multc;
                        copya.change(gr, copya.get(gr) - vl);
                        if (copya.zero()) {
				            for (itb = b.getbit(); itb != b.geteit(); itb++) b.change(itb->first, b.get(itb->first) * inMind);
                            return b;
                        }                  
                    }
                    return copya;
            }
        }
        else if (IsMyLeadingCoeffEqWith(b)) {
            if (!getGradOfLeadingCoeff()) {
                int resGCD = abs(get(0)); 
                resGCD = _gcd(resGCD, abs(b.get(0)));
                polynom res(resGCD);
                return res;
            }
            else {
                polynom copya = *this;
                int resGCDb = b.get(0);
                int resGCDa = get(0);
                eraseAllZeros();
                b.eraseAllZeros();
                for (itb = b.getbit(); itb != b.geteit(); itb++) {
                    if (!itb->second) continue;
                    resGCDb = _gcd(abs(resGCDb), abs(itb->second));
                }
                for (ita = grad.begin(); ita != grad.end(); ita++) {
                    if (!ita->second) continue;
                    resGCDa = _gcd(abs(resGCDa), abs(ita->second));
                }
                int inMind;
                inMind = _gcd(resGCDa, resGCDb);
                for (itb = b.getbit(); itb != b.geteit(); itb++) {
                    b.change(itb->first, b.get(itb->first) / resGCDb);
                }
                for (ita = grad.begin(); ita != grad.end(); ita++) {
                    copya.change(ita->first, copya.get(ita->first) / resGCDa);
                }
                    while (b.getGradOfLeadingCoeff() <= copya.getGradOfLeadingCoeff()) {
                        copya.eraseAllZeros();
                        b.eraseAllZeros();
                        if (_gcd(abs(copya.getLeadingCoeff()), abs(b.getLeadingCoeff())) != abs(b.getLeadingCoeff())) return polynom(1);
                        int multg = copya.getGradOfLeadingCoeff() - b.getGradOfLeadingCoeff();
                        int multc = copya.getLeadingCoeff()/b.getLeadingCoeff();
                        itb = b.geteit(); itb--;
                        for (; itb != b.getbit(); itb--) {
                            int gr = itb->first + multg;
                            int vl = itb->second * multc;
                            copya.change(gr, copya.get(gr) - vl);
                        }
                        int gr = itb->first + multg;
                        int vl = itb->second * multc;
                        copya.change(gr, copya.get(gr) - vl);
                        if (copya.zero()) {
                            for (itb = b.getbit(); itb != b.geteit(); itb++) {
                                b.change(itb->first, itb->second*inMind);
                            }
                            return b;
                        }                  
                    } 
                    return copya;
            }
        }
        return polynom("1");
    }
};

template <class T>
T gcd(T a, T b) {
    polynom zero("0");
    polynom one("1");
    if (a == b) return a;
    if (a == zero || a.empty()) return b;
    else if (b == zero || b.empty()) return a;
    if (a == one || b == one) return one;
    if (a >= b) { polynom res = a%b; return gcd(res, b); }
    else return gcd(b, a);
}

int main() {
    polynom a, b;
    a.inputPoly();
    b.inputPoly();
    gcd<polynom>(a, b).printPoly();
  //  map < polynom, polynom > tests(10);
    //vector
    return 0;
}
