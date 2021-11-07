################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Program\ Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2/platform/base/hal/plugin/serial/cortexm/efm32/com.c 

OBJS += \
./serial/com.o 

C_DEPS += \
./serial/com.d 


# Each subdirectory must supply rules for building sources it contributes
serial/com.o: C:/Program\ Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2/platform/base/hal/plugin/serial/cortexm/efm32/com.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=gnu99 '-DCONFIGURATION_HEADER="app/framework/util/config.h"' '-DCORTEXM3=1' '-DCORTEXM3_EFM32_MICRO=1' '-DCORTEXM3_EFR32=1' '-DCORTEXM3_EFR32_MICRO=1' '-DAPP_GECKO_INFO_PAGE_BTL=1' '-DATTRIBUTE_STORAGE_CONFIGURATION="eyeair_blank_endpoint_config.h"' '-DCORTEXM3_EFR32MG14P732F256IM48=1' '-DCORTEXM3_EFR32MG14P732F256IM48_MICRO=1' '-DGENERATED_TOKEN_HEADER="eyeair_blank_tokens.h"' '-DZA_GENERATED_HEADER="eyeair_blank.h"' '-DPLATFORM_HEADER="platform/base/hal/micro/cortexm3/compiler/gcc.h"' '-DEFR32MG14P=1' '-DEFR32MG14P732F256IM48=1' '-DEFR32_SERIES1_CONFIG4_MICRO=1' '-DLOCKBITS_IN_MAINFLASH_SIZE=0' '-DPSSTORE_SIZE=0' '-DLONGTOKEN_SIZE=0' '-DHAL_CONFIG=1' '-DEMBER_AF_USE_HWCONF=1' '-DEMBER_AF_API_EMBER_TYPES="stack/include/ember-types.h"' '-DEMBER_AF_API_DEBUG_PRINT="app/framework/util/print.h"' '-DEMBER_AF_API_AF_HEADER="app/framework/include/af.h"' '-DEMBER_AF_API_AF_SECURITY_HEADER="app/framework/security/af-security.h"' '-DEMBER_AF_API_NEIGHBOR_HEADER="stack/include/stack-info.h"' '-DEMBER_STACK_ZIGBEE=1' '-DMBEDTLS_CONFIG_FILE="mbedtls-config-generated.h"' '-DEMLIB_USER_CONFIG=1' '-DSL_CATALOG_POWER_MANAGER_PRESENT=1' '-DAPPLICATION_TOKEN_HEADER="znet-token.h"' '-DAPPLICATION_MFG_TOKEN_HEADER="znet-mfg-token.h"' '-DMBEDTLS_DEVICE_ACCELERATION_CONFIG_FILE="config-device-acceleration.h"' '-DMBEDTLS_DEVICE_ACCELERATION_CONFIG_APP_FILE="config-device-acceleration-app.h"' '-DPHY_RAIL=1' -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//hardware/kit/common/drivers" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2/" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base/hal" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base/hal//plugin" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base/hal//micro/cortexm3/efm32" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base/hal//micro/cortexm3/efm32/config" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base/hal//micro/cortexm3/efm32/efr32" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../CMSIS/Include" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../emdrv/common/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../emdrv/config" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../emdrv/dmadrv/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../emdrv/gpiointerrupt/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../service/sleeptimer/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../service/sleeptimer/config" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../common/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../emdrv/sleep/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../emdrv/spidrv/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../emdrv/tempdrv/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../emdrv/uartdrv/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../emdrv/ustimer/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../emlib/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../middleware/glib" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../middleware/glib/glib" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../radio/rail_lib/plugin" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../radio/rail_lib/chip/efr32/rf/common/cortex" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../radio/rail_lib/chip/efr32/rf/rfprotocol/ieee802154/cortex" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base//../radio/mac" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/halconfig/inc/hal-config" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//hardware/module/config" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//hardware/kit/common/halconfig" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//hardware/kit/common/bsp" -I"C:\Users\babahin\SimplicityStudio\v5_workspace\eyeair_sensors" -I"C:\Users\babahin\SimplicityStudio\v5_workspace\eyeair_sensors\hal-config" -I"C:\Users\babahin\SimplicityStudio\v5_workspace\eyeair_sensors\external-generated-files" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base/hal/micro/cortexm3/efm32" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/bootloader/api" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/app/framework" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/stack" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/app/util" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/app/framework/include" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/Device/SiliconLabs/EFR32MG14P/Include" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/base/hal/micro/cortexm3/efm32/config/segger" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/bootloader" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/radio/rail_lib/chip/efr32/efr32xg1x" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/radio/rail_lib/common" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/radio/rail_lib/plugin/coexistence/common" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/radio/rail_lib/plugin/coexistence/hal/efr32" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/radio/rail_lib/plugin/coexistence/protocol/ieee802154" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/radio/rail_lib/plugin/pa-conversions" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/radio/rail_lib/protocol/ble" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/radio/rail_lib/protocol/ieee802154" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/radio/rail_lib/protocol/zwave" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/service/mpu/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/service/power_manager/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/service/sleeptimer/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//platform/service/sleeptimer/src" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/tool/appbuilder/../../app/framework/../../../../platform/common/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/tool/appbuilder/../../app/framework/../../../../platform/radio/mac" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//protocol/zigbee/tool/appbuilder/../../app/framework/../../../../util/silicon_labs/silabs_core" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//util/plugin/plugin-common/mbedtls" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//util/third_party/crypto/mbedtls" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//util/third_party/crypto/mbedtls/include" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//util/third_party/crypto/mbedtls/include/mbedtls" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//util/third_party/crypto/mbedtls/include/psa" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//util/third_party/crypto/mbedtls/library" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//util/third_party/crypto/sl_component/sl_alt/include" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//util/third_party/crypto/sl_component/sl_mbedtls_support/config" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//util/third_party/crypto/sl_component/sl_mbedtls_support/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//util/third_party/crypto/sl_component/sl_protocol_crypto/src" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//util/third_party/crypto/sl_component/sl_psa_driver/inc" -I"C:/Program Files/SimplicityStudio-5/developer/sdks/gecko_sdk_suite/v3.2//util/third_party/segger/systemview/SEGGER" -I"C:\Users\babahin\SimplicityStudio\v5_workspace\eyeair_sensors\hal-config" -I"C:\Users\babahin\SimplicityStudio\v5_workspace\eyeair_sensors\battery" -I"C:\Users\babahin\SimplicityStudio\v5_workspace\eyeair_sensors\buzzer" -I"C:\Users\babahin\SimplicityStudio\v5_workspace\eyeair_sensors\ccs811" -I"C:\Users\babahin\SimplicityStudio\v5_workspace\eyeair_sensors\esp12f" -I"C:\Users\babahin\SimplicityStudio\v5_workspace\eyeair_sensors\pmsa003" -I"C:\Users\babahin\SimplicityStudio\v5_workspace\eyeair_sensors\sht20" -I"C:\Users\babahin\SimplicityStudio\v5_workspace\eyeair_sensors\ws2812" -Os -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -c -fmessage-length=0 -MMD -MP -MF"serial/com.d" -MT"serial/com.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

