/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLASYNCHRONIZATIONLISTENER_H
#define DEVELOPER_STUDIO_HLASYNCHRONIZATIONLISTENER_H

#include <memory>
#include <string>
#include <set>

#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaSynchronizationManager.h>
#include <LunarSimulation/HlaLibSettings.h>    

namespace LunarSimulation {

    /**
    * Listener for all synchronizations.
    */
    class HlaSynchronizationListener {
    public:

        LIBAPI virtual ~HlaSynchronizationListener() {}

        /**
        * This method is invoked when a synchronization point is registered.
        *
        * @param synchronizationPointLabel label for the synchronization point
        * @param timeStamp the time when the synchronization point was registered
        */
        LIBAPI virtual void synchronizationPointRegistered(std::wstring synchronizationPointLabel, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is invoked when a federation is synchronized for a synchronization point.
        *
        * @param synchronizationPointLabel label for the synchronization point
        * @param timeStamp the time when the synchronization point was synchronized
        */
        LIBAPI virtual void synchronizationPointSynchronized(std::wstring synchronizationPointLabel, HlaTimeStampPtr timeStamp) = 0;

        class Adapter;
        class AutoAchieveAdapter;
    };


    /**
    * An adapter class that implements the HlaSynchronizationListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    class HlaSynchronizationListener::Adapter : public HlaSynchronizationListener {
    public:

        LIBAPI virtual void synchronizationPointRegistered(std::wstring synchronizationPointLabel, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void synchronizationPointSynchronized(std::wstring synchronizationPointLabel, HlaTimeStampPtr timeStamp) {}

    };


    /**
    * Adapter to auto achieve registered synchronization points.
    */
    class HlaSynchronizationListener::AutoAchieveAdapter : public HlaSynchronizationListener {
    public:
        /**
        * Create an auto achieve adapter listener that will auto achieve all registered synchronization points.
        *
        * @param synchronizationManager the Synchronization Manager
        */
        LIBAPI AutoAchieveAdapter(HlaSynchronizationManagerPtr synchronizationManager) :
            _synchronizationManager(synchronizationManager) {}

        /**
        * Create an auto achieve adapter listener that will delegate to the supplied listener for the set of
        * synchronization point labels and auto achieve all other synchronization points.
        *
        * @param synchronizationManager the Synchronization Manager
        * @param delegateListener the listener to delegate to
        * @param synchronizationPointLabels the synchronization points to delegate to the listener,
        *                                   all other synchronization points will be auto achieved
        */
        LIBAPI AutoAchieveAdapter(HlaSynchronizationManagerPtr synchronizationManager,
            HlaSynchronizationListenerPtr delegateListener,
            std::set<std::wstring> synchronizationPointLabels) :
            _synchronizationManager(synchronizationManager),
            _listener(delegateListener),
            _synchronizationPointLabels(synchronizationPointLabels)
        {}

        /**
        * This method is invoked when a synchronization point is registered.
        *
        * @param synchronizationPointLabel label for the synchronization point
        * @param timeStamp the time when the synchronization point was registered
        */
        LIBAPI void synchronizationPointRegistered(std::wstring synchronizationPointLabel, HlaTimeStampPtr timeStamp) {
            if (_synchronizationPointLabels.find(synchronizationPointLabel) != _synchronizationPointLabels.end()) {
                _listener->synchronizationPointRegistered(synchronizationPointLabel, timeStamp);
            } else {
                _synchronizationManager->achieveSynchronizationPoint(synchronizationPointLabel);
            }
        }

        /**
        * This method is invoked when a federation is synchronized for a synchronization point.
        *
        * @param synchronizationPointLabel label for the synchronization point
        * @param timeStamp the time when the synchronization point was synchronized
        */
        LIBAPI void synchronizationPointSynchronized(std::wstring synchronizationPointLabel, HlaTimeStampPtr timeStamp) {
            if (_synchronizationPointLabels.find(synchronizationPointLabel) != _synchronizationPointLabels.end()) {
                _listener->synchronizationPointSynchronized(synchronizationPointLabel, timeStamp);
            }
        }

    private:
        HlaSynchronizationManagerPtr _synchronizationManager;
        HlaSynchronizationListenerPtr _listener;
        std::set<std::wstring> _synchronizationPointLabels;
    };


}
#endif
