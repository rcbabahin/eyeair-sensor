// This file is generated by Simplicity Studio.  Please do not edit manually.
//
//

// Enclosing macro to prevent multiple inclusion
#ifndef SILABS_ZNET_CONFIG
#define SILABS_ZNET_CONFIG


/**** Included Header Section ****/



// Networks
#define EM_AF_GENERATED_NETWORK_TYPES { \
  EM_AF_NETWORK_TYPE_ZIGBEE_PRO, /* Primary */ \
}
#define EM_AF_GENERATED_ZIGBEE_PRO_NETWORKS { \
  { \
    /* Primary */ \
    ZA_ROUTER, \
    EMBER_AF_SECURITY_PROFILE_HA, \
  }, \
}
#define EM_AF_GENERATED_NETWORK_STRINGS  \
  "Primary (pro)", \
/**** ZCL Section ****/
#define ZA_PROMPT "eyeair_blank"
#define ZCL_USING_BASIC_CLUSTER_SERVER
#define ZCL_USING_IDENTIFY_CLUSTER_CLIENT
#define ZCL_USING_IDENTIFY_CLUSTER_SERVER
#define ZCL_USING_TEMP_MEASUREMENT_CLUSTER_SERVER
#define ZCL_USING_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER_SERVER
#define ZCL_USING_CARBON_DIOXIDE_MFG_SPECIFIC_CLUSTER_CLIENT
#define ZCL_USING_CARBON_DIOXIDE_MFG_SPECIFIC_CLUSTER_SERVER
#define ZCL_USING_PM1_0_MFG_SPECIFIC_CLUSTER_CLIENT
#define ZCL_USING_PM1_0_MFG_SPECIFIC_CLUSTER_SERVER
#define ZCL_USING_PM10_0_MFG_SPECIFIC_CLUSTER_CLIENT
#define ZCL_USING_PM10_0_MFG_SPECIFIC_CLUSTER_SERVER
#define ZCL_USING_PM2_5_MFG_SPECIFIC_CLUSTER_CLIENT
#define ZCL_USING_PM2_5_MFG_SPECIFIC_CLUSTER_SERVER
#define ZCL_USING_TVOC_MFG_SPECIFIC_CLUSTER_CLIENT
#define ZCL_USING_TVOC_MFG_SPECIFIC_CLUSTER_SERVER
/**** Optional Attributes ****/
#define ZCL_USING_CARBON_DIOXIDE_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_ONE_ATTRIBUTE 
#define ZCL_USING_CARBON_DIOXIDE_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_TWO_ATTRIBUTE 
#define ZCL_USING_CARBON_DIOXIDE_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_THREE_ATTRIBUTE 
#define ZCL_USING_CARBON_DIOXIDE_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_FOUR_ATTRIBUTE 
#define ZCL_USING_PM1_0_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_ONE_ATTRIBUTE 
#define ZCL_USING_PM1_0_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_TWO_ATTRIBUTE 
#define ZCL_USING_PM1_0_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_THREE_ATTRIBUTE 
#define ZCL_USING_PM1_0_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_FOUR_ATTRIBUTE 
#define ZCL_USING_PM10_0_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_ONE_ATTRIBUTE 
#define ZCL_USING_PM10_0_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_TWO_ATTRIBUTE 
#define ZCL_USING_PM10_0_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_THREE_ATTRIBUTE 
#define ZCL_USING_PM10_0_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_FOUR_ATTRIBUTE 
#define ZCL_USING_PM2_5_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_ONE_ATTRIBUTE 
#define ZCL_USING_PM2_5_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_TWO_ATTRIBUTE 
#define ZCL_USING_PM2_5_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_THREE_ATTRIBUTE 
#define ZCL_USING_PM2_5_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_FOUR_ATTRIBUTE 
#define ZCL_USING_TVOC_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_ONE_ATTRIBUTE 
#define ZCL_USING_TVOC_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_TWO_ATTRIBUTE 
#define ZCL_USING_TVOC_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_THREE_ATTRIBUTE 
#define ZCL_USING_TVOC_MFG_SPECIFIC_CLUSTER_ATTRIBUTE_FOUR_ATTRIBUTE 
#define EMBER_AF_MANUFACTURER_CODE 0x1002
#define EMBER_AF_DEFAULT_RESPONSE_POLICY_CONDITIONAL

