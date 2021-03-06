#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const int min_val = 0x80000000; // INT_MIN

class Heap {
public:
    explicit Heap(vector <int> _data) {
        for (auto &i : _data) {
            data.push_back(i);
        }
        for (ssize_t i = data.size() / 2 ; i >= 0; --i) {
            outer_repair(i);
        }
    }

    void outer_repair(ssize_t idx) {
        while (has_children(idx)) {
            int child1 = data[2 * idx + 1];
            int child2;
            if (2 * idx + 2 >= size()) {
                child2 = min_val;
            } else {
                child2 = data[2 * idx + 2];
            }
            if (data[idx] >= child1 && data[idx] >= child2) {
                return;
            } else {
                if (child1 > child2) {
                    swap(data[idx], data[2 * idx + 1]);
                    idx = 2 * idx + 1;
                } else {
                    swap(data[idx], data[2 * idx + 2]);
                    idx = 2 * idx + 2;
                }
            }
        }
    }

    int extract_root() {
        assert(size() > 0);
        int root = data[0];
        data[0] = data[size() - 1];
        data.pop_back();
        outer_repair(0);
        return root;
    }

    void insert(int elem) {
        data.push_back(elem);
        inner_repair(size() - 1);
    }

    void inner_repair(ssize_t idx) {
        while (idx > 0) {
            if (data[idx / 2] < data[idx]) {
                swap(data[idx / 2], data[idx]);
                idx /= 2;
            } else {
                return;
            }
        }
    }
    int get(ssize_t idx) {
        assert(idx < size());
        return data[idx];
    }
    void set(ssize_t idx, int value) {
        assert(idx < size());
        if (value < data[idx]) {
            decrease(idx, value);
        } else if (value > data[idx]) {
            increase(idx, value);
        }
    }
    void remove(ssize_t idx) {
        assert(idx < size());
        set(idx, data[size() - 1]);
        data.pop_back();
    }

    ssize_t size() {
        return (ssize_t)data.size();
    }
    void dump() {
        for (auto &i : data) {
            cout << i << " ";
        }
        cout << endl;
    }
protected:
    bool has_children(size_t idx) {
        return 2 * idx + 1 < size();
    }
    void decrease(ssize_t idx, int value) {
        assert(idx < size());
        assert(value < data[idx]);
        data[idx] = value;
        outer_repair(idx);
    }
    void increase(ssize_t idx, int value) {
        assert(idx < size());
        assert(value > data[idx]);
        data[idx] = value;
        inner_repair(idx);
    }
    vector <int> data;
};

int main() {
    int n;
    cin >> n;
    vector <int> v(n);

    for (auto &i : v) {
        cin >> i;
    }

    Heap heap(v);

    vector <int> sorted(n, 0);

    for (int i = n - 1; i >= 0; --i) {
        sorted[i] = heap.extract_root();
    }

    for (auto &i : sorted) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
