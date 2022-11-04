#pragma once

#include <iostream>
#include <vector>
#include "IceCube.hpp"

using namespace std;


class Problem {
private:
    float _jumping_distance;
    vector<IceCube> _ice_cubes;
    vector<int> _results;

public:
    void solve();

    friend istream &operator>>(istream &is, Problem &problem);
    friend ostream &operator<<(ostream &os, const Problem &problem);
};
