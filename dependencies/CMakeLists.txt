include(ExternalProject)


###############################################################################
# CUSP
###############################################################################

ExternalProject_Add(
    cusplibrary
    
    GIT_REPOSITORY "git@git.ustclug.org:yaoxu/cusplibrary.git"
    GIT_TAG        "cuda9"
    
    SOURCE_DIR     "${PROJECT_SOURCE_DIR}/dependencies/cusplibrary_cuda9"

    CONFIGURE_COMMAND  ""
    BUILD_COMMAND   ""
    INSTALL_COMMAND ""

    UPDATE_DISCONNECTED 1
)
set_target_properties(cusplibrary PROPERTIES EXCLUDE_FROM_ALL TRUE)

set(cusp_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/dependencies/cusplibrary_cuda9")
include_directories(${cusp_INCLUDE_DIRS})

###############################################################################
# Yao
###############################################################################

ExternalProject_Add(
    yao
    
    GIT_REPOSITORY  "git@git.ustclug.org:yaoxu/YaoLib.git"
    GIT_TAG         "master"

    SOURCE_DIR      "${PROJECT_SOURCE_DIR}/dependencies/yaolibrary"
 
    CONFIGURE_COMMAND  ""
    BUILD_COMMAND   ""
    INSTALL_COMMAND ""

    UPDATE_DISCONNECTED 1
)
set_target_properties(yao PROPERTIES EXCLUDE_FROM_ALL TRUE)

set(yao_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/dependencies/yaolibrary")
include_directories(${yao_INCLUDE_DIRS})


###############################################################################
# json
###############################################################################
ExternalProject_Add(
    json
    
    GIT_REPOSITORY "git@git.ustclug.org:yaoxu/json_backup.git"
    GIT_TAG        "develop"
    
    SOURCE_DIR     "${PROJECT_SOURCE_DIR}/dependencies/json"

    CONFIGURE_COMMAND  ""
    BUILD_COMMAND   ""
    INSTALL_COMMAND ""

    UPDATE_DISCONNECTED 1
)
set_target_properties(json PROPERTIES EXCLUDE_FROM_ALL TRUE)

set(json_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/dependencies/json/src")
include_directories(${json_INCLUDE_DIRS})

###############################################################################
# CUDA sample
###############################################################################
include_directories($ENV{NVCUDASAMPLES_ROOT}/common/inc)