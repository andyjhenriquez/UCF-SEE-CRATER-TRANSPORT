/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPOINTERS_H
#define DEVELOPER_STUDIO_HLAPOINTERS_H


#include <memory>

namespace LunarSimulation {

   class HlaHLAobjectRoot;
   class HlaHLAobjectRootAttributes;
   class HlaHLAobjectRootListener;
   class HlaHLAobjectRootManager;
   class HlaHLAobjectRootManagerListener;
   class HlaHLAobjectRootValueListener;
   class HlaHLAobjectRootUpdater;
   class HlaPhysicalEntity;
   class HlaPhysicalEntityAttributes;
   class HlaPhysicalEntityListener;
   class HlaPhysicalEntityManager;
   class HlaPhysicalEntityManagerListener;
   class HlaPhysicalEntityValueListener;
   class HlaPhysicalEntityUpdater;
   class HlaDynamicalEntity;
   class HlaDynamicalEntityAttributes;
   class HlaDynamicalEntityListener;
   class HlaDynamicalEntityManager;
   class HlaDynamicalEntityManagerListener;
   class HlaDynamicalEntityValueListener;
   class HlaDynamicalEntityUpdater;
   class HlaPayload;
   class HlaPayloadAttributes;
   class HlaPayloadListener;
   class HlaPayloadManager;
   class HlaPayloadManagerListener;
   class HlaPayloadValueListener;
   class HlaPayloadUpdater;
   class HlaLauncher;
   class HlaLauncherAttributes;
   class HlaLauncherListener;
   class HlaLauncherManager;
   class HlaLauncherManagerListener;
   class HlaLauncherValueListener;
   class HlaLauncherUpdater;
   class HlaPhysicalInterface;
   class HlaPhysicalInterfaceAttributes;
   class HlaPhysicalInterfaceListener;
   class HlaPhysicalInterfaceManager;
   class HlaPhysicalInterfaceManagerListener;
   class HlaPhysicalInterfaceValueListener;
   class HlaPhysicalInterfaceUpdater;
   class HlaReferenceFrame;
   class HlaReferenceFrameAttributes;
   class HlaReferenceFrameListener;
   class HlaReferenceFrameManager;
   class HlaReferenceFrameManagerListener;
   class HlaReferenceFrameValueListener;
   class HlaReferenceFrameUpdater;
   class HlaMoon;
   class HlaMoonAttributes;
   class HlaMoonListener;
   class HlaMoonManager;
   class HlaMoonManagerListener;
   class HlaMoonValueListener;
   class HlaMoonUpdater;
   class HlaExecutionConfiguration;
   class HlaExecutionConfigurationAttributes;
   class HlaExecutionConfigurationListener;
   class HlaExecutionConfigurationManager;
   class HlaExecutionConfigurationManagerListener;
   class HlaExecutionConfigurationValueListener;
   class HlaExecutionConfigurationUpdater;
   class HlaInteractionListener;
   class HlaHLAinteractionRootInteraction;
   class HlaStartStopInteraction;
   class HlaModeTransitionRequestParameters;
   class HlaModeTransitionRequestInteraction;
   class HlaSettings;
   class HlaInteractionManager;
   class HlaSaveRestoreManager;
   class HlaTimeStamp;
   class HlaTimeStampFactory;
   class HlaPacer;
   class HlaWorld;
   class HlaWorldListener;
   class HlaException;
   class HlaFederateId;
   class HlaLogicalTime;
   class HlaSaveRestoreListener;

