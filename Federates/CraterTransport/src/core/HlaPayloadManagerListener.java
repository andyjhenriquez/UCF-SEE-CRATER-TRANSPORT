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



/**
 * Listener for changes of HlaPayload instances.
 */
public interface HlaPayloadManagerListener {

   /**
    * This method is called when a new HlaPayload instance is discovered.
    * A discovered instance is initially within interest.
    *
    * @param payload the object which is discovered
    * @param timeStamp the time when the update was initiated
    */
    void hlaPayloadDiscovered(HlaPayload payload, HlaTimeStamp timeStamp);

   /**
    * This method is called when a HlaPayload instance is initialized.
    * An instance is initialized when it has been discovered and all attribute marked with
    * <i>initialized</i> has a value.
    *
    * @param payload the object which is initialized
    * @param timeStamp the time when the update was initiated
    * @param logicalTime the logical time when the update was initiated
    */
    void hlaPayloadInitialized(HlaPayload payload, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when a HlaPayload instance comes within interest.
    * A discovered instance is initially within interest, so this will not
    * be called at the time of discovery.
    *
    * @param payload the object which has come into interest
    * @param timeStamp the time when the update was initiated
    */
    void hlaPayloadInInterest(HlaPayload payload, HlaTimeStamp timeStamp);

   /**
    * This method is called when a HlaPayload instance goes out of interest.
    *
    * @param payload the object which has gone out of interest
    * @param timeStamp the time when the update was initiated
    */
    void hlaPayloadOutOfInterest(HlaPayload payload, HlaTimeStamp timeStamp);

   /**
    * This method is called when a HlaPayload instance is deleted.
    *
    * @param payload the object which is deleted
    * @param timeStamp the time when the update was initiated
    * @param logicalTime the logical time when the update was initiated
    */
    void hlaPayloadDeleted(HlaPayload payload, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * An abstract adapter class that implements the HlaPayloadManagerListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    public abstract static class Adapter implements HlaPayloadManagerListener {
        public void hlaPayloadDiscovered(HlaPayload payload, HlaTimeStamp timeStamp) {}
        public void hlaPayloadInitialized(HlaPayload payload, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void hlaPayloadInInterest(HlaPayload payload, HlaTimeStamp timeStamp) {}
        public void hlaPayloadOutOfInterest(HlaPayload payload, HlaTimeStamp timeStamp) {}
        public void hlaPayloadDeleted(HlaPayload payload, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
    }
}
