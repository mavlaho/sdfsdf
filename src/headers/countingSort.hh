#ifndef COUNTINGSORT_HH
#define COUNTINGSORT_HH 

#include <memory>


// Stabilno sortira polje A[0,1,2,...n-1] t.d. je A[i] = 0,1,2,...,k-1

template <typename T, int k>
void countingSort( T * const A , std::size_t n )
{

    std::unique_ptr<T[]> B( new T[n] );
    std::unique_ptr<T[]> C( new T[k] );

    for(unsigned int j=0; j<k; ++j)
        C[j] = 0ull;

    for(unsigned int j=0; j<n; ++j)
        C[ static_cast<unsigned long long int >(A[j]) ]++;

    for(unsigned int j=1; j<k; ++j)
        C[j] += C[j-1];
    
    for( int j=n-1 ; j>=0 ; --j )
        B[ (C[A[j]]--) - 1 ] = A[j];

    std::copy( B.get() , B.get()+n , A );

    return;
}


#endif //COUNTINGSORT_HH