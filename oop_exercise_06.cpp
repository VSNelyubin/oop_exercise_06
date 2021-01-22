// Written by VSNelyubin, m80-206b-19, Original Code, do not steal!

#include <map>

#include <algorithm>

#include <memory>

#include <iostream>

#include <cmath>

#include <vector>

#include <list>

double dabs(double a){
	if(a<0){return -a;}
	return a;
}

template <class T>
double dist(std::pair<T,T> a,std::pair<T,T> b){
	double rez=std::pow((double)a.first-(double)b.first,2);
	rez+=std::pow((double)a.second-(double)b.second,2);
	return std::sqrt(rez);
}

template <class T>
class Figure;

template <class T>
void prent(Figure<T> *c);

template <class T>
class Figure{
	public:	std::pair<T,T>*cord;
	int verNum;
	Figure(int vern){
		verNum=vern;
		cord=new std::pair<T,T>[vern];
	}
	~Figure(){
		delete[] cord;
	}
	void prt(){
		prent(this);
	}
};

template <class T>
bool checkEven(Figure<T>*ta){
    if(ta->verNum<3){return true;}
    double rez=dist(ta->cord[0],ta->cord[ta->verNum-1]);
    for(int arei=1;arei<ta->verNum;arei++){
        if(rez!=dist(ta->cord[arei],ta->cord[arei-1])){return false;}
    }
	rez=dist(ta->cord[0],ta->cord[ta->verNum-2]);
	if(rez!=dist(ta->cord[1],ta->cord[ta->verNum-1])){return false;}
    for(int arei=2;arei<ta->verNum;arei++){
        if(rez!=dist(ta->cord[arei],ta->cord[arei-2])){return false;}
    }

    return true;
}


template <class T>
double figArea(Figure<T>*ta){
	if(ta->verNum<3){return 0;}
	double rez,res=0;
	for(int arei=2;arei<ta->verNum;arei++){
		rez=ta->cord[0].first*(ta->cord[arei-1].second-ta->cord[arei].second);
		rez+=ta->cord[arei-1].first*(ta->cord[arei].second-ta->cord[0].second);
		rez+=ta->cord[arei].first*(ta->cord[0].second-ta->cord[arei-1].second);
		res+=dabs(rez/2);
	}
	return res;
}

template <class T>
std::pair<double,double> finCenter(Figure<T>*t){
	std::pair<double,double>rez;
	rez.first=0;rez.second=0;
	for(int arei=0;arei<t->verNum;arei++){
		rez.first+=(double)t->cord[arei].first;
		rez.second+=(double)t->cord[arei].second;
	}
	rez.first=rez.first/(double)t->verNum;
	rez.second=rez.second/(double)t->verNum;
	return rez;
}

template <class T>
std::ostream& operator << (std::ostream & out, Figure<T> &c) {
        for(int arei=0;arei<c.verNum;arei++){
                out<<c.cord[arei].first<<" : "<<c.cord[arei].second<<"\n";
        }
        return out;
}

template <class T>
std::istream& operator >> (std::istream & out, Figure<T> &c) {
        for(int arei=0;arei<c.verNum;arei++){
                out>>c.cord[arei].first>>c.cord[arei].second;
        }
		if(!checkEven(&c)){std::cout<<"figure sides are not even\n";}
        return out;
}

template <class T>
void prent(Figure<T> *c) {
//printf("entered prent\n");
	if(c==nullptr){printf("null\n");return;}
//	printf("notnull\n");
        std::cout<<*c;
}

template <class T>
void prent(Figure<T> **c) {
if(c==nullptr){printf("*null\n");return;}
	prent(*c);
}


template <class T>
class sqr : public Figure<T> { //XD public figure
        public:
        	sqr():Figure<T>(4){
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
//	pointer address( reference x ) const noexcept;
	const_pointer address( const_reference x ) const;
//	const_pointer address( const_reference x ) const noexcept;
	//address()
	//allocate()
	//deallocate()
	//max_size()
	//construct()
	//destroy()
};
*/







template <class T,size_t maxdata>
class mylloc{
private:
	T*data;
	int size;
	int curpos;
	int fir;
	int*nxt;
public:
	mylloc<T,maxdata>(){
		data=new T[maxdata];//(T*)malloc(sizeof(T)*maxdata);
		size=0;
		curpos=0;
		nxt=new int[maxdata];
		for(int i=0;i<maxdata;i++){
			nxt[i]=-1;
		}
		fir=0;
	}
	T* operator [](int pos){
//printf("op-\n");
		if(pos>size){
printf("err %d\n",pos);
			return nullptr;
		}
		curpos=fir;
		for(int i=0;i<pos;i++){
			curpos=nxt[curpos];
		}
//printf("op-\n");
		return &data[curpos];
//		return &data[pos];
	}

