/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAENUMSET_H
#define DEVELOPER_STUDIO_HLAENUMSET_H

#include <vector>
#include <set>
#include <algorithm>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

    /**
     * HlaEnumSet is used by object instance listeners to store object attribute enums.
     *
     * The API is similar to std::set.
     *
     * Each attribute shall be inserted only once. A std::vector is used for storing the
     * attribute enums in order, allowing fast lookup.
     */
    template <class T> class HlaEnumSet {

    public:
        /**
        * Constant iterator
        */
        typedef typename std::vector<T>::const_iterator const_iterator;
        /**
        * Value type
        */
        typedef typename std::vector<T>::value_type value_type;
        /**
        * Size type
        */
        typedef typename std::vector<T>::size_type size_type;

        /**
        * Iterator to the beginning.
        *
        * @return An iterator to the beginning.
        */
        LIBAPI const_iterator begin() const { return storage.begin(); }
        /**
        * @return An iterator to the end.
        */
        LIBAPI const_iterator end() const { return storage.end(); }

        /**
        * Finds all values in set that matches the value. Either 1 or 0.
        * @param val The value search for
        * @return 1 if the set contains the value, 0 i it does not.
        */
        LIBAPI size_type count(const value_type& val) const {
            return std::binary_search(storage.begin(), storage.end(), val) ? 1 : 0;
        }

        /**
        * @param val The value to search for
        * @return An iterator to the element matching the value. If the set doesn't contain the value the <code>end()</code> iterator is returned.
        */
        LIBAPI const_iterator find(const value_type& val) const {
            return binary_find(storage.begin(), storage.end(), val);
        }

        /**
        * @return Size of the set
        */
        LIBAPI size_type size() const {
            return storage.size();
        }

        /**
        * Conversion method back to a std::set for legacy code
        * @return The set as an std::set
        */
        LIBAPI std::set<T> as_set() const {
            std::set<T> set;
            for (const_iterator iter = begin(); iter != end(); iter++) {
                set.insert(*iter);
            }
            return set;
        }

       /*
        * Non-const methods available only when constructing the EnumSet.
        */

        /**
        * Constructor
        * @param capacity Capacity of the set
        */
        explicit HlaEnumSet(size_type capacity) {
            storage.reserve(capacity);
        }

        /**
        * Inserts element into the set
        * @param val Value to insert
        */
        void insert(const value_type& val) {
            storage.push_back(val);
        }

        /**
        * Sorts the set in ascending order
        */
        void freeze() {
            std::sort(storage.begin(), storage.end());
        }

    private:
        std::vector<T> storage;

        const_iterator binary_find(const_iterator begin, const_iterator end, const value_type& val) const {
            const_iterator iter = std::lower_bound(begin, end, val);

            if (iter != end && !(val < *iter)) {
                return iter;
            } else {
                return end;
            }
        }
    };
}
#endif

