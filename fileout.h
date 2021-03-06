#ifndef __FILEOUT__
#define __FILEOUT__

#include "globals.h"

namespace fileout {
	
	FILE *actor_index_file;
	FILE *group_index_file;
	FILE *properties_file;
	
	
	/* FUNCTION: output_actor_indexes
	 * DESC: Outputs the given metric values for all the vertices in the graph
	 */
	template <typename Graph> void output_actor_indexes(Graph &g, vector<double> &actor_indexes, FILE *actor_index_file) {
		typename property_map<Graph, vertex_name_t>::type vertexName = get(vertex_name, g);

		typename graph_traits<Graph>::vertex_iterator vit, vitEnd;

		for(tie(vit, vitEnd) = vertices(g); vit != vitEnd; ++vit) {
			fprintf(actor_index_file, "%.3f   %s\n", actor_indexes[*vit], vertexName[*vit].c_str());
		}
	}

	/* FUNCTION: output_group_info
	 * DESC: Outputs the overall group level index received as parameter
	 */

	void output_group_index(double &group_index, FILE *group_index_file) {
		fprintf(group_index_file, "Group Level Index: %.3g\n", group_index);
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
	
	
	/* FUNCTION: output_density
	 * DESC: Outputs to a file the density of the graph
	 */
	void output_density(double density) {
		properties_file = fopen("properties.txt", "a");
		
		fprintf(properties_file, "Graph Density: %.3g\n", density);
		
		fclose(properties_file);
	}
	
	
	/* FUNCTION: output_num_edges_vertices
	 * DESC: Outputs to a file the received number of vertices and
	 * edges of the graph
	 */
	void output_num_edges_vertices(int num_edges, int num_vertices) {
		properties_file = fopen("properties.txt", "a");
		
		fprintf(properties_file, "Number of Edges: %d\n", num_edges);
		fprintf(properties_file, "Number of Vertices: %d\n", num_vertices);
		
		fclose(properties_file);
	}
}
#endif
