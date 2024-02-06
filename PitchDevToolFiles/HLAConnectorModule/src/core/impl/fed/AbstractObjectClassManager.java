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

import se.pitch.ral.api.ObjectClassHandle;
import se.pitch.ral.api.ObjectInstanceHandle;

import java.util.Set;


public abstract class AbstractObjectClassManager {
   public abstract void discoverObjectInstance(ObjectInstanceHandle objectInstanceHandle,
                                               String instanceName, HlaTimeStamp timeStamp,
                                               HlaFederateId producingFederate);

   public abstract void reflectAttributeValues(ObjectInstanceHandle objectInstanceHandle, NameValueMap attributes,
                                               HlaTimeStamp timeStamp, HlaLogicalTime logicalTime,
                                               HlaFederateId producingFederate);

   public abstract void removeObjectInstance(ObjectInstanceHandle objectInstanceHandle, HlaTimeStamp timeStamp,
                                             HlaLogicalTime logicalTime);

   public abstract boolean isEnabled(String objectClassName);
   public abstract boolean isOptional(String objectClassName);

   public abstract void connected(ObjectClassHandle objectClassHandle, String objectClassName)
      throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
             HlaSaveInProgressException, HlaRestoreInProgressException;

   public abstract void disconnected(ObjectClassHandle objectClassHandle);

   public abstract void provideAttributeValueUpdate(ObjectInstanceHandle objectInstanceHandle, Set<String> attributes,
                                                    HlaTimeStamp timeStamp);

   public abstract void attributesInScope(ObjectInstanceHandle objectInstanceHandle, Set<String> attributes);

   public abstract void attributesOutOfScope(ObjectInstanceHandle objectInstanceHandle, Set<String> attributes);

   public abstract void save(ObjectClassHandle objectClassHandle) throws HlaSaveFederateException;

   public abstract void restore(ObjectClassHandle objectClassHandle) throws HlaRestoreFederateException;
}
