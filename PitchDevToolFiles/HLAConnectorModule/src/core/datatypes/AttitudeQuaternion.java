package core.datatypes;

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
 * Implementation of the <code>AttitudeQuaternion</code> data type from the FOM.
 * <br>Description from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
 * <p>
 * This class is <code>Immutable</code> (and therefore <code>ThreadSafe</code>)
 * as defined by <i>Java Concurrency in Practice</i>,
 * see <a href="http://jcip.net/annotations/doc/net/jcip/annotations/package-summary.html">jcip.net</a>.
 */
public final class AttitudeQuaternion {

   /**
    * The value of the scalar field.
    * <br>FOM name: <code>scalar</code>.
    * <br>Description from the FOM: The scalar component of the quaternion.
    */
    public final double scalar;
   /**
    * The value of the vector field.
    * <br>FOM name: <code>vector</code>.
    * <br>Description from the FOM: The vector component of the quaternion.
    */
    public final double[/* 3 */] vector;

    private AttitudeQuaternion(
        double scalar,
        double[/* 3 */] vector
    ) {
        this.scalar = scalar;
        this.vector = vector;
    }

   /**
    * Create a new AttitudeQuaternion.
    *
    * @param scalar value of the scalar field
    * <br>Description from the FOM: The scalar component of the quaternion.
    * <br>Description of the data type from the FOM: A unitless scalar value. [unit: NA, resolution: NA, accuracy: NA]
    * @param vector value of the vector field
    * <br>Description from the FOM: The vector component of the quaternion.
    * <br>Description of the data type from the FOM: A unitless 3-vector.
    *
    * @return a new AttitudeQuaternion
    */
    public static AttitudeQuaternion create(
        double scalar,
        double[/* 3 */] vector
    ) {
        if (vector == null) {
            throw new NullPointerException("vector can not be null");
        }

        return new AttitudeQuaternion(
           scalar,
           vector
        );
    }

   /**
    * Get the value of the scalar field.
    * <br>FOM name: <code>scalar</code>.
    * <br>Description from the FOM: The scalar component of the quaternion.
    * <br>Description of the data type from the FOM: A unitless scalar value. [unit: NA, resolution: NA, accuracy: NA]
    *
    * @return the value of the scalar field
    */
    public double getScalar() {
        return scalar;
    }

   /**
    * Get the value of the vector field.
    * <br>FOM name: <code>vector</code>.
    * <br>Description from the FOM: The vector component of the quaternion.
    * <br>Description of the data type from the FOM: A unitless 3-vector.
    *
    * @return the value of the vector field
    */
    public double[/* 3 */] getVector() {
        return vector;
    }

   @Override
   public boolean equals(Object object) {
      if (this == object) {
         return true;
      }
      if (object == null || getClass() != object.getClass()) {
         return false;
      }

      AttitudeQuaternion other = (AttitudeQuaternion)object;

      return new EqualsBuilder()
            .append(scalar, other.scalar)
            .append(vector, other.vector)
            .isEquals();
   }

   @Override
   public int hashCode() {
      return new HashCodeBuilder()
            .append(scalar)
            .append(vector)
            .toHashCode();
   }

   @Override
   public String toString() {
      return new ToStringBuilder(this)
            .append("scalar", scalar)
            .append("vector", vector)
            .getToString();
   }
}