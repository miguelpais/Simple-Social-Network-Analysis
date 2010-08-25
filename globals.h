#ifndef __GLOBALS__H
#define __GLOBALS__H

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/betweenness_centrality.hpp>


using namespace boost;
using namespace std;

typedef property<vertex_index_t, int, property<vertex_name_t, string> > VertexProperty;
typedef adjacency_list<vecS, setS, undirectedS, VertexProperty > UndirectedGraph; 
typedef	adjacency_list<vecS, setS, directedS, VertexProperty > DirectedGraph; 

template<typename T> T highest(vector<T> &obj) {
	typename vector<T>::iterator it;
	T highest;
	bool first = true;
	for(it = obj.begin(); it != obj.end(); ++it) {
		if (first) {
			highest = *it;
			first = false;
		}
		else {
			if (*it > highest) {
				highest = *it;
			}
		}
	}
	return highest;
}

#endif
