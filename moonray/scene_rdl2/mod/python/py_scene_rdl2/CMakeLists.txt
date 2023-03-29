# Copyright 2023 DreamWorks Animation LLC
# SPDX-License-Identifier: Apache-2.0

cmake_path(GET PROJECT_SOURCE_DIR FILENAME package_name)
set(component __${package_name}__)

find_package(Python COMPONENTS Interpreter Development)
# find_package(Boost REQUIRED
#   COMPONENTS
#     system
#     python
#     date_time
#     chrono)
# -----------------------------------
# NOTE: (Marcelo) This is for boost-1.70 or newer.
# Since we are using Python 3, boost will be 1.70.x
# Finding Boost Python using Boost provided cmake.config fails.
option(Boost_NO_BOOST_CMAKE "Disable boost-provided cmake config" ON) # boost-1.70+
if($ENV{REZ_PYTHON_VERSION} EQUAL "3.7.7")
    find_package(Boost REQUIRED
        COMPONENTS
            system
            date_time
            chrono
            python37
    )
    set(Boost_PYTHON_LIBRARY "${Boost_PYTHON37_LIBRARY}")
elseif($ENV{REZ_PYTHON_VERSION} EQUAL "3.9.7")
    find_package(Boost REQUIRED
        COMPONENTS
            system
            date_time
            chrono
            python39
    )
    set(Boost_PYTHON_LIBRARY "${Boost_PYTHON39_LIBRARY}")
endif()
# -----------------------------------

add_library(${component} SHARED "")
add_library(${PROJECT_NAME}::${component} ALIAS ${component})

target_sources(${component}
    PRIVATE
        py_scene_rdl2_attribute.cc
        py_scene_rdl2_camera.cc
        py_scene_rdl2.cc
        py_scene_rdl2_displacement.cc
        py_scene_rdl2_enums.cc
        py_scene_rdl2_envmap.cc
        py_scene_rdl2_geometry.cc
        py_scene_rdl2_geometry_set.cc
        py_scene_rdl2.h
        py_scene_rdl2_helpers.cc
        py_scene_rdl2_helpers.h
        py_scene_rdl2_layer.cc
        py_scene_rdl2_light.cc
        py_scene_rdl2_light_filter.cc
        py_scene_rdl2_light_set.cc
        py_scene_rdl2_map.cc
        py_scene_rdl2_material.cc
        py_scene_rdl2_metadata.cc
        py_scene_rdl2_misc.cc
        py_scene_rdl2_node.cc
        py_scene_rdl2_proxies.cc
        py_scene_rdl2_render_output.cc
        py_scene_rdl2_scene_class.cc
        py_scene_rdl2_scene_context.cc
        py_scene_rdl2_scene_object.cc
        py_scene_rdl2_scene_variables.cc
        py_scene_rdl2_types.cc
        py_scene_rdl2_userdata.cc)

target_include_directories(${component}
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(${component} SYSTEM
    PRIVATE
        ${Python_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
)

# target_link_libraries(${component}
#     PRIVATE
#         Boost::system
#         Boost::python
#         Boost::date_time
#         Boost::chrono
#         ${PROJECT_NAME}::${package_name}
#         ${Python_LIBRARIES}
# )
# -----------------------------------
# NOTE: (Marcelo) This is for boost-1.70 or newer.
if($ENV{REZ_PYTHON_VERSION} EQUAL "3.7.7")
    target_link_libraries(${component}
        PRIVATE
            Boost::system
            Boost::python37
            Boost::date_time
            Boost::chrono
            ${PROJECT_NAME}::${package_name}
            ${Python_LIBRARIES}
    )
elseif($ENV{REZ_PYTHON_VERSION} EQUAL "3.9.7")
    target_link_libraries(${component}
        PRIVATE
            Boost::system
            Boost::python39
            Boost::date_time
            Boost::chrono
            ${PROJECT_NAME}::${package_name}
            ${Python_LIBRARIES}
    )
endif()
# -----------------------------------

if(${Python_VERSION_MAJOR} VERSION_GREATER_EQUAL 3)
    target_compile_definitions(${component}
        PRIVATE
            IS_PY3
            BOOST_BIND_GLOBAL_PLACEHOLDERS
    )
else()
    target_compile_definitions(${component}
        PRIVATE
            BOOST_BIND_GLOBAL_PLACEHOLDERS
    )
    if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
        target_compile_options(${component} PRIVATE -Wno-register)
    endif()
endif()

# Suppress prefix "lib" because Python does not allow this prefix
set_target_properties(${component} PROPERTIES PREFIX "")

# Set standard compile/link options
SceneRdl2_cxx_compile_definitions(${component})
SceneRdl2_cxx_compile_features(${component})
SceneRdl2_cxx_compile_options(${component})
SceneRdl2_link_options(${component})

set(python_install_dir
    python/lib/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/${package_name})

install(TARGETS ${component} DESTINATION ${python_install_dir})

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py DESTINATION ${python_install_dir})
