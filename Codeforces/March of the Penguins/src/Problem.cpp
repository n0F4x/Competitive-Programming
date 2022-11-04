#include "Problem.hpp"


void Problem::solve() {
    // TODO
}


istream &operator>>(istream &is, Problem &problem) {
    int n;
    is >> n >> problem._jumping_distance;
    problem._ice_cubes.clear();
    problem._results.clear();
    problem._ice_cubes.resize(n);
    for (auto &ice_cube : problem._ice_cubes) {
        is >> ice_cube.position.x >> ice_cube.position.y >> ice_cube.penguins >> ice_cube.capacity;
    }
    return is;
}

ostream &operator<<(ostream &os, const Problem &problem) {
    for (auto result : problem._results) {
        os << result << ' ';
    }
    os << '\n';
    return os;
}
