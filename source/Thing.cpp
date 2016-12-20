#include "Thing.h"
/*define constructors*/

Thing::Thing() {
	label = static_cast<char>(BASE_LABEL + count++);
	cout << "  Constructing " << (*this) << " via " << __FUNCTION__ << endl;
}

Thing::Thing(int a) : x(a) {
	label = static_cast<char>(BASE_LABEL + count++);
	cout << "  Constructing " << (*this) << " via " << __FUNCTION__ << endl;
}

/*define copy assignment operator*/
Thing& Thing::operator=(const Thing& other) { 
	x = other.x; // note: don't copy the label -- implicit version will copy all data members
	cout << "  Copying      " << (*this) << " via " << __FUNCTION__ << endl;
	return *this; 
}

/*define copy constructor*/
Thing::Thing(const Thing& other) { 
	label = static_cast<char>(BASE_LABEL + count++);
	// impicit version will copy all data members, ie, x = other.x
	// I've skipped doing so to demo that if you customize a copy constructor, you need to provide that behavior!
	cout << "  Constructing " << (*this) << " via " << __FUNCTION__ << endl;
}
/*define destructor*/
Thing::~Thing() { 
	cout << "  Destroying   " << (*this) << " via " << __FUNCTION__ << endl;
}
/*operator overloading*/
ostream& operator<<(ostream& out, const Thing& t) {
	return out << typeid(t).name() << " " << t.label;  // https://msdn.microsoft.com/en-us/library/fyf39xec.aspx
}

int Thing::count = 0;  // need to initialize count before using it