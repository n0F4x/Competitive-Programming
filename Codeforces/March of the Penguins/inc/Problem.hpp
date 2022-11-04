#pragma once

#include <iostream>
#include <vector>
#include "IceCube.hpp"


class Problem {
private:
    float _jumping_distance;
    std::vector<IceCube> _ice_cubes;
    std::vector<int> _results;

public:
    void solve();

    friend istream &operator>>(istream &is, Problem &problem);
    friend ostream &operator<<(ostream &os, const Problem &problem);
};
