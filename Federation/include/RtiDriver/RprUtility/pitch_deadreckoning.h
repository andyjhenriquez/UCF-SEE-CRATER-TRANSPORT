/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef PITCH_DEADRECKONING_H_DEFINED
#define PITCH_DEADRECKONING_H_DEFINED

#include "pitch_spatial.h"
#include "pitch_libsettings.h"

namespace RprUtility {

   /**
    * Extrapolate Spatial to time defined by deltaTime.
    *
    * @param spatial0  The Spatial object to extrapolate from.
    * @param deltaTime The time increment to extrapolate the spatial to. [s]
    *
    * @return A Spatial extrapolated from spatial0 to the time increment deltaTime.
    */
   RTIDRIVERDLL_API SpatialStruct createExtrapolatedSpatial(SpatialStruct spatial0, double deltaTime);

   /**
    * Extrapolate Spatial to time defined by deltaTime.
    *
    * @param spatial0  The Spatial object to extrapolate from.
    * @param deltaTime The time increment to extrapolate the spatial to. [s]
    *
    * @return A Spatial extrapolated from spatial0 to the time increment deltaTime.
    *
    * @deprecated Replaced by createExtrapolatedSpatial()
    */
   RTIDRIVERDLL_API SpatialStruct extrapolate(SpatialStruct spatial0, double deltaTime);

   /**
    * Determine if this extrapolated spatial is outside default threshold limits.
    * This function always returns true if DRM is STATIC.
    * To minimize computation position threshold is tested individually for each axis (x,y,z).
    * To minimize computation rotation threshold is tested individually for each angle of rotation (phi, theta, psi).
    * If a more exact calculation of threshold is required this methods should not be used.
    * The default threshold limits are 1 m for position and 3 degrees for rotation.
    *
    * @param spatial   The Spatial
    * @param reference A reference Spatial to compare with.
    *
    * @return A boolean that is true if outside threshold limits.
    */
   RTIDRIVERDLL_API bool isOutsideThreshold(SpatialStruct spatial, SpatialStruct reference);

   /**
    * Determine if this extrapolated spatial is outside defined threshold limits.
    * This function always returns true if DRM is STATIC.
    * To minimize computation position threshold is tested individually for each axis (x,y,z).
    * To minimize computation rotation threshold is tested individually for each angle of rotation (phi, theta, psi).
    * If a more exact calculation of threshold is required this methods should not be used.
    *
    * @param spatial              The Spatial
    * @param reference            A reference Spatial to compare with.
    * @param positionThreshold    Threshold in [m] for position updates
    * @param orientationThreshold Threshold in [degrees] for orientation updates.
    *
    * @return A boolean that is true if outside threshold limits.
    */
   RTIDRIVERDLL_API bool isOutsideThreshold(SpatialStruct spatial, SpatialStruct reference,
                                            double positionThreshold, double orientationThreshold);

   /**
    * Calculate a Spatial in world coordinates for a relativeSpatial, and the Spatial that it
    * is attached to.
    *
    * @param attachedTo The Spatial for the entity that the relativeSpatial is attached to.
    * @param relativeSpatial A relative spatial.
    * @return The Spatial in world coordinates
    */
   RTIDRIVERDLL_API SpatialStruct getWorldSpatial(SpatialStruct attachedTo, SpatialStruct relativeSpatial);
}

#endif