/**** Cluster endpoint counts ****/
#define EMBER_AF_BASIC_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_IDENTIFY_CLUSTER_CLIENT_ENDPOINT_COUNT (1)
#define EMBER_AF_IDENTIFY_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_TEMP_MEASUREMENT_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_CARBON_DIOXIDE_MFG_SPECIFIC_CLUSTER_CLIENT_ENDPOINT_COUNT (1)
#define EMBER_AF_CARBON_DIOXIDE_MFG_SPECIFIC_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_PM1_0_MFG_SPECIFIC_CLUSTER_CLIENT_ENDPOINT_COUNT (1)
#define EMBER_AF_PM1_0_MFG_SPECIFIC_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_PM10_0_MFG_SPECIFIC_CLUSTER_CLIENT_ENDPOINT_COUNT (1)
#define EMBER_AF_PM10_0_MFG_SPECIFIC_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_PM2_5_MFG_SPECIFIC_CLUSTER_CLIENT_ENDPOINT_COUNT (1)
#define EMBER_AF_PM2_5_MFG_SPECIFIC_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_TVOC_MFG_SPECIFIC_CLUSTER_CLIENT_ENDPOINT_COUNT (1)
#define EMBER_AF_TVOC_MFG_SPECIFIC_CLUSTER_SERVER_ENDPOINT_COUNT (1)

/**** Cluster Endpoint Summaries ****/
#define EMBER_AF_MAX_SERVER_CLUSTER_COUNT (9)
#define EMBER_AF_MAX_CLIENT_CLUSTER_COUNT (6)
#define EMBER_AF_MAX_TOTAL_CLUSTER_COUNT (15)

/**** CLI Section ****/
#define EMBER_AF_GENERATE_CLI
#define EMBER_COMMAND_INTEPRETER_HAS_DESCRIPTION_FIELD

/**** Security Section ****/
#define EMBER_AF_HAS_SECURITY_PROFILE_HA

/**** Network Section ****/
#define EMBER_SUPPORTED_NETWORKS (1)
#define EMBER_AF_ZC_AND_ZR_DEVICE_COUNT (1)
#define EMBER_AF_NETWORK_INDEX_PRIMARY (0)
#define EMBER_AF_DEFAULT_NETWORK_INDEX EMBER_AF_NETWORK_INDEX_PRIMARY
#define EMBER_AF_HAS_ROUTER_NETWORK
#define EMBER_AF_HAS_RX_ON_WHEN_IDLE_NETWORK
#define EMBER_AF_TX_POWER_MODE EMBER_TX_POWER_MODE_USE_TOKEN

/**** Callback Section ****/
#define EMBER_CALLBACK_MAIN_START
#define EMBER_CALLBACK_MAIN_INIT
#define EMBER_CALLBACK_ENERGY_SCAN_RESULT
#define EMBER_CALLBACK_SCAN_COMPLETE
#define EMBER_CALLBACK_NETWORK_FOUND
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_CLUSTER_SERVER_INIT
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_CLUSTER_SERVER_TICK
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_CLUSTER_SERVER_ATTRIBUTE_CHANGED
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_QUERY
#define EMBER_CALLBACK_INCOMING_PACKET_HANDOFF
#define EMBER_APPLICATION_HAS_INCOMING_PACKET_HANDOFF
#define EMBER_CALLBACK_OUTGOING_PACKET_HANDOFF
#define EMBER_APPLICATION_HAS_PACKET_HANDOFF
#define EMBER_CALLBACK_GET_CURRENT_SLEEP_CONTROL
#define EMBER_CALLBACK_GET_DEFAULT_SLEEP_CONTROL
#define EMBER_CALLBACK_SET_DEFAULT_SLEEP_CONTROL
#define EMBER_CALLBACK_COUNTER_HANDLER
#define EMBER_APPLICATION_HAS_COUNTER_HANDLER
#define EMBER_CALLBACK_EZSP_COUNTER_ROLLOVER_HANDLER
#define EZSP_APPLICATION_HAS_COUNTER_ROLLOVER_HANDLER
/**** Debug printing section ****/

// Global switch
// #define EMBER_AF_PRINT_ENABLE
// Individual areas
#define EMBER_AF_PRINT_CORE 0x0001
#define EMBER_AF_PRINT_APP 0x0002
#define EMBER_AF_PRINT_ATTRIBUTES 0x0004
#define EMBER_AF_PRINT_BITS { 0x07 }
#define EMBER_AF_PRINT_NAMES { \
  "Core",\
  "Application",\
  "Attributes",\
  NULL\
}
#define EMBER_AF_PRINT_NAME_NUMBER 3




// Generated plugin macros

// Use this macro to check if ADC plugin is included
#define EMBER_AF_PLUGIN_ADC

// Use this macro to check if Address Table plugin is included
#define EMBER_AF_PLUGIN_ADDRESS_TABLE
// User options for plugin Address Table
#define EMBER_AF_PLUGIN_ADDRESS_TABLE_SIZE 2
#define EMBER_AF_PLUGIN_ADDRESS_TABLE_TRUST_CENTER_CACHE_SIZE 2

