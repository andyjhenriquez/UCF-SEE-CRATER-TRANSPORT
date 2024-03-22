/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_LISTENERSET_H
#define DEVELOPER_STUDIO_LISTENERSET_H

#include <set>

#include <mutex>

#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

    template<class T> class ListenerSet : private LunarSimulation::noncopyable {
    private:
        mutable std::mutex _mutex;
        std::set<T> _mySet;

    public:
        typedef typename std::set<T>::iterator iterator;

        ListenerSet() : _mySet(std::set<T>()) {}

        std::set<T> getListeners() {
            std::unique_lock<std::mutex> lock(_mutex);
            return std::set<T>(_mySet.begin(), _mySet.end());
        }

        void add(T element) {
            std::unique_lock<std::mutex> lock(_mutex);
            _mySet.insert(element);
        }

        void remove(T element) {
            std::unique_lock<std::mutex> lock(_mutex);
            _mySet.erase(element);
        }

        bool empty() {
            std::unique_lock<std::mutex> lock(_mutex);
            return _mySet.empty();
        }

        void clear() {
            std::unique_lock<std::mutex> lock(_mutex);
            _mySet.clear();
        }
    };
}
#endif
