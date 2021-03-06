#ifndef __GLOBALS__H
#define __GLOBALS__H

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/betweenness_centrality.hpp>


using namespace boost;
using namespace std;

typedef property<vertex_name_t, string> VertexProperty;
typedef adjacency_list<setS, vecS, undirectedS, VertexProperty > UndirectedGraph; 
typedef	adjacency_list<setS, vecS, bidirectionalS, VertexProperty > DirectedGraph; //bidirectionalS takes up twice the mem

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
