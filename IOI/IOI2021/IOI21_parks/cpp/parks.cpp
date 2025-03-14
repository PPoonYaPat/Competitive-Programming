#include "parks.h"

int construct_roads(std::vector<int> x, std::vector<int> y) {
    if (x.size() == 1) {
	build({}, {}, {}, {});
        return 1;
    }
    std::vector<int> u, v, a, b;
    u.push_back(0);
    v.push_back(1);
    a.push_back(x[0]+1);
    b.push_back(y[0]-1);
    build(u, v, a, b);
    return 1;
}
