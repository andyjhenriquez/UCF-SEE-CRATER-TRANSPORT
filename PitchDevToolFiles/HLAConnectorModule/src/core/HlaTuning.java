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
 * Class used to support Tuning of the generated code.
 * <p>
 * This class is <code>Immutable</code> (and therefore <code>ThreadSafe</code>)
 * as defined by <i>Java Concurrency in Practice</i>,
 * see <a href="http://jcip.net/annotations/doc/net/jcip/annotations/package-summary.html">jcip.net</a>.
 */
public final class HlaTuning {

   /**
    * Perform an request of attribute value update when a new instance is discovered or comes within interest.
    * Instances are requested after a delay [REQUEST_MIN_DELAY_MS, REQUEST_MAX_DELAY_MS].
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>request</b></code>
    * to a valid <code>boolean</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.request", Boolean.toString(false));
    * </code></pre>
    *
    * The default value is <code>true</code>.
    *
    * @see #PROVIDE
    * @see #REQUEST_MIN_DELAY_MS
    * @see #REQUEST_MAX_DELAY_MS
    */
   public static final boolean REQUEST = getSetting("request", true);

   /**
    * Min delay for request of attribute value update for discovered instances, in milliseconds.
    * A random value between <i>min</i> and <i>max</i> is used.
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>requestMinDelayMs</b></code>
    * to a valid <code>long</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.requestMinDelayMs", Long.toString(500));
    * </code></pre>
    *
    * Valid range is {@code [0 <= <i>min</i> <= <i>max</i> <= 3 600 000]} ({@code [0 ms ... 1 hr]}).
    * The default value is <code>20</code> ms.
    *
    * @see #REQUEST
    * @see #REQUEST_MAX_DELAY_MS
    */
   public static final long REQUEST_MIN_DELAY_MS =
         inRange(0, getSetting("requestMinDelayMs", 20L), 60 * 60 * 1000); //in ms

   /**
    * Max delay for request of attribute value update for discovered instances, in milliseconds.
    * A random value between <i>min</i> and <i>max</i> is used.
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>requestMaxDelayMs</b></code>
    * to a valid <code>long</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.requestMaxDelayMs", Long.toString(1000));
    * </code></pre>
    *
    * Valid range is {@code [0 <= <i>min</i> <= <i>max</i> <= 3 600 000]} ({@code [0 ms ... 1 hr]}).
    * The default value is <code>50</code> ms.
    *
    * @see #REQUEST
    * @see #REQUEST_MIN_DELAY_MS
    */
   public static final long REQUEST_MAX_DELAY_MS =
         inRange(REQUEST_MIN_DELAY_MS, getSetting("requestMaxDelayMs", 50L), 60 * 60 * 1000); //in ms

   /**
    * Perform an attribute update when a provide is requested.
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>provide</b></code>
    * to a valid <code>boolean</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.provide", Boolean.toString(false));
    * </code></pre>
    *
    * The default value is <code>true</code>.
    *
    * @see #REQUEST
    */
   public static final boolean PROVIDE = getSetting("provide", true);

   /**
    * Turn on the Convey Producing Federate option in the Switches table when using HLA Evolved
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>conveyProducingFederate</b></code>
    * to a valid <code>boolean</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.conveyProducingFederate", Boolean.toString(false));
    * </code></pre>
    *
    * The default value is <code>true</code>.

    */
   public static final boolean CONVEY_PRODUCING_FEDERATE = getSetting("conveyProducingFederate", true);

   /**
    * Perform automatic achieve on all announced synchronization points.
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>autoAchieve</b></code>
    * to a valid <code>boolean</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.autoAchieve", Boolean.toString(false));
    * </code></pre>
    *
    * The default value is <code>true</code>.
    */
   public static final boolean AUTO_ACHIEVE = getSetting("autoAchieve", true);

