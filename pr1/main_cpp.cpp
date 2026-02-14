#include <iostream>
#include <thread>
using namespace std;

//Our .c funcs
extern "C" {
	#include "module1.h"
	#include "module2.h"
}

int main() {
	cout << "Main(C++) - starting threads..." << endl;
	//creating and launching threads
	thread t1(do_work_module1, nullptr);
	thread t2(do_work_module2, nullptr);

	//waiting till the end
	t1.join();
	t2.join();
	cout << "Main(C++) - all threads have finished." << endl;
	return 0;
}
