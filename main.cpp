#include <iostream>
#include "dvr.h"

int main(int argc, char **argv){
    if(argc != 2){
        std::printf("Usage: %s input_graph_file\n", argv[0]);
        return 0;
    }
    Graph* topology_graph = file_io::create_graph_from_file(argv[1]);
    topology_graph->dvr("bellman-ford");

    delete topology_graph;
    return 0;
}