   /**
    * Include a dump of the data in <code>HlaDecodeException</code>.
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>includeDataInDecodeException</b></code>
    * to a valid <code>boolean</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.includeDataInDecodeException", Boolean.toString(true));
    * </code></pre>
    *
    * The default value is <code>false</code>.
    *
    * @see core.exceptions.HlaDecodeException
    */
   public static final boolean INCLUDE_DATA_IN_DECODE_EXCEPTION = getSetting("includeDataInDecodeException", false);

   /**
    * Verify the length of all received data, throws a <code>HlaDecodeException</code> if the lengths do not match.
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>verifyReceivedDataLength</b></code>
    * to a valid <code>boolean</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.verifyReceivedDataLength", Boolean.toString(true));
    * </code></pre>
    *
    * The default value is <code>false</code>.
    *
    * @see core.exceptions.HlaDecodeException
    */
   public static final boolean VERIFY_RECEIVED_DATA_LENGTH = getSetting("verifyReceivedDataLength", false);

   /**
    * The resign action.
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>resignAction</b></code>
    * to a valid <code>int</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.resignAction", Integer.toString(0));
    * </code></pre>
    *
    * Valid values are:
    * <ul>
    *  <li> 0: UNCONDITIONALLY_DIVEST_ATTRIBUTES - divests all owned attributes </li>
    *  <li> 1: DELETE_OBJECTS - deletes all object instances that the federate owns </li>
    *  <li> 2: CANCEL_PENDING_OWNERSHIP_ACQUISITIONS - cancels all pending ownership acquisitions </li>
    *  <li> 3: DELETE_OBJECTS_THEN_DIVEST - combines 1 and 0 </li>
    *  <li> 4: CANCEL_THEN_DELETE_THEN_DIVEST - combines 2, 1, and 0 </li>
    *  <li> 5: NO_ACTION - no handling of owned attributes or pending acquisitions </li>
    * </ul>
    * <p>
    * The default value is <code>4</code>, CANCEL_THEN_DELETE_THEN_DIVEST.
    */
   public static final int RESIGN_ACTION = getSetting("resignAction", 4);

   /**
    * Create the federation with the selected time representation for logical time,
    * even if HLA Time Management is not enabled.
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>createFederationWithTimeRepresentation</b></code>
    * to a valid <code>boolean</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.createFederationWithTimeRepresentation", Boolean.toString(true));
    * </code></pre>
    *
    * The default value is <code>false</code>.
    */
   public static final boolean CREATE_FEDERATION_WITH_TIME_REPRESENTATION = getSetting("createFederationWithTimeRepresentation", false);

   /**
    * Always send and receive updates and interactions with a <code>LogicalTime</code>,
    * even if HLA Time Management is not enabled.
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>alwaysUseLogicalTime</b></code>
    * to a valid <code>boolean</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.alwaysUseLogicalTime", Boolean.toString(true));
    * </code></pre>
    *
    * The default value is <code>false</code>.
    */
   public static final boolean ALWAYS_USE_LOGICAL_TIME = getSetting("alwaysUseLogicalTime", false);

   /**
    * Do an initial time advance to <code>GALT</code> when only time constrained.
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>initialAdvanceWhenConstrained</b></code>
    * to a valid <code>boolean</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.initialAdvanceWhenConstrained", Boolean.toString(false));
    * </code></pre>
    *
    * The default value is <code>true</code>.
    */
   public static final boolean INITIAL_ADVANCE_WHEN_CONSTRAINED = getSetting("initialAdvanceWhenConstrained", true);

   /**
    * Do an initial time advance to a <code>LogicalTime</code> that is even divisible by the initial step size.
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>initialAdvanceToEvenStepSize</b></code>
    * to a valid <code>boolean</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.initialAdvanceToEvenStepSize", Boolean.toString(false));
    * </code></pre>
    *
    * The default value is <code>true</code>.
    */
   public static final boolean INITIAL_ADVANCE_TO_EVEN_STEP_SIZE = getSetting("initialAdvanceToEvenStepSize", true);

