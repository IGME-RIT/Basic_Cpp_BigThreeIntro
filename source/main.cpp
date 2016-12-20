/*
BigThreeIntro
(c) 2016
original authors: David I. Schwartz
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*	This tutorial demonstrates the concept of the Law of the Big Three.
*	It covers issues such as typeid operator and Microsoft-specific predefined macro
	__FUNCTION__.
*/

#include "Thing.h"
#include "Basic.h"
using namespace std;  // for output

// Big Three (The law of The Big Three): Destructor, Copy constructor, Copy assignment operator
// for constructor: see https://msdn.microsoft.com/en-us/library/s16xw1a8.aspx
// for copy constructor and copy assignment operator: see https://msdn.microsoft.com/en-us/library/87by589c.aspx

int main() {
	cout << "\n-------------------------------------------------" << endl;  // output: -------------------------------------------------
	cout << "Basic implicit member functions: " << endl;                    // output: Basic implicit member functions:
	cout << "-------------------------------------------------" << endl;    // output: -------------------------------------------------
	Basic b1;  // instantiate a Basic Object b1
	b1.x = 10; // assign 10 as b1's data member x's value
	Basic b2(b1);    // assign b1 to b2
	Basic b3 = b1;   // assign b1 to b3
	Basic b4 = b3 = b2 = b1;  // assign b1 to b2 to b3 to b4
	cout << "  " << b1.x << endl;  // output: 10
	cout << "  " << b2.x << endl;  // output: 10
	cout << "  " << b3.x << endl;  // output: 10
	cout << "  " << b4.x << endl;  // output: 10

	cout << "\n-------------------------------------------------" << endl;  // output: -------------------------------------------------
	cout << "Thing: Test stack allocation and initialization: " << endl;    // output: Thing: Test stack allocation and initialization:
	cout << "-------------------------------------------------" << endl;    // output: -------------------------------------------------
	
	cout << "\nRegular constructors:" << endl;                              // output: Regular constructors:
	Thing t1;       // create a Thing object t1                             // output:   Constructing class Thing a via Thing::Thing
	Thing t2(1);    // initialize a Thing object t2 using default constructor| output:  Constructing class Thing b via Thing::Thing
		   		    // "most vexing parse": https://en.wikipedia.org/wiki/Most_vexing_parse
	// Thing t3();  // http://stackoverflow.com/questions/2318650/is-no-parentheses-on-a-constructor-with-no-arguments-a-language-standard
				    // http://stackoverflow.com/questions/1300327/sort-function-does-not-work-with-function-object-created-on-stack

	cout << "\nCopy constructors:" << endl;                                 // output: Copy constructors:
	Thing t4 = Thing();  // create a Thing object t4 using default constructor|output:  Constructing class Thing c via Thing::Thing
	Thing t5(2);         // initialize a Thing obejct t5, pass 2 as argument  |output:  Constructing class Thing d via Thing::Thing
	Thing t6(t5);        // create a Thing object t6 using copy constructor   |output:  Constructing class Thing e via Thing::Thing
	cout << "Check t5 and t6 values:" << endl; // output: Check t5 and t6 values:
	cout << "  " << t5.x << endl;              // output:  2
	cout << "  " << t6.x << endl;              // output:  0
	cout << "Change t5.x and recheck t5 and t6 values:" << endl;  // output: Change t5.x and recheck t5 and t6 values:
	t5.x = 3;            // assign t5's data member 3
	cout << "  " << t5.x << " " << t5 << endl; // output:  3 class Thing d
	cout << "  " << t6.x << " " << t6 << endl; // output:  0 class Thing e
	
	cout << "\nCopy assignment:" << endl;  // output: Copy assignment:
	Thing t7(20);   // initialize a Thing Object t7, pass 20 as its data member
	Thing t8 = t7;  // not copy assignment! (copy constructor instead)http://www.geeksforgeeks.org/copy-constructor-vs-assignment-operator-in-c/
					// see also http://stackoverflow.com/questions/15077466/what-is-a-converting-constructor-in-c-what-is-it-for
					// and http://en.cppreference.com/w/cpp/language/converting_constructor
	t8 = t7;        // this one is copy assignment
	cout << "Check t7 and t8 values:" << endl;  // output: Check t7 and t8 values:
	cout << "  " << t7.x << endl;  // output:  20
	cout << "  " << t8.x << endl;  // output:  20
	cout << "Change t5.x and recheck t5 and t6 values:" << endl;  // output: Change t5.x and recheck t5 and t6 values:
	t7.x = 90;  // change t7's data member value to 90
	cout << "  " << t7.x << " " << t7 << endl;  // output:  90 class Thing f
	cout << "  " << t8.x << " " << t8 << endl;  // output:  20 class Thing g

	cout << "\n-------------------------------------------------" << endl;
	cout << "Thing: C++11 initialization: " << endl;
	cout << "-------------------------------------------------" << endl;

	Thing t9{50};         // output:  Constructing class Thing h via Thing::Thing
	Thing t10 = Thing{};  // output:  Constructing class Thing i via Thing::Thing
	t10 = t9;             // output:  Copying      class Thing i via Thing::operator =
	cout << "  " << t9.x << " " << t9 << endl;   // output:  50 class Thing h
	cout << "  " << t10.x << " " << t10 << endl; // output:  50 class Thing i

	cout << "\n-------------------------------------------------" << endl;
	cout << "Thing: heap initialization: " << endl;
	cout << "-------------------------------------------------" << endl;

	Thing* a = new Thing;    // allocate memory in the heap for a Thing object | output:  Constructing class Thing j via Thing::Thing
	Thing* b = new Thing();  // allocate memory in the heap for a Thing object | output:  Constructing class Thing k via Thing::Thing
	cout << endl;
	cout << "  " << a->x << " " << *a << endl;  // output:  0 class Thing j
	cout << "  " << b->x << " " << *b << endl;  // output:  0 class Thing k
	cout << endl;
	b->x = 90; //assign 90 to b's data member x 
	*a = *b;   // why not just "a=b"? Ans: it will cause runtime error!
	b->x = 70; // change b's data member x to 70
	cout << "  " << a->x << " " << *a << endl;  // output:  90 class Thing j
	cout << "  " << b->x << " " << *b << endl;  // output:  70 class Thing k
	cout << endl;
	Thing* c = new Thing(*b);  // output:   Constructing class Thing l via Thing::Thing
	b->x = 50;
	cout << "  " << b->x << " " << *b << endl;  // output:  50 class Thing k
	cout << "  " << c->x << " " << *c << endl;  // output:  0 class Thing l

	cout << "\n-------------------------------------------------" << endl;
	cout << "Deallocate everything: " << endl;
	cout << "-------------------------------------------------" << endl;
	/*output:
	Destroying   class Thing l via Thing::~Thing
    Destroying   class Thing k via Thing::~Thing
	Destroying   class Thing j via Thing::~Thing
	Destroying   class Thing i via Thing::~Thing
	Destroying   class Thing h via Thing::~Thing
	Destroying   class Thing g via Thing::~Thing
	Destroying   class Thing f via Thing::~Thing
	Destroying   class Thing e via Thing::~Thing
	Destroying   class Thing d via Thing::~Thing
	*/
	delete c;  // output: Destroying   class Thing c via Thing::~Thing
	delete b;  // output: Destroying   class Thing b via Thing::~Thing
	delete a;  // output: Destroying   class Thing a via Thing::~Thing
	// no output for ~Basic, because we're using the default
	// all other "Things" were stack allocated, so no delete for them

}



