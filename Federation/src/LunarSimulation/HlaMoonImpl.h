/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAMOONIMPL_H
#define DEVELOPER_STUDIO_HLAMOONIMPL_H

#include <string>
#include <map>

#include <mutex>
#include <memory>

#include <RtiDriver/Types.h>

#include <LunarSimulation/HlaTimeStamped.h>


#include <LunarSimulation/HlaMoon.h>
#include "ImplPointers.h"
#include "AttributeValue.h"
#include "ParameterValue.h"
#include "ListenerSet.h"


namespace LunarSimulation {

    class HlaWorldImpl;
    class HlaMoonManagerImpl;

    class HlaMoonImpl : public HlaMoon , public std::enable_shared_from_this<HlaMoonImpl> {
    private:
        bool _isLocal;
        HlaFederateIdImplPtr _createdByFederate;
        bool _initializeFired;
        bool _removed;
        HlaWorldImpl* _hlaWorld;
        HlaMoonManagerImpl* _objectClassManager;
        ObjectInstanceHandlePtr _objectInstanceHandle;

        ListenerSet<HlaMoonValueListenerPtr> _moonValueListeners;
        ListenerSet<HlaMoonListenerPtr> _moonListeners;

        mutable std::recursive_mutex _attributesLock;
        mutable std::recursive_mutex _sendLock;

        AttributeValue<std::wstring > _nameAttribute;
        AttributeValue<std::wstring > _parentNameAttribute;
        AttributeValue<LunarSimulation::SpaceTimeCoordinateState > _stateAttribute;

    public:
        typedef std::map<HlaMoonAttributes::Attribute, std::shared_ptr<void> > AttributeMap;

        HlaMoonImpl(HlaWorldImpl* hlaWorld, HlaMoonManagerImpl* objectClassManager, ObjectInstanceHandlePtr objectInstanceHandle, bool local, const HlaFederateIdImplPtr federateId) :
            _isLocal(local),
            _createdByFederate(federateId),
            _initializeFired(false),
            _removed(false),
            _hlaWorld(hlaWorld),
            _objectClassManager(objectClassManager),
            _objectInstanceHandle(objectInstanceHandle)
        {}

        ObjectInstanceHandlePtr getObjectInstanceHandle() {
            return _objectInstanceHandle;
        }

        static RtiDriver::NameSet getAttributes();

        bool isInitialized();

        bool isWithinInterest() const;

        bool isInitializedFired() const {
            return _initializeFired;
        }

        void setInitializedFired() {
            _initializeFired = true;
        }

        void setRemoved() {
            _removed = true;
            _moonValueListeners.clear();
            _moonListeners.clear();
        }

        bool isLocal() const {
            return _isLocal;
        }

        bool isRemoved() const {
            return _removed;
        }

        HlaMoonAttributesPtr getHlaMoonAttributes();

        HlaMoonUpdaterPtr getHlaMoonUpdater();

        std::wstring getHlaInstanceName() const;

        std::vector<char> getEncodedHlaObjectInstanceHandle() const;

        HlaObjectInstanceBase::ObjectClassType getClassType() const {
            return HlaObjectInstanceBase::MOON;
        }

        HlaFederateIdPtr getProducingFederate() const {
            return _createdByFederate;
        }

        HlaFederateIdPtr getLastProducingFederate(HlaMoonAttributes::Attribute attribute);


        void addHlaMoonListener(HlaMoonListenerPtr listener);
        void removeHlaMoonListener(HlaMoonListenerPtr listener);
        void addHlaMoonValueListener(HlaMoonValueListenerPtr valueListener);
        void removeHlaMoonValueListener(HlaMoonValueListenerPtr valueListener);

        bool hasName();

        std::wstring getName()
            THROW_SPEC (HlaValueNotSetException);
        std::wstring getName(std::wstring defaultValue);

        LunarSimulation::HlaTimeStamped< std::wstring > getNameTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasParentName();

        std::wstring getParentName()
            THROW_SPEC (HlaValueNotSetException);
        std::wstring getParentName(std::wstring defaultValue);

        LunarSimulation::HlaTimeStamped< std::wstring > getParentNameTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasState();

        LunarSimulation::SpaceTimeCoordinateState getState()
            THROW_SPEC (HlaValueNotSetException);
        LunarSimulation::SpaceTimeCoordinateState getState(LunarSimulation::SpaceTimeCoordinateState defaultValue);

        LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > getStateTimeStamped()
            THROW_SPEC (HlaValueNotSetException);


        HlaFederateIdImplPtr getFederateIdImpl();

        /*
         * Functions used by HlaMoonUpdaterImpl
         */

        void applyUpdate(const AttributeMap& attributeMap, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void reflectAttributeValues(const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);

        void provideAttributeValueUpdate(const RtiDriver::NameSet& attributes, HlaTimeStampPtr timeStamp);

        RtiDriver::NameSet getUnsetAttributeNames();


    private:

        HlaMoonAttributesImplPtr applyUpdate(const AttributeMap& attributeMap, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void sendAttributes(const AttributeMap& attributeMap, HlaMoonAttributesImplPtr attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);

        void firenameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateName();
        void fireparent_nameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateParentName();
        void firestateUpdated(std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > value, const AttributeValue<LunarSimulation::SpaceTimeCoordinateState >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateState();

        void fireAttributesUpdated(const HlaEnumSet<HlaMoonAttributes::Attribute> & attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireProducingFederateUpdated(HlaMoonAttributes::Attribute attribute, const HlaFederateIdImplPtr oldFederateId, const HlaFederateIdImplPtr newFederateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);

        AttributeMap getAttributeMap(const RtiDriver::NameSet& attributeNames);

    };
}
#endif
