include_directories(Catch/single_include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${CMAKE_BINARY_DIR}) # for config.h
add_definitions("-DTEST_DATA_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\"")

if(WITH_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    
    find_program(LCOV NAMES lcov PATHS /usr/bin /usr/local/bin)
    find_program (GCOV NAMES gcov gcov-7 gcov-6 gcov-5 PATHS /usr/bin /usr/local/bin)

    if(LCOV AND GCOV)
        message(STATUS "lcov found: ${LCOV}")
        message(STATUS "gcov found: ${GCOV}")
        add_custom_target(coverage_tilde
            COMMAND ${LCOV}
                --gcov-tool=${GCOV}
                --directory ${PROJECT_BINARY_DIR} #"${CMAKE_BINARY_DIR}"
                --capture
                --remove "${CMAKE_SOURCE_DIR}/../imgui/imgui/*"
                --remove "${CMAKE_SOURCE_DIR}/src/Properties/json/*"
                --remove "${CMAKE_SOURCE_DIR}/tests/Catch/*"
                --output-file coverage_tilde.info
            COMMAND ${LCOV}
                --extract coverage_tilde.info
                    "${CMAKE_SOURCE_DIR}/src/*" 
                --remove "${CMAKE_SOURCE_DIR}/../imgui/imgui/*"
                --remove "${CMAKE_SOURCE_DIR}/src/Properties/json/*"
                --remove "${CMAKE_SOURCE_DIR}/tests/Catch/*"
                --output-file coverage_tilde.info
            COMMAND ${LCOV}
                --list coverage_tilde.info)
#            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}

        add_custom_target(coverage_report_tilde
            COMMAND genhtml --output-directory ${CMAKE_BINARY_DIR}/coverage_tilde coverage_tilde.info
            COMMAND open ${CMAKE_BINARY_DIR}/coverage_tilde/index.html)
    endif()
endif()

macro(tilde_add_test title name)
    add_executable("test_${name}" "test_${name}.cpp")
    target_link_libraries("test_${name}" test_catch_main_lib_tilde xpd_static pd_core_static )
    if (LCOV AND GCOV)
        target_link_libraries("test_${name}" gcov )
    endif()
    set(_exec_cmd "test_${name}")

    add_test(NAME ${title} COMMAND ${_exec_cmd})
endmacro()

add_library(test_catch_main_lib_tilde STATIC tests_catch_main.cpp)


tilde_add_test(properties tilde_properties)
target_sources(test_tilde_properties PUBLIC "${PROJECT_SOURCE_DIR}/src/Properties/Property.cpp")
target_sources(test_tilde_properties PUBLIC "${PROJECT_SOURCE_DIR}/src/Properties/PropertyList.cpp")
target_sources(test_tilde_properties PUBLIC "${PROJECT_SOURCE_DIR}/src/Properties/PropertyTypes.cpp")
target_sources(test_tilde_properties PUBLIC "${PROJECT_SOURCE_DIR}/src/FileIO/PdStringConverter.cpp")

tilde_add_test(undo tilde_undo)
target_sources(test_tilde_undo PUBLIC "${PROJECT_SOURCE_DIR}/src/Undo/UICommand.cpp")
target_sources(test_tilde_undo PUBLIC "${PROJECT_SOURCE_DIR}/src/Undo/UndoStack.cpp")

tilde_add_test(canvas_data tilde_canvas_data)
target_sources(test_tilde_canvas_data PUBLIC "${PROJECT_SOURCE_DIR}/src/DataModels/CanvasData.cpp")
target_sources(test_tilde_canvas_data PUBLIC "${PROJECT_SOURCE_DIR}/src/DataModels/Clipboard.cpp")
target_sources(test_tilde_canvas_data PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_imgui_mvc.h")
target_sources(test_tilde_canvas_data PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_views.h")
target_sources(test_tilde_canvas_data PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_canvas_data.h")

tilde_add_test(object_base tilde_object_base)
target_sources(test_tilde_object_base PUBLIC "${PROJECT_SOURCE_DIR}/src/Views/UIObjectBase.cpp")
target_sources(test_tilde_object_base PUBLIC "${PROJECT_SOURCE_DIR}/src/Properties/Property.cpp")
target_sources(test_tilde_object_base PUBLIC "${PROJECT_SOURCE_DIR}/src/Properties/PropertyTypes.cpp")
target_sources(test_tilde_object_base PUBLIC "${PROJECT_SOURCE_DIR}/src/FileIO/PdStringConverter.cpp")
target_sources(test_tilde_object_base PUBLIC "${PROJECT_SOURCE_DIR}/src/Views/UIObjectFactory.cpp")

tilde_add_test(object_data tilde_object_data)
target_sources(test_tilde_object_data PUBLIC "${PROJECT_SOURCE_DIR}/src/DataModels/UIObjectData.cpp")
target_sources(test_tilde_object_data PUBLIC "${PROJECT_SOURCE_DIR}/src/Properties/Property.cpp")
target_sources(test_tilde_object_data PUBLIC "${PROJECT_SOURCE_DIR}/src/Properties/PropertyList.cpp")
target_sources(test_tilde_object_data PUBLIC "${PROJECT_SOURCE_DIR}/src/FileIO/PdStringConverter.cpp")

tilde_add_test(file_io tilde_file_io)
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/src/FileIO/FileParser.cpp")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/src/FileIO/FileSaver.cpp")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/src/FileIO/LegacyParser.cpp")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_imgui_mvc.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_views.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_view_controllers.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_app_controller.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_patch_controller.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_grid.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_undostack.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_common_menus.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_patch_menus.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_preferences.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_properties_window.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_uiobject_base.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_uiobject.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/src/FileIO/PdStringConverter.cpp")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_clipboard.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_fileparser.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_filesaver.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_object_menu.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_arrangeobjects.h")
target_sources(test_tilde_file_io PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_object_base.h")

tilde_add_test(patch_controller tilde_patch_controller)
target_sources(test_tilde_patch_controller PUBLIC "${PROJECT_SOURCE_DIR}/src/Controllers/Patch/PdPatchViewController.cpp")
target_sources(test_tilde_patch_controller PUBLIC "${PROJECT_SOURCE_DIR}/src/Controllers/Patch/PutMenuActions.cpp")
#target_sources(test_tilde_patch_controller PUBLIC "${PROJECT_SOURCE_DIR}/src/Controllers/Patch/ArrangeObjects.cpp")
target_sources(test_tilde_patch_controller PUBLIC "${PROJECT_SOURCE_DIR}/src/Views/UIObjectFactory.cpp")

tilde_add_test(console_controller tilde_console_controller)
target_sources(test_tilde_console_controller PUBLIC "${PROJECT_SOURCE_DIR}/src/Controllers/PdConsoleViewController.cpp")

tilde_add_test(app_controller tilde_app_controller)
target_sources(test_tilde_app_controller PUBLIC "${PROJECT_SOURCE_DIR}/src/Controllers/AppController.cpp")
target_sources(test_tilde_app_controller PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_console_controller.h")
target_sources(test_tilde_app_controller PUBLIC "${PROJECT_SOURCE_DIR}/tests/mocks/mock_app_controller_base.h")