	int ffe(){
//printf("ffe-\n");
		for(int i=0;i<maxdata;i++){
			if((nxt[i]==-1)&&(i!=curpos)){
				return i;
			}
		}
//printf("-ffe\n");

		return -1;
	}

	void expand(int ni){
//printf("exp-\n");
		int nsize;
		if(ni>maxdata){
			nsize=maxdata;
		}
		else{
			nsize=ni;
		}
//printf("curpos %d\n",curpos);
		while(nxt[curpos]!=-1){curpos=nxt[curpos];}
//printf("curpos %d\n",curpos);
		for(size;size<nsize;size++){
			nxt[curpos]=this->ffe();
			curpos=nxt[curpos];
		}
//printf("-exp\n");
	}
};


template <class T>
   class stdallocator {
     public:
       // type definitions
       typedef T        value_type;
       typedef T*       pointer;
       typedef const T* const_pointer;
       typedef T&       reference;
       typedef const T& const_reference;
       typedef std::size_t    size_type;
       typedef std::ptrdiff_t difference_type;

       // rebind allocator to type U
       template <class U>
       struct rebind {
           typedef stdallocator<U> other;
       };

       // return address of values
       pointer address (reference value) const {
           return &value;
       }
       const_pointer address (const_reference value) const {
           return &value;
       }

       /* constructors and destructor
        * - nothing to do because the allocator has no state
        */
       stdallocator() throw() {
       }
       stdallocator(const stdallocator&) throw() {
       }
       template <class U>
         stdallocator (const stdallocator<U>&) throw() {
       }
       ~stdallocator() throw() {
       }

       // return maximum number of elements that can be allocated
       size_type max_size () const throw() {
           return std::numeric_limits<std::size_t>::max() / sizeof(T);
       }

       // allocate but don't initialize num elements of type T
       pointer allocate (size_type num, const void* = 0) {
           // print message and allocate memory with global new
           std::cerr << "allocate " << num << " element(s)"
                     << " of size " << sizeof(T) << std::endl;
           pointer ret = (pointer)(::operator new(num*sizeof(T)));
           std::cerr << " allocated at: " << (void*)ret << std::endl;
           return ret;
       }

       // initialize elements of allocated storage p with value value
       void construct (pointer p, const T& value) {
           // initialize memory with placement new
           new((void*)p)T(value);
       }

       // destroy elements of initialized storage p
       void destroy (pointer p) {
           // destroy objects by calling their destructor
           p->~T();
       }

       // deallocate storage p of deleted elements
       void deallocate (pointer p, size_type num) {
           // print message and deallocate memory with global delete
           std::cerr << "deallocate " << num << " element(s)"
                     << " of size " << sizeof(T)
                     << " at: " << (void*)p << std::endl;
           ::operator delete((void*)p);
       }
   };

   // return that all specializations of this allocator are interchangeable
   template <class T1, class T2>
   bool operator== (const stdallocator<T1>&,
                    const stdallocator<T2>&) throw() {
       return true;
   }
   template <class T1, class T2>
   bool operator!= (const stdallocator<T1>&,
                    const stdallocator<T2>&) throw() {
       return false;
   }

template <class T,size_t maxdata>
class Mylloc{
private:
	std::list<T,stdallocator<T>> datt;
	int size;
public:
	Mylloc<T,maxdata>(){
	}


	T* operator [](int pos){
		if(pos>size){
			printf("err %d\n",pos);
			return nullptr;
		}
		//typename std::list<T>::iterator it = datt.begin();
    		// Advance the iterator by 2 positions,
 		//std::advance(it, pos);
		auto it=std::next(datt.begin(), pos);
        	return &(*it);
	}

