/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_PARAMETERVALUE_H
#define DEVELOPER_STUDIO_PARAMETERVALUE_H

#include <memory>

namespace LunarSimulation {

    template <class T> class ParameterValue {
    private:
        std::shared_ptr<T> _value;
        bool _hasValue;

    public:

        ParameterValue()
            : _hasValue(false)
        {
        }

        std::shared_ptr<T> getValue() const {
            return _value;
        }

        void setValue(std::shared_ptr<T> value) {
            _value = value;
            _hasValue = true;
        }

        bool hasValue() const {
            return _hasValue;
        }
    };
}

#endif
