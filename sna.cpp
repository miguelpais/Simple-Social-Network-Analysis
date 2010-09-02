#include "globals.h"
#include "filein.h"
#include "fileout.h"
#include "centrality_degree.h"
#include "prestige_degree.h"
#include "centrality_betweenness.h"
#include <iostream>
#include <sstream>

/* FUNCTION: num_of_files
 * DESC: get the number of arguments (argc) and the arguments themselves,
 * checks to see if the required number of files argument was provided
 * and converts it from char* to int
 * WARN: passing a number bigger than int will result in failure
 * Also, sometimes passing certain chars may be accepted and converted to int
 */
int num_of_files(int argc, char * number) {
	if (argc > 1) {
		string text_number(number);
		int num_files;
		istringstream ss(text_number);
		ss >> num_files;
		return num_files;
	}
	else {
		cout << "[Usage:] ./out {num_files} {-u | -d}" << endl;
		cout << "[Error:] Number of files not supplied, exiting..." << endl;
		exit(-1);
	}
}

/* FUNCTION: determine_directed
 * DESC: analyzes the parameter received to determine
 * if the graph we're about to analyze is directed (-d) or undirected (-u)
 * exit the program if none supplied
 * WARN: the function only checks the first letter of the
 * param, so passing -dice will count as -d
 */
bool determine_directed(int argc, char * param) {
	if (argc > 2) {
		// param[1] because param[0] is the '-' 
		if (param[1] == 'd') { 
			return true;
		}
		else if (param[1] == 'u') {
			return false;
		}
		else {
			cout << "[Usage:] ./out {num_files} {-u | -d}" << endl;
			cout << "[Error:] Unidentified parameter, exiting..." << endl;
			exit(-1);
		}
	}
}

/* FUNCTION: inform user
 * DESC: Informs the user after the processing of the arguments.
 * That way the user can check if he didn't commit a mistake
 * or if the program correctly translated the num_of_files from
 * string to int.
 */
void inform_user(int num_files, bool is_directed) {
	cout << "Processing " << num_files << (num_files == 1 ? " file..." : " files...") << endl;
	cout << "Processing a " << (is_directed ? "directed" : "undirected") << " graph..." << endl;
}



/* FUNCTION: load_and_process
 * DESC: loads the graph and calculated the degree and betweenness metrics
 */
template <typename Graph> void load_and_process(Graph &g, bool is_directed, int num_files) {
	filein::load(g, num_files);
	centrality::degree(g, is_directed);
	centrality::betweenness(g);
	
	if (is_directed) {
		prestige::degree(g);
	}
}


int main(int argc, char** args)
{
	int num_files = num_of_files(argc, args[1]);
	
	bool is_directed = determine_directed(argc, args[2]);
	
	inform_user(num_files, is_directed);

	if (is_directed) {
		DirectedGraph g; 
		load_and_process(g, is_directed, num_files);
	} else {
		UndirectedGraph g;
		load_and_process(g, is_directed, num_files);
	}
	
	cout << "\nDone!\nCheck results in actor_{metric}.txt and group_{metric}.txt files!\n";
	
	return 0;
}
