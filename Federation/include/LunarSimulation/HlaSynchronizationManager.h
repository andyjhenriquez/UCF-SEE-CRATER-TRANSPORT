/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLASYNCHRONIZATIONMANAGER_H
#define DEVELOPER_STUDIO_HLASYNCHRONIZATIONMANAGER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <string>
#include <set>
#include <vector>

#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {
    /**
    * Manager used to manage all synchronization.
    */
    class HlaSynchronizationManager : private LunarSimulation::noncopyable {
    public:

        LIBAPI virtual ~HlaSynchronizationManager() {}

        /**
        * Register a synchronization point for all federates in the federation.
        * <br>
        * The registration can fail if the label for the synchronization point is not unique.
        *
        * @param synchronizationPointLabel label for the synchronization point
        *
        * @return <code>True</code> if synchronization point was registered, <code>false</code> otherwise.
        *
        * @throws HlaNotConnectedException if the federate is not connected
        * @throws HlaRtiException on exception from the RTI
        * @throws HlaSaveInProgressException if a federation save is in progress
        * @throws HlaRestoreInProgressException if a federation restore is in progress
        */
        LIBAPI virtual bool registerSynchronizationPoint(const std::wstring& synchronizationPointLabel)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

        /**
        * Register a synchronization point for set of federates in the federation.
        * <br>
        * The registration can fail if the label for the synchronization point is not unique or if
        * any of the encoded <code>HLA federate handle</code>s are invalid.
        *
        * @param synchronizationPointLabel label for the synchronization point
        * @param encodedFederateHandleSynchronizationSet encoded <code>HLA federate handle</code>s for all federates
        *                                                that should be synchronized by this synchronization point
        *
        * @return <code>True</code> if synchronization point was registered, <code>false</code> otherwise.
        *
        * @throws HlaNotConnectedException if the federate is not connected
        * @throws HlaRtiException on exception from the RTI
        * @throws HlaSaveInProgressException if a federation save is in progress
        * @throws HlaRestoreInProgressException if a federation restore is in progress
        */
        LIBAPI virtual bool registerSynchronizationPoint(const std::wstring& synchronizationPointLabel,
                                                         std::set<std::vector<char> > encodedFederateHandleSynchronizationSet)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

        /**
        * Check if the synchronization point is registered.
        *
        * @param synchronizationPointLabel label for the synchronization point
        *
        * @return <code>True</code> if the synchronization point is registered, <code>false</code> otherwise.
        */
        LIBAPI virtual bool isSynchronizationPointRegistered(const std::wstring& synchronizationPointLabel) const = 0;

        /**
        * Get list of all currently registered synchronization point labels.
        *
        * @return List of all currently registered synchronization point labels.
        *
        * @see #getPendingAchieveSynchronizationPointLabels()
        */
        LIBAPI virtual std::set<std::wstring> getRegisteredSynchronizationPointLabels() const = 0;

        /**
        * Get list of all currently registered synchronization point labels with
        * pending achieve from this federate.
        * This a subset of all currently registered synchronization points.
        *
        * @return List of all currently registered synchronization point labels with pending achieve.
        *
        * @see #getRegisteredSynchronizationPointLabels()
        */
        LIBAPI virtual std::set<std::wstring> getPendingAchieveSynchronizationPointLabels() const = 0;

        /**
        * Wait for synchronization point to be registered.
        *
        * @param synchronizationPointLabel label for the synchronization point
        * @param timeout_ms the maximum time to wait in milliseconds
        *
        * @return <code>True</code> if the synchronization point was registered, <code>false</code> otherwise.
        */
        LIBAPI virtual bool waitForSynchronizationPointRegistration(const std::wstring& synchronizationPointLabel, unsigned long long timeout_ms) = 0;

        /**
        * Achieve a previously registered synchronization point.
        *
        * @param synchronizationPointLabel label for the synchronization point
        *
        * @return <code>True</code> if synchronization point was achieved,
        *         <code>false</code> if the synchronization point label was invalid.
        *
        * @throws HlaNotConnectedException if the federate is not connected
        * @throws HlaRtiException on exception from the RTI
        * @throws HlaSaveInProgressException if a federation save is in progress
        * @throws HlaRestoreInProgressException if a federation restore is in progress
        */
        LIBAPI virtual bool achieveSynchronizationPoint(const std::wstring& synchronizationPointLabel)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

        /**
        * Achieve a previously registered synchronization point and wait for the federation to be synchronized.
        * Use the achieveSynchronizationPointAndWaitForSynchronized() method with the additional didTimeout
        * parameter to know if the federation was synchronized before the timeout was reached.
        *
        * @param synchronizationPointLabel label for the synchronization point
        * @param timeout_ms the maximum time to wait in milliseconds
        *
        * @return <code>True</code> if synchronization point was achieved,
        *         <code>false</code> if the synchronization point label was invalid.
        *
        * @throws HlaNotConnectedException if the federate is not connected
        * @throws HlaRtiException on exception from the RTI
        * @throws HlaSaveInProgressException if a federation save is in progress
        * @throws HlaRestoreInProgressException if a federation restore is in progress
        */
        LIBAPI virtual bool achieveSynchronizationPointAndWaitForSynchronized(const std::wstring& synchronizationPointLabel, unsigned long long timeout_ms)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

        /**
        * Achieve a previously registered synchronization point and wait for the federation to be synchronized.
        *
        * @param synchronizationPointLabel label for the synchronization point
        * @param timeout_ms the maximum time to wait in milliseconds
        * @param didTimeout out parameter, <code>true</code> if if the maximum time to wait was reached,
        *                   <code>false</code> if the federation was synchronized before reaching maximum time
        *
        * @return <code>True</code> if synchronization point was achieved,
        *         <code>false</code> if the synchronization point label was invalid.
        *
        * @throws HlaNotConnectedException if the federate is not connected
        * @throws HlaRtiException on exception from the RTI
        * @throws HlaSaveInProgressException if a federation save is in progress
        * @throws HlaRestoreInProgressException if a federation restore is in progress
        */
        LIBAPI virtual bool achieveSynchronizationPointAndWaitForSynchronized(const std::wstring& synchronizationPointLabel, unsigned long long timeout_ms, bool & didTimeout)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

        /**
        * Add a synchronization listener.
        *
        * @param listener listener to add
        */
        LIBAPI virtual void addHlaSynchronizationListener(HlaSynchronizationListenerPtr listener) = 0;

        /**
        * Remove a synchronization listener.
        *
        * @param listener listener to remove
        */
        LIBAPI virtual void removeHlaSynchronizationListener(HlaSynchronizationListenerPtr listener) = 0;
    };
}
#endif
