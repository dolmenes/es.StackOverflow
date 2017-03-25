#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <cstdlib> // rand( ) y srand( ).

struct Data {
  int value;
  std::ptrdiff_t left, right;

  Data( int v );
  bool operator<( const Data &o ) const { return value < o.value; }
};

// Facilita la lectura.
typedef std::vector< Data > VectorType;
typedef VectorType::iterator Iterator;

// Auxiliar para indicar quién es el padre.
// iter -> iterador al padre.
// left -> 'true' o 'false'.
struct ParentPos {
  Iterator iter;
  bool left;

  ParentPos( ) : iter( ), left( false ) { }
  ParentPos( const Iterator &i, bool l ) : iter( i ), left( l ) { }
  ParentPos &operator=( const ParentPos &o ) {
    iter = o.iter;
    left = o.left;
    return *this;
  }
};

VectorType Vector;
static unsigned Steps = 0; // Para comparar los resultados.

// Para volcado del vector.
std::ostream &operator<<( std::ostream &, const Data & );
// Las posibles optimizaciones
void PreInsert( Iterator &, const Data &, ParentPos &);
void PostInsert( Iterator &, const Data &, ParentPos & );

// Por si queremos volcar el vector durante las pruebas.
void Dump( std::ostream &os = std::cout ) {
  Iterator iter = Vector.begin( );

  while( iter != Vector.end( ) ) {
    os << *iter << std::endl;
    ++ iter;
  }
}

// Seleciona aleatoriamente quién será el padre del dato.
// Recibe el ÍNDICE en el que se insertará.
// Modifica el padre para que referencie al hijo.
// Devuelve un 'Iterator' al padre.
ParentPos SelectParent( ptrdiff_t pos ) {
  bool left = rand( ) & 1; // ¿ hijo left o right ?
  Iterator iter = Vector.begin( );

  while( true ) {
    if( left && ( iter->left == -1 ) ) {
      iter->left = pos;
      break;
    }

    if( ( !left ) && ( iter->right == -1 ) ) {
      iter->right = pos;
      break;
    }

    ++iter;
  }

  return ParentPos( iter, left );
}

void Insert( int v ) {
  Data aux( v );
  ParentPos pp;
  Iterator END;
  Iterator BEGIN;
  Iterator iter;

  std::cout << "Añadido " << v << " en la pos ";

  // Para evitar invalidar los iteradores, nos aseguramos
  // de que tengamos espacio para 1 elemento mas.
  Vector.reserve( Vector.size( ) + 1 );

  END = Vector.end( );
  BEGIN = Vector.begin( );

  // Buscamos el final de su grupo.
  iter = std::upper_bound( BEGIN, END, aux );

  std::cout << std::distance( BEGIN, iter );

  // Si 'Vector' NO ESTÁ VACÍO, escogemos un padre.
  if( !Vector.empty( ) ) {
    pp = SelectParent( std::distance( BEGIN, iter ) );
    std::cout << " al padre " << pp.iter->value;
  }

  std::cout << std::endl;

  // Caso FÁCIL; añadir al final del vector.
  // NO cambia el orden relativo de los enlaces.
  // NO es necesario optimizar nada.
  if( iter == END ) {
    Vector.push_back( aux );
  } else {
  // Caso normal. SE INSERTA EN ALGÚN PUNTO DISTINTO DEL FINAL.
    PreInsert( iter, aux, pp );
    Vector.insert( iter, aux );
    PostInsert( iter, aux, pp );
  }
}

int main( void ) {
  // int count = 4; // 1 mas de los que queramos.

  // Para tener resultados reproducibles.
  srand( 0 );
  // Borrar la pantalla (¡ Linux !)
  std::cout << "\033c";

//  while( --count )
//    Insert( rand( ) % 10 );
  Insert( 3 );
  Insert( 6 );
  Dump( );
  Insert( 5 );
  Dump( );

  std::cout << std::endl;
  std::cout << "Pasos: " << Steps << std::endl;

  return 0;
}

/***********************
*                      *
* Constructor de Data. *
*                      *
************************/
Data::Data( int v ) :
  value( v ),
  left( -1 ),
  right( -1 )
{

}
/*********************************************************
*                                                        *
* Método a implementar para el volcado de cada elemento. *
*                                                        *
**********************************************************/
std::ostream &operator<<( std::ostream &os, const Data &dat ) {
  os << " Value: ";
  os << std::setw( 2 ) << std::setfill( '0' ) << dat.value;
  os << " [" << dat.left << "][" << dat.right << "]";

  // La función 'Dump' añade al final un 'std::endl'.
  return os;
}

/*********************************************************
*                                                        *
*  Funciónes a reimplementar para buscar optimizaciones. *
*                                                        *
**********************************************************/
// pos -> Posición en la que se insertará.
// d -> Dato.
// parent -> padre.
void PreInsert( Iterator &pos, const Data &d, ParentPos &parent ) {
  Iterator iter = Vector.begin( );
  ptrdiff_t relative = std::distance( Vector.begin( ), pos );

  while( iter != Vector.end( ) ) {
    // Para mantener el orden relativo de los índices.
    if( parent.iter == iter ) {
      if( parent.left ) {
        if( iter->right >= relative )
          ++iter->right;
      } else {
        if( iter->left >= relative )
          ++iter->left;
      }

      ++iter;
      continue;
    }

    if( iter != pos ) {
      if( iter->left >= relative )
        ++iter->left;

      if( iter->right >= relative )
        ++iter->right;
    }

    ++iter;
  }
}

// pos -> Posición en la que se insertó.
// d -> dato.
// parent -> padre.
void PostInsert( Iterator &pos, const Data &d, ParentPos &parent ) {

}