include_directories(${SFML2_INCLUDE_DIRS})

file(GLOB PHYSICS_SRC "*.cc")

add_executable(physics ${PHYSICS_SRC})

target_link_libraries(physics
  gzzzt-server0
  gzzzt-shared0
  ${SFML2_LIBRARIES}
)
