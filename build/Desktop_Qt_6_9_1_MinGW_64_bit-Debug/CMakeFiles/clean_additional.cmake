# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SlayTheShrike_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SlayTheShrike_autogen.dir\\ParseCache.txt"
  "SlayTheShrike_autogen"
  )
endif()
