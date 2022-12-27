cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

project(irig106 C CXX)

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




include_directories(include)


################################################################################
# Source groups
################################################################################

file(GLOB HEADERS "include/*.h")


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

add_library(${PROJECT_NAME} OBJECT  ${Sources})


add_library("${PROJECT_NAME}_SHARED" SHARED  $<TARGET_OBJECTS:${PROJECT_NAME}>)
add_library("${PROJECT_NAME}_STATIC" STATIC  $<TARGET_OBJECTS:${PROJECT_NAME}>)

#set_target_properties("${PROJECT_NAME}_SHARED" PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
#set_target_properties("${PROJECT_NAME}_STATIC" PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")


target_link_libraries("${PROJECT_NAME}_SHARED" PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")
target_link_libraries("${PROJECT_NAME}_STATIC" PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

set_target_properties("${PROJECT_NAME}_SHARED" PROPERTIES PUBLIC_HEADER "${HEADERS}")
set_target_properties("${PROJECT_NAME}_STATIC" PROPERTIES PUBLIC_HEADER "${HEADERS}")


install(TARGETS "${PROJECT_NAME}_SHARED" PUBLIC_HEADER  DESTINATION ${PROJECT_SOURCE_DIR}/dist)
install(TARGETS "${PROJECT_NAME}_STATIC" PUBLIC_HEADER  DESTINATION ${PROJECT_SOURCE_DIR}/dist)