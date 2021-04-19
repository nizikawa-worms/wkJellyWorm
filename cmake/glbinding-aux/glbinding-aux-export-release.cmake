#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "glbinding::glbinding-aux" for configuration "Release"
set_property(TARGET glbinding::glbinding-aux APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(glbinding::glbinding-aux PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/glbinding-aux.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/./glbinding-aux.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS glbinding::glbinding-aux )
list(APPEND _IMPORT_CHECK_FILES_FOR_glbinding::glbinding-aux "${_IMPORT_PREFIX}/lib/glbinding-aux.lib" "${_IMPORT_PREFIX}/./glbinding-aux.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
