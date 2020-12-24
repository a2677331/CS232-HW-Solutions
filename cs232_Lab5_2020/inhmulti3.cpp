	#include <iostream>


	class base1 {
	public:
	    base1(void);
	    ~base1();
	    void fn1();
	};

	class base2 : protected base1 {
	public:
	    base2(void);
	    ~base2();
	    void fn2();
	};

	class base3 : protected base2 {
	public:
	    base3(void);
	    ~base3();
	    void fn3();
	};

	class derived : protected base3 {   //order of constructors
	public:
	    derived(void);
	    ~derived();
	    void fn4();
	};


	int main()
	{   derived obj;


	    cout << endl;
	    return 0;
	}


	base1::base1(void)
	{
	    cout << "a";
	}
	base1::~base1()
	{cout << "destroy 1 " << endl;}
	base2::base2(void)
	{
	    cout << "b";
	}
	base2::~base2()
	{cout << "destroy 2 " << endl;}
	base3::base3(void)
	{
	    cout << "c";
	}
	base3::~base3()
	{cout << "destroy 3 " << endl;}
	derived::derived(void)
	{
	    cout << "d";
	}
	derived::~derived()
	{cout << "destroy D  " << endl;}

	void derived::fn4()
	{ cout << "derived class method" << endl;
	fn1();
	fn2();
	fn3();
	}

	void base1::fn1()
	{cout << " base 1 class method " << endl;
	}

	void base2::fn2()
	{cout << " base 2 class method " << endl;
	}

	void base3::fn3()
	{cout << " base 3 class method " << endl;
	}
