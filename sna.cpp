#include "globals.h"
#include "file_loader.h"
#include "degree.h"
#include "betweenness.h"
#include <sstream>

/* FUNCTION: num_of_files
 * DESC: get the number of arguments (argc) and the arguments themselves,
 * checks to see if the required number of files argument was provided
 * and converts it from char* to int
 */
int num_of_files(int argc, char * number) {
	// argc == 2 because we want $ ./a.out number
	if (argc == 2) {
		string text_number(number);
		int num_files;
		istringstream ss(text_number);
		ss >> num_files;
		return num_files;
	}
	else return 0;
}

int main(int argc, char** args)
{
	int num_files = num_of_files(argc, args[1]);
	
	Graph g;

	load(g, num_files);
	degree(g);
	betweenness(g);

	return 0;
}

