#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const int min_val = -9999999;

class Heap {
public:
    // Окучивание, конструктор
    explicit Heap(vector <int> _data) {
        for (auto &i : _data) {
            data.push_back(i);
            //cerr << "A" << endl;
        }
        for (ssize_t i = data.size() - 1; i >= 0; --i) {
            outer_repair(i);
        }
    }

    void outer_repair(ssize_t idx) {
        while (has_children(idx)) {
            //cerr << "A" << idx << endl;
            int child1 = data[2 * idx + 1];
            int child2;
            if (2 * idx + 2 >= size()) {
                //cerr << "B" << endl;
                child2 = min_val;
            } else {
                //cerr << "C" << endl;
                child2 = data[2 * idx + 2];
            }
            if (data[idx] >= child1 && data[idx] >= child2) {
                //cerr << "D" << endl;
                return;
            } else {
                //cerr << "E" << endl;
                if (child1 > child2) {
                    //cerr << "F" << endl;
                    swap(data[idx], data[2 * idx + 1]);
                    idx = 2 * idx + 1;
                } else {
                    //cerr << "G" << endl;
                    swap(data[idx], data[2 * idx + 2]);
                    idx = 2 * idx + 2;
                }
            }
        }
    }

    int extract_root() {
        cerr << "sz: " << size() << endl;
        assert(size() > 0);
        int root = data[0];
        data[0] = data[size() - 1];
        data.pop_back();
        outer_repair(0);
        return root;
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
    vector <int> data;
    bool has_children(size_t idx) {
        return 2 * idx + 1 < size();
    }
};


int main() {
    int n;
    cin >> n;
    vector <int> v(n);

    for (auto &i : v) {
        cin >> i;
    }
    Heap heap(v);
//    heap.dump();
//    cout << "root: " << heap.extract_root() << endl;
//    heap.dump();

    vector <int> sorted(n, 0);
    for (int i = n - 1; i >= 0; --i) {
        sorted[i] = heap.extract_root();
    }
    for (auto &i : sorted) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
/*
    for (auto &i : v) {
        cout << i << " ";
    }
    */
}