   typedef std::shared_ptr<HlaHLAobjectRoot> HlaHLAobjectRootPtr;
   typedef std::shared_ptr<HlaHLAobjectRootAttributes> HlaHLAobjectRootAttributesPtr;
   typedef std::shared_ptr<HlaHLAobjectRootListener> HlaHLAobjectRootListenerPtr;
   typedef std::shared_ptr<HlaHLAobjectRootManager> HlaHLAobjectRootManagerPtr;
   typedef std::shared_ptr<HlaHLAobjectRootManagerListener> HlaHLAobjectRootManagerListenerPtr;
   typedef std::shared_ptr<HlaHLAobjectRootValueListener> HlaHLAobjectRootValueListenerPtr;
   typedef std::shared_ptr<HlaHLAobjectRootUpdater> HlaHLAobjectRootUpdaterPtr;
   typedef std::shared_ptr<HlaPhysicalEntity> HlaPhysicalEntityPtr;
   typedef std::shared_ptr<HlaPhysicalEntityAttributes> HlaPhysicalEntityAttributesPtr;
   typedef std::shared_ptr<HlaPhysicalEntityListener> HlaPhysicalEntityListenerPtr;
   typedef std::shared_ptr<HlaPhysicalEntityManager> HlaPhysicalEntityManagerPtr;
   typedef std::shared_ptr<HlaPhysicalEntityManagerListener> HlaPhysicalEntityManagerListenerPtr;
   typedef std::shared_ptr<HlaPhysicalEntityValueListener> HlaPhysicalEntityValueListenerPtr;
   typedef std::shared_ptr<HlaPhysicalEntityUpdater> HlaPhysicalEntityUpdaterPtr;
   typedef std::shared_ptr<HlaDynamicalEntity> HlaDynamicalEntityPtr;
   typedef std::shared_ptr<HlaDynamicalEntityAttributes> HlaDynamicalEntityAttributesPtr;
   typedef std::shared_ptr<HlaDynamicalEntityListener> HlaDynamicalEntityListenerPtr;
   typedef std::shared_ptr<HlaDynamicalEntityManager> HlaDynamicalEntityManagerPtr;
   typedef std::shared_ptr<HlaDynamicalEntityManagerListener> HlaDynamicalEntityManagerListenerPtr;
   typedef std::shared_ptr<HlaDynamicalEntityValueListener> HlaDynamicalEntityValueListenerPtr;
   typedef std::shared_ptr<HlaDynamicalEntityUpdater> HlaDynamicalEntityUpdaterPtr;
   typedef std::shared_ptr<HlaPayload> HlaPayloadPtr;
   typedef std::shared_ptr<HlaPayloadAttributes> HlaPayloadAttributesPtr;
   typedef std::shared_ptr<HlaPayloadListener> HlaPayloadListenerPtr;
   typedef std::shared_ptr<HlaPayloadManager> HlaPayloadManagerPtr;
   typedef std::shared_ptr<HlaPayloadManagerListener> HlaPayloadManagerListenerPtr;
   typedef std::shared_ptr<HlaPayloadValueListener> HlaPayloadValueListenerPtr;
   typedef std::shared_ptr<HlaPayloadUpdater> HlaPayloadUpdaterPtr;
   typedef std::shared_ptr<HlaLauncher> HlaLauncherPtr;
   typedef std::shared_ptr<HlaLauncherAttributes> HlaLauncherAttributesPtr;
   typedef std::shared_ptr<HlaLauncherListener> HlaLauncherListenerPtr;
   typedef std::shared_ptr<HlaLauncherManager> HlaLauncherManagerPtr;
   typedef std::shared_ptr<HlaLauncherManagerListener> HlaLauncherManagerListenerPtr;
   typedef std::shared_ptr<HlaLauncherValueListener> HlaLauncherValueListenerPtr;
   typedef std::shared_ptr<HlaLauncherUpdater> HlaLauncherUpdaterPtr;
   typedef std::shared_ptr<HlaPhysicalInterface> HlaPhysicalInterfacePtr;
   typedef std::shared_ptr<HlaPhysicalInterfaceAttributes> HlaPhysicalInterfaceAttributesPtr;
   typedef std::shared_ptr<HlaPhysicalInterfaceListener> HlaPhysicalInterfaceListenerPtr;
   typedef std::shared_ptr<HlaPhysicalInterfaceManager> HlaPhysicalInterfaceManagerPtr;
   typedef std::shared_ptr<HlaPhysicalInterfaceManagerListener> HlaPhysicalInterfaceManagerListenerPtr;
   typedef std::shared_ptr<HlaPhysicalInterfaceValueListener> HlaPhysicalInterfaceValueListenerPtr;
   typedef std::shared_ptr<HlaPhysicalInterfaceUpdater> HlaPhysicalInterfaceUpdaterPtr;
   typedef std::shared_ptr<HlaReferenceFrame> HlaReferenceFramePtr;
   typedef std::shared_ptr<HlaReferenceFrameAttributes> HlaReferenceFrameAttributesPtr;
   typedef std::shared_ptr<HlaReferenceFrameListener> HlaReferenceFrameListenerPtr;
   typedef std::shared_ptr<HlaReferenceFrameManager> HlaReferenceFrameManagerPtr;
   typedef std::shared_ptr<HlaReferenceFrameManagerListener> HlaReferenceFrameManagerListenerPtr;
   typedef std::shared_ptr<HlaReferenceFrameValueListener> HlaReferenceFrameValueListenerPtr;
   typedef std::shared_ptr<HlaReferenceFrameUpdater> HlaReferenceFrameUpdaterPtr;
   typedef std::shared_ptr<HlaMoon> HlaMoonPtr;
   typedef std::shared_ptr<HlaMoonAttributes> HlaMoonAttributesPtr;
   typedef std::shared_ptr<HlaMoonListener> HlaMoonListenerPtr;
   typedef std::shared_ptr<HlaMoonManager> HlaMoonManagerPtr;
   typedef std::shared_ptr<HlaMoonManagerListener> HlaMoonManagerListenerPtr;
   typedef std::shared_ptr<HlaMoonValueListener> HlaMoonValueListenerPtr;
   typedef std::shared_ptr<HlaMoonUpdater> HlaMoonUpdaterPtr;
   typedef std::shared_ptr<HlaExecutionConfiguration> HlaExecutionConfigurationPtr;
   typedef std::shared_ptr<HlaExecutionConfigurationAttributes> HlaExecutionConfigurationAttributesPtr;
   typedef std::shared_ptr<HlaExecutionConfigurationListener> HlaExecutionConfigurationListenerPtr;
   typedef std::shared_ptr<HlaExecutionConfigurationManager> HlaExecutionConfigurationManagerPtr;
   typedef std::shared_ptr<HlaExecutionConfigurationManagerListener> HlaExecutionConfigurationManagerListenerPtr;
   typedef std::shared_ptr<HlaExecutionConfigurationValueListener> HlaExecutionConfigurationValueListenerPtr;
   typedef std::shared_ptr<HlaExecutionConfigurationUpdater> HlaExecutionConfigurationUpdaterPtr;
   typedef std::shared_ptr<HlaInteractionListener> HlaInteractionListenerPtr;
   typedef std::shared_ptr<HlaHLAinteractionRootInteraction> HlaHLAinteractionRootInteractionPtr;
   typedef std::shared_ptr<HlaStartStopInteraction> HlaStartStopInteractionPtr;
   typedef std::shared_ptr<HlaModeTransitionRequestParameters> HlaModeTransitionRequestParametersPtr;
   typedef std::shared_ptr<HlaModeTransitionRequestInteraction> HlaModeTransitionRequestInteractionPtr;
   typedef std::shared_ptr<HlaSettings> HlaSettingsPtr;
   typedef std::shared_ptr<HlaInteractionManager> HlaInteractionManagerPtr;
   typedef std::shared_ptr<HlaSaveRestoreManager> HlaSaveRestoreManagerPtr;
   typedef std::shared_ptr<HlaTimeStamp> HlaTimeStampPtr;
   typedef std::shared_ptr<HlaTimeStampFactory> HlaTimeStampFactoryPtr;
   typedef std::shared_ptr<HlaPacer> HlaPacerPtr;
   typedef std::shared_ptr<HlaWorld> HlaWorldPtr;
   typedef std::shared_ptr<HlaWorldListener> HlaWorldListenerPtr;
   typedef std::shared_ptr<HlaException> HlaExceptionPtr;
   typedef std::shared_ptr<HlaFederateId> HlaFederateIdPtr;
   typedef std::shared_ptr<HlaLogicalTime> HlaLogicalTimePtr;
   typedef std::shared_ptr<HlaSaveRestoreListener> HlaSaveRestoreListenerPtr;


}
#endif
