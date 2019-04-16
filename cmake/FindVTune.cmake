
# - Find VTune ittnotify.
# Defines:
# VTune_FOUND
# VTune_INCLUDE_DIRS
# VTune_LIBRARIES
set(dirs
  "C:/Program Files (x86)/IntelSWTools/VTune Amplifier/"
  "C:/Program Files (x86)/Intel/VTune Amplifier XE 2013/"
  "$ENV{VTUNE_AMPLIFIER_XE_2011_DIR}/"
  "C:/Program Files (x86)/Intel/VTune Amplifier XE 2011/"
  )

find_path(VTune_INCLUDE_DIRS ittnotify.h
    PATHS ${dirs}
    PATH_SUFFIXES include)

if (CMAKE_SIZEOF_VOID_P MATCHES "8")
  set(vtune_lib_dir lib64)
else()
  set(vtune_lib_dir lib32)
endif()

find_library(VTune_LIBRARIES libittnotify
    HINTS "${VTune_INCLUDE_DIRS}/.."
    PATHS ${dirs}
    PATH_SUFFIXES ${vtune_lib_dir})


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    VTune DEFAULT_MSG VTune_LIBRARIES VTune_INCLUDE_DIRS)


if(VTune_FOUND AND NOT TARGET VTune::VTune)
    add_library(VTune::VTune INTERFACE IMPORTED)
    set_target_properties(VTune::VTune PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${VTune_INCLUDE_DIRS}"
        INTERFACE_LINK_LIBRARIES "${VTune_LIBRARIES}"
    )
endif()
