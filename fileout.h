#ifndef __FILEOUT__
#define __FILEOUT__

#include "globals.h"

namespace fileout {
	
	FILE *actor_index_file;
	FILE *group_index_file;
	
	
	/* FUNCTION: output_actor_indexes
	 * DESC: Outputs the given metric values for all the vertices in the graph
	 */
	template <typename Graph> void output_actor_indexes(Graph &g, vector<double> &actor_indexes, FILE *actor_index_file) {
		typename property_map<Graph, vertex_name_t>::type vertexName = get(vertex_name, g);
		typename property_map<Graph, vertex_index_t>::type vertexIndex = get(vertex_index, g);

		typename graph_traits<Graph>::vertex_iterator vit, vitEnd;

		for(tie(vit, vitEnd) = vertices(g); vit != vitEnd; ++vit) {
			fprintf(actor_index_file, "%s %14f\n", vertexName[*vit].c_str(), actor_indexes[vertexIndex[*vit]]);
		}
	}

	/* FUNCTION: output_group_info
	 * DESC: Outputs the overall group level index received as parameter
	 */

	void output_group_index(double &group_index, FILE *group_index_file) {
		fprintf(group_index_file, "Group Level Index: %9g\n", group_index);
	}


	/* FUNCTION: output_info
	 * DESC: Outputs the given metric values for all the vertices in the graph
	 * and the overall group level index, both received as parameter
	 */

	template <typename Graph> void output_info(Graph &g, vector<double> &actor_indexes, double &group_index,
	 															string actor_filename, string group_filename) {

		actor_index_file = fopen(actor_filename.c_str(), "w");
		group_index_file = fopen(group_filename.c_str(), "w");

		output_actor_indexes(g, actor_indexes, actor_index_file);
		output_group_index(group_index, group_index_file);

		fclose(actor_index_file);
		fclose(group_index_file);
	}
}
#endif
