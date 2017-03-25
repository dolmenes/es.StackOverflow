#include <string>
#include <cstddef>
#include <iostream>

template< typename T > struct utf8iterator {    
  T ptr;
  ::size_t size;
  char bytes[5];

  utf8iterator( const T &p ) :
    ptr( p ),
    size( 0 )
  {
    bytes[4] = 0;
  }
  utf8iterator &operator=( const T &iter ) {
    ptr = iter;
    size = 0;
    return *this;
  }

  bool operator==( const utf8iterator< T > &other ) const noexcept { return ptr == other.ptr; }
  bool operator!=( const utf8iterator< T > &other ) const noexcept { return ptr != other.ptr; }

  ::size_t calculateSize( ) const {
    if( ( *ptr & 248 ) == 240 ) {
      return 4;
    } else if( ( *ptr & 240 ) == 224 ) {
      return 3;
    } else if( ( *ptr & 224 ) == 192 )
      return 2;

    return 1;
  }
  utf8iterator &operator++( ) {
    if( size ) {
      ptr += size;
      size = 0;
    } else
      ptr += calculateSize( );

    return *this;
  }
  utf8iterator operator++( int ) {
    utf8iterator tmp( *this );

    if( size ) {
      ptr += size;
      size = 0;
    } else
      ptr += calculateSize( );

    return tmp;
  }
  void update( ) {
    ::size_t c;
    T iter( ptr );

    size = calculateSize( );

    for( c = 0; c != size; ++c ) {
      bytes[c] = *iter;
      ++iter;
    }

    if( size != 4 )
      bytes[size] = 0;
  }
  operator const char *( ) {
    if( !size )
      update( );

    return bytes;
  }
};


int main( void ) {
  const char *test = "abcdeññ";
  std::string str( test );

  utf8iterator< const char * > charIter( test );
  utf8iterator< std::string::iterator > strIter( str.begin( ) );

  while( *charIter ) {
    std::cout << charIter << ": ";
    std::cout << charIter.size << "\n";
    ++charIter;
  }

  while( strIter != str.end( ) ) {
    std::cout << strIter << ": ";
    std::cout << strIter.size << "\n";
    ++strIter;
  }

  std::cout << std::endl;

  return 0;
}
