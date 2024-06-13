#pragma once

#include "search_tree.h"

/*
   ______ ____   ____  _      _____  _____ _    _    _____ ______ _______
 |  ____/ __ \ / __ \| |    |_   _|/ ____| |  | |  / ____|  ____|__   __|
 | |__ | |  | | |  | | |      | | | (___ | |__| | | (___ | |__     | |
 |  __|| |  | | |  | | |      | |  \___ \|  __  |  \___ \|  __|    | |
 | |   | |__| | |__| | |____ _| |_ ____) | |  | |  ____) | |____   | |
 |_|    \____/ \____/|______|_____|_____/|_|  |_| |_____/|______|  |_|

*/

namespace bmstu {
template<typename stype>
class set {
 public:
    using treenode = bmstu::search_tree<stype>::TreeNode;
    using It = typename search_tree<stype>::iterator;
    set() : data(new bmstu::search_tree<stype>()) {}

    ~set() {
        delete data;
    }

    void insert(stype value) {
        data->insert(value);
    }

    void erase(stype value) {
        data->remove(value);
    }

    size_t size() {
        return data->size();
    }

    void clear() {
        delete data;
        data = new bmstu::search_tree<stype>();
    }

    void print() {
        data->inorderTraversal(std::cout);
    }

    bool empty() {
        return data->size() == 0;
    }

    treenode *find(stype value) {
        return data->find(value);
    }

    It begin() const {
        return data->begin();
    }

    It end() const {
        return data->end();
    }

 private:
    bmstu::search_tree<stype> *data;
};
}  // namespace bmstu
