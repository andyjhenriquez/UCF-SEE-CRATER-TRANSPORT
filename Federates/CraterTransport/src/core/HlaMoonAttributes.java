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

import core.datatypes.SpaceTimeCoordinateState;
import core.exceptions.HlaValueNotSetException;

import java.util.HashMap;
import java.util.Map;


/**
 * Interface used to represent all attributes for an object instance.
 * <p>
 * This class is <code>Immutable</code> (and therefore <code>ThreadSafe</code>)
 * as defined by <i>Java Concurrency in Practice</i>,
 * see <a href="http://jcip.net/annotations/doc/net/jcip/annotations/package-summary.html">jcip.net</a>.
 */
public interface HlaMoonAttributes extends HlaReferenceFrameAttributes {

  /**
   * An enumeration of the attributes of an HlaMoon.
   *
   * <table>
   * <caption>All attributes</caption>
   * <tr><td><b>Enum constant</b></td><td><b>Java name</b></td><td><b>FOM name</b></td></tr>
   * <tr><td>NAME</td><td> name</td><td> <code>name</code></td></tr>
   * <tr><td>PARENT_NAME</td><td> parentName</td><td> <code>parent_name</code></td></tr>
   * <tr><td>STATE</td><td> state</td><td> <code>state</code></td></tr>
   * </table>
   */
   enum Attribute {
      /**
      * name (FOM name: <code>name</code>).
      * <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
      */
      NAME("name"),
      /**
      * parentName (FOM name: <code>parent_name</code>).
      * <br>Description from the FOM: The name of this frame's parent reference frame. If this frame has no parent (i.e., is a 'root' reference frame), then this string must be empty, otherwise the non-empty string must correspond to the name attribute of some other ReferenceFrame object instance in the simulation.
      */
      PARENT_NAME("parent_name"),
      /**
      * state (FOM name: <code>state</code>).
      * <br>Description from the FOM: A four dimensional representation of the reference frame with respect to its parent reference frame.  If the parent fame is an empty string, then only the time dimension has meaning.
      */
      STATE("state");
      
      private static final Map<String, Attribute> NAMES;

      static {
         NAMES = new HashMap<String, Attribute>(values().length);
         for (Attribute val : values()) {
            NAMES.put(val._name, val);
         }
      }

      private final String _name;

      private Attribute(String name) {
         _name = name;
      }

     /**
      * Get the name of the Attribute.
      *
      * @return the name of the attribute
      */
      public String getName() {
         return _name;
      }

     /**
      * Find the Attribute with the specified name.
      *
      * @param name name of the attribute to find
      *
      * @return the attribute with the specified <code>name</code>, or <code>null</code> if not found
      */
      public static Attribute find(String name) {
         return NAMES.get(name);
      }
   }


   /**
    * Returns true if the <code>name</code> attribute has received a value yet.
    *
    * <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
    *
    * @return true if <code>name</code> is available.
    */
    boolean hasName();

   /**
    * Gets the value of the <code>name</code> attribute.
    *
    * <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
    * <br>Description of the data type from the FOM: 
    *
    * @return the <code>name</code> attribute.
    *
    * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
    */
    String getName() throws HlaValueNotSetException;

   /**
    * Gets the value of the <code>name</code> attribute, or <code>defaultValue</code> if value was not set.
    *
    * <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
    * <br>Description of the data type from the FOM: 
    *
    * @param defaultValue default value
    *
    * @return the <code>name</code> attribute or <code>defaultValue</code> if not set
    */
    String getName(String defaultValue);

    /**
     * Gets the time stamped value of the <code>name</code> attribute.
     *
     * <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
     * <br>Description of the data type from the FOM: 
     *
     * @return the time stamped <code>name</code> attribute.
     *
     * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
     */
     HlaTimeStamped<String> getNameTimeStamped() throws HlaValueNotSetException;

   /**
    * Returns true if the <code>parentName</code> attribute has received a value yet.
    *
    * <br>Description from the FOM: The name of this frame's parent reference frame. If this frame has no parent (i.e., is a 'root' reference frame), then this string must be empty, otherwise the non-empty string must correspond to the name attribute of some other ReferenceFrame object instance in the simulation.
    *
    * @return true if <code>parentName</code> is available.
    */
    boolean hasParentName();

   /**
    * Gets the value of the <code>parentName</code> attribute.
    *
    * <br>Description from the FOM: The name of this frame's parent reference frame. If this frame has no parent (i.e., is a 'root' reference frame), then this string must be empty, otherwise the non-empty string must correspond to the name attribute of some other ReferenceFrame object instance in the simulation.
    * <br>Description of the data type from the FOM: 
    *
    * @return the <code>parentName</code> attribute.
    *
    * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
    */
    String getParentName() throws HlaValueNotSetException;

   /**
    * Gets the value of the <code>parentName</code> attribute, or <code>defaultValue</code> if value was not set.
    *
    * <br>Description from the FOM: The name of this frame's parent reference frame. If this frame has no parent (i.e., is a 'root' reference frame), then this string must be empty, otherwise the non-empty string must correspond to the name attribute of some other ReferenceFrame object instance in the simulation.
    * <br>Description of the data type from the FOM: 
    *
    * @param defaultValue default value
    *
    * @return the <code>parentName</code> attribute or <code>defaultValue</code> if not set
    */
    String getParentName(String defaultValue);

    /**
     * Gets the time stamped value of the <code>parentName</code> attribute.
     *
     * <br>Description from the FOM: The name of this frame's parent reference frame. If this frame has no parent (i.e., is a 'root' reference frame), then this string must be empty, otherwise the non-empty string must correspond to the name attribute of some other ReferenceFrame object instance in the simulation.
     * <br>Description of the data type from the FOM: 
     *
     * @return the time stamped <code>parentName</code> attribute.
     *
     * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
     */
     HlaTimeStamped<String> getParentNameTimeStamped() throws HlaValueNotSetException;

   /**
    * Returns true if the <code>state</code> attribute has received a value yet.
    *
    * <br>Description from the FOM: A four dimensional representation of the reference frame with respect to its parent reference frame.  If the parent fame is an empty string, then only the time dimension has meaning.
    *
    * @return true if <code>state</code> is available.
    */
    boolean hasState();

   /**
    * Gets the value of the <code>state</code> attribute.
    *
    * <br>Description from the FOM: A four dimensional representation of the reference frame with respect to its parent reference frame.  If the parent fame is an empty string, then only the time dimension has meaning.
    * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
    *
    * @return the <code>state</code> attribute.
    *
    * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
    */
    SpaceTimeCoordinateState getState() throws HlaValueNotSetException;

   /**
    * Gets the value of the <code>state</code> attribute, or <code>defaultValue</code> if value was not set.
    *
    * <br>Description from the FOM: A four dimensional representation of the reference frame with respect to its parent reference frame.  If the parent fame is an empty string, then only the time dimension has meaning.
    * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
    *
    * @param defaultValue default value
    *
    * @return the <code>state</code> attribute or <code>defaultValue</code> if not set
    */
    SpaceTimeCoordinateState getState(SpaceTimeCoordinateState defaultValue);

    /**
     * Gets the time stamped value of the <code>state</code> attribute.
     *
     * <br>Description from the FOM: A four dimensional representation of the reference frame with respect to its parent reference frame.  If the parent fame is an empty string, then only the time dimension has meaning.
     * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
     *
     * @return the time stamped <code>state</code> attribute.
     *
     * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
     */
     HlaTimeStamped<SpaceTimeCoordinateState> getStateTimeStamped() throws HlaValueNotSetException;
}
