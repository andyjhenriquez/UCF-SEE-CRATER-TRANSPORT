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
 * Listener for changes of HlaMoon instances.
 */
public interface HlaMoonManagerListener {

   /**
    * This method is called when a new HlaMoon instance is discovered.
    * A discovered instance is initially within interest.
    *
    * @param moon the object which is discovered
    * @param timeStamp the time when the update was initiated
    */
    void hlaMoonDiscovered(HlaMoon moon, HlaTimeStamp timeStamp);

   /**
    * This method is called when a HlaMoon instance is initialized.
    * An instance is initialized when it has been discovered and all attribute marked with
    * <i>initialized</i> has a value.
    *
    * @param moon the object which is initialized
    * @param timeStamp the time when the update was initiated
    * @param logicalTime the logical time when the update was initiated
    */
    void hlaMoonInitialized(HlaMoon moon, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when a HlaMoon instance comes within interest.
    * A discovered instance is initially within interest, so this will not
    * be called at the time of discovery.
    *
    * @param moon the object which has come into interest
    * @param timeStamp the time when the update was initiated
    */
    void hlaMoonInInterest(HlaMoon moon, HlaTimeStamp timeStamp);

   /**
    * This method is called when a HlaMoon instance goes out of interest.
    *
    * @param moon the object which has gone out of interest
    * @param timeStamp the time when the update was initiated
    */
    void hlaMoonOutOfInterest(HlaMoon moon, HlaTimeStamp timeStamp);

   /**
    * This method is called when a HlaMoon instance is deleted.
    *
    * @param moon the object which is deleted
    * @param timeStamp the time when the update was initiated
    * @param logicalTime the logical time when the update was initiated
    */
    void hlaMoonDeleted(HlaMoon moon, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * An abstract adapter class that implements the HlaMoonManagerListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    public abstract static class Adapter implements HlaMoonManagerListener {
        public void hlaMoonDiscovered(HlaMoon moon, HlaTimeStamp timeStamp) {}
        public void hlaMoonInitialized(HlaMoon moon, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void hlaMoonInInterest(HlaMoon moon, HlaTimeStamp timeStamp) {}
        public void hlaMoonOutOfInterest(HlaMoon moon, HlaTimeStamp timeStamp) {}
        public void hlaMoonDeleted(HlaMoon moon, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
    }
}
