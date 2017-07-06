#include "std_lib_facilities_4.h"
#include "Graph.h"      
#include "GUI.h"
#include "Aggie_snap.h"

int main()
try{
	Simple_window win{Point{100,100},800,500,"AggieSnap"};

	win.wait_for_button();
	return gui_main();
	
}
catch(exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Some exception\n";
	return 2;
}
