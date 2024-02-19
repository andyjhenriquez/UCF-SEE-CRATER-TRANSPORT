/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAHLAOBJECTROOTIMPL_H
#define DEVELOPER_STUDIO_HLAHLAOBJECTROOTIMPL_H

#include <string>
#include <map>

#include <mutex>
#include <memory>

#include <RtiDriver/Types.h>

#include <LunarSimulation/HlaTimeStamped.h>


#include <LunarSimulation/HlaHLAobjectRoot.h>
#include "ImplPointers.h"
#include "AttributeValue.h"
#include "ParameterValue.h"
#include "ListenerSet.h"


namespace LunarSimulation {

    class HlaWorldImpl;
    class HlaHLAobjectRootManagerImpl;

    class HlaHLAobjectRootImpl : public HlaHLAobjectRoot , public std::enable_shared_from_this<HlaHLAobjectRootImpl> {
    private:
        bool _isLocal;
        HlaFederateIdImplPtr _createdByFederate;
        bool _initializeFired;
        bool _removed;
        HlaWorldImpl* _hlaWorld;
        HlaHLAobjectRootManagerImpl* _objectClassManager;
        ObjectInstanceHandlePtr _objectInstanceHandle;

        ListenerSet<HlaHLAobjectRootValueListenerPtr> _hLAobjectRootValueListeners;
        ListenerSet<HlaHLAobjectRootListenerPtr> _hLAobjectRootListeners;

        mutable std::recursive_mutex _attributesLock;
        mutable std::recursive_mutex _sendLock;


    public:
        typedef std::map<HlaHLAobjectRootAttributes::Attribute, std::shared_ptr<void> > AttributeMap;

        HlaHLAobjectRootImpl(HlaWorldImpl* hlaWorld, HlaHLAobjectRootManagerImpl* objectClassManager, ObjectInstanceHandlePtr objectInstanceHandle, bool local, const HlaFederateIdImplPtr federateId) :
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
            _hLAobjectRootValueListeners.clear();
            _hLAobjectRootListeners.clear();
        }

        bool isLocal() const {
            return _isLocal;
        }

        bool isRemoved() const {
            return _removed;
        }

        HlaHLAobjectRootAttributesPtr getHlaHLAobjectRootAttributes();

        HlaHLAobjectRootUpdaterPtr getHlaHLAobjectRootUpdater();

        std::wstring getHlaInstanceName() const;

        std::vector<char> getEncodedHlaObjectInstanceHandle() const;

        HlaObjectInstanceBase::ObjectClassType getClassType() const {
            return HlaObjectInstanceBase::HLAOBJECT_ROOT;
        }

        HlaFederateIdPtr getProducingFederate() const {
            return _createdByFederate;
        }


        void addHlaHLAobjectRootListener(HlaHLAobjectRootListenerPtr listener);
        void removeHlaHLAobjectRootListener(HlaHLAobjectRootListenerPtr listener);
        void addHlaHLAobjectRootValueListener(HlaHLAobjectRootValueListenerPtr valueListener);
        void removeHlaHLAobjectRootValueListener(HlaHLAobjectRootValueListenerPtr valueListener);


        HlaFederateIdImplPtr getFederateIdImpl();

        /*
         * Functions used by HlaHLAobjectRootUpdaterImpl
         */

        void applyUpdate(const AttributeMap& attributeMap, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void reflectAttributeValues(const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);

        void provideAttributeValueUpdate(const RtiDriver::NameSet& attributes, HlaTimeStampPtr timeStamp);

        RtiDriver::NameSet getUnsetAttributeNames();


    private:

        HlaHLAobjectRootAttributesImplPtr applyUpdate(const AttributeMap& attributeMap, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void sendAttributes(const AttributeMap& attributeMap, HlaHLAobjectRootAttributesImplPtr attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);


        void fireAttributesUpdated(const HlaEnumSet<HlaHLAobjectRootAttributes::Attribute> & attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);

        AttributeMap getAttributeMap(const RtiDriver::NameSet& attributeNames);

    };
}
#endif
