include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include/gzzzt)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

# Client
file(GLOB GZZZT_SRC
	"client/*.cc"
)

add_executable(gzzzt ${GZZZT_SRC})

target_link_libraries(gzzzt
  gzzzt0
  gzzzt-shared0
  ${Boost_LIBRARIES}
)

set_target_properties(gzzzt
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY client/
)

install(
  TARGETS gzzzt
  RUNTIME DESTINATION games
)

# Server
file(GLOB GZZZTSERVER_SRC
	"server/*.cc"
)

add_executable(gzzzt-server ${GZZZTSERVER_SRC})

target_link_libraries(gzzzt-server
  gzzzt-server0
  gzzzt-shared0
  ${Boost_LIBRARIES}
)

set_target_properties(gzzzt-server
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY server/
)

install(
  TARGETS gzzzt-server
  RUNTIME DESTINATION games
)

