/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef PITCH_SPATIAL_H_DEFINED
#define PITCH_SPATIAL_H_DEFINED

#include "pitch_geotypes.h"
#include "pitch_libsettings.h"

namespace RprUtility {

   /**
    * VelocityVector is used to express the speed of an object
    */
   typedef struct {
      /**
       * Speed in m/s along the x-axis
       */
      float xVelocity;
      /**
       * Speed in m/s along the y-axis
       */
      float yVelocity;
      /**
       * Speed in m/s along the z-axis
       */
      float zVelocity;
   } VelocityVector;

   /**
    * AngularVelocityVector is used to express the rotation speed of an object
    */
   typedef struct {
      /**
       * Rotation speed around the X-axis in rad/s
       */
      float xAngularVelocity;
      /**
       * Rotation speed around the Y-axis in rad/s
       */
      float yAngularVelocity;
      /**
       * Rotation speed around the Z-axis in rad/s
       */
      float zAngularVelocity;
   } AngularVelocityVector;

   /**
    * AccelerationVector is used to express the acceleration of an object
    */
   typedef struct {
      /**
       * Acceleration along the X-axis in m/s^2
       */
      float xAcceleration;
      /**
       * Acceleration along the Y-axis in m/s^2
       */
      float yAcceleration;
      /**
       * Acceleration along the Z-axis in m/s^2
       */
      float zAcceleration;
   } AccelerationVector;

   /**
    * The different dead-reckoning algorithms that a Spatial can use according to
    * the GRIM RPR
    */
   typedef enum {
      /**
       * Any other dead-reckoning algorithm not defined by the other alternatives
       */
      OTHER,

      /**
       * A static object, no dead-reckoning is performed
       */
      STATIC,

      /**
       * Position is extrapolated from velocity in world coordinate system.
       */
      DRM_FPW,

      /**
       * Rotation is extrapolated from angular velocities.
       * Position is extrapolated from velocity in world coordinate system.
       */
      DRM_RPW,

      /**
       * Rotation is extrapolated from angular velocities.
       * Position is extrapolated from velocity and acceleration in world coordinate system.
       */
      DRM_RVW,

      /**
       * Position is extrapolated from velocity and acceleration in world coordinate system.
       */
      DRM_FVW,

      /**
       * Position is extrapolated from velocity in body coordinate system.
       */
      DRM_FPB,

      /**
       * Rotation is extrapolated from angular velocities.
       * Position is extrapolated from velocity in body coordinate system.
       */
      DRM_RPB,

      /**
       * Rotation is extrapolated from angular velocities.
       * Position is extrapolated from velocity and acceleration in body coordinate system.
       */
      DRM_RVB,

      /**
       * Position is extrapolated from velocity and acceleration in body coordinate system.
       */
      DRM_FVB
   } DeadReckoningMethod;

   /**
    * No dead-reckoning is performed
    */
   typedef struct {
      /**
       * Coordinate in a geocentric coordinate system
       */
      WorldLocation worldLocation;

      /**
       * A frozen object is not moving
       */
      bool          isFrozen;

      /**
       * Orientation using euler angles
       */
      Orientation   orientation;
   } SpatialStructStatic;

   /**
    * Position is extrapolated from velocity
    */
   typedef struct {
      /**
       * Coordinate in a geocentric coordinate system
       */
      WorldLocation   worldLocation;

      /**
       * A frozen object is not moving
       */
      bool            isFrozen;

      /**
       * Orientation using euler angles
       */
      Orientation     orientation;

      /**
       * Speed of the object
       */
      VelocityVector  velocity;
   } SpatialStructFP;

   /**
    * Rotation is extrapolated from angular velocities.
    * Position is extrapolated from velocity
    */
   typedef struct {
      /**
       * Coordinate in a geocentric coordinate system
       */
      WorldLocation         worldLocation;

      /**
       * A frozen object is not moving
       */
      bool                  isFrozen;

      /**
       * Orientation using euler angles
       */
      Orientation           orientation;

      /**
       * Speed of the object
       */
      VelocityVector        velocity;

      /**
       * Rotation speed of the object
       */
      AngularVelocityVector angularVelocity;
   } SpatialStructRP;

   /**
    * Rotation is extrapolated from angular velocities.
    * Position is extrapolated from velocity and acceleration
    */
   typedef struct {
      /**
       * Coordinate in a geocentric coordinate system
       */
      WorldLocation         worldLocation;

      /**
       * A frozen object is not moving
       */
      bool                  isFrozen;

      /**
       * Orientation using euler angles
       */
      Orientation           orientation;

      /**
       * Speed of the object
       */
      VelocityVector        velocity;

      /**
       * Acceleration of the object
       */
      AccelerationVector    acceleration;

      /**
       * Rotation speed of the object
       */
      AngularVelocityVector angularVelocity;
   } SpatialStructRV;

   /**
    * Position is extrapolated from velocity and acceleration
    */
   typedef struct {
      /**
       * Coordinate in a geocentric coordinate system
       */
      WorldLocation      worldLocation;

      /**
       * A frozen object is not moving
       */
      bool               isFrozen;

      /**
       * Orientation using euler angles
       */
      Orientation        orientation;

      /**
       * Speed of the object
       */
      VelocityVector     velocity;

      /**
       * Acceleration of the object
       */
      AccelerationVector acceleration;
   } SpatialStructFV;


   /**
    * SpatialStruct contains a DeadReckoningMethod enum that is used
    * to indicate which dead-reckoning algorithm is currently stored in the
    * union. An alternative that ends with W uses world coordinates while
    * an alternative that ends with B uses body coordinates.
    */
   typedef struct {
      /**
       * Indicates with dead-reckoning algorithm is currently stored in the union
       */
      DeadReckoningMethod drm;
      union  {
         SpatialStructStatic spatialStatic;
         SpatialStructFP     spatialFPW;
         SpatialStructRP     spatialRPW;
         SpatialStructRV     spatialRVW;
         SpatialStructFV     spatialFVW;
         SpatialStructFP     spatialFPB;
         SpatialStructRP     spatialRPB;
         SpatialStructRV     spatialRVB;
         SpatialStructFV     spatialFVB;
      };
   } SpatialStruct;

   /**
    * Get the world location from a SpatialStruct
    *
    * @param spatial SpatialStruct to get world location from
    *
    * @return WorldLocation
    */
   RTIDRIVERDLL_API WorldLocation getWorldLocation(SpatialStruct spatial);

   /**
    * Get the orientation from a SpatialStruct
    *
    * @param spatial SpatialStruct to get orientation from
    *
    * @return Orientation
    */
   RTIDRIVERDLL_API Orientation getOrientation(SpatialStruct spatial);

   /**
    * If a SpatialStruct is frozen or not, i.e. not moving.
    *
    * @param spatial SpatialStruct
    *
    * @return bool true if frozen otherwise false
    */
   RTIDRIVERDLL_API bool getIsFrozen(SpatialStruct spatial);
}

#endif
