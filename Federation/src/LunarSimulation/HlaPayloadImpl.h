/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPAYLOADIMPL_H
#define DEVELOPER_STUDIO_HLAPAYLOADIMPL_H

#include <string>
#include <map>

#include <mutex>
#include <memory>

#include <RtiDriver/Types.h>

#include <LunarSimulation/HlaTimeStamped.h>


#include <LunarSimulation/HlaPayload.h>
#include "ImplPointers.h"
#include "AttributeValue.h"
#include "ParameterValue.h"
#include "ListenerSet.h"


namespace LunarSimulation {

    class HlaWorldImpl;
    class HlaPayloadManagerImpl;

    class HlaPayloadImpl : public HlaPayload , public std::enable_shared_from_this<HlaPayloadImpl> {
    private:
        bool _isLocal;
        HlaFederateIdImplPtr _createdByFederate;
        bool _initializeFired;
        bool _removed;
        HlaWorldImpl* _hlaWorld;
        HlaPayloadManagerImpl* _objectClassManager;
        ObjectInstanceHandlePtr _objectInstanceHandle;

        ListenerSet<HlaPayloadValueListenerPtr> _payloadValueListeners;
        ListenerSet<HlaPayloadListenerPtr> _payloadListeners;

        mutable std::recursive_mutex _attributesLock;
        mutable std::recursive_mutex _sendLock;

        AttributeValue<std::vector</* 3 */ double > > _positionAttribute;
        AttributeValue<std::vector</* 3 */ double > > _velocityAttribute;
        AttributeValue<double > _healthAttribute;
        AttributeValue<std::vector</* 3 */ double > > _forceAttribute;
        AttributeValue<std::vector</* 3 */ double > > _torqueAttribute;
        AttributeValue<double > _massAttribute;
        AttributeValue<double > _massRateAttribute;
        AttributeValue<std::vector</* 9 */ double > > _inertiaAttribute;
        AttributeValue<std::vector</* 9 */ double > > _inertiaRateAttribute;
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
        typedef std::map<HlaPayloadAttributes::Attribute, std::shared_ptr<void> > AttributeMap;

        HlaPayloadImpl(HlaWorldImpl* hlaWorld, HlaPayloadManagerImpl* objectClassManager, ObjectInstanceHandlePtr objectInstanceHandle, bool local, const HlaFederateIdImplPtr federateId) :
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
            _payloadValueListeners.clear();
            _payloadListeners.clear();
        }

        bool isLocal() const {
            return _isLocal;
        }

        bool isRemoved() const {
            return _removed;
        }

        HlaPayloadAttributesPtr getHlaPayloadAttributes();

        HlaPayloadUpdaterPtr getHlaPayloadUpdater();

        std::wstring getHlaInstanceName() const;

        std::vector<char> getEncodedHlaObjectInstanceHandle() const;

        HlaObjectInstanceBase::ObjectClassType getClassType() const {
            return HlaObjectInstanceBase::PAYLOAD;
        }

        HlaFederateIdPtr getProducingFederate() const {
            return _createdByFederate;
        }

        HlaFederateIdPtr getLastProducingFederate(HlaPayloadAttributes::Attribute attribute);


        void addHlaPayloadListener(HlaPayloadListenerPtr listener);
        void removeHlaPayloadListener(HlaPayloadListenerPtr listener);
        void addHlaPayloadValueListener(HlaPayloadValueListenerPtr valueListener);
        void removeHlaPayloadValueListener(HlaPayloadValueListenerPtr valueListener);

        bool hasPosition();

        std::vector</* 3 */ double > getPosition()
            THROW_SPEC (HlaValueNotSetException);
        std::vector</* 3 */ double > getPosition(std::vector</* 3 */ double > defaultValue);

        LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getPositionTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasVelocity();

        std::vector</* 3 */ double > getVelocity()
            THROW_SPEC (HlaValueNotSetException);
        std::vector</* 3 */ double > getVelocity(std::vector</* 3 */ double > defaultValue);

        LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getVelocityTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasHealth();

        double getHealth()
            THROW_SPEC (HlaValueNotSetException);
        double getHealth(double defaultValue);

        LunarSimulation::HlaTimeStamped< double > getHealthTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasForce();

        std::vector</* 3 */ double > getForce()
            THROW_SPEC (HlaValueNotSetException);
        std::vector</* 3 */ double > getForce(std::vector</* 3 */ double > defaultValue);

        LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getForceTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasTorque();

        std::vector</* 3 */ double > getTorque()
            THROW_SPEC (HlaValueNotSetException);
        std::vector</* 3 */ double > getTorque(std::vector</* 3 */ double > defaultValue);

        LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getTorqueTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasMass();

        double getMass()
            THROW_SPEC (HlaValueNotSetException);
        double getMass(double defaultValue);

        LunarSimulation::HlaTimeStamped< double > getMassTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasMassRate();

        double getMassRate()
            THROW_SPEC (HlaValueNotSetException);
        double getMassRate(double defaultValue);

        LunarSimulation::HlaTimeStamped< double > getMassRateTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasInertia();

        std::vector</* 9 */ double > getInertia()
            THROW_SPEC (HlaValueNotSetException);
        std::vector</* 9 */ double > getInertia(std::vector</* 9 */ double > defaultValue);

        LunarSimulation::HlaTimeStamped< std::vector</* 9 */ double > > getInertiaTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasInertiaRate();

        std::vector</* 9 */ double > getInertiaRate()
            THROW_SPEC (HlaValueNotSetException);
        std::vector</* 9 */ double > getInertiaRate(std::vector</* 9 */ double > defaultValue);

        LunarSimulation::HlaTimeStamped< std::vector</* 9 */ double > > getInertiaRateTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

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
         * Functions used by HlaPayloadUpdaterImpl
         */

        void applyUpdate(const AttributeMap& attributeMap, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void reflectAttributeValues(const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);

        void provideAttributeValueUpdate(const RtiDriver::NameSet& attributes, HlaTimeStampPtr timeStamp);

        RtiDriver::NameSet getUnsetAttributeNames();


    private:

        HlaPayloadAttributesImplPtr applyUpdate(const AttributeMap& attributeMap, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void sendAttributes(const AttributeMap& attributeMap, HlaPayloadAttributesImplPtr attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);

        void firepositionUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updatePosition();
        void firevelocityUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateVelocity();
        void firehealthUpdated(std::shared_ptr<double > value, const AttributeValue<double >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateHealth();
        void fireforceUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateForce();
        void firetorqueUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateTorque();
        void firemassUpdated(std::shared_ptr<double > value, const AttributeValue<double >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateMass();
        void firemass_rateUpdated(std::shared_ptr<double > value, const AttributeValue<double >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateMassRate();
        void fireinertiaUpdated(std::shared_ptr<std::vector</* 9 */ double > > value, const AttributeValue<std::vector</* 9 */ double > >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateInertia();
        void fireinertia_rateUpdated(std::shared_ptr<std::vector</* 9 */ double > > value, const AttributeValue<std::vector</* 9 */ double > >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateInertiaRate();
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

        void fireAttributesUpdated(const HlaEnumSet<HlaPayloadAttributes::Attribute> & attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireProducingFederateUpdated(HlaPayloadAttributes::Attribute attribute, const HlaFederateIdImplPtr oldFederateId, const HlaFederateIdImplPtr newFederateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);

        AttributeMap getAttributeMap(const RtiDriver::NameSet& attributeNames);

    };
}
#endif
