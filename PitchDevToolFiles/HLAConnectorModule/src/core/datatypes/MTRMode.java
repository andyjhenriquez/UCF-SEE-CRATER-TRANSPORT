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
 * Implementation of the <code>MTRMode</code> data type from the FOM.
 * <br>Description from the FOM: Mode Transition Request (MTR) transition values.  This enumeration is used to request a specific mode transition.  However, not all mode transition requests are accepted for any given Run Mode.  See mode transition validation table in the Space Reference FOM documentation.
 * <p>
 * This class is <code>Immutable</code> (and therefore <code>ThreadSafe</code>)
 * as defined by <i>Java Concurrency in Practice</i>,
 * see <a href="http://jcip.net/annotations/doc/net/jcip/annotations/package-summary.html">jcip.net</a>.
 */
public enum MTRMode implements HlaEnumDataType {
    /** <code>MTR_GOTO_RUN</code> (with ordinal 2) */
    MTR_GOTO_RUN("MTR_GOTO_RUN", 2),
    /** <code>MTR_GOTO_FREEZE</code> (with ordinal 3) */
    MTR_GOTO_FREEZE("MTR_GOTO_FREEZE", 3),
    /** <code>MTR_GOTO_SHUTDOWN</code> (with ordinal 4) */
    MTR_GOTO_SHUTDOWN("MTR_GOTO_SHUTDOWN", 4);

   /**
    * The name of the enum.
    */
    public final String name;
   /**
    * The ordinal of the enum.
    */
    public final long ordinal;

    private MTRMode(String name, long ordinal) {
        this.name = name;
        this.ordinal = ordinal;
    }

    public long getOrdinal() {
        return ordinal;
    }

    public String getName() {
        return name;
    }

   /**
    * Find the enum with the specified ordinal.
    *
    * @param ordinal ordinal of the enum to find
    *
    * @return the enum with the specified <code>ordinal</code>, or <code>null</code> if not found
    */
    public static MTRMode find(long ordinal) {
        for (MTRMode value : values()) {
            if (value.getOrdinal() == ordinal) {
                return value;
            }
        }
        return null;
    }

   /**
    * Find the enum with the specified name.
    *
    * @param name name of the enum to find
    *
    * @return the enum with the specified <code>name</code>, or <code>null</code> if not found
    */
    public static MTRMode find(String name) {
        for (MTRMode value : values()) {
            if (value.getName().equals(name)) {
                return value;
            }
        }
        return null;
    }
}
