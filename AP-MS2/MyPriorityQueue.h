#ifndef AP_MS2_MYPRIORITYQUEUE_H
#define AP_MS2_MYPRIORITYQUEUE_H

#include <queue>
#include <algorithm>

//PriorityQueue with find and remove function, taken from SO
template<class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>>
class MyPriorityQueue : public std::priority_queue<T, Container, Compare> {
public:
    typedef typename std::priority_queue<T, Container, Compare>::container_type::const_iterator const_iterator;

    const_iterator find(const T &val) const {
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first != last) {
            if (*first == val) return first;
            ++first;
        }
        return last;
    }

    const_iterator end() const {
        auto last = this->c.cend();
        return last;
    }


    bool remove(const T &value) {
        auto it = std::find(this->c.begin(), this->c.end(), value);
        if (it != this->c.end()) {
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
            return true;
        } else {
            return false;
        }
    }
};

#endif //AP_MS2_MYPRIORITYQUEUE_H
