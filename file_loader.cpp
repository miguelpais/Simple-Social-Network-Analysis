#include "file_loader.h"
#include <iostream>
#include <fstream>

/* FUNCTION: get_line_from_file
 * DESC: Reads a line of the file and stores in the strings each
 * one of the three tokens present int the line
 * token id1 id2 
 */

int get_line_from_file(ifstream &infile, string &token, string &idfrom, string &idto) {
	infile >> token;
	if(infile.fail()) {	
		return -1;
	}
	
	infile >> idfrom;
	if(infile.fail()) {
		return -1;
	}
	
	infile >> idto;
	if(infile.fail()) {
		return -1;
	}
	
	return 0;
}

/* FUNCTION: check_and_add_vertex
 * DESC: Checks if the vertex-id received from the text file line already is
 * exists in the graph as a vertex. If not it creates it.
 */

void check_and_add_vertex(string &id, Vertex &vertex, map<string, Vertex> &nameVertexMap, Graph &g, int &index) {
	property_map<Graph, vertex_name_t>::type vertexName = get(vertex_name, g);
	property_map<Graph, vertex_index_t>::type vertexIndex = get(vertex_index, g);
	map<string, Vertex>::iterator it;
	
	it = nameVertexMap.find(id);
	if(it == nameVertexMap.end()) { //didn't fount the vertex
		vertex = add_vertex(g);
		vertexName[vertex] = id; //mapping the vertexID we got from the textfile to its internal id in the graph structure
		nameVertexMap[id] = vertex; //the same the other way around
      	vertexIndex[vertex] = index++;
	}
	else {
		vertex = it->second;
	}
}

/* FUNCTION: is_friendship_relationship
 * DESC: Determines if the relationship line just read from the file
 * is a friendship one. If it does, it is identified in the file
 * by the token "a" which we must have read
 * WARN: token is a string but we're dealing with it as a char
 * works as long as the tokens in the file are all 1-char long
 */
inline int is_friendship_relationship(string token) {
	return token[0] == 'a';     //     /!\ SEE WARN
}


/* FUNCTION: parse_file
 * DESC: Reads the file infile consisting of lines following the format
 * token id1 id2 
 * where token describes the connection between actor id1 and id2.
 * Adds those edges to the graph and creates the vertices if needed
 */
void parse_file(Graph &g, ifstream &infile, map<string, Vertex> &nameVertexMap, int &index) {
	string token, idfrom, idto;
	
	while(!infile.eof()) { 
		// file not over, read a line
		
		if (get_line_from_file(infile, token, idfrom, idto) < 0) {
			break;
		}
		
		if (!is_friendship_relationship(token)) {
			continue;
		}
		
		Vertex from,to;
		check_and_add_vertex(idfrom, from, nameVertexMap, g, index);
		check_and_add_vertex(idto, to, nameVertexMap, g, index);


		add_edge(from, to, g);
	} 
}


/* FUNCTION: load
 * DESC: Loads all the textfiles formated as a{id}.txt from a1.txt to a{numfiles}.txt
 * and constructs the graph given by the connections in the textfiles
 */
void load(Graph &g, int numfiles)
{
	char filename[10];
	int index = 0;
	map<string, Vertex> nameVertexMap; //maps the textfile known vertex-ids to internal graph ids
	
	for(int i = 1; i <= numfiles; ++i) { 
		//generating current filename
		sprintf(filename, "a%d.txt", i);

		ifstream infile((const char*) filename);
		if(!infile.is_open()) {
			cout << "Error: unable to open file a" << i << ".txt" << endl;
			exit(-1);
		}
		
		parse_file(g, infile, nameVertexMap, index);	
	}
}
