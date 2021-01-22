// Written by VSNelyubin, m80-206b-19, Original Code, do not steal!

#include <map>

#include <algorithm>

#include <memory>

#include <iostream>

#include <cmath>

#include <vector>

#include <queue>

double dabs(double a)
{
    if (a < 0) {
        return -a;
    }
    return a;
}

template <class T>
double dist(std::pair<T, T> a, std::pair<T, T> b)
{
    double rez = std::pow((double)a.first - (double)b.first, 2);
    rez += std::pow((double)a.second - (double)b.second, 2);
    return std::sqrt(rez);
}

template <class T>
class Figure;

template <class T>
void prent(Figure<T>* c);

template <class T>
class Figure {
public:
    std::pair<T, T>* cord;
    int verNum;
    Figure(int vern)
    {
        verNum = vern;
        cord = new std::pair<T, T>[vern];
    }
    ~Figure()
    {
        delete[] cord;
    }
    void prt()
    {
        prent(this);
    }
};

template <class T>
bool checkEven(Figure<T>* ta)
{
    if (ta->verNum < 3) {
        return true;
    }
    double rez = dist(ta->cord[0], ta->cord[ta->verNum - 1]);
    for (int arei = 1; arei < ta->verNum; arei++) {
        if (rez != dist(ta->cord[arei], ta->cord[arei - 1])) {
            return false;
        }
    }
    rez = dist(ta->cord[0], ta->cord[ta->verNum - 2]);
    if (rez != dist(ta->cord[1], ta->cord[ta->verNum - 1])) {
        return false;
    }
    for (int arei = 2; arei < ta->verNum; arei++) {
        if (rez != dist(ta->cord[arei], ta->cord[arei - 2])) {
            return false;
        }
    }

    return true;
}

template <class T>
double figArea(Figure<T>* ta)
{
    if (ta->verNum < 3) {
        return 0;
    }
    double rez, res = 0;
    for (int arei = 2; arei < ta->verNum; arei++) {
        rez = ta->cord[0].first * (ta->cord[arei - 1].second - ta->cord[arei].second);
        rez += ta->cord[arei - 1].first * (ta->cord[arei].second - ta->cord[0].second);
        rez += ta->cord[arei].first * (ta->cord[0].second - ta->cord[arei - 1].second);
        res += dabs(rez / 2);
    }
    return res;
}

template <class T>
std::pair<double, double> finCenter(Figure<T>* t)
{
    std::pair<double, double> rez;
    rez.first = 0;
    rez.second = 0;
    for (int arei = 0; arei < t->verNum; arei++) {
        rez.first += (double)t->cord[arei].first;
        rez.second += (double)t->cord[arei].second;
    }
    rez.first = rez.first / (double)t->verNum;
    rez.second = rez.second / (double)t->verNum;
    return rez;
}

template <class T>
std::ostream& operator<<(std::ostream& out, Figure<T>& c)
{
    for (int arei = 0; arei < c.verNum; arei++) {
        out << c.cord[arei].first << " : " << c.cord[arei].second << "\n";
    }
    return out;
}

template <class T>
std::istream& operator>>(std::istream& out, Figure<T>& c)
{
    for (int arei = 0; arei < c.verNum; arei++) {
        out >> c.cord[arei].first >> c.cord[arei].second;
    }
    if (!checkEven(&c)) {
        std::cout << "figure sides are not even\n";
    }
    return out;
}

template <class T>
void prent(Figure<T>* c)
{
    if (c == nullptr) {
        printf("null\n");
        return;
    }
    std::cout << *c;
}

template <class T>
void prent(Figure<T>** c)
{
    if (c == nullptr) {
        printf("*null\n");
        return;
    }
    prent(*c);
}

template <class T>
class sqr : public Figure<T> { //XD public figure
public:
    sqr()
        : Figure<T>(4)
    {
    }
};

/*
template<class T>
class retardallocator{
public:

	typedef size_t     size_type;
      typedef ptrdiff_t  difference_type;
      typedef T*       pointer;
      typedef const T* const_pointer;
      typedef T&       reference;
      typedef const T& const_reference;
      typedef T        value_type;


	value_type T;
	pointer T*;
	const_pointer const T*;
	reference T&;
	const_reference const T&;
	size_type std::size_t
	difference_type std::ptrdiff_t;
	propagate_on_container_move_assignment std::true_type;
	rebind template< class U > struct rebind { typedef allocator<U> other; };
	is_always_equal std::true_type;








	retardallocator<T>();
	~retardallocator();
	pointer address( reference x ) const;
	const_pointer address( const_reference x ) const;
};
*/

