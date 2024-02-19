/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef PITCH_GEOTYPES_H_DEFINED
#define PITCH_GEOTYPES_H_DEFINED

/*
 * Constants for the WGS84 ellipsoid
 */
#define WGS84_A 6378137.0 
#define WGS84_F (1.0 / 298.257223563)

namespace RprUtility {

   /**
    * An Ellipsoid data structure.
    */
   typedef struct {
      /**
       * Semi-major axis
       */
      double a;
      /**
       * Flattening constant
       */
      double f;
   } Ellipsoid;

   /**
    * The WGS84 ellipsoid
    */
   static const Ellipsoid wgs84_ellipsoid = {WGS84_A, WGS84_F};

   /**
    * Orientation uses the Euler angles psi, theta and phi
    */
   typedef struct {
      /**
       * Rotation around the Z-axis in radians
       */
      double psi;
      /**
       * Rotation around the Y-axis in radians
       */
      double theta;
      /**
       * Rotation around the X-axis in radians
       */
      double phi;
   } Orientation;

   /**
    * GeodeticLocation represents a coordinate in a geodetic coordinate system
    */
   typedef struct {
      /**
       * Distance from the equator in radians [-pi/2, pi/2]
       */
      double latitude;
      /**
       * Distance from the Greenwich Meridian in radians [-pi, pi]
       */
      double longitude;
      /**
       * Height in meters
       */
      double altitude;
   } GeodeticLocation;

   /**
    * WorldLocation represents a 3-dimensional cartesian coordinate in an earth
    * centered coordinate system.
    */
   typedef struct {
      /**
       * The X axis is aligned with the 0 degrees Meridian at the equator
       */
      double x;
      /**
       * The Y axis is aligned with the 90 degrees Meridian at the equator
       */
      double y;
      /**
       * The Z axis is aligned with the north pole
       */
      double z;
   } WorldLocation;
}
#endif
