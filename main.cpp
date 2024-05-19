// Standard (system) header files
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Course.h"
#include "Student.h"
#include "SimpleUI.h"


// Main program
int main ()
{

StudentDB DB1;
SimpleUI UI1 (DB1);
UI1.run();
	return 0;
}
