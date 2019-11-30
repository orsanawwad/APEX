#ifndef AP_MS2_ICACHEMANAGER_H
#define AP_MS2_ICACHEMANAGER_H

#include <unordered_map>


namespace server_side {
    template<typename Key, typename Value>
    class ICacheManager {
    protected:
        std::unordered_map<Key, Value> solutionsMap;

    public:
/**
 * Checks if the solution for the given problem is added before.
 */
        virtual bool doesExist(Key key) = 0;

/**
 * Returns the solution for the given problem.
 */
        virtual Value get(Key key) = 0;

/**
 * Sets the given problem to the solution.
 */
        virtual void set(Key key, Value value) = 0;

        virtual ~ICacheManager();
    };

    template<typename Key, typename Value>
    ICacheManager<Key, Value>::~ICacheManager() {}
}

#endif //AP_MS2_ICACHEMANAGER_H
