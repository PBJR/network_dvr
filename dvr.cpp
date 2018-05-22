#include "dvr.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cfloat>

//Beginning of Graph functions
Graph::Graph(){
}

void Graph::insert_vertex(std::string vertex_name, Vertex* input_vertex){
    vertices[vertex_name] = input_vertex;
}

void Graph::dvr(std::string source_vertex){
    //Initial conditions for Bellman-Ford algorithm
    for(auto & vertex : vertices){
        distances[vertex.first] = DBL_MAX;
        prev_hops[vertex.first] = "";
    }
    distances[source_vertex] = 0;

    std::cout << std::endl << "--Shortest Path Distance List Iterations--" << std::endl;
 
    for(auto & kv : distances){
        if(kv.second > 10000000){
            std::cout << kv.first << ": " << "inf ";
        }
        else{
            std::cout << kv.first << ": " << kv.second << " ";
        }
    }
    std::cout << std::endl;

    //Run the Bellman-Ford algorithm (vertices)-1 times
    for(int i = 0; i < vertices.size()-1; i++){
        
        //For every edge in our graph: we update the min distance and min hop if we find a shorter path
        for(auto & vertex : vertices){
            std::string source_vertex = vertex.first;
            for(auto & edge : vertex.second->adjacency_list){
                std::string destination_vertex = edge.first;

                double edge_weight = edge.second;
                if(distances[source_vertex] + edge_weight < distances[destination_vertex] && distances[source_vertex] + edge_weight >= 0){
                    distances[destination_vertex] = distances[source_vertex] + edge_weight;
                    prev_hops[destination_vertex] = source_vertex;
                }
            }
        }

        //Output the shortest path distances every iteration
        for(auto & kv : distances){
            if(kv.second > 10000000){
                std::cout << kv.first << ": " << "inf ";
            }
            else{
                std::cout << kv.first << ": " << kv.second << " ";
            }
        }
        std::cout << std::endl;
    }

    
    std::cout << std::endl << "--Shortest Path Predecessor List--" << std::endl;
    for(auto & kv : prev_hops){
        std::cout << kv.first << " preceeded by " << kv.second<< std::endl;
    }

}

Graph::~Graph(){
    for(auto & vertex : vertices){
        delete vertex.second;
    }
}


//Beginning of File Input/Output functions
Graph* file_io::create_graph_from_file(std::string input_file){
    Graph* output_graph = new Graph();

    std::ifstream fin;
    fin.open(input_file);

    std::string curr_line;
    while(getline(fin, curr_line)){
        Vertex* curr_vertex = new Vertex();

        std::istringstream ss(curr_line);
        std::string vertex_name;
        ss >> vertex_name;

        std::string curr_edge;
        double curr_weight;
        while(ss >> curr_edge){
            ss >> curr_weight;
            curr_vertex->adjacency_list[curr_edge] = curr_weight;
        }

        output_graph->insert_vertex(vertex_name, curr_vertex);
    }

    return output_graph;
}
