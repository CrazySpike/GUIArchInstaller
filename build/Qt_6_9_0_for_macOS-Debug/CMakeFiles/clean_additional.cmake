# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/archinstaller_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/archinstaller_autogen.dir/ParseCache.txt"
  "archinstaller_autogen"
  )
endif()
