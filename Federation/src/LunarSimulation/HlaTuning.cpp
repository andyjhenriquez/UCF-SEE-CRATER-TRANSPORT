/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#include <LunarSimulation/HlaAllHeaders.h>

#include <LunarSimulation/HlaTuning.h>

#include "StringUtil.h"

using namespace LunarSimulation;

HlaTuning::HlaTuning(HlaSettingsPtr settings) :
    _settings(settings),
    REQUEST(getSetting("request", true)),
    REQUEST_MIN_DELAY_MS(inRange(0, getSetting("requestMinDelayMs", 20), 60*60*1000)), //in ms
    REQUEST_MAX_DELAY_MS(inRange(REQUEST_MIN_DELAY_MS, getSetting("requestMaxDelayMs", 50), 60*60*1000)), //in ms
    PROVIDE(getSetting("provide", true)),
    CONVEY_PRODUCING_FEDERATE(getSetting("conveyProducingFederate", true)),
    AUTO_ACHIEVE(getSetting("autoAchieve", true)),
    INCLUDE_DATA_IN_DECODE_EXCEPTION(getSetting("includeDataInDecodeException", false)),
    VERIFY_RECEIVED_DATA_LENGTH(getSetting("verifyReceivedDataLength", false)),
    RESIGN_ACTION(getSetting("resignAction", 4)),
    CREATE_FEDERATION_WITH_TIME_REPRESENTATION(getSetting("createFederationWithTimeRepresentation", false)),
    ALWAYS_USE_LOGICAL_TIME(getSetting("alwaysUseLogicalTime", false)),
    INITIAL_ADVANCE_WHEN_CONSTRAINED(getSetting("initialAdvanceWhenConstrained", true)),
    INITIAL_ADVANCE_TO_EVEN_STEP_SIZE(getSetting("initialAdvanceToEvenStepSize", true)),
    FORCE_FRAME_TIMES_WHEN_EVENT_BASED(getSetting("forceFrameTimesWhenEventBased", true)),
    ENABLE_ASYNCHRONOUS_DELIVERY(getSetting("enableAsynchronousDelivery", true)),
    NOTIFICATION_QUEUE_CAPACITY(inRange(0, getSetting("notificationQueueCapacity", 200000), 2147483647)), // 2^31 - 1 == 2 147 483 647
    ADVANCE_WAITS_FOR_NOTIFICATIONS(getSetting("advanceWaitsForNotifications", true)),
    ENABLE_TIME_MANAGEMENT_ON_CONNECT(getSetting("enableTimeManagementOnConnect", true))
    {}

//Get the value from Settings file
bool HlaTuning::getSetting(std::string key, bool defaultValue) {
    std::string setting = _settings->getSetting(key);
    if (setting.empty()) {
        return defaultValue;
    } else {
        return StringUtil::stringToBool(setting);
    }
}

//Get the value from the settings file
int HlaTuning::getSetting(std::string key, int defaultValue) {
    std::string setting = _settings->getSetting(key);
    if (setting.empty()) {
        return defaultValue;
    } else {
        return atoi(setting.c_str());
    }
}
