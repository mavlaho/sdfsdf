#include <iostream>
#include <random>
#include <memory>
#include "countingSort.hh"
#include "testSortness.hh"
#include "debug.hh"


int main( int argc , char *argv[] )
{

    // A[0,1,2,...,n-1], A[i]=0,1,2,...,k-1

    constexpr unsigned long int k = 1000;
    constexpr unsigned long int n = 100000;

    std::unique_ptr<unsigned long int[]> A( new unsigned long int[n] );


    std::default_random_engine generator(static_cast<unsigned long int>(time(0)));
    std::uniform_int_distribution<unsigned long long int> distribution(0,k-1);
    for( unsigned int i=0 ; i<n ; ++i )
    {
        A[i] = distribution(generator);
        DEBUG_MSG( A[i] );
    }



    try
    {
        countingSort<unsigned long int,k>( A.get() , n );
    }
    catch( std::exception const & e )
    {
        std::cout << e.what() << "\n";
    }
    

    DEBUG_MSG( "\nSorted array:\n" );
    for( unsigned int i=0 ; i<n ; ++i )
        DEBUG_MSG( A[i] );



    auto cmpfunc = []( unsigned long int const & a, unsigned long int const & b )
    {
        if( a == b )
            return 0;
        else
            return ( a < b ) ? -1 : +1 ;
    };
    if( testSortness( A.get() , n , cmpfunc ) == false )
        std::cout << "Counting sort failed!"     << std::endl;
    else
        std::cout << "Counting sort successfull!" << std::endl;


    return 0;
}