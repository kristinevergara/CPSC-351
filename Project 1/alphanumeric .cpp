#include <pthread.h>
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <cctype>

std::string       phrase;
std::stringstream head;
std::string       word;
bool bit[2] = { 0, 0 };

void* alpha  ( void* ); 
void* numeric( void* ); 

int main( int argc, char* argv[] )
{
    if( argc < 2 )
    {
        fprintf(stderr, "USAGE: %s <message string>\n", argv[0]);         
        exit(-1);
    }
    phrase = argv[1];
    head << phrase;
    head >> word;
    pthread_t t1;
    pthread_t t2;
    pthread_create( &t1, NULL, alpha, NULL );
    pthread_create( &t2, NULL, numeric, NULL );
    pthread_join( t1, NULL );
    pthread_join( t2, NULL );
    return 0;
}

void* alpha( void* arg ) 
{
    do
    {
        if ( isalpha( word[0] ) || ispunct( word[0] ) )
        {
            std::cout << "alpha: " << word << std::endl;
            bit[1] = true;
        }
        else 
        {
            bit[0] = true;
            bit[1] = false;
            if( !head )
            {
                break;
            }
            while ( bit[0] )
        {
            continue;
        }
        }
        if ( bit[1] )
        {
            head >> word;
        }
    }
    while ( head );
    bit[0] = true;
    pthread_exit( 0 );
    
}

void* numeric( void* arg ) 
{
    do
    {
        if( isdigit( word[0] ) )
        {
            std::cout << "numeric: " << word << std::endl;
            bit[1] = true;
        }
        else
        {
            bit[0] = false;
            bit[1] = false;
            if( !head )
            {
                break;
            }
            while( !bit[0] )
            {
                continue;
            }
        }
        if ( bit[1] )
        {
            head >> word;
        }
    }
    while ( head );
    bit[0] = false;
    pthread_exit( 0 ); 
}
