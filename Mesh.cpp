# include <glm/glm.hpp>
#include "Mesh.hpp"
#include <iostream>
#include "VisualServer.h"
#include <sstream>
#include <glm/gtx/string_cast.hpp>
// #include <sstream>
#include <string>
#include <fstream>


glm::vec4 parse_point(std::istringstream& iss) {
    float x, y, z;
    iss >> x >> y >> z;
    return glm::vec4(x, y, z, 1);
}

std::vector<glm::vec4> build_triangulated_polygon(const std::vector<glm::vec4>& points, std::istringstream& iss) {
    std::vector<size_t> indexes;
    std::vector<glm::vec4> triangles;
    size_t index;
    while (iss >> index) {
        index -= 1;
        indexes.push_back(index);
        if (indexes.size() == 3) {
            triangles.push_back(points[indexes[0]]);
            triangles.push_back(points[indexes[1]]);
            triangles.push_back(points[indexes[2]]);
            indexes.erase(std::next(indexes.begin())); // parse the polygon as a set of triangles
        }
    }
    return triangles;
}

void Mesh::load_obj_file(std::string path) {
    std::ifstream input(path);
    std::vector<glm::vec4> points;
    triangles = {};

    for( std::string line; getline( input, line ); )
    {
        if (line.size() < 2) {
            continue;
        }
        std::istringstream iss(line.substr(2));
        std::string token = line.substr(0, 2);
        
        if (token == "v ") {
            points.push_back(parse_point(iss));
            std::cout << "point: " << glm::to_string(points.back()).c_str() << "\n";
        } else if (token == "f ") {
            std::vector<glm::vec4> triangulated_polygon = build_triangulated_polygon(points, iss);
            triangles.insert(triangles.end(), triangulated_polygon.begin(), triangulated_polygon.end());
        }
    }
    int i = 0;
    std::cout << "triangles.size():  " <<triangles.size() << "\n";
    while (i < triangles.size()) {
        std::cout << "trinangle: " << glm::to_string(triangles[i]).c_str() << " " << glm::to_string(triangles[i + 1]).c_str() << " " << glm::to_string(triangles[i + 2]).c_str() << "\n";
        i += 3;
    }

}

void Mesh::draw_self(VisualServer* server) const {
    std::cout << "Draw Mesh\n";
    server->draw_polygon(triangles);
}

