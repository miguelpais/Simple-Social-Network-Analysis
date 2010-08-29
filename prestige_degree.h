#include "globals.h"


namespace prestige {

	FILE *degrees_file;

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

	/* FUNCTION: output_degree_info
	 * DESC: Outputs all the info previously calculated by the functions actor_prestige_degree (after normalization)
	 */

	template <typename Graph> void output_degree_info(Graph &g, vector<double> &prestige) {
		typename property_map<Graph, vertex_name_t>::type vertexName = get(vertex_name, g);
		typename property_map<Graph, vertex_index_t>::type vertexIndex = get(vertex_index, g);
		degrees_file = fopen("actor_prestige_degrees.txt", "w");
	
		typename graph_traits<Graph>::vertex_iterator vit, vitEnd;

		for(tie(vit, vitEnd) = vertices(g); vit != vitEnd; ++vit) {
		
			fprintf(degrees_file, "%9g %s\n", prestige[vertexIndex[*vit]], vertexName[*vit].c_str());
		}
	
		fclose(degrees_file);
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

		actor_degree(g, prestige);
		normalize_degree_indexes(g, prestige);
	
		output_degree_info(g, prestige);
	}
}