template <class T, size_t maxdata>
class mylloc {
private:
    T* data;
    int size;

public:
    mylloc<T, maxdata>()
    {
        data = new T[maxdata]; //(T*)malloc(sizeof(T)*maxdata);
        size = 0;
    }
    T* operator[](int pos)
    {
        if (pos > size) {
            printf("err %d\n", pos);
            return nullptr;
        }
        return &data[pos];
    }
    void expand(int ni)
    {
        if (ni > maxdata) {
            size = maxdata;
        }
        else {
            size = ni;
        }
    }
};

const int MAXS = 32;

template <class D>
class quu {
public:
    std::shared_ptr<D[]> bod;
    int itr;
    int len, mlen, beg;
    mylloc<D, MAXS> boda;
    quu<D>(int n)
    {
        bod = std::shared_ptr<D[]>(new D[n]);
        len = 0;
        itr = 0;
        beg = 0;
        mlen = n;
        boda.expand(n);
    }

    void dbg()
    {
        for (int i = 0; i < mlen; i++) {
            printf("%d\n", *boda[i]);
        }
    }

    void itr_b()
    {
        itr = beg;
    }

    void itr_move(int pos)
    {
        if (pos > len) {
            std::cout << "position out of bounds\n";
            return;
        }
        if (pos < itr) {
            this->itr_b();
        }
        for (; itr < pos; itr++)
            ;
    }

    void itr_e()
    {
        for (; itr < len; itr++)
            ;
    }

    void grow()
    {
        if (mlen == MAXS) {
            std::cout << "hard limit reached\n";
            this->pop();
        }
        if (beg) {
            for (int i = 0; i < len; i++) {
                *boda[i] = *boda[beg + i];
            }
        }
        else {
            mlen *= 2;
            if (mlen >= MAXS) {
                mlen = MAXS;
            }
            boda.expand(mlen);
            /*std::shared_ptr<D[]> bod2(new D[mlen*2]);
                        for(int i=0;i<len;i++){
                                bod2[i]=bod[i];
                        }
                        mlen*=2;
                	bod=bod2;*/
        }
    }

    void push(D elm)
    {
        if (len == mlen) {
            this->grow();
        }
        *boda[len] = elm;
        len++;
    }

    void insert(D elm)
    {
        if (len == mlen) {
            this->grow();
        }
        for (int i = len; i > itr; i--) {
            *boda[i] = *boda[i - 1];
        }
        *boda[itr] = elm;
        len++;
    }

    void erase()
    {
        for (int i = itr; i < len; i++) {
            *boda[i] = *boda[i + 1];
        }
        len--;
    }

    D* pop()
    {
        D* rez = boda[beg];
        beg++;
        len--;
        return rez;
    }

    D* cur()
    {
        return boda[itr];
    }

    D* top()
    { //but why?
        return boda[beg];
    }
    D* begin()
    {
        return boda[beg];
    }
    D* end()
    {
        return boda[len];
    }
};

int main()
{
    int len;
    std::cin >> len;
    quu<Figure<int>*> arr(len);
    sqr<int>* a;
    char fgt;
    for (int i = 0; i < len; i++) {
        a = new sqr<int>;
        std::cin >> *a;
        arr.push(a);
    }
    std::for_each(arr.begin(), arr.end(), [](Figure<int>* tra) {prent(tra);std::cout<<"\n"; });
    int dl, dt;
    std::cout << "\n";
    std::cin >> dl;
    for (int i = 0; i < dl; i++) {
        std::cin >> dt;
        if (dt < len) {
            arr.itr_move(dt);
            arr.erase();
            len--;
        }
    }
    std::for_each(arr.begin(), arr.end(), [](Figure<int>* tra) {prent(tra);std::cout<<"\n"; });
    printf("\n");
    int rez = 0;
    double are;
    std::cin >> are;
    for (int i = 0; i < len; i++) {
        arr.itr_move(i);
        std::cout << figArea(*arr.cur()) << "\n";
    }
    rez += std::count_if(arr.begin(), arr.end(), [are](Figure<int>* tra) { return (figArea(tra) < are); });
    std::cout << "there are " << rez << " figures with surface less than " << are << "\n";

    return 0;
}