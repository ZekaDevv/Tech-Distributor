# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/tech_distributor_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/tech_distributor_autogen.dir/ParseCache.txt"
  "tech_distributor_autogen"
  )
endif()
