#include "globals.h"


namespace properties {
	
	
	/* FUNCTION: directed_density
	 * DESC: Calculates digraph density, according to this formula
	 * d = L / (n * (n - 1)), L equals total number of ties in the digraph
	 * and n the number of vertices
	 */
	template <typename Graph> double directed_density(Graph &g) {
		double L = num_edges(g);
		double n = num_vertices(g);
	
		return L/(n*(n-1));
	}
	
	
	/* FUNCTION: directed_density
	 * DESC: Calculates digraph density, according to this formula
	 * d = L / ((n* (n - 1)) / 2), L equals total number of ties in the graph
	 * and n the number of vertices
	 */
	template <typename Graph> double undirected_density(Graph &g) {
		double L = num_edges(g);
		double n = num_vertices(g);
	
		return L/(n*(n-1)/2.0);
	}
	
	
	/* FUNCTION: density
	 * DESC: Calculates graph density, which is the ratio of present ties
	 * taken over the maximum possible number that could exist (complete graph)
	 */
	template<typename Graph> void density(Graph &g, bool is_directed) {
		double density;
		
		if (is_directed) {
			density = directed_density(g);
		}
		else {
			density = undirected_density(g);
		}
		
		fileout::output_density(density);
	}
	
	/* FUNCTION: print_num_edges_vertices(Graph &g)
	 * DESC: Prints to the file the number of edges and vertices of the graph
	 */
	template<typename Graph> void num_edges_vertices(Graph &g) {
		fileout::output_num_edges_vertices(num_edges(g), num_vertices(g));
	}
}