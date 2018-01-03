# Copyright (c) 2017, Jens Pauwels
# All rights reserved.
#
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential.
#

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(spytank-server C)

INCLUDE (CheckFunctionExists)
INCLUDE(FindPkgConfig)

SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
ADD_DEFINITIONS(-Os -Wall -Werror -Wmissing-declarations --std=gnu99)

SET(SOURCES
    main.c
    config/config.c
    tank/helper_functions.c
    tank/tank_json_api.c
    tank/tank_router.c
    tank/gpio.c
)

ADD_EXECUTABLE(spytank-server ${SOURCES})

FIND_LIBRARY(libwembed NAMES wembed libwembed)
FIND_LIBRARY(libjson NAMES json-c json)
TARGET_LINK_LIBRARIES(spytank-server ${libwembed} ${libjson})

INSTALL(TARGETS spytank-server
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
)
