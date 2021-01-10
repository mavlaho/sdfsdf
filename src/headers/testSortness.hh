#ifndef TESTSORTNESS_HH
#define TESTSORTNESS_HH 

#include <memory>


// Stabilno sortira polje A[0,1,2,...n-1] t.d. je A[i] = 0,1,2,...,k-1

template <typename T, typename F>
bool testSortness( T * const A , std::size_t n , F cmpfunc )
{

    for( unsigned int i = 0 ; i < n-1 ; ++i )
        if( cmpfunc(A[i],A[i+1]) > 0 )
            return false;

    return true;
}


#endif //TESTSORTNESS_HH
