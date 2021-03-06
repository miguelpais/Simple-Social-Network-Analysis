#include "globals.h"
#include "fileout.h"


namespace centrality {

	/* FUNCTION: group_betweenness
	* DESC: Calculates and stores the overall graph group degree
	* Group Centrality{Betweenness} = 2 * [Sum Centrality{Betweeness}(n*) - Centrality{Betweeness}(n{i}) ] / (g-1)^2(g-2)
	*/
	
	template <typename Graph> void group_betweenness(Graph &g, vector<double> &centrality, double &group_centrality) {
		double max_centrality = highest(centrality); // see globals.h for function definition
		double sum_of_difs = 0;
		double max_connects = num_vertices(g) - 1; // g - 1
		double denominator = max_connects * max_connects * (max_connects -1); // (g - 1)^2 * (g-2)
	
		vector<double>::iterator it;
		for(it = centrality.begin(); it != centrality.end(); ++it) {
			sum_of_difs += max_centrality - *it; 
		}
	
		group_centrality = 2 * sum_of_difs / denominator;
	}


	/* FUNCTION: normalize_betweenness_indexes
	 * DESC: normalizes all the actor centrality indexes
	 * Normalized_Centrality{Betweeness} = Regular_Centrality{Betweenness} / ((g-1)(g-2) / 2)
	 */
	template <typename Graph> void normalize_betweenness_indexes(Graph &g, vector<double> &centrality) {
	
		int max_connects = num_vertices(g) - 1; // g-1
		double normalizer = max_connects * (max_connects -1) / 2.0; // (g-1)(g-2) / 2
	
		typename graph_traits<Graph>::vertex_iterator vit, vitEnd;

		for(tie(vit, vitEnd) = vertices(g); vit != vitEnd; ++vit) {

			double unormalized_centrality = centrality[*vit];
			double normalized_centrality = unormalized_centrality / normalizer;

			centrality[*vit] = normalized_centrality;
		}
	}


	/* FUNCTION: actor_betweenness
	 * DESC: Calculates the actor betweenness index using the available function of the Boost Library
	 */
	template <typename Graph> void actor_betweenness(Graph &g, vector<double> &centrality) {
		brandes_betweenness_centrality(g, centrality_map(make_iterator_property_map(centrality.begin(), get(vertex_index, g))));
	}


	/* FUNCTION: betweenness
	 * DESC: Calculates the actor and group betweenness indexes and outputs the information to a file
	 */
	template <typename Graph> void betweenness(Graph &g) {
		vector<double> centrality(num_vertices(g));
		double group_centrality;

		actor_betweenness(g, centrality);
		group_betweenness(g, centrality, group_centrality);
		normalize_betweenness_indexes(g, centrality);

		fileout::output_info(g, centrality, group_centrality, "actor_betweenness.txt", "group_betweenness.txt");
	}
}