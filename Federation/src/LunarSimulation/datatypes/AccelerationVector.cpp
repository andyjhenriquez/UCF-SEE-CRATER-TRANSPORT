/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#include <LunarSimulation/HlaAllHeaders.h>

#include <LunarSimulation/datatypes/AccelerationVector.h>

#include <vector>
#include "../StringUtil.h"

namespace LunarSimulation {

    std::wostream  & operator << (std::wostream& o, std::vector< double >const &d) {
        o << L"<AccelerationVector: { ";
        for(size_t i = 0; i < d.size(); i++) {
            o << d[i];
            if (i != d.size() -1) {
                o << L", ";
            }
        }
        o << L" }>";
        return o;
    }

    std::ostream  & operator << (std::ostream& o, std::vector< double >const &d) {
        o << "<AccelerationVector: { ";
        for(size_t i = 0; i < d.size(); i++) {
            o << d[i];
            if (i != d.size() -1) {
                o << ", ";
            }
        }
        o << " }>";
        return o;
    }
}
