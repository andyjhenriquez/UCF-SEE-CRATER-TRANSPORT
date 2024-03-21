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

#include "CharPair.h"

#include "../StringUtil.h"

using namespace LunarSimulation;

std::wostream  & operator << (std::wostream &o, std::pair<char, char> const &d) {
    o << L"< "
      << (wchar_t)d.first
      << L" , "
      << (wchar_t)d.second
      << L" >";
    return o;
}

std::ostream  & operator << (std::ostream &o, std::pair<char, char> const &d) {
    o << "< "
      << d.first
      << " , "
      << d.second
      << " >";
    return o;
}
