/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPHYSICALINTERFACEIMPL_H
#define DEVELOPER_STUDIO_HLAPHYSICALINTERFACEIMPL_H

#include <string>
#include <map>

#include <mutex>
#include <memory>

#include <RtiDriver/Types.h>

#include <LunarSimulation/HlaTimeStamped.h>


#include <LunarSimulation/HlaPhysicalInterface.h>
#include "ImplPointers.h"
#include "AttributeValue.h"
#include "ParameterValue.h"
#include "ListenerSet.h"


namespace LunarSimulation {

    class HlaWorldImpl;
    class HlaPhysicalInterfaceManagerImpl;

    class HlaPhysicalInterfaceImpl : public HlaPhysicalInterface , public std::enable_shared_from_this<HlaPhysicalInterfaceImpl> {
    private:
        bool _isLocal;
        HlaFederateIdImplPtr _createdByFederate;
        bool _initializeFired;
        bool _removed;
        HlaWorldImpl* _hlaWorld;
        HlaPhysicalInterfaceManagerImpl* _objectClassManager;
        ObjectInstanceHandlePtr _objectInstanceHandle;

        ListenerSet<HlaPhysicalInterfaceValueListenerPtr> _physicalInterfaceValueListeners;
        ListenerSet<HlaPhysicalInterfaceListenerPtr> _physicalInterfaceListeners;

        mutable std::recursive_mutex _attributesLock;
        mutable std::recursive_mutex _sendLock;

        AttributeValue<std::wstring > _nameAttribute;
        AttributeValue<std::wstring > _parentNameAttribute;
        AttributeValue<std::vector</* 3 */ double > > _positionAttribute;
        AttributeValue<LunarSimulation::AttitudeQuaternion > _attitudeAttribute;

    public:
        typedef std::map<HlaPhysicalInterfaceAttributes::Attribute, std::shared_ptr<void> > AttributeMap;

        HlaPhysicalInterfaceImpl(HlaWorldImpl* hlaWorld, HlaPhysicalInterfaceManagerImpl* objectClassManager, ObjectInstanceHandlePtr objectInstanceHandle, bool local, const HlaFederateIdImplPtr federateId) :
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
            _physicalInterfaceValueListeners.clear();
            _physicalInterfaceListeners.clear();
        }

        bool isLocal() const {
            return _isLocal;
        }

        bool isRemoved() const {
            return _removed;
        }

        HlaPhysicalInterfaceAttributesPtr getHlaPhysicalInterfaceAttributes();

        HlaPhysicalInterfaceUpdaterPtr getHlaPhysicalInterfaceUpdater();

        std::wstring getHlaInstanceName() const;

        std::vector<char> getEncodedHlaObjectInstanceHandle() const;

        HlaObjectInstanceBase::ObjectClassType getClassType() const {
            return HlaObjectInstanceBase::PHYSICAL_INTERFACE;
        }

        HlaFederateIdPtr getProducingFederate() const {
            return _createdByFederate;
        }

        HlaFederateIdPtr getLastProducingFederate(HlaPhysicalInterfaceAttributes::Attribute attribute);


        void addHlaPhysicalInterfaceListener(HlaPhysicalInterfaceListenerPtr listener);
        void removeHlaPhysicalInterfaceListener(HlaPhysicalInterfaceListenerPtr listener);
        void addHlaPhysicalInterfaceValueListener(HlaPhysicalInterfaceValueListenerPtr valueListener);
        void removeHlaPhysicalInterfaceValueListener(HlaPhysicalInterfaceValueListenerPtr valueListener);

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

        bool hasPosition();

        std::vector</* 3 */ double > getPosition()
            THROW_SPEC (HlaValueNotSetException);
        std::vector</* 3 */ double > getPosition(std::vector</* 3 */ double > defaultValue);

        LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getPositionTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasAttitude();

        LunarSimulation::AttitudeQuaternion getAttitude()
            THROW_SPEC (HlaValueNotSetException);
        LunarSimulation::AttitudeQuaternion getAttitude(LunarSimulation::AttitudeQuaternion defaultValue);

        LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > getAttitudeTimeStamped()
            THROW_SPEC (HlaValueNotSetException);


        HlaFederateIdImplPtr getFederateIdImpl();

        /*
         * Functions used by HlaPhysicalInterfaceUpdaterImpl
         */

        void applyUpdate(const AttributeMap& attributeMap, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void reflectAttributeValues(const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);

        void provideAttributeValueUpdate(const RtiDriver::NameSet& attributes, HlaTimeStampPtr timeStamp);

        RtiDriver::NameSet getUnsetAttributeNames();


    private:

        HlaPhysicalInterfaceAttributesImplPtr applyUpdate(const AttributeMap& attributeMap, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void sendAttributes(const AttributeMap& attributeMap, HlaPhysicalInterfaceAttributesImplPtr attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);

        void firenameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateName();
        void fireparent_nameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateParentName();
        void firepositionUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updatePosition();
        void fireattitudeUpdated(std::shared_ptr<LunarSimulation::AttitudeQuaternion > value, const AttributeValue<LunarSimulation::AttitudeQuaternion >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateAttitude();

        void fireAttributesUpdated(const HlaEnumSet<HlaPhysicalInterfaceAttributes::Attribute> & attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireProducingFederateUpdated(HlaPhysicalInterfaceAttributes::Attribute attribute, const HlaFederateIdImplPtr oldFederateId, const HlaFederateIdImplPtr newFederateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);

        AttributeMap getAttributeMap(const RtiDriver::NameSet& attributeNames);

    };
}
#endif
