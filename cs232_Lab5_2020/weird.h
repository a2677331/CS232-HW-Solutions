#include <iostream>

template <class t>
class weird
{
public:
    weird();
    void operator %(float);
    void write();
private:
    t x;
};

template <class t>
weird<t>::weird()
{
    x = t(10000);
}

template <class t>
void weird<t>::operator%(float z)
{
    x = float(x) * z;
    return;
}

//place the definition of function write here
//it should send the contents of the object to the screen
