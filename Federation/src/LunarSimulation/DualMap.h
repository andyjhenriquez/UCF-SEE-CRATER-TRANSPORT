/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_DUALMAP_H
#define DEVELOPER_STUDIO_DUALMAP_H

#include <map>

#include <mutex>

namespace LunarSimulation {
    template<class T> class DualMapComparator {
    public:
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs < rhs;
        }
    };

    template<class T> class DualMapPtrComparator {
    public:
        bool operator()(const T& lhs, const T& rhs) const {
            return lhs-> operator< (*rhs);
        }
    };

    // K.operator< and V->operator< must exist!
    template<class K, class V, class C = DualMapPtrComparator<V> > class DualMap {
    public:
        void put(const K& key, V value) {
            std::lock_guard<std::recursive_mutex> lock(_mutex);
            if ((_map.find(key) != _map.end()) || (_reverseMap.find(value) != _reverseMap.end())) {
                throw std::logic_error("key or value already exists!");
            }
            _map[key] = value;
            _reverseMap[value] = key;
        }

        bool find(const K& key) const {
            std::lock_guard<std::recursive_mutex> lock(_mutex);
            return _map.find(key) != _map.end();
        }

        bool find(const K& key, V& value) const {
            std::lock_guard<std::recursive_mutex> lock(_mutex);
            typename std::map<K, V>::const_iterator iter = _map.find(key);
            if (iter != _map.end()) {
                value = iter->second;
                return true;
            }
            return false;
        }

        bool findByValue(const V& value, K& key) const {
            std::lock_guard<std::recursive_mutex> lock(_mutex);
            typename std::map<V, K, C>::const_iterator iter = _reverseMap.find(value);
            if (iter != _reverseMap.end()) {
                key = iter->second;
                return true;
            }
            return false;
        }

        void removeByValue(const V& value) {
            std::lock_guard<std::recursive_mutex> lock(_mutex);
            K key = _reverseMap[value];
            _reverseMap.erase(value);
            _map.erase(key);
        }

    private:
        std::map<K, V> _map;
        std::map<V, K, C> _reverseMap;

        mutable std::recursive_mutex _mutex;
    };
}
#endif
