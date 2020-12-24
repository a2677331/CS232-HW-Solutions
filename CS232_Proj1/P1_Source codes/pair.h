#ifndef PAIR_H
#define PAIR_H



// more or less from STL library
// found in <utility> and <pair>


template< class T1, class T2>
class Pair
  {
  public:

    T1 first;
    T2 second;

    // default constructor
    Pair(): first( T1() ), second( T2() )
    { }

    // constructor that initializes first and second
    Pair(  const T1 v1,  const T2 v2 ):
        first(v1), second(v2)
    { }


    //copy constructor
    template< typename U1, typename U2 >
    Pair ( const Pair<U1,U2>& X)
        : first( X.first ),  second( X.second )
    {}

    // overload <=
    template< typename U1, typename U2 >
    Pair& operator= ( const  Pair<U1,U2>& init )
    {
      return *this = Pair(init);
    }


    // overload <
    friend bool operator< ( const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs )
    {
      return lhs.first < rhs.first || !( rhs.first < lhs.first  && lhs.second < rhs.second   );
    }

    // overload ==
    friend bool operator== ( const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs )
    {
      return lhs.first == rhs.first && lhs.second == rhs.second ;
    }



  };



template< class T1, class T2 >
Pair<T1,T2> makePair(  const T1& v1,  const T2& v2   )
{
  return  Pair< T1, T2>(v1,v2);
}





#endif
