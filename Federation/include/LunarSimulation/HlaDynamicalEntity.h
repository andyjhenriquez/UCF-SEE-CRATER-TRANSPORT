/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLADYNAMICALENTITY_H
#define DEVELOPER_STUDIO_HLADYNAMICALENTITY_H

#include <iostream>
#include <memory>
#include <vector>


#include <LunarSimulation/HlaObjectInstanceBase.h>
#include <LunarSimulation/HlaDynamicalEntityAttributes.h>
#include <LunarSimulation/HlaDynamicalEntityListener.h>
#include <LunarSimulation/HlaDynamicalEntityValueListener.h>
#include <LunarSimulation/HlaDynamicalEntityUpdater.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaFederateId.h>

namespace LunarSimulation {

    /**
    * Interface used to represent an object instance.
    */
    class HlaDynamicalEntity : public HlaDynamicalEntityAttributes , public HlaObjectInstanceBase {

    public:

        /**
        * Tells if this HlaDynamicalEntity object is local or remote.
        * A local object instance is an instance that you have originally created.
        *
        * @return true if local.
        */
        LIBAPI virtual bool isLocal() const = 0;

        /**
        * Tells if this HlaDynamicalEntity is initialized.
        * An object is initialized if all attributes marked with <i>Initialized</i> has a value.
        *
        * @return true if initialized.
        */
        LIBAPI virtual bool isInitialized() = 0;

        /**
        * Tells if this HlaDynamicalEntity is within interest.
        * A removed instance is never within interest.
        *
        * @return true if within interest.
        */
        LIBAPI virtual bool isWithinInterest() const = 0;

        /**
        * Tells if this HlaDynamicalEntity has been removed.
        *
        * @return true if removed.
        */
        LIBAPI virtual bool isRemoved() const = 0;

        /**
        * Gets an immutable snapshot of the HlaDynamicalEntity's attributes.
        * The attributes returned are always the most recent values available
        * for the attributes.
        *
        * @return attribute snapshot.
        */
        LIBAPI virtual HlaDynamicalEntityAttributesPtr getHlaDynamicalEntityAttributes() = 0;

        /**
        * Gets an updater.
        * The updater is used to update a set of attributes on the HlaDynamicalEntity in
        * an atomic fashion. The update object may only be used for at most
        * one update.
        *
        * @return updater object.
        */
        LIBAPI virtual HlaDynamicalEntityUpdaterPtr getHlaDynamicalEntityUpdater() = 0;

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
        LIBAPI virtual HlaObjectInstanceBase::ObjectClassType getClassType() const = 0;

        /**
        * Adds a listener.
        * The listener is notified when any attribute of this object is updated.
        * This listener is also called when an interaction is sent to this object.
        * This method is idempotent.
        *
        * To make sure that no attribute updates arrive before adding the listener,
        * use: @link HlaDynamicalEntityManager#addHlaDynamicalEntityDefaultInstanceListener(HlaDynamicalEntityListenerPtr listener)@endlink.
        *
        * @param listener The listener to add.
        */
        LIBAPI virtual void addHlaDynamicalEntityListener(HlaDynamicalEntityListenerPtr listener) = 0;

        /**
        * Removes a listener.
        * This method is idempotent. Trying to remove a nonregistered listener is equivalent to a no-op.
        *
        * @param listener The listener to remove.
        */
        LIBAPI virtual void removeHlaDynamicalEntityListener(HlaDynamicalEntityListenerPtr listener) = 0;

        /**
        * Adds a valueListener.
        * The valueListener is notified when any attribute of this object is updated.
        * Note that the attribute values that are notified are not guaranteed to
        * be the latest available values for that attribute.
        * This method is idempotent.
        *
        * To make sure that no attribute updates arrive before adding the listener,
        * use: @link HlaDynamicalEntityManager#addHlaDynamicalEntityDefaultInstanceValueListener(HlaDynamicalEntityValueListenerPtr valueListener)@endlink.
        *
        * @param valueListener The valueListener to add.
        */
        LIBAPI virtual void addHlaDynamicalEntityValueListener(HlaDynamicalEntityValueListenerPtr valueListener) = 0;

        /**
        * Removes a valueListener.
        * This method is idempotent. Trying to remove a nonregistered valueListener is equivalent to a no-op.
        *
        * @param valueListener The valueListener to remove.
        */
        LIBAPI virtual void removeHlaDynamicalEntityValueListener(HlaDynamicalEntityValueListenerPtr valueListener) = 0;

        /**
        * Get the HlaFederateId for the federate that created this HlaDynamicalEntity instance
        *
        * @return The federate id for the federate that created this instance
        */
        LIBAPI virtual HlaFederateIdPtr getProducingFederate() const = 0;

        /**
        * Get the HlaFederateId for the federate that last updated the given attribute.
        *
        * @param attribute the attribute to get the last producing federate for
        *
        * @return The federate id for the federate that last updated the attribute
        */
        LIBAPI virtual HlaFederateIdPtr getLastProducingFederate(HlaDynamicalEntityAttributes::Attribute attribute) = 0;
    };
}
#endif
