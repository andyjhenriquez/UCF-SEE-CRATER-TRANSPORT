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
 * Listener for changes of HlaLauncher instances.
 */
public interface HlaLauncherManagerListener {

   /**
    * This method is called when a new HlaLauncher instance is discovered.
    * A discovered instance is initially within interest.
    *
    * @param launcher the object which is discovered
    * @param timeStamp the time when the update was initiated
    */
    void hlaLauncherDiscovered(HlaLauncher launcher, HlaTimeStamp timeStamp);

   /**
    * This method is called when a HlaLauncher instance is initialized.
    * An instance is initialized when it has been discovered and all attribute marked with
    * <i>initialized</i> has a value.
    *
    * @param launcher the object which is initialized
    * @param timeStamp the time when the update was initiated
    * @param logicalTime the logical time when the update was initiated
    */
    void hlaLauncherInitialized(HlaLauncher launcher, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when a HlaLauncher instance comes within interest.
    * A discovered instance is initially within interest, so this will not
    * be called at the time of discovery.
    *
    * @param launcher the object which has come into interest
    * @param timeStamp the time when the update was initiated
    */
    void hlaLauncherInInterest(HlaLauncher launcher, HlaTimeStamp timeStamp);

   /**
    * This method is called when a HlaLauncher instance goes out of interest.
    *
    * @param launcher the object which has gone out of interest
    * @param timeStamp the time when the update was initiated
    */
    void hlaLauncherOutOfInterest(HlaLauncher launcher, HlaTimeStamp timeStamp);

   /**
    * This method is called when a HlaLauncher instance is deleted.
    *
    * @param launcher the object which is deleted
    * @param timeStamp the time when the update was initiated
    * @param logicalTime the logical time when the update was initiated
    */
    void hlaLauncherDeleted(HlaLauncher launcher, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * An abstract adapter class that implements the HlaLauncherManagerListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    public abstract static class Adapter implements HlaLauncherManagerListener {
        public void hlaLauncherDiscovered(HlaLauncher launcher, HlaTimeStamp timeStamp) {}
        public void hlaLauncherInitialized(HlaLauncher launcher, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void hlaLauncherInInterest(HlaLauncher launcher, HlaTimeStamp timeStamp) {}
        public void hlaLauncherOutOfInterest(HlaLauncher launcher, HlaTimeStamp timeStamp) {}
        public void hlaLauncherDeleted(HlaLauncher launcher, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
    }
}