// Use this macro to check if Antenna Stub plugin is included
#define EMBER_AF_PLUGIN_ANTENNA_STUB

// Use this macro to check if Binding Table Library plugin is included
#define EMBER_AF_PLUGIN_BINDING_TABLE_LIBRARY
// User options for plugin Binding Table Library
#define EMBER_BINDING_TABLE_SIZE 3

// Use this macro to check if CCM* Encryption plugin is included
#define EMBER_AF_PLUGIN_CCM_ENCRYPTION
// User options for plugin CCM* Encryption
#define EMBER_AF_PLUGIN_CCM_ENCRYPTION_SOFTWARE_CCM
#define USE_SOFTWARE_CCM

// Use this macro to check if Radio Coexistence Stub plugin is included
#define EMBER_AF_PLUGIN_COEXISTENCE_STUB

// Use this macro to check if Counters plugin is included
#define EMBER_AF_PLUGIN_COUNTERS
// User options for plugin Counters

// Use this macro to check if Debug Basic Library plugin is included
#define EMBER_AF_PLUGIN_DEBUG_BASIC_LIBRARY

// Use this macro to check if Debug JTAG plugin is included
#define EMBER_AF_PLUGIN_DEBUG_JTAG

// Use this macro to check if Ember Minimal Printf plugin is included
#define EMBER_AF_PLUGIN_EMBER_MINIMAL_PRINTF

// Use this macro to check if Form and Join Library plugin is included
#define EMBER_AF_PLUGIN_FORM_AND_JOIN

// Use this macro to check if HAL Library plugin is included
#define EMBER_AF_PLUGIN_HAL_LIBRARY

// Use this macro to check if I2C Driver plugin is included
#define EMBER_AF_PLUGIN_I2C_DRIVER
// User options for plugin I2C Driver
#define EMBER_AF_PLUGIN_I2C_DRIVER_TRANSACTION_TIMEOUT 50

// Use this macro to check if Identify Cluster plugin is included
#define EMBER_AF_PLUGIN_IDENTIFY

// Use this macro to check if Idle/Sleep plugin is included
#define EMBER_AF_PLUGIN_IDLE_SLEEP
// User options for plugin Idle/Sleep
#define EMBER_AF_PLUGIN_IDLE_SLEEP_MINIMUM_SLEEP_DURATION_MS 5
#define EMBER_AF_PLUGIN_IDLE_SLEEP_BACKOFF_SLEEP_MS 0

// Use this macro to check if Install Code Library plugin is included
#define EMBER_AF_PLUGIN_INSTALL_CODE_LIBRARY

// Use this macro to check if mbed TLS plugin is included
#define EMBER_AF_PLUGIN_MBEDTLS
// User options for plugin mbed TLS
#define EMBER_AF_PLUGIN_MBEDTLS_CONF_DEVICE_ACCELERATION
#define EMBER_AF_PLUGIN_MBEDTLS_CONF_DEVICE_ACCELERATION_APP

// Use this macro to check if Network Steering plugin is included
#define EMBER_AF_PLUGIN_NETWORK_STEERING
// User options for plugin Network Steering
#define EMBER_AF_PLUGIN_NETWORK_STEERING_CHANNEL_MASK 0x0318C800
#define EMBER_AF_PLUGIN_NETWORK_STEERING_RADIO_TX_POWER 3
#define EMBER_AF_PLUGIN_NETWORK_STEERING_SCAN_DURATION 4
#define EMBER_AF_PLUGIN_NETWORK_STEERING_COMMISSIONING_TIME_S 180
#define EMBER_AF_PLUGIN_NETWORK_STEERING_OPTIMIZE_SCANS

// Use this macro to check if Packet Handoff plugin is included
#define EMBER_AF_PLUGIN_PACKET_HANDOFF
// User options for plugin Packet Handoff
#define EMBER_AF_PLUGIN_PACKET_HANDOFF_ALLOW_ALL_PACKETS
#define PACKET_HANDOFF_BUFFER_SIZE 256

// Use this macro to check if Packet Validate Library plugin is included
#define EMBER_AF_PLUGIN_PACKET_VALIDATE_LIBRARY

// Use this macro to check if RAIL Library plugin is included
#define EMBER_AF_PLUGIN_RAIL_LIBRARY
// User options for plugin RAIL Library
#define EMBER_AF_PLUGIN_RAIL_LIBRARY_RAILPHYDEF 1

// Use this macro to check if Scan Dispatch plugin is included
#define EMBER_AF_PLUGIN_SCAN_DISPATCH
// User options for plugin Scan Dispatch
#define EMBER_AF_PLUGIN_SCAN_DISPATCH_SCAN_QUEUE_SIZE 10

// Use this macro to check if Serial plugin is included
#define EMBER_AF_PLUGIN_SERIAL

