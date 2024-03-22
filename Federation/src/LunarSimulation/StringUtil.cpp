/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#include <LunarSimulation/HlaAllHeaders.h>

#include "StringUtil.h"

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>


using namespace LunarSimulation;

std::string StringUtil::toHexString(const std::vector<char> &in) {
    std::ostringstream hexStream;
    hexStream.fill('0');
    hexStream  << std::hex << std::setw(2);
    int i = 1;

    for (std::vector<char>::const_iterator it = in.begin(); it != in.end(); it++, i++) {
        hexStream << (static_cast<int>(*it) & 0xFF);
        if (i % 4 == 0) {
            hexStream << " ";
        }
    }
    return hexStream.str();
}

std::string StringUtil::tostring(const std::string &in) {
    return in;
}

std::string StringUtil::tostring(const std::wstring &in) {
    return convert(in);
}

std::wstring StringUtil::towstring(const std::string &in) {
    return convert(in);
}

std::wstring StringUtil::towstring(const std::wstring &in) {
    return in;
}

void StringUtil::string2wstring(std::wstring &dest, const std::string &src) {
    dest.resize(src.size());
    for (std::string::size_type i = 0; i < src.size(); i++)
        dest[i] = static_cast<wchar_t>(src[i]);
}

void StringUtil::string2wstrings(std::vector<std::wstring> &dest, const std::string &src) {
   dest.clear();

   if (!src.empty()) {
      std::stringstream ss(src);
      std::string str;
      while (std::getline(ss, str, ';')) {
         StringUtil::removeWhitespaces(str);
         if (!str.empty()) {
            dest.push_back(towstring(str));
         }
      }
   }
}

void StringUtil::wstring2string(std::string &dest, const std::wstring &src) {
    dest.resize(src.size());
    for (std::string::size_type i = 0; i < src.size(); i++)
        dest[i] = static_cast<unsigned char>(src[i]);
}

std::wstring StringUtil::convert(const std::string &src) {
    std::wstring res;
    string2wstring(res, src);
    return res;
}

std::string StringUtil::convert(const std::wstring &src) {
    std::string res;
    wstring2string(res, src);
    return res;
}

void StringUtil::removeWhitespaces(std::string& line) {
    std::string whitespaces = " \t\f\v\n\r";
    size_t found = line.find_first_not_of(whitespaces);
    if (found != std::string::npos)
        line.erase(0, found);

    found = line.find_last_not_of(whitespaces);
    if (found != std::string::npos)
        line.erase(found+1);
    else line.clear();
}

void StringUtil::removeComment(std::string& line) {
    size_t commentPos = line.find("#");
    if (commentPos != std::string::npos)
        line.erase(commentPos, line.size());
}

bool StringUtil::stringToBool(std::string boolean) {
    if (boolean.size() != 4) {
        return false;
    }

    return (boolean[0] == 'T' || boolean[0] == 't') &&
           (boolean[1] == 'R' || boolean[1] == 'r') &&
           (boolean[2] == 'U' || boolean[2] == 'u') &&
           (boolean[3] == 'E' || boolean[3] == 'e');
}

std::wstring StringUtil::ulonglongToWstring(unsigned long long i) {
    std::wstringstream out;
    out << i;
    return out.str();
}

std::wstring StringUtil::intToWstring(int i) {
    std::wstringstream out;
    out << i;
    return out.str();
}

std::wstring StringUtil::uintToWstring(unsigned int i) {
    std::wstringstream out;
    out << i;
    return out.str();
}

std::wstring StringUtil::sizeToWstring(std::size_t i) {
    std::wstringstream out;
    out << i;
    return out.str();
}
