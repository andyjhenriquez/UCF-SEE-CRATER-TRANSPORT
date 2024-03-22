/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAOBJECTINSTANCEBASE_H
#define DEVELOPER_STUDIO_HLAOBJECTINSTANCEBASE_H

#include <string>
#include <memory>
#include <vector>

#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaFederateId.h>


namespace LunarSimulation {

    /**
    * Base interface used by all object instances.
    */
    class HlaObjectInstanceBase {

    public:

        /**
        * An enumeration of all object class types.
        */
        enum ObjectClassType {
            /** HLAobjectRoot, instance of <code>HlaHLAobjectRoot</code> (FOM name <code>HLAobjectRoot</code>) */
            HLAOBJECT_ROOT,
            /** PhysicalEntity, instance of <code>HlaPhysicalEntity</code> (FOM name <code>HLAobjectRoot.PhysicalEntity</code>) */
            PHYSICAL_ENTITY,
            /** DynamicalEntity, instance of <code>HlaDynamicalEntity</code> (FOM name <code>HLAobjectRoot.PhysicalEntity.DynamicalEntity</code>) */
            DYNAMICAL_ENTITY,
            /** Payload, instance of <code>HlaPayload</code> (FOM name <code>HLAobjectRoot.PhysicalEntity.DynamicalEntity.Payload</code>) */
            PAYLOAD,
            /** Launcher, instance of <code>HlaLauncher</code> (FOM name <code>HLAobjectRoot.PhysicalEntity.Launcher</code>) */
            LAUNCHER,
            /** PhysicalInterface, instance of <code>HlaPhysicalInterface</code> (FOM name <code>HLAobjectRoot.PhysicalInterface</code>) */
            PHYSICAL_INTERFACE,
            /** ReferenceFrame, instance of <code>HlaReferenceFrame</code> (FOM name <code>HLAobjectRoot.ReferenceFrame</code>) */
            REFERENCE_FRAME,
            /** Moon, instance of <code>HlaMoon</code> (FOM name <code>HLAobjectRoot.ReferenceFrame.Moon</code>) */
            MOON,
            /** ExecutionConfiguration, instance of <code>HlaExecutionConfiguration</code> (FOM name <code>HLAobjectRoot.ExecutionConfiguration</code>) */
            EXECUTION_CONFIGURATION
        };

        /**
        * Tells if this object instance is local or remote.
        * An local object is an object that you have originally created.
        *
        * @return true if local.
        */
        LIBAPI virtual bool isLocal() const = 0;

        /**
        * Tells if this object instance is initialized.
        *
        * @return true if initialized.
        */
        LIBAPI virtual bool isInitialized() = 0;

        /**
        * Tells if this object instance is within interest.
        * A removed instance is never within interest.
        *
        * @return true if within interest.
        */
        LIBAPI virtual bool isWithinInterest() const = 0;

        /**
        * Tells if this object instance has been removed.
        *
        * @return true if removed.
        */
        LIBAPI virtual bool isRemoved() const = 0;

        /**
        * Get the <code>HLA instance name</code>.
        *
        * @return the <code>HLA instance name</code>.
        */
        LIBAPI virtual std::wstring getHlaInstanceName() const = 0;

        /**
        * Get the encoded <code>HLA instance handle</code>.
        *
        * @return the encoded <code>HLA instance handle</code>.
        */
        LIBAPI virtual std::vector<char> getEncodedHlaObjectInstanceHandle() const = 0;

        /**
        * Get the object class type for this object instance.
        *
        * @return the object class type for this object instance
        */
        LIBAPI virtual ObjectClassType getClassType() const = 0;

        /**
        * Get the HlaFederateId for the federate that created this instance
        *
        * @return The federate id for the federate that created this instance
        */
        LIBAPI virtual HlaFederateIdPtr getProducingFederate() const = 0;

        LIBAPI virtual ~HlaObjectInstanceBase() {}
    };
}
#endif
