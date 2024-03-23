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

#include <LunarSimulation/HlaSettings.h>

#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>
#include <sstream>

#include "StringUtil.h"

using namespace std;
using namespace LunarSimulation;

static const char CRC_HOST[] = "crcHost";
static const char CRC_PORT[] = "crcPort";
static const char LOCAL_SETTINGS_DESIGNATOR[] = "localSettingsDesignator";
static const char FEDERATE_NAME[] = "federateName";
static const char FEDERATE_TYPE[] = "federateType";
static const char FEDERATION_NAME[] = "federationName";
static const char FOM_URL[] = "fomURL";   //For backwards compatibility
static const char CLASSIC_FOM_URL[] = "classicFomURL";
static const char EVOLVED_FOM_URL[] = "evolvedFomURL";
static const char ADDITIONAL_FOM_URLS[] = "additionalFomURLs";
static const char FED_URL[] = "fedURL";
static const char CREATE_FEDERATION[] = "createFederation";
static const char DESTROY_FEDERATION[] = "destroyFederation";
static const char RTI_DRIVER_PROFILE[] = "rtiDriverProfile";
static const char TIME_STAMP_FACTORY[] = "timeStampFactory";
static const char LOOKAHEAD[] = "lookahead";
static const char STEP_SIZE[] = "stepSize";
static const char TIME_REGULATING[] = "timeRegulating";
static const char TIME_CONSTRAINED[] = "timeConstrained";

HlaSettings::HlaSettings() :
_crcHost(L"localhost"),
_crcPort(8989),
_localSettingsDesignator(L""),
_federateName(L"DevStudio"),
_federateType(L"DevStudio"),
_federationName(L"Moon PSR"),
_classicFomUrl(L""),
_evolvedFomUrl(L"Combined.xml"),
_additionalFomUrls(std::vector<std::wstring>()),
_fedUrl(L""),
_createFederation(true),
_destroyFederation(true),
_rtiDriverProfile(L""),
_stepSize(1),
_lookahead(1),
_timeRegulating(true),
_timeConstrained(true),
LOADED_DEFAULT_SETTINGS(loadDefaultSettings())
{
    StringUtil::string2wstrings(_additionalFomUrls, "");
    applySettings();
}

HlaSettings::HlaSettings(const std::wstring& crcHost, int crcPort) :
_crcHost(crcHost),
_crcPort(crcPort),
_localSettingsDesignator(L""),
_federateName(L"DevStudio"),
_federateType(L"DevStudio"),
_federationName(L"Moon PSR"),
_classicFomUrl(L""),
_evolvedFomUrl(L"Combined.xml"),
_additionalFomUrls(std::vector<std::wstring>()),
_fedUrl(L""),
_createFederation(true),
_destroyFederation(true),
_rtiDriverProfile(L""),
_stepSize(1),
_lookahead(1),
_timeRegulating(true),
_timeConstrained(true),
LOADED_DEFAULT_SETTINGS(loadDefaultSettings())
{
    StringUtil::string2wstrings(_additionalFomUrls, "");
    applySettings();
}

HlaSettings::HlaSettings(const std::wstring& localSettingsDesignator) :
_crcHost(L""),
_crcPort(8989),
_localSettingsDesignator(localSettingsDesignator),
_federateName(L"DevStudio"),
_federateType(L"DevStudio"),
_federationName(L"Moon PSR"),
_classicFomUrl(L""),
_evolvedFomUrl(L"Combined.xml"),
_additionalFomUrls(std::vector<std::wstring>()),
_fedUrl(L""),
_createFederation(true),
_destroyFederation(true),
_rtiDriverProfile(L""),
_stepSize(1),
_lookahead(1),
_timeRegulating(true),
_timeConstrained(true),
LOADED_DEFAULT_SETTINGS(loadDefaultSettings())
{
    StringUtil::string2wstrings(_additionalFomUrls, "");
    applySettings();
}

bool HlaSettings::loadSettingsFile(const std::wstring& settingsFile) {
    if (!loadSettings(StringUtil::tostring(settingsFile).c_str())) {
        return false;
    }
    applySettings();
    return true;
}

void HlaSettings::addVariableFromString(std::string& line) {
    size_t pos = line.find("=");
    if (pos != string::npos) {
        string variable = line.substr(0, pos);
        StringUtil::removeWhitespaces(variable);
        string value = line.substr(pos + 1);
        StringUtil::removeWhitespaces(value);
        _variables[variable] = value;
    }
}

bool HlaSettings::fileSettingsVariableExists(const std::string variableName) {
    std::map<std::string, std::string>::const_iterator it = _variables.find(variableName);
    return it != _variables.end() && !it->second.empty();
}

