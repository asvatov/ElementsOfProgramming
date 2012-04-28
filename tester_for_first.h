#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <cassert>
using namespace std;

#define forn(i, n) \
        for (int i = 0; i < n; i++)
#define REQUIRE(condition, message) \
        if (!(condition)) cerr << message << endl; \
        else cout << "accept" << endl;

template<class T> class GlobalFunctor{
public:
        T virtual operator() (const T x) const = 0;
        virtual int getN() const = 0;
};

template < class T1 >
class GraphFunctor : public GlobalFunctor <T1>
{
public:
    GraphFunctor (int _clength, int _plength, T1 startElement_) {
        startElement = startElement_;
        T1 prev = startElement;
        T1 count = startElement;
        clength = _clength;
        plength = _plength;
        forn(i, plength) {
            count = count + 1;
            T1 next = count;
            nextElement.insert(make_pair(prev, next));
            prev = next;
        }
        T1 firstCycleElement = prev;
        forn(i, clength - 1) {
            count = count + 1;
            T1 next = count;
            nextElement.insert(make_pair(prev, next));
            prev = next;
        max = plength+clength;
        nextElement.insert(make_pair(prev, firstCycleElement));
    }
    }
    T1 operator () (const T1 argument) const {
        T1 cur = nextElement.find(argument) -> second;
        return cur;
    }
    int getN() const {
        return max;
    }
private:
    typedef map < T1, T1> Map;
    Map nextElement;	
    typename Map::iterator it;
    int max;
    int clength;
    int plength;
    T1 startElement;
};

int GenerateCycleLength(int i) {
    srand(time(NULL)+i);
    return rand()%100;
}

int GeneratePreCycleLength(int i) {
    srand(time(NULL)+i);
    return rand()%100;
}

int GenerateAmountOfTests() {
    srand(time(NULL));
    return rand()%100;
}