	void expand(int ni){
		int nsize;
		if(ni>maxdata){
			nsize=maxdata;
		}
		else{
			nsize=ni;
		}
		size=nsize;
		datt.resize(nsize);
		/*for(size;size<nsize;size++){
                	datt.push_back(nullptr);
		}*/
	}
};






const int MAXS =32;









template <class D>
class quu{
public:
	std::shared_ptr<D[]> bod;
	int itr;
	int len, mlen,beg;
	mylloc<D,MAXS> boda;
	quu<D>(int n){
		bod=std::shared_ptr<D[]>(new D[n]);
		len=0;
		itr=0;
		beg=0;
		mlen=n;
		boda.expand(n);
	}

	void dbg(){
		for(int i=0;i<mlen;i++){
			printf("%d\n",*boda[i]);
		}
	}

	void itr_b(){
		itr=beg;
	}

	void itr_move(int pos){
		if(pos>len){std::cout<<"position out of bounds\n";return;}
		if(pos<itr){this->itr_b();}
		for(;itr<pos;itr++);
	}

	void itr_e(){
		for(;itr<len;itr++);
    	}

	void grow(){
		if(mlen==MAXS){
			std::cout<<"hard limit reached\n";
			this->pop();
		}
		if(beg){
                	for(int i=0;i<len;i++){
                        	*boda[i]=*boda[beg+i];
                                //bod[i]=bod[beg+i];
                        }
                        //beg=0;
                }
                else{
                	mlen*=2;
                        	if(mlen>=MAXS){mlen=MAXS;}
                        boda.expand(mlen);
                        /*std::shared_ptr<D[]> bod2(new D[mlen*2]);
                        for(int i=0;i<len;i++){
                                bod2[i]=bod[i];
                        }
                        mlen*=2;
                	bod=bod2;*/
               }
	}

	void push(D elm){
//printf("entered push %d\n",elm);
		if(len==mlen){
			this->grow();
		}
		*boda[len]=elm;
//printf("boda[%d]=%d\n",len,*boda[len]);
		//bod[len]=elm;
		len++;
	}

	void insert(D elm){
        if(len==mlen){
		this->grow();
        }
	for(int i=len;i>itr;i--){
        	//bod[i]=bod[i-1];
		*boda[i]=*boda[i-1];
	}
	*boda[itr]=elm;
	//bod[itr]=elm;
        len++;
    }

	void erase(){
		for(int i=itr;i<len;i++){
			//bod[i]=bod[i+1];
			*boda[i]=*boda[i+1];
		}
		len--;
	}

        D* pop(){
                D* rez=boda[beg];
                beg++;
                len--;
                return rez;
        }

        D* cur(){
                return boda[itr];
        }

        D* top(){//but why?
                return boda[beg];
        }
        D* begin(){
                return boda[beg];
        }
        D* end(){
                return boda[len];
        }
};


int main(){
//	std::map<char,int,std::less<char>,retardallocator<std::pair<const char,int>>> m { {'C', 10}, {'G', 15}, {'R', 20}, };
	int len;
    	std::cin>>len;
	quu<Figure<int>*> arr(len);
	sqr<int>*a;
	char fgt;
	for(int i=0;i<len;i++){
		a=new sqr<int>;
		std::cin>>*a;
		//arr.push_back(a);
		arr.push(a);
	}
	std::for_each(arr.begin(),arr.end(),[](Figure<int>* tra){prent(tra);std::cout<<"\n";});
//printf("yes\n");
	int dl,dt;
	std::cout<<"\n";
	std::cin>>dl;
	for(int i=0;i<dl;i++){
		std::cin>>dt;
		if(dt<len){
			arr.itr_move(dt);
			arr.erase();
			len--;
		}
	}
	std::for_each(arr.begin(),arr.end(),[](Figure<int>* tra){prent(tra);std::cout<<"\n";});
	printf("\n");
	int rez=0;
	double are;
	std::cin>>are;
	for(int i=0;i<len;i++){
		arr.itr_move(i);
	        std::cout<<figArea(*arr.cur())<<"\n";
	}
	rez += std::count_if(arr.begin(),arr.end(),[are](Figure<int>*tra){return (figArea(tra)<are);});
	std::cout<<"there are "<<rez<<" figures with surface less than "<<are<<"\n";

	return 0;
}
