/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_PERSISTENTHELPER_H
#define DEVELOPER_STUDIO_PERSISTENTHELPER_H

#include <string>
#include <map>

namespace LunarSimulation {
    template <class T> class PersistentHelper {
    public:
        bool saveState(std::wstring label, T state) {
            _persistentState[label] = state;
            return true;
        }

        bool loadState(std::wstring label, T& state) {
            typename std::map<std::wstring, T>::iterator it = _persistentState.find(label);
            if (it != _persistentState.end()) {
                state = it->second;
                return true;
            }
            return false;
        }

        void clear() {
            _persistentState.clear();
        }

    private:
        std::map<std::wstring, T> _persistentState;
    };
}

#endif
