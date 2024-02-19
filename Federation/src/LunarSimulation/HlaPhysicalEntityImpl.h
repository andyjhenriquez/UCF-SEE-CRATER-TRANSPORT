/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPHYSICALENTITYIMPL_H
#define DEVELOPER_STUDIO_HLAPHYSICALENTITYIMPL_H

#include <string>
#include <map>

#include <mutex>
#include <memory>

#include <RtiDriver/Types.h>

#include <LunarSimulation/HlaTimeStamped.h>


#include <LunarSimulation/HlaPhysicalEntity.h>
#include "ImplPointers.h"
#include "AttributeValue.h"
#include "ParameterValue.h"
#include "ListenerSet.h"


namespace LunarSimulation {

    class HlaWorldImpl;
    class HlaPhysicalEntityManagerImpl;

    class HlaPhysicalEntityImpl : public HlaPhysicalEntity , public std::enable_shared_from_this<HlaPhysicalEntityImpl> {
    private:
        bool _isLocal;
        HlaFederateIdImplPtr _createdByFederate;
        bool _initializeFired;
        bool _removed;
        HlaWorldImpl* _hlaWorld;
        HlaPhysicalEntityManagerImpl* _objectClassManager;
        ObjectInstanceHandlePtr _objectInstanceHandle;

        ListenerSet<HlaPhysicalEntityValueListenerPtr> _physicalEntityValueListeners;
        ListenerSet<HlaPhysicalEntityListenerPtr> _physicalEntityListeners;

        mutable std::recursive_mutex _attributesLock;
        mutable std::recursive_mutex _sendLock;

        AttributeValue<std::wstring > _nameAttribute;
        AttributeValue<std::wstring > _typeAttribute;
        AttributeValue<std::wstring > _statusAttribute;
        AttributeValue<std::wstring > _parentReferenceFrameAttribute;
        AttributeValue<LunarSimulation::SpaceTimeCoordinateState > _stateAttribute;
        AttributeValue<std::vector</* 3 */ double > > _accelerationAttribute;
        AttributeValue<std::vector</* 3 */ double > > _rotationalAccelerationAttribute;
        AttributeValue<std::vector</* 3 */ double > > _centerOfMassAttribute;
        AttributeValue<LunarSimulation::AttitudeQuaternion > _bodyWrtStructuralAttribute;

    public:
        typedef std::map<HlaPhysicalEntityAttributes::Attribute, std::shared_ptr<void> > AttributeMap;

        HlaPhysicalEntityImpl(HlaWorldImpl* hlaWorld, HlaPhysicalEntityManagerImpl* objectClassManager, ObjectInstanceHandlePtr objectInstanceHandle, bool local, const HlaFederateIdImplPtr federateId) :
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
            _physicalEntityValueListeners.clear();
            _physicalEntityListeners.clear();
        }

        bool isLocal() const {
            return _isLocal;
        }

        bool isRemoved() const {
            return _removed;
        }

        HlaPhysicalEntityAttributesPtr getHlaPhysicalEntityAttributes();

        HlaPhysicalEntityUpdaterPtr getHlaPhysicalEntityUpdater();

        std::wstring getHlaInstanceName() const;

        std::vector<char> getEncodedHlaObjectInstanceHandle() const;

        HlaObjectInstanceBase::ObjectClassType getClassType() const {
            return HlaObjectInstanceBase::PHYSICAL_ENTITY;
        }

        HlaFederateIdPtr getProducingFederate() const {
            return _createdByFederate;
        }

        HlaFederateIdPtr getLastProducingFederate(HlaPhysicalEntityAttributes::Attribute attribute);


        void addHlaPhysicalEntityListener(HlaPhysicalEntityListenerPtr listener);
        void removeHlaPhysicalEntityListener(HlaPhysicalEntityListenerPtr listener);
        void addHlaPhysicalEntityValueListener(HlaPhysicalEntityValueListenerPtr valueListener);
        void removeHlaPhysicalEntityValueListener(HlaPhysicalEntityValueListenerPtr valueListener);

        bool hasName();

        std::wstring getName()
            THROW_SPEC (HlaValueNotSetException);
        std::wstring getName(std::wstring defaultValue);

