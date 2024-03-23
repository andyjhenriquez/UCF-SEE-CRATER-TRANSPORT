/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLASETTINGS_H
#define DEVELOPER_STUDIO_HLASETTINGS_H

#include <string>
#include <map>
#include <vector>
#include <exception>
#include <iostream>

#include <RtiDriver/Detective.h>

#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

    /**
    * Settings for a HlaWorld.
    * <p>
    * It is recommended to use the regular configuration mechanism of the application to control the HLA configuration.
    * This should be done by overriding this class, and combine that with the usual configuration mechanism.
    * <p>
    * It is possible to override the settings for a HlaWorld with a <code>FederateConfig.txt</code>
    * file in the current directory.
    * <p>
    * The <code>loadSettingsFile</code> method can be used to load a settings file with a name other
    * than <code>FederateConfig.txt</code>. Doing this will not trigger the override behaviour.
    * <p>
    * A template for FederateConfig.txt:

<pre><code>
#
# HlaWorld template settings file for a Developer Studio generated federate
#

# CRC host
crcHost = localhost

# CRC port
crcPort = 8989

# Local Settings Designator for HLA 1516-2010 Evolved
localSettingsDesignator = 

# Federate name
federateName = DevStudio

# Federation name
federationName = Moon PSR

# HLA 1516-2000 FOM URL
classicFomURL = 

# Main HLA 1516-2010 Evolved FOM Module URL
evolvedFomURL = Combined.xml

# Additional HLA 1516-2010 Evolved FOM Module URLs
additionalFomURLs = 

# HLA 1.3 FED URL
fedURL = 

# Try to create the federation before join
createFederation = true

# Try to destroy the federation after resign
destroyFederation = true

# RTI Profile to use (empty, A, B, C, D, E or F), default when empty is to use the
# environment variable RTI_DRIVER_PROFILE
rtiDriverProfile = B

# Enable HLA Time Management with time constrained
timeConstrained = true

# Enable HLA Time Management with time regulating
timeRegulating = true

# Step size
stepSize = 1

# HLA Time Management lookahead
lookahead = 1

# Time stamp factory to use (none, system_clock, rpr_relative or rpr_absolute)
timeStampFactory = system_clock
</code></pre>

    */
    class HlaSettings : private LunarSimulation::noncopyable {
    public:
        /** Enumeration for the different HLA standards */
        enum HlaVersion {
            /** <code>HLA_13</code> (with ordinal 0) */
            HLA_13,
            /** <code>HLA_1516</code> (with ordinal 1) */
            HLA_1516,
            /** <code>HLA_EVOLVED</code> (with ordinal 2) */
            HLA_EVOLVED,
            /** <code>HLA_4</code> (with ordinal 3) */
            HLA_4,
            /** <code>HLA_VERSION_NONE</code> used by DIS profile (with ordinal 4) */
            HLA_VERSION_NONE
        };

        /** Enumeration for different HLA call types */
        enum CallType {
            /** Create Federation Execution */
            CREATE, 
            /** Join Federation Execution */
            JOIN
        };

        /**
        * Creates a HlaSettings with the default settings and then reads the settings file and updates the
        * settings that are specified in the file.
        */
        LIBAPI HlaSettings();

        /**
        * Creates a HlaSettings with the default settings and then reads the settings file and updates the
        * settings that are specified in the file, finally overrides CRC host and CRC port with the
        * values specified here.
        *
        * @param crcHost CRC host
        * @param crcPort CRC port
        */
        LIBAPI HlaSettings(const std::wstring& crcHost, int crcPort);

        /**
        * Creates a HlaSettings with the default settings and then reads the settings file and updates the
        * settings that are specified in the file, finally overrides Local Settings Designator with the
        * value specified here.
        *
        * @param localSettingsDesignator Local Settings Designator
        */
        LIBAPI HlaSettings(const std::wstring& localSettingsDesignator);

        LIBAPI virtual ~HlaSettings() {}

        /**
        * Get the CRC host.
        *
        * @return the CRC host
        */
        LIBAPI virtual std::wstring getCrcHost() const {
            return _crcHost;
        }

        /**
        * Get the CRC port.
        *
        * @return the CRC port
        */
        LIBAPI virtual int getCrcPort() const {
            return _crcPort;
        }

        /**
        * Get the Local Settings Designator (LSD) for HLA Evolved.
        * The LSD can be used instead of CRC Host and Port to specify CRC to connect to.
        *
        * Note that the LSD is only used if connecting to HLA Evolved and to use the default LSD (an empty string),
        * the returned CRC host also has to be an empty string.
        *
        * @return the Local Settings Designator (LSD)
        */
        LIBAPI virtual std::wstring getLocalSettingsDesignator() const {
            return _localSettingsDesignator;
        }

        /**
        * Get the Federate name.
        *
        * @return the Federate name
        */
        LIBAPI virtual std::wstring getFederateName() const {
            return _federateName;
        }

        /**
        * Get the Federate type.
        *
        * @return the Federate type
        */
        LIBAPI virtual std::wstring getFederateType() const {
            return _federateType;
        }

        /**
        * Get the Federation name.
        *
        * @return the Federation name
        */
        LIBAPI virtual std::wstring getFederationName() const {
            return _federationName;
        }

        /**
        * Get the FOM URL.
        *
        * @param callType   Type of HLA call
        * @param hlaVersion HLA version of the RTI in use
        *
        * @return the FOM URL
        */
        LIBAPI virtual std::wstring getFomUrl(CallType callType, HlaVersion hlaVersion) const {
            if (hlaVersion == HLA_13) {
                return _fedUrl;
            } else if (hlaVersion == HLA_1516) {
                return _classicFomUrl;
            } else if (hlaVersion == HLA_4) {
                return _evolvedFomUrl;  // use Evolved FOM for now
            } else {
                return _evolvedFomUrl;
            }
        }

        /**
         * Get additional FOM Module URLs.
         *
         * @param callType   Type of HLA call
         * @param hlaVersion HLA version of the RTI in use
         *
         * @return the FOM URLs
         */
        LIBAPI virtual std::vector<std::wstring> getAdditionalFomUrls(CallType callType, HlaVersion hlaVersion) const {
            return _additionalFomUrls;
        }

        /**
        * Get if the Federation should be created before join.
        *
        * @return <code>true</code> if the Federation should be created before join
        */
        LIBAPI virtual bool getCreateFederation() const {
            return _createFederation;
        }

        /**
        * Get if the Federation should be destroyed after resign.
        *
        * @return <code>true</code> if the Federation should be destroyed after resign
        */
        LIBAPI virtual bool getDestroyFederation() const {
            return _destroyFederation;
        }

        /**
        * Get the RTI Driver Profile name.
        *
        * @return The RTI Driver Profile name.
        */
        LIBAPI virtual std::wstring getRtiDriverProfile() const {
            return _rtiDriverProfile;
        }

        /**
        * Get the RTI Driver Detectives.
        *
        * <b>The ability to attach detectives must be used with caution. Misbehaving detectives can
        * cause the entire HlaWorld to misbehave or even crash.</b>
        *
        * Note that the detectives will be installed in reverse order:
        * <pre>
        *    Federate -> Detective(count = n) -> ... -> Detective(count = 2) -> Detective(count = 1) -> RTI
        * </pre>
        *
        * @param count call count, starts at 1 and will be incremented for each call.
        *
        * @return The RTI Driver Detective, use <code>null</code> to indicate <i>no more detectives</i>
        */
        LIBAPI virtual std::unique_ptr<RtiDriver::Detective> getRtiDriverDetective(int count) {
            return std::unique_ptr<RtiDriver::Detective>((RtiDriver::Detective*)NULL);
        }

        /**
        * Check if a settings file has been defined that should override the user supplied settings.
        *
        * @return <code>True</code> if a settings file has been defined, <code>false</code> otherwise.
        */
        LIBAPI virtual bool hasSettingsFile() const {
            return LOADED_DEFAULT_SETTINGS;
        }

        /**
        * Get the time stamp factory name.
        *
        * @return The time stamp factory name.
        */
        LIBAPI virtual std::wstring getTimeStampFactoryName() const {
            return _timeStampFactory;
        }

        /**
        * Help function for HlaTuning.
        *
        * @return the setting corresponding to the specific name <code>setting</code>. Returns the empty string if the
        * setting is not found.
        */
        LIBAPI virtual std::string getSetting(std::string setting) const;

        /**
        * Get if this federate should be time constrained using <code>HLA Time Management</code>.
        *
        * @return <code>true</code> if this federate should be time constrained
        */
        LIBAPI virtual bool getTimeConstrained() const {
            return _timeConstrained;
        }

        /**
        * Get if this federate should be time regulating using <code>HLA Time Management</code>.
        *
        * @return <code>true</code> if this federate should be time regulating
        */
        LIBAPI virtual bool getTimeRegulating() const {
            return _timeRegulating;
        }

        /**
        * Get the step size for this federate.
        *
        * @return the step size for this federate
        */
        LIBAPI virtual long long getStepSize(HlaLogicalTimePtr nextLogicalTime) {
            return _stepSize;
        }

        /**
        * Set the step size for this federate.
        */
        LIBAPI virtual void setStepSize(long long stepSize) {
            _stepSize = stepSize;
        }

        /**
        * Get the <code>HLA Time Management</code> lookahead for this federate.
        *
        * @return the lookahead for this federate
        */
        LIBAPI virtual long long getLookahead(HlaLogicalTimePtr nextLogicalTime) {
            return _lookahead;
        }

        /**
        * Set the <code>HLA Time Management</code> lookahead for this federate.
        */
        LIBAPI virtual void setLookahead(long long lookahead) {
            _lookahead = lookahead;
        }

    protected:
        std::wstring _crcHost; /**< CRC Host, i.e. localhost */
        int _crcPort; /**< CRC Port, i.e. 8989 */
        std::wstring _localSettingsDesignator; /**< Local Settings Designator (LSD) for HLA 1516-2010 Evolved */
        std::wstring _federateName; /**< Name of the federate */
        std::wstring _federateType; /**< The type of federate */
        std::wstring _federationName; /**< Name of the federation */
        std::wstring _classicFomUrl; /**< The Url to the HLA 1516-2000 FOM */
        std::wstring _evolvedFomUrl; /**< The Url to the Base HLA 1516-2010 Evolved FOM module */
        std::vector<std::wstring> _additionalFomUrls; /**< The Urls to the additional HLA 1516-2010 Evolved FOM Modules */
        std::wstring _fedUrl; /**< The Url to the HLA 1.3 FED file */
        bool _createFederation; /**< True if the Federation should be created before join. */
        bool _destroyFederation; /**< True if the Federation should be destroyed after resign. */
        std::wstring _rtiDriverProfile; /**< The RTI Driver Profile. */
        std::wstring _timeStampFactory; /**< The time stamp factory name. */
        long long _stepSize;  /**< The step size for time management */
        long long _lookahead; /**< The lookahead for time management */
        bool _timeRegulating; /**< If the federate is time regulating */
        bool _timeConstrained; /**< If the federate is time constrained */

        /**
        * Reads the specified settings file and updates the settings.
        *
        * @param settingsFile settings file to load
        *
        * @return <code>true</code> if the settings file was loaded, <code>false</code> otherwise.
        */
        LIBAPI bool loadSettingsFile(const std::wstring& settingsFile);


    private:
        std::map<std::string, std::string> _variables;
        const bool LOADED_DEFAULT_SETTINGS; /**< Loaded default settings */

        void addVariableFromString(std::string& line);
        bool fileSettingsVariableExists(const std::string variableName);
        bool loadSettings(const char* fileName);
        bool loadDefaultSettings();
        void applySettings();
    };
}
#endif