   /**
    * Always advance time to the expected frame times when using <code>advanceToNextEvent()</code>.
    * <p>
    * Example (step size is 5 and an event is received at logical time 12):
    * <ul>
    *    <li>Granted logical times when value set to <code>true</code>: 5, 10, 12, 15, 20</li>
    *    <li>Granted logical times when value set to <code>false</code>: 5, 10, 12, 17, 22</li>
    * </ul>
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>forceFrameTimesWhenEventBased</b></code>
    * to a valid <code>boolean</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.forceFrameTimesWhenEventBased", Boolean.toString(false));
    * </code></pre>
    *
    * The default value is <code>true</code>.
    */
   public static final boolean FORCE_FRAME_TIMES_WHEN_EVENT_BASED = getSetting("forceFrameTimesWhenEventBased", true);

   /**
    * Deliver receive order messages in both time advancing state and time granted state.
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>enableAsynchronousDelivery</b></code>
    * to a valid <code>boolean</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.enableAsynchronousDelivery", Boolean.toString(false));
    * </code></pre>
    *
    * The default value is <code>true</code>.
    */
   public static final boolean ENABLE_ASYNCHRONOUS_DELIVERY = getSetting("enableAsynchronousDelivery", true);

   /**
    * The capacity of the Notification Queue.
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>notificationQueueCapacity</b></code>
    * to a valid <code>int</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.notificationQueueCapacity", Integer.toString(10));
    * </code></pre>
    *
    * Valid range is {@code [0 <= <i>value</i> <= Integer.MAX_VALUE]}.
    * Use 0 for unlimited capacity.
    * The default value is <code>200 000</code> entries.
    */
   public static final int NOTIFICATION_QUEUE_CAPACITY =
         inRange(0, getSetting("notificationQueueCapacity", 200000), Integer.MAX_VALUE);

   /**
    * The time advance methods will wait for all notifications received in the advancing state to
    * be precessed before returning from the advance method.
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>advanceWaitsForNotifications</b></code>
    * to a valid <code>boolean</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.advanceWaitsForNotifications", Boolean.toString(false));
    * </code></pre>
    *
    * The default value is <code>true</code>.
    */
   public static final boolean ADVANCE_WAITS_FOR_NOTIFICATIONS = getSetting("advanceWaitsForNotifications", true);

   /**
    * If configured to use HLA Time Management, it will be enabled on connect.
    * If flag is false, <code>HlaWorld.enableTimeManagement</code> must be called to enable HLA Time Management.
    *
    * This flag has no effect if federate is not configured to use HLA Time Management.
    * <p>
    * This value is changed by setting the System Property
    * <code>core.tuning.<b>delayEnablingTimeManagement</b></code>
    * to a valid <code>boolean</code> value before this class is loaded.
    *
    * <pre><code>
    * System.setProperty("core.tuning.enableTimeManagementOnConnect", Boolean.toString(false));
    * </code></pre>
    *
    * The default value is <code>true</code>.
    */
   public static final boolean ENABLE_TIME_MANAGEMENT_ON_CONNECT = getSetting("enableTimeManagementOnConnect", true);


   private static final String KEY_PREFIX = "core" + ".tuning.";

   private HlaTuning() {
   }

   private static int inRange(int min, int value, int max) {
      return Math.max(min, Math.min(value, max));
   }

   private static long inRange(long min, long value, long max) {
      return Math.max(min, Math.min(value, max));
   }

   private static String getSetting(String key, String defaultValue) {
      return System.getProperty(KEY_PREFIX + key, defaultValue);
   }

   private static int getSetting(String key, int defaultValue) {
      return Integer.getInteger(KEY_PREFIX + key, defaultValue);
   }

   private static long getSetting(String key, long defaultValue) {
      return Long.getLong(KEY_PREFIX + key, defaultValue);
   }

   private static boolean getSetting(String key, boolean defaultValue) {
      boolean result = defaultValue;
      try {
          result = Boolean.parseBoolean(System.getProperty(KEY_PREFIX + key, Boolean.toString(defaultValue)));
      } catch (IllegalArgumentException e) {
         //ignore
      } catch (NullPointerException e) {
         //ignore
      }
      return result;
   }
}