std::string HlaSettings::getSetting(std::string setting) const {
    std::map<std::string, std::string>::const_iterator it = _variables.find(setting);
    if (it == _variables.end()) {
        return "";
    } else {
        return it->second;
    }
}

bool HlaSettings::loadSettings(const char* fileName) {
    ifstream stream;
    stream.open(fileName, ifstream::in);

    if (!stream) {
        return false;
    }

    string line;
    while (stream) {
        getline(stream, line);
        if (stream) {
            StringUtil::removeComment(line);
            addVariableFromString(line);
        }
    }

    return true;
}

bool HlaSettings::loadDefaultSettings() {
    bool defaultsLoaded = loadSettings("FederateConfig.txt");
    loadSettings("FederateTuning.txt");
    return defaultsLoaded;
}

void HlaSettings::applySettings() {
    if (fileSettingsVariableExists(CRC_HOST)) StringUtil::string2wstring(_crcHost, _variables[CRC_HOST]);
    if (fileSettingsVariableExists(CRC_PORT)) {
        std::istringstream istrm(_variables[CRC_PORT]);
        if (!(istrm >> _crcPort)) {
            throw std::runtime_error("Reading CRC port from settings file failed");
        }
    }
    if (fileSettingsVariableExists(LOCAL_SETTINGS_DESIGNATOR)) StringUtil::string2wstring(_localSettingsDesignator, _variables[LOCAL_SETTINGS_DESIGNATOR]);
    if (fileSettingsVariableExists(FEDERATE_NAME)) StringUtil::string2wstring(_federateName, _variables[FEDERATE_NAME]);
    if (fileSettingsVariableExists(FEDERATE_TYPE)) StringUtil::string2wstring(_federateType, _variables[FEDERATE_TYPE]);
    if (fileSettingsVariableExists(FEDERATION_NAME)) StringUtil::string2wstring(_federationName, _variables[FEDERATION_NAME]);

    if (fileSettingsVariableExists(CLASSIC_FOM_URL)) {
        StringUtil::string2wstring(_classicFomUrl, _variables[CLASSIC_FOM_URL]);
    } else if (fileSettingsVariableExists(FOM_URL)) {
        StringUtil::string2wstring(_classicFomUrl, _variables[FOM_URL]);
    }

    if (fileSettingsVariableExists(EVOLVED_FOM_URL)) {
        StringUtil::string2wstring(_evolvedFomUrl, _variables[EVOLVED_FOM_URL]);
    } else if (fileSettingsVariableExists(FOM_URL)) {
        StringUtil::string2wstring(_evolvedFomUrl, _variables[FOM_URL]);
    }
    if (fileSettingsVariableExists(ADDITIONAL_FOM_URLS)) StringUtil::string2wstrings(_additionalFomUrls, _variables[ADDITIONAL_FOM_URLS]);

    if (fileSettingsVariableExists(FED_URL)) {
        StringUtil::string2wstring(_fedUrl, _variables[FED_URL]);
    } else if (fileSettingsVariableExists(FOM_URL)) {
        StringUtil::string2wstring(_fedUrl, _variables[FOM_URL]);
    }

    if (fileSettingsVariableExists(CREATE_FEDERATION)) _createFederation = _variables[CREATE_FEDERATION] == "true";
    if (fileSettingsVariableExists(DESTROY_FEDERATION)) _destroyFederation = _variables[DESTROY_FEDERATION] == "true";
    if (fileSettingsVariableExists(RTI_DRIVER_PROFILE)) StringUtil::string2wstring(_rtiDriverProfile, _variables[RTI_DRIVER_PROFILE]);
    if (fileSettingsVariableExists(TIME_STAMP_FACTORY)) StringUtil::string2wstring(_timeStampFactory, _variables[TIME_STAMP_FACTORY]);

    if (fileSettingsVariableExists(LOOKAHEAD)) {
        std::istringstream istrm(_variables[LOOKAHEAD]);
        if (!(istrm >> _lookahead)) {
            throw std::runtime_error("Reading lookahead from settings file failed");
        }
    }

    if (fileSettingsVariableExists(STEP_SIZE)) {
        std::istringstream istrm(_variables[STEP_SIZE]);
        if (!(istrm >> _stepSize)) {
            throw std::runtime_error("Reading step size from settings file failed");
        }
    }

    if (fileSettingsVariableExists(TIME_REGULATING)) _timeRegulating = _variables[TIME_REGULATING] == "true";
    if (fileSettingsVariableExists(TIME_CONSTRAINED)) _timeConstrained = _variables[TIME_CONSTRAINED] == "true";
}
