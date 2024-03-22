/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAMOONVALUELISTENER_H
#define DEVELOPER_STUDIO_HLAMOONVALUELISTENER_H

#include <memory>

#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>
#include <string>

#include <LunarSimulation/HlaLogicalTime.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaMoonAttributes.h>    

namespace LunarSimulation {

   /**
   * Listener for updates of attributes, with the new updated values.  
   */
   class HlaMoonValueListener {

   public:

      LIBAPI virtual ~HlaMoonValueListener() {}
    
      /**
      * This method is called when the attribute <code>name</code> is updated.
      * <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
      * <br>Description of the data type from the FOM: 
      *
      * @param moon The object which is updated.
      * @param name The new value of the attribute in this update
      * @param validOldName True if oldName contains a valid value
      * @param oldName The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void nameUpdated(HlaMoonPtr moon, std::wstring name, bool validOldName, std::wstring oldName, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>parentName</code> is updated.
      * <br>Description from the FOM: The name of this frame's parent reference frame. If this frame has no parent (i.e., is a 'root' reference frame), then this string must be empty, otherwise the non-empty string must correspond to the name attribute of some other ReferenceFrame object instance in the simulation.
      * <br>Description of the data type from the FOM: 
      *
      * @param moon The object which is updated.
      * @param parentName The new value of the attribute in this update
      * @param validOldParentName True if oldParentName contains a valid value
      * @param oldParentName The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void parentNameUpdated(HlaMoonPtr moon, std::wstring parentName, bool validOldParentName, std::wstring oldParentName, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>state</code> is updated.
      * <br>Description from the FOM: A four dimensional representation of the reference frame with respect to its parent reference frame.  If the parent fame is an empty string, then only the time dimension has meaning.
      * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
      *
      * @param moon The object which is updated.
      * @param state The new value of the attribute in this update
      * @param validOldState True if oldState contains a valid value
      * @param oldState The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void stateUpdated(HlaMoonPtr moon, SpaceTimeCoordinateState state, bool validOldState, SpaceTimeCoordinateState oldState, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
      /**
      * This method is called when the producing federate of an attribute is changed.
      * Only available when using HLA Evolved.
      *
      * @param moon The object which is updated.
      * @param attribute The attribute that now has a new producing federate
      * @param oldProducingFederate The federate handle of the old producing federate
      * @param newProducingFederate The federate handle of the new producing federate
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void producingFederateUpdated(HlaMoonPtr moon, HlaMoonAttributes::Attribute attribute, HlaFederateIdPtr oldProducingFederate, HlaFederateIdPtr newProducingFederate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;

      class Adapter;
   };

   /**
   * An adapter class that implements the HlaMoonValueListener interface with empty methods.
   * It might be used as a base class for a listener.
   */
   class HlaMoonValueListener::Adapter : public HlaMoonValueListener {

   public:

      LIBAPI virtual void nameUpdated(HlaMoonPtr moon, std::wstring name, bool validOldName, std::wstring oldName, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void parentNameUpdated(HlaMoonPtr moon, std::wstring parentName, bool validOldParentName, std::wstring oldParentName, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void stateUpdated(HlaMoonPtr moon, SpaceTimeCoordinateState state, bool validOldState, SpaceTimeCoordinateState oldState, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
      LIBAPI virtual void producingFederateUpdated(HlaMoonPtr moon, HlaMoonAttributes::Attribute attribute, HlaFederateIdPtr oldProducingFederate, HlaFederateIdPtr newProducingFederate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
   };

}
#endif
