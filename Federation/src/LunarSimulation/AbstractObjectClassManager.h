/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_ABSTRACTOBJECTCLASSMANAGER_H
#define DEVELOPER_STUDIO_ABSTRACTOBJECTCLASSMANAGER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <RtiDriver/InteractionClassHandle.h>
#include <RtiDriver/ObjectInstanceHandle.h>
#include <RtiDriver/Types.h>

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaTimeStamp.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>
#include "ImplPointers.h"

namespace LunarSimulation {
    class AbstractObjectClassManager : private LunarSimulation::noncopyable {
    public:
        virtual ~AbstractObjectClassManager() {}

        virtual bool isEnabled(const std::wstring& objectClassName) = 0;
        virtual bool isOptional(const std::wstring& objectClassName) = 0;

        virtual void connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
            THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

        virtual void discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp) = 0;

        virtual void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) = 0;

        virtual void removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp,HlaLogicalTimePtr logicalTime) = 0;
      
        virtual void disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle) = 0;

        virtual void provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp) = 0;

        virtual void attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) = 0;

        virtual void attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) = 0;

        virtual void save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException) = 0;

        virtual void restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException) = 0;
    };
}
#endif
