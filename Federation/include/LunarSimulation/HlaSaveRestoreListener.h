/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLASAVERESTORELISTENER_H
#define DEVELOPER_STUDIO_HLASAVERESTORELISTENER_H

#include <memory>
#include <string>
#include <set>

#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

   /**
    * Listeners for saving and restoring the federation.
    */
    class HlaSaveRestoreListener {
    public:

        LIBAPI virtual ~HlaSaveRestoreListener() {}

       /**
        * Enum used to describe save failure reasons.
        */
        enum HlaSaveFailure {
           /** The RTI was unable to save */
           SAVE_FAILURE_RTI_UNABLE_TO_SAVE,
           /** A federate reported failure */
           SAVE_FAILURE_FEDERATE_REPORTED_FAILURE,
           /** A federate resigned during save */
           SAVE_FAILURE_FEDERATE_RESIGNED,
           /** The RTI detected a failure */
           SAVE_FAILURE_RTI_DETECTED_FAILURE,
           /** The requested save time can not be honored */
           SAVE_FAILURE_SAVE_TIME_CANNOT_BE_HONORED,
           /** The save was aborted */
           SAVE_FAILURE_SAVE_ABORTED,
           /** Unknown */
           SAVE_FAILURE_UNKNOWN
        };

       /**
        * Enum used to describe restore failure reasons.
        */
        enum HlaRestoreFailure {
           /** The RTI was unable to restore */
           RESTORE_FAILURE_RTI_UNABLE_TO_RESTORE,
           /** A federate reported failure */
           RESTORE_FAILURE_FEDERATE_REPORTED_FAILURE,
           /** A federate resigned during restore */
           RESTORE_FAILURE_FEDERATE_RESIGNED,
           /** The RTI detected a failure */
           RESTORE_FAILURE_RTI_DETECTED_FAILURE,
           /** The restore was aborted */
           RESTORE_FAILURE_RESTORE_ABORTED,
           /** Unknown */
           RESTORE_FAILURE_UNKNOWN
        };

       /**
        * The federate should save its state, if <code>true</code> is returned the
        * HlaWorld will save its internal state.
        *
        * @param label label used to identify the save state
        * @param saveTime logical time when the federation should be saved
        *
        * @return <code>true</code> if the save was successful
        */
        LIBAPI virtual bool performFederateSave(const std::wstring& label, HlaLogicalTimePtr saveTime) = 0;

       /**
        * All federates in the federation has successfully saved its respective state.
        */
        LIBAPI virtual void federationSaved() = 0;

       /**
        * Federation was not saved, one ore more federates could not save its state.
        *
        * @param saveFailureReason reason for the failure
        */
        LIBAPI virtual void federationNotSaved(HlaSaveFailure saveFailureReason) = 0;

        /**
         * The federate is about to restore its state, if <code>true</code> is returned the
         * HlaWorld will restore its internal state.
         *
         * @param label label used to identify the restore state
         *
         * @return <code>true</code> if the restore was successful
         */
        LIBAPI virtual bool performFederateRestore(const std::wstring& label) = 0;

       /**
        * All federates in the federation has successfully restored its respective state.
        * <p>
        * If the federate was not in the advancing time state and the save/restore was
        * time managed, the federate might need to wait until the granted time state is
        * reached.
        *
        * @param restoredTime logical time when the federation was saved
        * @param wasAdvancing <code>true</code> if the local federate was in the
        *                     advancing time state when the restore was performed
        *
        * @see HlaSaveRestoreManager#awaitGrantedStateAfterRestore
        */
        LIBAPI virtual void federationRestored(HlaLogicalTimePtr restoredTime, bool wasAdvancing) = 0;

       /**
        * Federation was not restored, one or more federates could not restore its state.
        * The federates that failed to restore its state are now in an <b>undefined</b> state,
        * this may affect the entire federation.
        * <p>
        * If the federate was not in the advancing time state and the save/restore was
        * time managed, the federate might need to wait until the granted time state is
        * reached.
        *
        * @param restoreFailureReason reason for the failure
        * @param localRestoreWasSuccessful <code>true</code> if the local federate restore was successful
        * @param localRestoredTime logical time when the local federate was restored
        * @param wasAdvancing <code>true</code> if the local federate was in the
        *                     advancing time state when the restore was performed
        *
        * @see HlaSaveRestoreManager#awaitGrantedStateAfterRestore
        */
        LIBAPI virtual void federationNotRestored(HlaRestoreFailure restoreFailureReason,
                                                  bool localRestoreWasSuccessful,
                                                  HlaLogicalTimePtr localRestoredTime,
                                                  bool wasAdvancing) = 0;

        class Adapter;
    };


   /**
    * An abstract adapter class that implements the <code>HlaSaveRestoreListener</code> interface with empty methods.
    * Save and restore requests will be rejected by returning <code>false</code> from
    * <code>performFederateSave</code> and <code>performFederateRestore</code>.
    * <p>
    * It can be used as a base class for a listener.
    */
    class HlaSaveRestoreListener::Adapter : public HlaSaveRestoreListener {
    public:

        LIBAPI virtual bool performFederateSave(const std::wstring& label, HlaLogicalTimePtr saveTime) { return false; }

        LIBAPI virtual void federationSaved() {}

        LIBAPI virtual void federationNotSaved(HlaSaveFailure saveFailureReason) {}

        LIBAPI virtual bool performFederateRestore(const std::wstring& label) { return false; }

        LIBAPI virtual void federationRestored(HlaLogicalTimePtr restoredTime, bool wasAdvancing) {}

        LIBAPI virtual void federationNotRestored(HlaRestoreFailure restoreFailureReason, bool localRestoreWasSuccessful, HlaLogicalTimePtr localRestoredTime, bool wasAdvancing) {}
    };

}
#endif
