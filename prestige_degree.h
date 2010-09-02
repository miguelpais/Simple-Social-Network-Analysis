#include "globals.h"
#include "fileout.h"


namespace prestige {

	/* FUNCTION: actor_degree
	 * DESC: Calculates and stores each actor prestige degree in an vector
	 * Actor Prestige Degree is equal to the number of in-links for each vertex
	 * This index can only be calculate for unidirectional relations
	 */
	template <typename Graph> void actor_degree(Graph &g, vector<double> &prestige) {
		typename property_map<Graph, vertex_index_t>::type vertexIndex = get(vertex_index, g);
		typename graph_traits<Graph>::vertex_iterator vit, vitEnd;

		for(tie(vit, vitEnd) = vertices(g); vit != vitEnd; ++vit) {

			prestige[vertexIndex[*vit]] = in_degree(*vit, g);
		}
	}

	/* FUNCTION: normalize_degree_indexes
	 * DESC: normalizes all the actor prestige indexes
	 * Normalized_Prestige{Degree} = Regular_Prestige{Degree} / (g-1)
	 */
	template <typename Graph> void normalize_degree_indexes(Graph &g, vector<double> &prestige) {
		typename property_map<Graph, vertex_index_t>::type vertexIndex = get(vertex_index, g);
	
		double normalizer = num_vertices(g) - 1; // g-1
	
		typename graph_traits<Graph>::vertex_iterator vit, vitEnd;

		for(tie(vit, vitEnd) = vertices(g); vit != vitEnd; ++vit) {

			double unormalized_prestige = prestige[vertexIndex[*vit]];
			double normalized_prestige = unormalized_prestige / normalizer;

			prestige[vertexIndex[*vit]] = normalized_prestige;
		}
	}

	/* FUNCTION: degree
	 * DESC: Calculates each actor prestige degree normalizes it,
	 * and outputs the information
	 */

	template <typename Graph> void degree(Graph &g) {
		vector<double> prestige(num_vertices(g));
		double group_index;

		actor_degree(g, prestige);
		normalize_degree_indexes(g, prestige);
	
		fileout::output_info(g, prestige, group_index,  "actor_prestige_degrees.txt", "group_prestige.txt");
	}
}