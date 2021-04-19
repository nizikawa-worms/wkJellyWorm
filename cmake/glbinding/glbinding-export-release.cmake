#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "glbinding::glbinding" for configuration "Release"
set_property(TARGET glbinding::glbinding APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(glbinding::glbinding PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/glbinding.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/./glbinding.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS glbinding::glbinding )
list(APPEND _IMPORT_CHECK_FILES_FOR_glbinding::glbinding "${_IMPORT_PREFIX}/lib/glbinding.lib" "${_IMPORT_PREFIX}/./glbinding.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
