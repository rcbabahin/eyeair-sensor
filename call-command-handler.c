// This file is generated by Simplicity Studio.  Please do not edit manually.
//
//

// This is a set of generated functions that parse the
// the incomming message, and call appropriate command handler.



#include PLATFORM_HEADER
#ifdef EZSP_HOST
// Includes needed for ember related functions for the EZSP host
#include "stack/include/error.h"
#include "stack/include/ember-types.h"
#include "app/util/ezsp/ezsp-protocol.h"
#include "app/util/ezsp/ezsp.h"
#include "app/util/ezsp/ezsp-utils.h"
#include "app/util/ezsp/serial-interface.h"
#else
// Includes needed for ember related functions for the EM250
#include "stack/include/ember.h"
#endif // EZSP_HOST

#include "app/framework/util/util.h"
#include "af-structs.h"
#include "call-command-handler.h"
#include "command-id.h"
#include "callback.h"

static EmberAfStatus status(bool wasHandled, bool clusterExists, bool mfgSpecific)
{
  if (wasHandled) {
    return EMBER_ZCL_STATUS_SUCCESS;
  } else if (clusterExists) {
    return EMBER_ZCL_STATUS_UNSUP_COMMAND;
  } else {
    return EMBER_ZCL_STATUS_UNSUPPORTED_CLUSTER;
  }
}

// Main command parsing controller.
EmberAfStatus emberAfClusterSpecificCommandParse(EmberAfClusterCommand *cmd)
{
  EmberAfStatus result = status(false, false, cmd->mfgSpecific);
  if (cmd->direction == (uint8_t)ZCL_DIRECTION_SERVER_TO_CLIENT
      && emberAfContainsClientWithMfgCode(cmd->apsFrame->destinationEndpoint,
                               cmd->apsFrame->clusterId,
                               cmd->mfgCode)) {
    switch (cmd->apsFrame->clusterId) {
    case ZCL_IDENTIFY_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_CARBON_DIOXIDE_MFG_SPECIFIC_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_PM2_5_MFG_SPECIFIC_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_PM1_0_MFG_SPECIFIC_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_PM10_0_MFG_SPECIFIC_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_TVOC_MFG_SPECIFIC_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    default:
      // Unrecognized cluster ID, error status will apply.
      break;
    }
  } else if (cmd->direction == (uint8_t)ZCL_DIRECTION_CLIENT_TO_SERVER
             && emberAfContainsServerWithMfgCode(cmd->apsFrame->destinationEndpoint,
                                       cmd->apsFrame->clusterId,
                                       cmd->mfgCode)) {
    switch (cmd->apsFrame->clusterId) {
    case ZCL_BASIC_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_IDENTIFY_CLUSTER_ID:
      result = emberAfIdentifyClusterServerCommandParse(cmd);
      break;
    case ZCL_TEMP_MEASUREMENT_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_CARBON_DIOXIDE_MFG_SPECIFIC_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_PM2_5_MFG_SPECIFIC_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_PM1_0_MFG_SPECIFIC_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_PM10_0_MFG_SPECIFIC_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_TVOC_MFG_SPECIFIC_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    default:
      // Unrecognized cluster ID, error status will apply.
      break;
    }
  }
  return result;
}

// Cluster: Identify, server
EmberAfStatus emberAfIdentifyClusterServerCommandParse(EmberAfClusterCommand *cmd)
{
  bool wasHandled = false;
  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
    case ZCL_IDENTIFY_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint16_t identifyTime;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        identifyTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfIdentifyClusterIdentifyCallback(identifyTime);
        break;
      }
    case ZCL_IDENTIFY_QUERY_COMMAND_ID:
      {
        // Command is fixed length: 0
        wasHandled = emberAfIdentifyClusterIdentifyQueryCallback();
        break;
      }
    default:
      {
        // Unrecognized command ID, error status will apply.
        break;
      }
    }
  }
  return status(wasHandled, true, cmd->mfgSpecific);
}
