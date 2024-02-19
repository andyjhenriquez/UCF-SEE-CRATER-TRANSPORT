/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef PITCH_GEODETIC_H_DEFINED
#define PITCH_GEODETIC_H_DEFINED

#include "pitch_geotypes.h"
#include "pitch_libsettings.h"

/**
 * Class for conversion between geocentric and geodetic coordinates.
 * Note - The algorithms used for conversion are not accurate close to the north and south pole. Therefore it is not
 * recommended to use this package for latitudes above 89 degrees north or below 89 degrees south.
 */
namespace RprUtility {
   /**
    * Create a GeodeticLocation from x, y and z
    *
    * @param x [m]
    * @param y [m]
    * @param z [m]
    *
    * @return A GeodeticLocation
    */
   RTIDRIVERDLL_API GeodeticLocation createGeodeticLocationFromXYZ(double x, double y, double z);

   /**
    * Create a GeodeticLocation from a WorldLocation
    *
    * @param xyz WorldLocation
    *
    * @return A GeodeticLocation
    */
   RTIDRIVERDLL_API GeodeticLocation createGeodeticLocationFromWorldLocation(WorldLocation xyz);

   /**
    * Create a WorldLocation from a GeodeticLocation
    *
    * @param loc GeodeticLocation
    *
    * @return A WorldLocation
    */
   RTIDRIVERDLL_API WorldLocation createWorldLocationFromGeodeticLocation(GeodeticLocation loc);

   /**
    * Create a WorldLocation from latitude, longitude and altitude
    *
    * @param latitude [radians]
    * @param longitude [radians]
    * @param altitude (elevation) above reference ellipsoid. [m]
    *
    * @return A WorldLocation
    */
   RTIDRIVERDLL_API WorldLocation createWorldLocation(double latitude, double longitude, double altitude);

   /**
    * Radius att current latitude
    *
    * @return The radius [m]
    */
   RTIDRIVERDLL_API double earthRadius(GeodeticLocation loc);

   /**
    * Calculates great-circle distance between two GeodeticLocations along the spheroid surface. Altitudes of the two
    * GeodeticLocations are not taken into account.
    *
    * @param from A GeodeticLocation position to calculate distance from.
    * @param to A GeodeticLocation position to calculate distance to.
    *
    * @return Distance between positions [m]
    */
   RTIDRIVERDLL_API double distance(GeodeticLocation from, GeodeticLocation to);

   /**
    * Calculates absolute bearing between two GeodeticLocations.
    *
    * @param from A GeodeticLocation position to calculate bearing from.
    * @param to A GeodeticLocation position to calculate bearing to.
    *
    * @return Absolute bearing between positions in the range [0, 2*pi] [radians]
    */
   RTIDRIVERDLL_API double bearing(GeodeticLocation from, GeodeticLocation to);

   /**
    * Calculates a new GeodeticLocation based on a position, offset by a distance and absolute bearing, along the
    * spheroid surface. The same altitude is set on the new GeodeticLocation, but the altitude is not taken into
    * account when calculating the offset.
    *
    * @param from A GeodeticLocation position to calculate offset distance and bearing from.
    * @param distance The distance to the new offset point [m]
    * @param bearing  The bearing to the new offset point [radians]
    *
    * @return The new calculated GeodeticLocation.
    */
   RTIDRIVERDLL_API GeodeticLocation calculateOffset(GeodeticLocation from, double distance, double bearing);
}

#endif
