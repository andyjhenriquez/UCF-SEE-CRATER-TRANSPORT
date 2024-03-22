/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_ABSTRACTINTERACTIONCLASSMANAGER_H
#define DEVELOPER_STUDIO_ABSTRACTINTERACTIONCLASSMANAGER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <string>

#include <RtiDriver/InteractionClassHandle.h>
#include <RtiDriver/Types.h>

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaPointers.h>
#include "ImplPointers.h"

namespace LunarSimulation {
    class AbstractInteractionClassManager  {
    public:
        virtual ~AbstractInteractionClassManager() {}

        virtual void receiveInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle, const RtiDriver::NameValueMap& parameters,
            const HlaFederateIdImplPtr producingFederate, HlaTimeStampPtr hlaTimeStamp, HlaLogicalTimeImplPtr logicalTime) = 0;

        virtual bool isEnabled(const std::wstring& interactionClassName) = 0;
        virtual bool isOptional(const std::wstring& interactionClassName) = 0;

        virtual void connected(const RtiDriver::InteractionClassHandle& interactionClassHandle, const std::wstring& interactionClassName)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) = 0;
   
        virtual void disconnected(const LunarSimulation::InteractionClassHandlePtr interactionClassHandle) = 0;
    };
}
#endif
