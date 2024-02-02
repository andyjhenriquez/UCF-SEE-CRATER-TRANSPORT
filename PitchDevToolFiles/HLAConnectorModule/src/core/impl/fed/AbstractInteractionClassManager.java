package core.impl.fed;

/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

import core.HlaFederateId;
import core.HlaLogicalTime;
import core.HlaTimeStamp;
import core.exceptions.*;
import core.impl.utils.NameValueMap;

import se.pitch.ral.api.InteractionClassHandle;


public abstract class AbstractInteractionClassManager {
   public abstract void receiveInteraction(InteractionClassHandle interactionClassHandle, NameValueMap parameters,
                                           HlaTimeStamp hlaTimeStamp, HlaLogicalTime logicalTime,
                                           HlaFederateId producingFederate);

   public abstract boolean isEnabled(String interactionClassName);
   public abstract boolean isOptional(String interactionClassName);

   public abstract void connected(InteractionClassHandle interactionClassHandle, String interactionClassName)
      throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
             HlaSaveInProgressException, HlaRestoreInProgressException;

   public abstract void disconnected(InteractionClassHandle interactionClassHandle);
}
