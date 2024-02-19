/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef PITCH_TRANSFORMEDSPATIAL_H_DEFINED
#define PITCH_TRANSFORMEDSPATIAL_H_DEFINED

#include "pitch_spatial.h"
#include "pitch_libsettings.h"

namespace RprUtility {

   /**
    * Reference coordinate systems for transformations. All coordinate systems are right-handed.
    */
   typedef enum {
      /**
       * World geocentric cartesian.
       *
       * X-axis at the equator, aligned with the 0 degree meridian
       * Y-axis at the equator, aligned with the 90 degree east meridian
       * Z-axis aligned with the north pole
       */
      WORLD,

      /**
       * Local Tangent Plane Coordinate System.
       *
       * X-axis pointing North, parallel with the surface
       * Y-axis pointing East, parallel with the surface
       * Z-axis pointing down, 90 degrees angle to surface
       */
      NORTH_EAST_DOWN,

      /**
       * Local Tangent Plane Coordinate System.
       *
       * X-axis pointing East, parallel with the surface
       * Y-axis pointing North, parallel with the surface
       * Z-axis pointing Up, 90 degrees angle to surface
       */
      EAST_NORTH_UP,

      /**
       * A coordinate system aligned with the Body (Entity Coordinate System) of the entity.
       *
       * X-axis pointing forward.
       * Y-axis pointing to the right
       * Z-axis pointing down.
       */
      BODY

   } ReferenceSystem;

   /**
    * A TransformedSpatial is a representation of a Spatial transformed to a local coordinate system.
    * The local coordinate system is based on a geodetic location (latitude, longitude)
    */
   typedef struct {

      /**
       * Local orientation
       */
      Orientation localOrientation;

      /**
       * Local velocity vector
       */
      VelocityVector localVelocity;

      /**
       * Local acceleration vector
       */
      AccelerationVector localAcceleration;

      /**
       * Body angular velocity
       */
      AngularVelocityVector bodyAngularVelocity;

      /**
       * The GeodeticLocation for this transformed spatial, ie the local coordinate system reference.
       */
      GeodeticLocation latlon;

   } TransformedSpatial;

   /**
    * Creates a transformed spatial from a SpatialStruct.
    *
    * @param spatial              The Spatial defined in a world geocentric cartesian coordinate system
    * @param orientationReference The reference frame for orientation
    * @param vectorReference      The reference frame for vectors (velocity and acceleration)
    *
    * @return the transformed spatial
    */
   RTIDRIVERDLL_API TransformedSpatial getTransformedSpatial(SpatialStruct spatial,
                                                             ReferenceSystem orientationReference,
                                                             ReferenceSystem vectorReference);

   /**
    * Get a SpatialStruct from a TransformedSpatial
    *
    * @param orientationReference The reference frame for orientation
    * @param vectorReference      The reference frame for vectors (velocity and acceleration)
    * @param drm                  The DeadReckoningMethod alternative that should be created
    * @param transformed          The TransformedSpatial that should be used for calculations
    *
    * @return The orientation
    */
   RTIDRIVERDLL_API SpatialStruct getSpatialFromTransformedSpatial(ReferenceSystem orientationReference,
                                                                   ReferenceSystem vectorReference,
                                                                   DeadReckoningMethod drm,
                                                                   TransformedSpatial transformed);

   /**
    * Get orientation in the world reference system, based on this local ReferenceSystem.
    *
    * @param orientationReference The reference frame for orientation
    * @param referenceLocation    The origin for local reference coordinate system.
    * @param localOrientation     Orientation defined in local reference system.
    *
    * @return The orientation
    */
   RTIDRIVERDLL_API Orientation getOrientationWorld(ReferenceSystem orientationReference,
                                                    GeodeticLocation referenceLocation,
                                                    Orientation localOrientation);
}

#endif
