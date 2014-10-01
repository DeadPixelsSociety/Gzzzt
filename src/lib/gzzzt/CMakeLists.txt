include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SFML2_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include/gzzzt)

# Client
file(GLOB LIBGZZZT0_SRC
	"client/*.cc"
)

add_library(gzzzt0 SHARED
  ${LIBGZZZT0_SRC}
)

target_link_libraries(gzzzt0
  ${Boost_LIBRARIES}
  ${SFML2_LIBRARIES}
)

set_target_properties(gzzzt0
  PROPERTIES
  VERSION ${CPACK_PACKAGE_VERSION}
  SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}
  LIBRARY_OUTPUT_DIRECTORY client
)

install(
  TARGETS gzzzt0
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

# Server
file(GLOB LIBGZZZTSERVER0_SRC
	"server/*.cc"
)

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
  LIBRARY_OUTPUT_DIRECTORY server
)

install(
  TARGETS gzzzt-server0
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

# Shared
file(GLOB LIBGZZZTSHARED0_SRC
	"shared/*.cc"
)

add_library(gzzzt-shared0 SHARED
  ${LIBGZZZTSHARED0_SRC}
)

target_link_libraries(gzzzt-shared0
  ${Boost_LIBRARIES}
  ${SFML2_LIBRARIES}
)

set_target_properties(gzzzt-shared0
  PROPERTIES
  VERSION ${CPACK_PACKAGE_VERSION}
  SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}
  LIBRARY_OUTPUT_DIRECTORY shared
)

install(
  TARGETS gzzzt-shared0
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