        LunarSimulation::HlaTimeStamped< std::wstring > getNameTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasType();

        std::wstring getType()
            THROW_SPEC (HlaValueNotSetException);
        std::wstring getType(std::wstring defaultValue);

        LunarSimulation::HlaTimeStamped< std::wstring > getTypeTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasStatus();

        std::wstring getStatus()
            THROW_SPEC (HlaValueNotSetException);
        std::wstring getStatus(std::wstring defaultValue);

        LunarSimulation::HlaTimeStamped< std::wstring > getStatusTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasParentReferenceFrame();

        std::wstring getParentReferenceFrame()
            THROW_SPEC (HlaValueNotSetException);
        std::wstring getParentReferenceFrame(std::wstring defaultValue);

        LunarSimulation::HlaTimeStamped< std::wstring > getParentReferenceFrameTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasState();

        LunarSimulation::SpaceTimeCoordinateState getState()
            THROW_SPEC (HlaValueNotSetException);
        LunarSimulation::SpaceTimeCoordinateState getState(LunarSimulation::SpaceTimeCoordinateState defaultValue);

        LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > getStateTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasAcceleration();

        std::vector</* 3 */ double > getAcceleration()
            THROW_SPEC (HlaValueNotSetException);
        std::vector</* 3 */ double > getAcceleration(std::vector</* 3 */ double > defaultValue);

        LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getAccelerationTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasRotationalAcceleration();

        std::vector</* 3 */ double > getRotationalAcceleration()
            THROW_SPEC (HlaValueNotSetException);
        std::vector</* 3 */ double > getRotationalAcceleration(std::vector</* 3 */ double > defaultValue);

        LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getRotationalAccelerationTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasCenterOfMass();

        std::vector</* 3 */ double > getCenterOfMass()
            THROW_SPEC (HlaValueNotSetException);
        std::vector</* 3 */ double > getCenterOfMass(std::vector</* 3 */ double > defaultValue);

        LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getCenterOfMassTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasBodyWrtStructural();

        LunarSimulation::AttitudeQuaternion getBodyWrtStructural()
            THROW_SPEC (HlaValueNotSetException);
        LunarSimulation::AttitudeQuaternion getBodyWrtStructural(LunarSimulation::AttitudeQuaternion defaultValue);

        LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > getBodyWrtStructuralTimeStamped()
            THROW_SPEC (HlaValueNotSetException);


        HlaFederateIdImplPtr getFederateIdImpl();

        /*
         * Functions used by HlaPhysicalEntityUpdaterImpl
         */

        void applyUpdate(const AttributeMap& attributeMap, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void reflectAttributeValues(const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);

        void provideAttributeValueUpdate(const RtiDriver::NameSet& attributes, HlaTimeStampPtr timeStamp);

        RtiDriver::NameSet getUnsetAttributeNames();


    private:

        HlaPhysicalEntityAttributesImplPtr applyUpdate(const AttributeMap& attributeMap, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void sendAttributes(const AttributeMap& attributeMap, HlaPhysicalEntityAttributesImplPtr attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);

        void firenameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateName();
        void firetypeUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateType();
        void firestatusUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateStatus();
        void fireparent_reference_frameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateParentReferenceFrame();
        void firestateUpdated(std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > value, const AttributeValue<LunarSimulation::SpaceTimeCoordinateState >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateState();
        void fireaccelerationUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateAcceleration();
        void firerotational_accelerationUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateRotationalAcceleration();
        void firecenter_of_massUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateCenterOfMass();
        void firebody_wrt_structuralUpdated(std::shared_ptr<LunarSimulation::AttitudeQuaternion > value, const AttributeValue<LunarSimulation::AttitudeQuaternion >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateBodyWrtStructural();

        void fireAttributesUpdated(const HlaEnumSet<HlaPhysicalEntityAttributes::Attribute> & attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireProducingFederateUpdated(HlaPhysicalEntityAttributes::Attribute attribute, const HlaFederateIdImplPtr oldFederateId, const HlaFederateIdImplPtr newFederateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);

        AttributeMap getAttributeMap(const RtiDriver::NameSet& attributeNames);

    };
}
#endif
