package core;

/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

import java.util.Set;


/**
 * Listener for updates of attributes.  
 */
public interface HlaPayloadListener {

   /**
    * This method is called when a HLA <code>reflectAttributeValueUpdate</code> is received for an remote object,
    * or a set of attributes is updated on a local object.
    *
    * @param payload The payload which this update corresponds to.
    * @param attributes The set of attributes that are updated.
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void attributesUpdated(HlaPayload payload, Set<HlaPayloadAttributes.Attribute> attributes, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * An abstract adapter class that implements the HlaPayloadListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    public abstract static class Adapter implements HlaPayloadListener {
        public void attributesUpdated(HlaPayload payload, Set<HlaPayloadAttributes.Attribute> attributes, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
    }
}
