#ifndef DISTANCE_VECTOR_ROUTING
#define DISTANCE_VECTOR_ROUTING

#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>

struct Vertex{
    std::unordered_map<std::string, double> adjacency_list;
};

class Graph{
    public:
    Graph();
    void insert_vertex(std::string vertex_name, Vertex* input_vertex);
    void dvr(std::string source_vertex);
    ~Graph();
    
    private:
    std::unordered_map<std::string, Vertex*> vertices;
    std::unordered_map<std::string, double> distances;
    std::unordered_map<std::string, std::string> prev_hops;
};

namespace file_io {
    Graph* create_graph_from_file(std::string input_file);
}

#endif
