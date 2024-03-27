/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

/*
 * How to enable Precompiled Headers (PCH):
 *  1: Define DEVELOPER_STUDIO_USE_PRECOMPILED_HEADERS
 *  2: Enable Precompiled headers for project and use through file "LunarSimulation/HlaAllHeaders.h"
 *  3: Create Precompiled headers from one source file, for example FederateManager.cpp
 */

 #ifdef _WIN32
 #define _CRT_SECURE_NO_WARNINGS  // Disable warning C4996: 'gmtime'
 #endif

#ifdef DEVELOPER_STUDIO_USE_PRECOMPILED_HEADERS



/*
 * All standard header files
 */
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

/*
 * All RtiDriver header files
 */
#include <RtiDriver/Detective.h>
#include <RtiDriver/Exception.h>
#include <RtiDriver/FederateAmbassador.h>
#include <RtiDriver/FederateHandle.h>
#include <RtiDriver/InteractionClassHandle.h>
#include <RtiDriver/ObjectClassHandle.h>
#include <RtiDriver/ObjectInstanceHandle.h>
#include <RtiDriver/RprUtility/RprUtility.h>
#include <RtiDriver/RtiAmbassador.h>
#include <RtiDriver/RtiDriver.h>
#include <RtiDriver/Types.h>

#include <RtiDriver/Encoding/AbstractDataElement.h>
#include <RtiDriver/Encoding/BasicDataElements.h>
#include <RtiDriver/Encoding/HLAfixedArray.h>
#include <RtiDriver/Encoding/HLAfixedRecord.h>
#include <RtiDriver/Encoding/HLAopaqueData.h>
#include <RtiDriver/Encoding/HLApaddingTo16Array.h>
#include <RtiDriver/Encoding/HLApaddingTo32Array.h>
#include <RtiDriver/Encoding/HLApaddingTo64Array.h>
#include <RtiDriver/Encoding/HLAvariableArray.h>
#include <RtiDriver/Encoding/HLAvariableLengthlessArray.h>
#include <RtiDriver/Encoding/HLAvariableUnpaddedLengthlessArray.h>
#include <RtiDriver/Encoding/HLAvariantRecord.h>

#if 0 // Only system files and RtiDriver in precompiled headers

