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
 * A HlaWorldListener is notified of connects and disconnects.
 */
public interface HlaWorldListener {
  /**
   * This method is called when the federate is connected.
   *
   * @param timeStamp The time when the world was connected.
   */
   void connected(HlaTimeStamp timeStamp);

  /**
   * This method is called when the federate is disconnected.
   *
   * @param timeStamp The time when the world was disconnected.
   */
   void disconnected(HlaTimeStamp timeStamp);

  /**
   * This method is called when the federate requests to advance the logical time.
   *
   * @param timeStamp The time when the request was initiated.
   * @param requestedTime The requested logical time.
   */
   void timeAdvanceRequested(HlaTimeStamp timeStamp, HlaLogicalTime requestedTime);

  /**
   * This method is called when the federates request to advance the logical time is granted.
   *
   * @param timeStamp The time when the request was granted.
   * @param grantedTime The granted logical time.
   */
   void timeAdvanceGranted(HlaTimeStamp timeStamp, HlaLogicalTime grantedTime);

  /**
   * An abstract adapter class that implements the HlaWorldListener interface with empty methods.
   * It might be used as a base class for a listener.
   */
   public abstract static class Adapter implements HlaWorldListener {
      public void connected(HlaTimeStamp timeStamp) {}
      public void disconnected(HlaTimeStamp timeStamp) {}
      public void timeAdvanceRequested(HlaTimeStamp timeStamp, HlaLogicalTime requestedTime) {}
      public void timeAdvanceGranted(HlaTimeStamp timeStamp, HlaLogicalTime grantedTime) {}
   }
}
