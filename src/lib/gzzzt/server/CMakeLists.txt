include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SFML2_INCLUDE_DIRS})

file(GLOB LIBGZZZTSERVER0_SRC "*.cc")

add_library(gzzzt-server0 SHARED
  ${LIBGZZZTSERVER0_SRC}
)

target_link_libraries(gzzzt-server0
  ${Boost_LIBRARIES}
  ${SFML2_LIBRARIES}
)

set_target_properties(gzzzt-server0
  PROPERTIES
  VERSION ${CPACK_PACKAGE_VERSION}
  SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}
)

install(
  TARGETS gzzzt-server0
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
