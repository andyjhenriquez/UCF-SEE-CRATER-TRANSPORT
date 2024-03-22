/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_STRINGUTIL_H
#define DEVELOPER_STUDIO_STRINGUTIL_H

#include <string>
#include <vector>

namespace LunarSimulation {
    class StringUtil {
    public:
        static std::string toHexString(const std::vector<char> &in);
        static std::string tostring(const std::string &in);
        static std::string tostring(const std::wstring &in);
        static std::wstring towstring(const std::string &in);
        static std::wstring towstring(const std::wstring &in);
        static void string2wstring(std::wstring &dest, const std::string &src);
        static void string2wstrings(std::vector<std::wstring> &dest, const std::string &src);
        static void wstring2string(std::string &dest, const std::wstring &src);
        static std::wstring convert(const std::string &src);
        static std::string convert(const std::wstring &src);
        static void removeWhitespaces(std::string& line);
        static void removeComment(std::string& line);
        static std::wstring ulonglongToWstring(unsigned long long i);
        static std::wstring intToWstring(int i);
        static std::wstring uintToWstring(unsigned int i);
        static std::wstring sizeToWstring(std::size_t i);

        /* Help function for HlaTuning. */
        static bool stringToBool(std::string boolean);
    };
}

#endif
