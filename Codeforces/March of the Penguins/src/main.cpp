#include "Problem.hpp"

using namespace std;


int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        Problem problem;
        cin >> problem;
        problem.solve();
        cout << problem;
    }
    return 0;
}
