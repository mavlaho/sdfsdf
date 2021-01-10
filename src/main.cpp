#include <iostream>
#include <random>
#include <memory>
#include <algorithm>
#include <ctime>
#include "testSortness.hh"
#include "debug.hh"


struct number;
void countingSort( number * const A , unsigned digit , std::size_t n , std::size_t k );
void sort( unsigned long long int A[] , std::size_t n );


struct number
{
    unsigned long a0;
    unsigned long a1;
    unsigned long a2;

    number( unsigned long aa0 = 0 , unsigned long aa1 = 0 , unsigned long aa2 = 0 ) : a0(aa0) , a1(aa1) , a2(aa2) {};
};

void countingSort( number * const A , unsigned digit , std::size_t n , std::size_t k )
{
    std::unique_ptr<number[]> B( new number[n] );
    std::unique_ptr<unsigned long[]> C( new unsigned long[k] );

    for(unsigned int j=0; j<k; ++j)
        C[j] = 0ul;

    for(unsigned int j=0; j<n; ++j)
    {
        unsigned long a;
        switch( digit )
        {
            case 0:
                a = A[j].a0;
                break;
            case 1:
                a = A[j].a1;
                break;
            case 2:
                a = A[j].a2;
                break;
            default:
                throw std::logic_error("digit nije 0,1,2!");
        }
        C[ a ]++;
    }

    for(unsigned int j=1; j<k; ++j)
        C[j] += C[j-1];
    
    for( int j=n-1 ; j>=0 ; --j )
    {
        unsigned long a;
        switch( digit )
        {
            case 0:
                a = A[j].a0;
                break;
            case 1:
                a = A[j].a1;
                break;
            case 2:
                a = A[j].a2;
                break;
            default:
                throw std::logic_error("digit nije 0,1,2!");
        }

        B[ C[a] - 1 ] = A[j];
        C[a]--;

    }

    std::copy( B.get() , B.get()+n , A );

    return;
}

void sort( unsigned long long int A[] , std::size_t n )
{
    std::unique_ptr<number[]> a( new number[n] );

    for(unsigned int i=0; i<n; ++i)
    {
        auto a0 = A[i]%n;
        auto a1 = (A[i]/n)%n;
        auto a2 = ((A[i]/n)/n)%n;
        a[i] = number(a0,a1,a2);
    }

    countingSort( a.get() , 0 , n , n );
    countingSort( a.get() , 1 , n , n );
    countingSort( a.get() , 2 , n , n );

    for(unsigned int i=0; i<n; ++i)
    {
        unsigned long long int a0 = static_cast<unsigned long long int>(a[i].a0);
        unsigned long long int a1 = static_cast<unsigned long long int>(a[i].a1);
        unsigned long long int a2 = static_cast<unsigned long long int>(a[i].a2);

        A[i] = a0 + n*( a1 + n*a2 );
    }


    return;
}







int main( int argc , char *argv[] )
{
    int NofExperiments = 1;
    if( argc == 2 )
        NofExperiments = atoi( argv[1] );


    // unsigned long long int A[0,1,2,...,n-1]
    // A[i] = 0, 1, 2, ..., n^3-1
    // n <= 2 000 000

    constexpr unsigned long long int n = 1000000;
    constexpr unsigned long long int k = n*n*n;



    std::unique_ptr<unsigned long long int[]> A( new unsigned long long int[n] );
    std::unique_ptr<unsigned long long int[]> Acpy( new unsigned long long int[n] );

    std::default_random_engine generator(static_cast<unsigned long int>(time(0)));
    std::uniform_int_distribution<unsigned long long int> distribution(0,k-1);




    double time1 = 0;
    double time2 = 0;
    try
    {
        for(int iexperiment = 1 ; iexperiment <= NofExperiments ; iexperiment++ )
        {
            clock_t start;
            clock_t end;
            
            for( unsigned int i=0 ; i<n ; ++i )
                A[i] = Acpy[i] = distribution(generator);
            
            
            start = clock();
            sort( A.get() , n );
            end = clock();
            time1 += static_cast<double>( end-start )/CLOCKS_PER_SEC;

            start = clock();
            std::sort( Acpy.get() , Acpy.get()+n );
            end = clock();
            time2 += static_cast<double>( end-start )/CLOCKS_PER_SEC;

            std::cout << "experiment " << iexperiment << " finished!" << std::endl;
        }
    }
    catch( std::exception const & e )
    {
        std::cout << e.what() << "\n";
    }
    



    
    auto cmpfunc = []( unsigned long long int const & a, unsigned long long int const & b )
    {
        if( a == b )
            return 0;
        else
            return ( a < b ) ? -1 : +1 ;
    };
    if( testSortness( A.get() , n , cmpfunc ) == false )
        std::cout << "Radix sort failed!"     << std::endl;
    else
        std::cout << "Radix sort successfull!" << std::endl;


    std::cout << "Radix     time: " << time1/NofExperiments << " s" << std::endl;
    std::cout << "std::sort time: " << time2/NofExperiments << " s" << std::endl;



    return 0;
}
