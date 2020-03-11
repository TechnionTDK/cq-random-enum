//
// Created by shai.zeevi on 16/05/2019.
//

#ifndef RANDOMORDERENUMERATION_INDEXUTILS_H
#define RANDOMORDERENUMERATION_INDEXUTILS_H

#include <vector>

using namespace std;

typedef long long ll;

class IndexUtils {
public:

    inline static vector<ll> split(int flatIndex, const vector<ll> &dims) {
        return split(flatIndex, dims, dims.size());
    }

    inline static vector<ll> split(int flatIndex, const vector<ll> &dims, int k) {
        vector<ll> indices(k, 0);
        for (int i = k - 1; i >= 0; i--) {
            indices[i] = flatIndex % dims[i];
            flatIndex /= dims[i];
        }
        return indices;
    }

    inline static ll combine(const vector<ll>& addresses, const vector<ll>& dims) {
        ll flatIndex = addresses[addresses.size() - 1];
        for (int i = dims.size() - 2; i >= 0; i--) {
            flatIndex += addresses[i]*dims[i + 1];
        }
        return flatIndex;
    }
};


#endif //RANDOMORDERENUMERATION_INDEXUTILS_H
