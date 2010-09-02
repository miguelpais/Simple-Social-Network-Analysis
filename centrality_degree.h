#include "globals.h"
#include "fileout.h"


namespace centrality {

	/* FUNCTION: actor_degree
	 * DESC: Calculates and stores each actor degree in a vector
	 * Actor degree is equal to the number of out-links for each vertex
	 * Exception on undirected graphs where is the overall number of links a 
	 * vertex is tied to
	 */
	template <typename Graph> void actor_degree(Graph &g, vector<double> &centrality) {
		typename property_map<Graph, vertex_index_t>::type vertexIndex = get(vertex_index, g);
		typename graph_traits<Graph>::vertex_iterator vit, vitEnd;

		for(tie(vit, vitEnd) = vertices(g); vit != vitEnd; ++vit) {

			centrality[vertexIndex[*vit]] = out_degree(*vit, g);
		}
	}

	/* FUNCTION: group_undirected_degree
	 * DESC: Calculates and stores the overall graph undirected group degree
	 * Group Centrality{Degree} = [Sum Centrality{Degree}(n*) - Centrality{Degree}(n{i}) ] / (g-1)(g-2)
	 */
	template <typename Graph> void group_undirected_degree(Graph &g, vector<double> &centrality, double &group_centrality) {

		double sum_difs = 0;
		double max_centrality = highest(centrality); // Centrality{Degree}(n*) see globals.h for function definition
		double max_connects = num_vertices(g) -1; // g-1
		double denominator = max_connects * (max_connects -1); // (g-1)(g-2)

		vector<double>::iterator it;

		for(it = centrality.begin(); it != centrality.end(); ++it) {
			//summation 
			sum_difs += max_centrality - *it;
		}

		group_centrality = sum_difs/denominator;
	}


	/* FUNCTION: group_directed_degree
	 * DESC: Calculates and stores the overall graph directed group degree
	 * Group Centrality{Degree} = [Sum Centrality{Degree}(n*) - Centrality{Degree}(n{i}) ] / (g-1)^2
	 */
	template <typename Graph> void group_directed_degree(Graph &g, vector<double> &centrality, double &group_centrality) {

		double sum_difs = 0;
		double max_centrality = highest(centrality); // Centrality{Degree}(n*) see globals.h for function definition
		double max_connects = num_vertices(g) -1; // g-1
		double denominator = max_connects * max_connects; // (g-1)^2	

		vector<double>::iterator it;

		for(it = centrality.begin(); it != centrality.end(); ++it) {
			//summation 
			sum_difs += max_centrality - *it;
		}

		group_centrality = sum_difs/denominator;
	}
	

	/* FUNCTION: normalize_degree_indexes
	 * DESC: normalizes all the actor centrality indexes
	 * Normalized_Centrality{Degree} = Regular_Centrality{Degree} / (g-1)
	 */
	template <typename Graph> void normalize_degree_indexes(Graph &g, vector<double> &centrality) {
		typename property_map<Graph, vertex_index_t>::type vertexIndex = get(vertex_index, g);

		double normalizer = num_vertices(g) - 1; // g-1

		typename graph_traits<Graph>::vertex_iterator vit, vitEnd;

		for(tie(vit, vitEnd) = vertices(g); vit != vitEnd; ++vit) {

			double unormalized_centrality = centrality[vertexIndex[*vit]];
			double normalized_centrality = unormalized_centrality / normalizer;

			centrality[vertexIndex[*vit]] = normalized_centrality;
		}
	}

	template <typename Graph> void degree(Graph &g, bool is_directed) {
		vector<double> centrality(num_vertices(g));
		double group_centrality;

		actor_degree(g, centrality);

		if (is_directed) {
			group_directed_degree(g, centrality, group_centrality);
		}
		else {
			group_undirected_degree(g, centrality, group_centrality);
		}

		normalize_degree_indexes(g, centrality);
		fileout::output_info(g, centrality, group_centrality, "actor_centrality_degrees.txt", "group_centrality_degree.txt");
	}
}