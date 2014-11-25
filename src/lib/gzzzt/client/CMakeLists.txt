include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SFML2_INCLUDE_DIRS})

file(GLOB LIBGZZZT0_SRC "*.cc")

add_library(gzzzt0 SHARED
  ${LIBGZZZT0_SRC}
)

target_link_libraries(gzzzt0
  ${Boost_LIBRARIES}
  ${SFML2_LIBRARIES}
  ${LIBTMX_LIBRARIES}
)

set_target_properties(gzzzt0
  PROPERTIES
  VERSION ${CPACK_PACKAGE_VERSION}
  SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}
)

install(
  TARGETS gzzzt0
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
