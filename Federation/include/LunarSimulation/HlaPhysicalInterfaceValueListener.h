/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPHYSICALINTERFACEVALUELISTENER_H
#define DEVELOPER_STUDIO_HLAPHYSICALINTERFACEVALUELISTENER_H

#include <memory>

#include <LunarSimulation/datatypes/AttitudeQuaternion.h>
#include <LunarSimulation/datatypes/PositionVector.h>
#include <string>
#include <vector>

#include <LunarSimulation/HlaLogicalTime.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaPhysicalInterfaceAttributes.h>    

namespace LunarSimulation {

   /**
   * Listener for updates of attributes, with the new updated values.  
   */
   class HlaPhysicalInterfaceValueListener {

   public:

      LIBAPI virtual ~HlaPhysicalInterfaceValueListener() {}
    
      /**
      * This method is called when the attribute <code>name</code> is updated.
      * <br>Description from the FOM: A non-empty string that identifies the interface. Each PhysicalInterface instance in the federation must have a unique name.
      * <br>Description of the data type from the FOM: 
      *
      * @param physicalInterface The object which is updated.
      * @param name The new value of the attribute in this update
      * @param validOldName True if oldName contains a valid value
      * @param oldName The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void nameUpdated(HlaPhysicalInterfacePtr physicalInterface, std::wstring name, bool validOldName, std::wstring oldName, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>parentName</code> is updated.
      * <br>Description from the FOM: The HLA Object Instance Name of the PhysicalEntity or PhysicalInterface to which this interface is attached.
      * <br>Description of the data type from the FOM: 
      *
      * @param physicalInterface The object which is updated.
      * @param parentName The new value of the attribute in this update
      * @param validOldParentName True if oldParentName contains a valid value
      * @param oldParentName The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void parentNameUpdated(HlaPhysicalInterfacePtr physicalInterface, std::wstring parentName, bool validOldParentName, std::wstring oldParentName, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>position</code> is updated.
      * <br>Description from the FOM: A 3-vector that specifies the position of the interface reference frame origin with respect to the parent structural reference frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param physicalInterface The object which is updated.
      * @param position The new value of the attribute in this update
      * @param validOldPosition True if oldPosition contains a valid value
      * @param oldPosition The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void positionUpdated(HlaPhysicalInterfacePtr physicalInterface, std::vector</* 3 */ double > position, bool validOldPosition, std::vector</* 3 */ double > oldPosition, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>attitude</code> is updated.
      * <br>Description from the FOM: An attitude quaternion of the interfaces reference frame ('subject frame') with respect to its parent structural reference frame ('referent frame').
      * <br>Description of the data type from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
      *
      * @param physicalInterface The object which is updated.
      * @param attitude The new value of the attribute in this update
      * @param validOldAttitude True if oldAttitude contains a valid value
      * @param oldAttitude The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void attitudeUpdated(HlaPhysicalInterfacePtr physicalInterface, AttitudeQuaternion attitude, bool validOldAttitude, AttitudeQuaternion oldAttitude, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
      /**
      * This method is called when the producing federate of an attribute is changed.
      * Only available when using HLA Evolved.
      *
      * @param physicalInterface The object which is updated.
      * @param attribute The attribute that now has a new producing federate
      * @param oldProducingFederate The federate handle of the old producing federate
      * @param newProducingFederate The federate handle of the new producing federate
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void producingFederateUpdated(HlaPhysicalInterfacePtr physicalInterface, HlaPhysicalInterfaceAttributes::Attribute attribute, HlaFederateIdPtr oldProducingFederate, HlaFederateIdPtr newProducingFederate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;

      class Adapter;
   };

   /**
   * An adapter class that implements the HlaPhysicalInterfaceValueListener interface with empty methods.
   * It might be used as a base class for a listener.
   */
   class HlaPhysicalInterfaceValueListener::Adapter : public HlaPhysicalInterfaceValueListener {

   public:

      LIBAPI virtual void nameUpdated(HlaPhysicalInterfacePtr physicalInterface, std::wstring name, bool validOldName, std::wstring oldName, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void parentNameUpdated(HlaPhysicalInterfacePtr physicalInterface, std::wstring parentName, bool validOldParentName, std::wstring oldParentName, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void positionUpdated(HlaPhysicalInterfacePtr physicalInterface, std::vector</* 3 */ double > position, bool validOldPosition, std::vector</* 3 */ double > oldPosition, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void attitudeUpdated(HlaPhysicalInterfacePtr physicalInterface, AttitudeQuaternion attitude, bool validOldAttitude, AttitudeQuaternion oldAttitude, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
      LIBAPI virtual void producingFederateUpdated(HlaPhysicalInterfacePtr physicalInterface, HlaPhysicalInterfaceAttributes::Attribute attribute, HlaFederateIdPtr oldProducingFederate, HlaFederateIdPtr newProducingFederate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
   };

}
#endif
