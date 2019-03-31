include(ExternalProject)


###############################################################################
# CUSP
###############################################################################

ExternalProject_Add(
    cusplibrary
    
    GIT_REPOSITORY "ssh://git@tower:9022/yao/cusplibrary.git"
    GIT_TAG        "origin/cuda9"
    
    SOURCE_DIR     "${PROJECT_SOURCE_DIR}/dependencies/cusplibrary_cuda9"

    CONFIGURE_COMMAND  ""
    BUILD_COMMAND   ""
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
)
set_target_properties(cusplibrary PROPERTIES EXCLUDE_FROM_ALL TRUE)

set(cusp_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/dependencies/cusplibrary_cuda9")
include_directories(${cusp_INCLUDE_DIRS})

###############################################################################
# Yao
###############################################################################

ExternalProject_Add(
    yao
    
    GIT_REPOSITORY  "ssh://git@tower:9022/yao/YaoLib.git"
    GIT_TAG         "origin/master"

    SOURCE_DIR      "${PROJECT_SOURCE_DIR}/dependencies/yaolibrary"
 
    CONFIGURE_COMMAND  ""
    BUILD_COMMAND   ""
    INSTALL_COMMAND ""
)
set_target_properties(yao PROPERTIES EXCLUDE_FROM_ALL TRUE)

set(yao_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/dependencies/yaolibrary")
include_directories(${yao_INCLUDE_DIRS})


###############################################################################
# json
###############################################################################
ExternalProject_Add(
    json
    
    GIT_REPOSITORY "ssh://git@tower:9022/yao/json.git"
    GIT_TAG        "origin/develop"
    
    SOURCE_DIR     "${PROJECT_SOURCE_DIR}/dependencies/json"

    CONFIGURE_COMMAND  ""
    BUILD_COMMAND   ""
    INSTALL_COMMAND ""
)
set_target_properties(json PROPERTIES EXCLUDE_FROM_ALL TRUE)

set(json_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/dependencies/json/include")

include_directories(${json_INCLUDE_DIRS})

###############################################################################
# CUDA sample
###############################################################################
include_directories($ENV{NVCUDASAMPLES_ROOT}/common/inc)