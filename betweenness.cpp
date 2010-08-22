#include "betweenness.h"

/* FUNCTION: output_info
 * DESC: Outputs the betweenness centrality indexes for all the verticex in the graph
 * and the overall group index
 */

FILE *betweenness_file;
FILE *group_betweenness_file;

void output_betweenness_info(Graph &g, vector<double> &centrality, double &group_centrality) {
	property_map<Graph, vertex_name_t>::type vertexName = get(vertex_name, g);
	property_map<Graph, vertex_index_t>::type vertexIndex = get(vertex_index, g);
	
	betweenness_file = fopen("actor_betweeness.txt", "w");
	group_betweenness_file = fopen("group_betweeness.txt", "w");
	
	graph_traits<Graph>::vertex_iterator vit, vitEnd;

	for(tie(vit, vitEnd) = vertices(g); vit != vitEnd; ++vit) {
		fprintf(betweenness_file, "%9f %s\n", centrality[vertexIndex[*vit]], vertexName[*vit].c_str());
	}
	
	fprintf(group_betweenness_file, "%9f\n", group_centrality);
	
	fclose(betweenness_file);
	fclose(group_betweenness_file);
}

/* FUNCTION: group_betweenness
* DESC: Calculates and stores the overall graph group degree
* Group Centrality{Betweenness} = 2 * [Sum Centrality{Betweeness}(n*) - Centrality{Betweeness}(n{i}) ] / (g-1)^2(g-2)
*/
void group_betweenness(Graph &g, vector<double> &centrality, double &group_centrality) {
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
void normalize_betweenness_indexes(Graph &g, vector<double> &centrality) {
	property_map<Graph, vertex_index_t>::type vertexIndex = get(vertex_index, g);
	
	int max_connects = num_vertices(g) - 1; // g-1
	double normalizer = max_connects * (max_connects -1) / 2.0; // (g-1)(g-2) / 2
	
	graph_traits<Graph>::vertex_iterator vit, vitEnd;

	for(tie(vit, vitEnd) = vertices(g); vit != vitEnd; ++vit) {

		double unormalized_centrality = centrality[vertexIndex[*vit]];
		double normalized_centrality = unormalized_centrality / normalizer;

		centrality[vertexIndex[*vit]] = normalized_centrality;
	}
}


/* FUNCTION: actor_betweenness
 * DESC: Calculates the actor betweeness index using the available function of the Boost Library
 */
void actor_betweenness(Graph &g, vector<double> &centrality) {
	brandes_betweenness_centrality(g, centrality_map(make_iterator_property_map(centrality.begin(), get(vertex_index, g))));
}


/* FUNCTION: betweenness
 * DESC: Calculates the actor and group betweeness indexes and outputs the information to a file
 */
void betweenness(Graph &g) {
	vector<double> centrality(num_vertices(g));
	double group_centrality;

	actor_betweenness(g, centrality);
	group_betweenness(g, centrality, group_centrality);
	normalize_betweenness_indexes(g, centrality);

	output_betweenness_info(g, centrality, group_centrality);
}