/*
 * Generated header files
 */
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaFederateId.h>
#include <LunarSimulation/HlaHLAobjectRoot.h>
#include <LunarSimulation/HlaHLAobjectRootAttributes.h>
#include <LunarSimulation/HlaHLAobjectRootListener.h>
#include <LunarSimulation/HlaHLAobjectRootManager.h>
#include <LunarSimulation/HlaHLAobjectRootManagerListener.h>
#include <LunarSimulation/HlaHLAobjectRootValueListener.h>
#include <LunarSimulation/HlaHLAobjectRootUpdater.h>
#include <LunarSimulation/HlaPhysicalEntity.h>
#include <LunarSimulation/HlaPhysicalEntityAttributes.h>
#include <LunarSimulation/HlaPhysicalEntityListener.h>
#include <LunarSimulation/HlaPhysicalEntityManager.h>
#include <LunarSimulation/HlaPhysicalEntityManagerListener.h>
#include <LunarSimulation/HlaPhysicalEntityValueListener.h>
#include <LunarSimulation/HlaPhysicalEntityUpdater.h>
#include <LunarSimulation/HlaDynamicalEntity.h>
#include <LunarSimulation/HlaDynamicalEntityAttributes.h>
#include <LunarSimulation/HlaDynamicalEntityListener.h>
#include <LunarSimulation/HlaDynamicalEntityManager.h>
#include <LunarSimulation/HlaDynamicalEntityManagerListener.h>
#include <LunarSimulation/HlaDynamicalEntityValueListener.h>
#include <LunarSimulation/HlaDynamicalEntityUpdater.h>
#include <LunarSimulation/HlaPayload.h>
#include <LunarSimulation/HlaPayloadAttributes.h>
#include <LunarSimulation/HlaPayloadListener.h>
#include <LunarSimulation/HlaPayloadManager.h>
#include <LunarSimulation/HlaPayloadManagerListener.h>
#include <LunarSimulation/HlaPayloadValueListener.h>
#include <LunarSimulation/HlaPayloadUpdater.h>
#include <LunarSimulation/HlaLauncher.h>
#include <LunarSimulation/HlaLauncherAttributes.h>
#include <LunarSimulation/HlaLauncherListener.h>
#include <LunarSimulation/HlaLauncherManager.h>
#include <LunarSimulation/HlaLauncherManagerListener.h>
#include <LunarSimulation/HlaLauncherValueListener.h>
#include <LunarSimulation/HlaLauncherUpdater.h>
#include <LunarSimulation/HlaPhysicalInterface.h>
#include <LunarSimulation/HlaPhysicalInterfaceAttributes.h>
#include <LunarSimulation/HlaPhysicalInterfaceListener.h>
#include <LunarSimulation/HlaPhysicalInterfaceManager.h>
#include <LunarSimulation/HlaPhysicalInterfaceManagerListener.h>
#include <LunarSimulation/HlaPhysicalInterfaceValueListener.h>
#include <LunarSimulation/HlaPhysicalInterfaceUpdater.h>
#include <LunarSimulation/HlaReferenceFrame.h>
#include <LunarSimulation/HlaReferenceFrameAttributes.h>
#include <LunarSimulation/HlaReferenceFrameListener.h>
#include <LunarSimulation/HlaReferenceFrameManager.h>
#include <LunarSimulation/HlaReferenceFrameManagerListener.h>
#include <LunarSimulation/HlaReferenceFrameValueListener.h>
#include <LunarSimulation/HlaReferenceFrameUpdater.h>
#include <LunarSimulation/HlaMoon.h>
#include <LunarSimulation/HlaMoonAttributes.h>
#include <LunarSimulation/HlaMoonListener.h>
#include <LunarSimulation/HlaMoonManager.h>
#include <LunarSimulation/HlaMoonManagerListener.h>
#include <LunarSimulation/HlaMoonValueListener.h>
#include <LunarSimulation/HlaMoonUpdater.h>
#include <LunarSimulation/HlaExecutionConfiguration.h>
#include <LunarSimulation/HlaExecutionConfigurationAttributes.h>
#include <LunarSimulation/HlaExecutionConfigurationListener.h>
#include <LunarSimulation/HlaExecutionConfigurationManager.h>
#include <LunarSimulation/HlaExecutionConfigurationManagerListener.h>
#include <LunarSimulation/HlaExecutionConfigurationValueListener.h>
#include <LunarSimulation/HlaExecutionConfigurationUpdater.h>
#include <LunarSimulation/HlaObjectInstanceBase.h>
#include <LunarSimulation/HlaEnumSet.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaInteractionManager.h>
#include <LunarSimulation/HlaLogicalTime.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaPacer.h>
#include <LunarSimulation/HlaSettings.h>
#include <LunarSimulation/HlaTimeStampFactory.h>
#include <LunarSimulation/HlaTimeStamp.h>
#include <LunarSimulation/HlaTimeStamped.h>
#include <LunarSimulation/HlaTuning.h>
#include <LunarSimulation/HlaWorld.h>
#include <LunarSimulation/HlaWorldListener.h>
#include <LunarSimulation/HlaSaveRestoreManager.h>
#include <LunarSimulation/HlaSaveRestoreListener.h>
#include <LunarSimulation/HlaInteractionListener.h>
#include <LunarSimulation/HlaSynchronizationListener.h>
#include <LunarSimulation/HlaSynchronizationManager.h>

#include <LunarSimulation/datatypes/ExecutionMode.h>
#include <LunarSimulation/datatypes/MTRMode.h>
#include <LunarSimulation/datatypes/AttitudeQuaternion.h>
#include <LunarSimulation/datatypes/ReferenceFrameRotation.h>
#include <LunarSimulation/datatypes/ReferenceFrameTranslation.h>
#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>
#include <LunarSimulation/datatypes/VelocityVector.h>
#include <LunarSimulation/datatypes/Vector.h>
#include <LunarSimulation/datatypes/TorqueVector.h>
#include <LunarSimulation/datatypes/PositionVector.h>
#include <LunarSimulation/datatypes/InertiaRateMatrix.h>
#include <LunarSimulation/datatypes/InertiaMatrix.h>
#include <LunarSimulation/datatypes/ForceVector.h>
#include <LunarSimulation/datatypes/AngularVelocityVector.h>
#include <LunarSimulation/datatypes/AngularAccelerationVector.h>
#include <LunarSimulation/datatypes/AccelerationVector.h>

