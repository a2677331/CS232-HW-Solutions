#include <iostream>


class base1 {
        public:
            base1(char the_char);
        };

class base2 {
        public:
	    base2(char the_char);
	};

class derived : public base1, base2 {
    	public:
	    derived(char c1, char c2, char c3);
	};


int	main()
	{   derived obj('a','b','c');

	    cout << endl;
	    return 0;;
	}




	base1::base1(char the_char)
	{
	    cout << the_char;
	}

	base2::base2(char the_char)
	{
	    cout << the_char;
	}

	derived::derived(char c1, char c2, char c3) : base1(c2), base2(c3)
	{                               //when not using default constr
	    cout << c1;                 //you must list them
	}
