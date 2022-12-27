cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

project(irig106 C)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32"
     OR "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()






################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "src/irig106dll.def"
)
source_group("" FILES ${no_group_source_files})

set(Headers
    "src/config.h"
    "src/i106_data_stream.h"
    "src/i106_decode_1394.h"
    "src/i106_decode_1553f1.h"
    "src/i106_decode_16pp194.h"
    "src/i106_decode_arinc429.h"
    "src/i106_decode_can.h"
    "src/i106_decode_comp_gen_0.h"
    "src/i106_decode_discrete.h"
    "src/i106_decode_ethernet.h"
    "src/i106_decode_events.h"
    "src/i106_decode_image.h"
    "src/i106_decode_index.h"
    "src/i106_decode_message.h"
    "src/i106_decode_parallel.h"
    "src/i106_decode_pcmf1.h"
    "src/i106_decode_time.h"
    "src/i106_decode_tmats.h"
    "src/i106_decode_tmats_b.h"
    "src/i106_decode_tmats_c.h"
    "src/i106_decode_tmats_common.h"
    "src/i106_decode_tmats_d.h"
    "src/i106_decode_tmats_g.h"
    "src/i106_decode_tmats_m.h"
    "src/i106_decode_tmats_p.h"
    "src/i106_decode_tmats_r.h"
    "src/i106_decode_uart.h"
    "src/i106_decode_video.h"
    "src/i106_index.h"
    "src/i106_time.h"
    "src/irig106ch10.h"
    "src/irig106cl.h"
    "src/sha-256.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "src/i106_data_stream.c"
    "src/i106_decode_1553f1.c"
    "src/i106_decode_16pp194.c"
    "src/i106_decode_arinc429.c"
    "src/i106_decode_can.c"
    "src/i106_decode_discrete.c"
    "src/i106_decode_ethernet.c"
    "src/i106_decode_index.c"
    "src/i106_decode_pcmf1.c"
    "src/i106_decode_time.c"
    "src/i106_decode_tmats.c"
    "src/i106_decode_tmats_b.c"
    "src/i106_decode_tmats_c.c"
    "src/i106_decode_tmats_d.c"
    "src/i106_decode_tmats_g.c"
    "src/i106_decode_tmats_m.c"
    "src/i106_decode_tmats_p.c"
    "src/i106_decode_tmats_r.c"
    "src/i106_decode_uart.c"
    "src/i106_decode_video.c"
    "src/i106_index.c"
    "src/i106_time.c"
    "src/irig106ch10.c"
    "src/sha-256.c"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
 #   ${no_group_source_files}
    ${Headers}
    ${Sources}
)




################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "ws2_32"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "ws2_32"
    )
endif()




################################################################################
# Target
################################################################################
add_library("${PROJECT_NAME}_SHARED" SHARED  ${ALL_FILES})
add_library("${PROJECT_NAME}_STATIC" STATIC  ${ALL_FILES})


target_link_libraries("${PROJECT_NAME}_SHARED" PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")
target_link_libraries("${PROJECT_NAME}_STATIC" PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

#install(TARGETS "${PROJECT_NAME}_SHARED" DESTINATION ${PROJECT_SOURCE_DIR})
#install(TARGETS "${PROJECT_NAME}_STATIC" DESTINATION ${PROJECT_SOURCE_DIR})
