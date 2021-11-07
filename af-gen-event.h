// This file is generated by Simplicity Studio.  Please do not edit manually.
//
//

// Enclosing macro to prevent multiple inclusion
#ifndef __AF_GEN_EVENT__
#define __AF_GEN_EVENT__


// Code used to configure the cluster event mechanism
#define EMBER_AF_GENERATED_EVENT_CODE \
  EmberEventControl emberAfIdentifyClusterServerTickCallbackControl1; \
  extern EmberEventControl emberAfPluginFormAndJoinCleanupEventControl; \
  extern EmberEventControl emberAfPluginNetworkSteeringFinishSteeringEventControl; \
  extern EmberEventControl emberAfPluginUpdateTcLinkKeyBeginTcLinkKeyUpdateEventControl; \
  extern EmberEventControl startBuzzerAndRGBEventControl; \
  extern EmberEventControl startScanAndConnectEventControl; \
  extern EmberEventControl PMSAEventControl; \
  extern EmberEventControl SHTEventControl; \
  extern EmberEventControl CCSEventControl; \
  extern EmberEventControl startBuzzerSoundDangerousEventControl; \
  extern void emberAfPluginFormAndJoinCleanupEventHandler(void); \
  extern void emberAfPluginNetworkSteeringFinishSteeringEventHandler(void); \
  extern void emberAfPluginUpdateTcLinkKeyBeginTcLinkKeyUpdateEventHandler(void); \
  static void networkEventWrapper(EmberEventControl *control, EmberAfNetworkEventHandler handler, uint8_t networkIndex) \
  { \
    emberAfPushNetworkIndex(networkIndex); \
    emberEventControlSetInactive(*control); \
    (*handler)(); \
    emberAfPopNetworkIndex(); \
  } \
  EmberEventControl emberAfPluginScanDispatchScanNetworkEventControls[1]; \
  extern void emberAfPluginScanDispatchScanNetworkEventHandler(void); \
  void emberAfPluginScanDispatchScanNetworkEventWrapper0(void) { networkEventWrapper(&emberAfPluginScanDispatchScanNetworkEventControls[0], emberAfPluginScanDispatchScanNetworkEventHandler, 0); } \
  static void clusterTickWrapper(EmberEventControl *control, EmberAfTickFunction callback, uint8_t endpoint) \
  { \
    emberAfPushEndpointNetworkIndex(endpoint); \
    emberEventControlSetInactive(*control); \
    (*callback)(endpoint); \
    emberAfPopNetworkIndex(); \
  } \
  void emberAfIdentifyClusterServerTickCallbackWrapperFunction1(void) { clusterTickWrapper(&emberAfIdentifyClusterServerTickCallbackControl1, emberAfIdentifyClusterServerTickCallback, 1); } \
  extern void startBuzzerAndRGBEventHandler; \
  extern void startScanAndConnectEventHandler; \
  extern void PMSAEventHandler; \
  extern void SHTEventHandler; \
  extern void CCSEventHandler; \
  extern void startBuzzerSoundDangerousEventHandler; \


// EmberEventData structs used to populate the EmberEventData table
#define EMBER_AF_GENERATED_EVENTS   \
  { &emberAfIdentifyClusterServerTickCallbackControl1, emberAfIdentifyClusterServerTickCallbackWrapperFunction1 }, \
  { &emberAfPluginFormAndJoinCleanupEventControl, emberAfPluginFormAndJoinCleanupEventHandler }, \
  { &emberAfPluginNetworkSteeringFinishSteeringEventControl, emberAfPluginNetworkSteeringFinishSteeringEventHandler }, \
  { &emberAfPluginUpdateTcLinkKeyBeginTcLinkKeyUpdateEventControl, emberAfPluginUpdateTcLinkKeyBeginTcLinkKeyUpdateEventHandler }, \
  { &emberAfPluginScanDispatchScanNetworkEventControls[0], emberAfPluginScanDispatchScanNetworkEventWrapper0 }, \
  { &startBuzzerAndRGBEventControl, &startBuzzerAndRGBEventHandler }, \
  { &startScanAndConnectEventControl, &startScanAndConnectEventHandler}, \
  { &PMSAEventControl, &PMSAEventHandler}, \
	{ &SHTEventControl, &SHTEventHandler }, \
	{ &CCSEventControl, &CCSEventHandler }, \
	{ &startBuzzerSoundDangerousEventControl, &startBuzzerSoundDangerousEventHandler }, \


#define EMBER_AF_GENERATED_EVENT_STRINGS   \
  "Identify Cluster Server EP 1",  \
  "Form and Join Library Plugin Cleanup",  \
  "Network Steering Plugin FinishSteering",  \
  "Update TC Link Key Plugin BeginTcLinkKeyUpdate",  \
  "Scan Dispatch Plugin Scan NWK 0", \


// The length of the event context table used to track and retrieve cluster events
#define EMBER_AF_EVENT_CONTEXT_LENGTH 1

// EmberAfEventContext structs used to populate the EmberAfEventContext table
#define EMBER_AF_GENERATED_EVENT_CONTEXT { 0x1, 0x3, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfIdentifyClusterServerTickCallbackControl1}


#endif // __AF_GEN_EVENT__