#if 0 // Headers in source folder
#include <LunarSimulation/AbstractInteractionClassManager.h>
#include <LunarSimulation/AbstractObjectClassManager.h>
#include <LunarSimulation/AttributeValue.h>
#include <LunarSimulation/ParameterValue.h>
#include <LunarSimulation/BlockingQueue.h>
#include <LunarSimulation/Cache.h>
#include <LunarSimulation/ConditionVariable.h>
#include <LunarSimulation/DualMap.h>
#include <LunarSimulation/FederateManager.h>
#include <LunarSimulation/ImplPointers.h>
#include <LunarSimulation/HlaInteractionManagerImpl.h>
#include <LunarSimulation/InvokeLaterExecutor.h>
#include <LunarSimulation/ListenerSet.h>
#include <LunarSimulation/HlaLogicalTimeImpl.h>
#include <LunarSimulation/NotificationQueue.h>
#include <LunarSimulation/ObjectManager.h>
#include <LunarSimulation/RtiInteractionManager.h>
#include <LunarSimulation/Scheduler.h>
#include <LunarSimulation/StringUtil.h>
#include <LunarSimulation/TimeUtility.h>
#include <LunarSimulation/HlaWorldImpl.h>
#include <LunarSimulation/HlaSaveRestoreManagerImpl.h>
#include <LunarSimulation/SaveRestManager.h>
#include <LunarSimulation/PersistentHelper.h>
#include <LunarSimulation/HlaFederateIdImpl.h>
#include <LunarSimulation/HlaHLAobjectRootAttributesImpl.h>
#include <LunarSimulation/HlaHLAobjectRootImpl.h>
#include <LunarSimulation/HlaHLAobjectRootManagerImpl.h>
#include <LunarSimulation/HlaHLAobjectRootUpdaterImpl.h>
#include <LunarSimulation/HlaPhysicalEntityAttributesImpl.h>
#include <LunarSimulation/HlaPhysicalEntityImpl.h>
#include <LunarSimulation/HlaPhysicalEntityManagerImpl.h>
#include <LunarSimulation/HlaPhysicalEntityUpdaterImpl.h>
#include <LunarSimulation/HlaDynamicalEntityAttributesImpl.h>
#include <LunarSimulation/HlaDynamicalEntityImpl.h>
#include <LunarSimulation/HlaDynamicalEntityManagerImpl.h>
#include <LunarSimulation/HlaDynamicalEntityUpdaterImpl.h>
#include <LunarSimulation/HlaPayloadAttributesImpl.h>
#include <LunarSimulation/HlaPayloadImpl.h>
#include <LunarSimulation/HlaPayloadManagerImpl.h>
#include <LunarSimulation/HlaPayloadUpdaterImpl.h>
#include <LunarSimulation/HlaLauncherAttributesImpl.h>
#include <LunarSimulation/HlaLauncherImpl.h>
#include <LunarSimulation/HlaLauncherManagerImpl.h>
#include <LunarSimulation/HlaLauncherUpdaterImpl.h>
#include <LunarSimulation/HlaPhysicalInterfaceAttributesImpl.h>
#include <LunarSimulation/HlaPhysicalInterfaceImpl.h>
#include <LunarSimulation/HlaPhysicalInterfaceManagerImpl.h>
#include <LunarSimulation/HlaPhysicalInterfaceUpdaterImpl.h>
#include <LunarSimulation/HlaReferenceFrameAttributesImpl.h>
#include <LunarSimulation/HlaReferenceFrameImpl.h>
#include <LunarSimulation/HlaReferenceFrameManagerImpl.h>
#include <LunarSimulation/HlaReferenceFrameUpdaterImpl.h>
#include <LunarSimulation/HlaMoonAttributesImpl.h>
#include <LunarSimulation/HlaMoonImpl.h>
#include <LunarSimulation/HlaMoonManagerImpl.h>
#include <LunarSimulation/HlaMoonUpdaterImpl.h>
#include <LunarSimulation/HlaExecutionConfigurationAttributesImpl.h>
#include <LunarSimulation/HlaExecutionConfigurationImpl.h>
#include <LunarSimulation/HlaExecutionConfigurationManagerImpl.h>
#include <LunarSimulation/HlaExecutionConfigurationUpdaterImpl.h>
#include <LunarSimulation/HlaSynchronizationManagerImpl.h>
#include <LunarSimulation/SyncPointManager.h>

#include <LunarSimulation/datatypes/BaseEncoder.h>
#include <LunarSimulation/datatypes/CharPair.h>
#include <LunarSimulation/datatypes/ExecutionModeEncoder.h>
#include <LunarSimulation/datatypes/MTRModeEncoder.h>
#include <LunarSimulation/datatypes/AttitudeQuaternionEncoder.h>
#include <LunarSimulation/datatypes/ReferenceFrameRotationEncoder.h>
#include <LunarSimulation/datatypes/ReferenceFrameTranslationEncoder.h>
#include <LunarSimulation/datatypes/SpaceTimeCoordinateStateEncoder.h>
#include <LunarSimulation/datatypes/VelocityVectorEncoder.h>
#include <LunarSimulation/datatypes/VectorEncoder.h>
#include <LunarSimulation/datatypes/TorqueVectorEncoder.h>
#include <LunarSimulation/datatypes/PositionVectorEncoder.h>
#include <LunarSimulation/datatypes/InertiaRateMatrixEncoder.h>
#include <LunarSimulation/datatypes/InertiaMatrixEncoder.h>
#include <LunarSimulation/datatypes/ForceVectorEncoder.h>
#include <LunarSimulation/datatypes/AngularVelocityVectorEncoder.h>
#include <LunarSimulation/datatypes/AngularAccelerationVectorEncoder.h>
#include <LunarSimulation/datatypes/AccelerationVectorEncoder.h>
#endif

#endif

#endif