// Use this macro to check if Simulated EEPROM version 1 Library plugin is included
#define EMBER_AF_PLUGIN_SIM_EEPROM1
// User options for plugin Simulated EEPROM version 1 Library

// Use this macro to check if Simple Main plugin is included
#define EMBER_AF_PLUGIN_SIMPLE_MAIN

// Use this macro to check if Source Route Library plugin is included
#define EMBER_AF_PLUGIN_SOURCE_ROUTE_LIBRARY
// User options for plugin Source Route Library
#define EMBER_SOURCE_ROUTE_TABLE_SIZE 7

// Use this macro to check if Strong Random plugin is included
#define EMBER_AF_PLUGIN_STRONG_RANDOM
// User options for plugin Strong Random
#define EMBER_AF_PLUGIN_STRONG_RANDOM_RADIO_PRNG
#define USE_RADIO_API_FOR_TRNG

// Use this macro to check if Update TC Link Key plugin is included
#define EMBER_AF_PLUGIN_UPDATE_TC_LINK_KEY
// User options for plugin Update TC Link Key
#define EMBER_AF_PLUGIN_UPDATE_TC_LINK_KEY_MAX_ATTEMPTS 3

// Use this macro to check if ZCL Framework Core plugin is included
#define EMBER_AF_PLUGIN_ZCL_FRAMEWORK_CORE
// User options for plugin ZCL Framework Core
#define EMBER_AF_PLUGIN_ZCL_FRAMEWORK_CORE_CLI_ENABLED
#define ZA_CLI_FULL

// Use this macro to check if ZigBee PRO Stack Library plugin is included
#define EMBER_AF_PLUGIN_ZIGBEE_PRO_LIBRARY
// User options for plugin ZigBee PRO Stack Library
#define EMBER_MAX_END_DEVICE_CHILDREN 6
#define EMBER_PACKET_BUFFER_COUNT 75
#define EMBER_END_DEVICE_KEEP_ALIVE_SUPPORT_MODE EMBER_KEEP_ALIVE_SUPPORT_ALL
#define EMBER_END_DEVICE_POLL_TIMEOUT MINUTES_256
#define EMBER_END_DEVICE_POLL_TIMEOUT_SHIFT 6
#define EMBER_LINK_POWER_DELTA_INTERVAL 300
#define EMBER_APS_UNICAST_MESSAGE_COUNT 10
#define EMBER_BROADCAST_TABLE_SIZE 15
#define EMBER_NEIGHBOR_TABLE_SIZE 16


// Generated API headers

// API adc-cortexm3 from ADC plugin
#define EMBER_AF_API_ADC_CORTEXM3 "../../../../../Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2/platform/base/hal/plugin/adc/adc-cortexm3.h"

// API adc from ADC plugin
#define EMBER_AF_API_ADC "../../../../../Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2/platform/base/hal/plugin/adc/adc.h"

// API antenna from Antenna Stub plugin
#define EMBER_AF_API_ANTENNA "../../../../../Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2/platform/base/hal/plugin/antenna/antenna.h"

// API coexistence from Radio Coexistence Stub plugin
#define EMBER_AF_API_COEXISTENCE "../../../../../Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2/platform/radio/rail_lib/plugin/coexistence/protocol/ieee802154/coexistence-802154.h"

// API i2c-driver from I2C Driver plugin
#define EMBER_AF_API_I2C_DRIVER "../../../../../Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2/platform/base/hal/plugin/i2c-driver/i2c-driver.h"

// API network-steering from Network Steering plugin
#define EMBER_AF_API_NETWORK_STEERING "../../../../../Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2/protocol/zigbee/app/framework/plugin/network-steering/network-steering.h"

// API rail-library from RAIL Library plugin
#define EMBER_AF_API_RAIL_LIBRARY "../../../../../Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2/platform/radio/rail_lib/common/rail.h"

// API scan-dispatch from Scan Dispatch plugin
#define EMBER_AF_API_SCAN_DISPATCH "../../../../../Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2/protocol/zigbee/app/framework/plugin/scan-dispatch/scan-dispatch.h"

// API serial from Serial plugin
#define EMBER_AF_API_SERIAL "../../../../../Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2/platform/base/hal/plugin/serial/serial.h"

// API update-tc-link-key from Update TC Link Key plugin
#define EMBER_AF_API_UPDATE_TC_LINK_KEY "../../../../../Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2/protocol/zigbee/app/framework/plugin/update-tc-link-key/update-tc-link-key.h"

// API command-interpreter2 from ZCL Framework Core plugin
#define EMBER_AF_API_COMMAND_INTERPRETER2 "../../../../../Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2/protocol/zigbee/app/util/serial/command-interpreter2.h"


// Custom macros


#endif // SILABS_ZNET_CONFIG