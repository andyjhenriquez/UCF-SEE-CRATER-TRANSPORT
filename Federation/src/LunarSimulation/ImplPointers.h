/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_IMPLPOINTERS_H
#define DEVELOPER_STUDIO_IMPLPOINTERS_H

#include <LunarSimulation/HlaPointers.h>

#include <vector>

namespace RtiDriver {
    class InteractionClassHandle;
    class ObjectClassHandle;
    class ObjectInstanceHandle;
    class Region;
}

namespace LunarSimulation {
    typedef std::shared_ptr<RtiDriver::InteractionClassHandle> InteractionClassHandlePtr;
    typedef std::shared_ptr<RtiDriver::ObjectClassHandle> ObjectClassHandlePtr;
    typedef std::shared_ptr<RtiDriver::ObjectInstanceHandle> ObjectInstanceHandlePtr;
    typedef std::shared_ptr<RtiDriver::Region> RegionPtr;
    typedef std::shared_ptr<std::vector<RegionPtr> > RegionSetPtr;

    class HlaHLAobjectRootImpl;
    class HlaHLAobjectRootAttributesImpl;
    class HlaPhysicalEntityImpl;
    class HlaPhysicalEntityAttributesImpl;
    class HlaDynamicalEntityImpl;
    class HlaDynamicalEntityAttributesImpl;
    class HlaPayloadImpl;
    class HlaPayloadAttributesImpl;
    class HlaLauncherImpl;
    class HlaLauncherAttributesImpl;
    class HlaPhysicalInterfaceImpl;
    class HlaPhysicalInterfaceAttributesImpl;
    class HlaReferenceFrameImpl;
    class HlaReferenceFrameAttributesImpl;
    class HlaMoonImpl;
    class HlaMoonAttributesImpl;
    class HlaExecutionConfigurationImpl;
    class HlaExecutionConfigurationAttributesImpl;
    class HlaTuning;
    class HlaHLAinteractionRootInteractionImpl;
    class HlaHLAinteractionRootParametersImpl;
    class HlaStartStopInteractionImpl;
    class HlaStartStopParametersImpl;
    class HlaModeTransitionRequestInteractionImpl;
    class HlaModeTransitionRequestParametersImpl;
    class HlaFederateIdImpl;
    class HlaLogicalTimeImpl;

    typedef std::shared_ptr<HlaHLAobjectRootImpl> HlaHLAobjectRootImplPtr;
    typedef std::shared_ptr<HlaHLAobjectRootAttributesImpl> HlaHLAobjectRootAttributesImplPtr;
    typedef std::shared_ptr<HlaPhysicalEntityImpl> HlaPhysicalEntityImplPtr;
    typedef std::shared_ptr<HlaPhysicalEntityAttributesImpl> HlaPhysicalEntityAttributesImplPtr;
    typedef std::shared_ptr<HlaDynamicalEntityImpl> HlaDynamicalEntityImplPtr;
    typedef std::shared_ptr<HlaDynamicalEntityAttributesImpl> HlaDynamicalEntityAttributesImplPtr;
    typedef std::shared_ptr<HlaPayloadImpl> HlaPayloadImplPtr;
    typedef std::shared_ptr<HlaPayloadAttributesImpl> HlaPayloadAttributesImplPtr;
    typedef std::shared_ptr<HlaLauncherImpl> HlaLauncherImplPtr;
    typedef std::shared_ptr<HlaLauncherAttributesImpl> HlaLauncherAttributesImplPtr;
    typedef std::shared_ptr<HlaPhysicalInterfaceImpl> HlaPhysicalInterfaceImplPtr;
    typedef std::shared_ptr<HlaPhysicalInterfaceAttributesImpl> HlaPhysicalInterfaceAttributesImplPtr;
    typedef std::shared_ptr<HlaReferenceFrameImpl> HlaReferenceFrameImplPtr;
    typedef std::shared_ptr<HlaReferenceFrameAttributesImpl> HlaReferenceFrameAttributesImplPtr;
    typedef std::shared_ptr<HlaMoonImpl> HlaMoonImplPtr;
    typedef std::shared_ptr<HlaMoonAttributesImpl> HlaMoonAttributesImplPtr;
    typedef std::shared_ptr<HlaExecutionConfigurationImpl> HlaExecutionConfigurationImplPtr;
    typedef std::shared_ptr<HlaExecutionConfigurationAttributesImpl> HlaExecutionConfigurationAttributesImplPtr;
    typedef std::shared_ptr<HlaTuning> HlaTuningPtr;
    typedef std::shared_ptr<HlaHLAinteractionRootInteractionImpl> HlaHLAinteractionRootInteractionImplPtr;
    typedef std::shared_ptr<HlaHLAinteractionRootParametersImpl> HlaHLAinteractionRootParametersImplPtr;
    typedef std::shared_ptr<HlaStartStopInteractionImpl> HlaStartStopInteractionImplPtr;
    typedef std::shared_ptr<HlaStartStopParametersImpl> HlaStartStopParametersImplPtr;
    typedef std::shared_ptr<HlaModeTransitionRequestInteractionImpl> HlaModeTransitionRequestInteractionImplPtr;
    typedef std::shared_ptr<HlaModeTransitionRequestParametersImpl> HlaModeTransitionRequestParametersImplPtr;
    typedef std::shared_ptr<HlaFederateIdImpl> HlaFederateIdImplPtr;
    typedef std::shared_ptr<HlaLogicalTimeImpl> HlaLogicalTimeImplPtr;
}
#endif
