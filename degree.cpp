#include "degree.h"


FILE *degrees_file;
FILE *group_degree_file;

/* FUNCTION: actor_degree
 * DESC: Calculates and stores each actor degree in an ordered multimap
 * Actor degree is equal to the number of out-links for each vertex
 * Exception on undirected graphs where is the overall number of links a 
 * vertex is tied to
 */
void actor_degree(Graph &g, vector<double> &centrality) {
	property_map<Graph, vertex_index_t>::type vertexIndex = get(vertex_index, g);
	graph_traits<Graph>::vertex_iterator vit, vitEnd;

	for(tie(vit, vitEnd) = vertices(g); vit != vitEnd; ++vit) {

		centrality[vertexIndex[*vit]] = out_degree(*vit, g);
	}
}

/* FUNCTION: group_degree
 * DESC: Calculates and stores the overall graph group degree
 * Group Centrality{Degree} = [Sum Centrality{Degree}(n*) - Centrality{Degree}(n{i}) ] / (g-1)(g-2)
 */
void group_degree(Graph &g, vector<double> &centrality, double &group_centrality) {
	
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

/* FUNCTION: output_info
 * DESC: Outputs all the info previously calculated by the funcions actor and group degree
 */

void output_degree_info(Graph &g, vector<double> &centrality, double &group_centrality) {
	property_map<Graph, vertex_name_t>::type vertexName = get(vertex_name, g);
	property_map<Graph, vertex_index_t>::type vertexIndex = get(vertex_index, g);
	degrees_file = fopen("actor_degrees.txt", "w");
	group_degree_file = fopen("group_degree.txt", "w");	
	
	graph_traits<Graph>::vertex_iterator vit, vitEnd;

	for(tie(vit, vitEnd) = vertices(g); vit != vitEnd; ++vit) {
		
		fprintf(degrees_file, "%9g %s\n", centrality[vertexIndex[*vit]], vertexName[*vit].c_str());
	}
	
	fprintf(group_degree_file, "\n\nGroup Degree: %9g\n", group_centrality);	
	
	fclose(degrees_file);
	fclose(group_degree_file);
}


/* FUNCTION: normalize_degree_indexes
 * DESC: normalizes all the actor centrality indexes
 * Normalized_Centrality{Degree} = Regular_Centrality{Degree} / (g-1)
 */
void normalize_degree_indexes(Graph &g, vector<double> &centrality) {
	property_map<Graph, vertex_index_t>::type vertexIndex = get(vertex_index, g);
	
	double normalizer = num_vertices(g) - 1; // g-1
	
	graph_traits<Graph>::vertex_iterator vit, vitEnd;

	for(tie(vit, vitEnd) = vertices(g); vit != vitEnd; ++vit) {

		double unormalized_centrality = centrality[vertexIndex[*vit]];
		double normalized_centrality = unormalized_centrality / normalizer;

		centrality[vertexIndex[*vit]] = normalized_centrality;
	}
}

void degree(Graph &g) {
	vector<double> centrality(num_vertices(g));
	double group_centrality;

	actor_degree(g, centrality);
	group_degree(g, centrality, group_centrality);
	normalize_degree_indexes(g, centrality);
	output_degree_info(g, centrality, group_centrality);
}

