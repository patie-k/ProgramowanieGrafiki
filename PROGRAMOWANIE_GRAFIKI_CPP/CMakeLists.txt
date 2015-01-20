# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Tutorials)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-1c73e35")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.0.3/include/GLFW/
	external/glm-0.9.4.0/
	external/glew-1.9.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	GLFW_303
	GLEW_190
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# Zadanie 1 - ksztalty
add_executable(zadanie1_ksztalty 
	zadanie1_ksztalty/zadanie1_ksztalty.cpp
	common/shader.cpp
	common/shader.hpp
	
	zadanie1_ksztalty/SimpleFragmentShader.fragmentshader
	zadanie1_ksztalty/SimpleVertexShader.vertexshader
)
target_link_libraries(zadanie1_ksztalty
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(zadanie1_ksztalty PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/zadanie1_ksztalty/")
create_target_launcher(zadanie1_ksztalty WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/zadanie1_ksztalty/")
create_default_target_launcher(zadanie1_ksztalty WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/zadanie1_ksztalty/") # tut 1 is not the default or people would complain that tut 2 doesn't work

# Zadanie 2 - klawiatura
add_executable(zadanie2_klawiatura 
	zadanie2_klawiatura/zadanie2_klawiatura.cpp
	common/shader.cpp
	common/shader.hpp

	zadanie2_klawiatura/SimpleFragmentShader.fragmentshader
	zadanie2_klawiatura/SimpleVertexShader.vertexshader
)
#set_target_properties(zadanie2_klawiatura PROPERTIES RUNTIME_OUTPUT_DIRECTORY /test1)
target_link_libraries(zadanie2_klawiatura
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(zadanie2_klawiatura PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/zadanie2_klawiatura/")
create_target_launcher(zadanie2_klawiatura WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/zadanie2_klawiatura/") # Visual

# Zadanie 3 - textura
add_executable(zadanie3_textura
	zadanie3_textura/zadanie3_textura.cpp
	common/shader.cpp
	common/shader.hpp
	
	zadanie3_textura/SimpleFragmentShader.fragmentshader
	zadanie3_textura/SimpleVertexShader.vertexshader
)
target_link_libraries(zadanie3_textura
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(zadanie3_textura PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/zadanie3_textura/")
create_target_launcher(zadanie3_textura WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/zadanie3_textura/")

# Zadanie 4 - wczytywanie
add_executable(zadanie4_wczytywanie
	zadanie4_wczytywanie/zadanie4_wczytywanie.cpp
	common/shader.cpp
	common/shader.hpp
	common/texture.cpp
	common/texture.hpp
	
	zadanie4_wczytywanie/SimpleFragmentShader.fragmentshader
	zadanie4_wczytywanie/SimpleVertexShader.vertexshader
)
target_link_libraries(zadanie4_wczytywanie
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(zadanie4_wczytywanie PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/zadanie4_wczytywanie/")
create_target_launcher(zadanie4_wczytywanie WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/zadanie4_wczytywanie/")

# Zadanie 5 - swiatlo
add_executable(zadanie5_swiatlo
	zadanie5_swiatlo/zadanie5_swiatlo.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	
	zadanie5_swiatlo/SimpleFragmentShader.fragmentshader
	zadanie5_swiatlo/SimpleVertexShader.vertexshader
)
target_link_libraries(zadanie5_swiatlo
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(zadanie5_swiatlo PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/zadanie5_swiatlo/")
create_target_launcher(zadanie5_swiatlo WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/zadanie5_swiatlo/")

# Zadanie 6 - licznik
add_executable(zadanie6_licznik
	zadanie6_licznik/zadanie6_licznik.cpp
	common/shader.cpp
	common/shader.hpp
	common/texture.cpp
	common/texture.hpp
	common/text2D.cpp
	common/text2D.hpp

	zadanie6_licznik/SimpleFragmentShader.fragmentshader
	zadanie6_licznik/SimpleVertexShader.vertexshader
	zadanie6_licznik/TextVertexShader.fragmentshader
	zadanie6_licznik/TextVertexShader.vertexshader
	
)
target_link_libraries(zadanie6_licznik
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(zadanie6_licznik PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/zadanie6_licznik/")
create_target_launcher(zadanie6_licznik WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/zadanie6_licznik/")



SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )


if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

add_custom_command(
   TARGET zadanie1_ksztalty POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/zadanie1_ksztalty${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/zadanie1_ksztalty/"
)
add_custom_command(
   TARGET zadanie2_klawiatura POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/zadanie2_klawiatura${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/zadanie2_klawiatura/"
)
add_custom_command(
   TARGET zadanie3_textura POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/zadanie3_textura${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/zadanie3_textura/"
)
add_custom_command(
   TARGET zadanie4_wczytywanie POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/zadanie4_wczytywanie${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/zadanie4_wczytywanie/"
)
add_custom_command(
   TARGET zadanie5_swiatlo POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/zadanie5_swiatlo${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/zadanie5_swiatlo/"
)
add_custom_command(
   TARGET zadanie6_licznik POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/zadanie6_licznik${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/zadanie6_licznik/"
)


elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

