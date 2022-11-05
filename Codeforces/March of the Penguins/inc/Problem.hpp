#pragma once

#include <iostream>
#include <vector>
#include "IceCube.hpp"


class Problem {
private:
    float _jumping_distance;
    std::vector<IceCube> _ice_cubes;
    std::vector<size_t> _results;

public:
    void solve();

    friend std::istream &operator>>(std::istream &is, Problem &problem);
    friend std::ostream &operator<<(std::ostream &os, const Problem &problem);
};
