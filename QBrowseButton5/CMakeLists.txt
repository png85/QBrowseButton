find_package(Qt5Widgets)

if(Qt5Widgets_FOUND AND QBrowseButton_ENABLE_QT5)
    if(WIN32)
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(QBrowseButton_LIBRARY QBrowseButton5d)
        else(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(QBrowseButton_LIBRARY QBrowseButton5)
        endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    else(WIN32)
        set(QBrowseButton_LIBRARY QBrowseButton5)
    endif(WIN32)

    #
    # QBrowseButton5: Qt5 version of QBrowseButton widget
    add_library(${QBrowseButton_LIBRARY} ${LIB_TYPE} ../src/QBrowseButton.cc ../include/QBrowseButton.h ../src/qbrowsebutton.qrc)
    target_compile_features(${QBrowseButton_LIBRARY} PRIVATE cxx_nullptr)
    qt5_use_modules(${QBrowseButton_LIBRARY} Widgets)
    set_target_properties(${QBrowseButton_LIBRARY} PROPERTIES COMPILE_DEFINITIONS "QBrowseButton_EXPORTS" ${QT_DEFINITIONS})
    if(UNIX AND QBrowseButton_BUILD_SHARED_LIBS)
        set_target_properties(${QBrowseButton_LIBRARY} PROPERTIES SONAME "QBrowseButton5"
                                                        VERSION ${QBrowseButton_VERSION_MAJOR}.${QBrowseButton_VERSION_MINOR}
                                                        SOVERSION ${QBrowseButton_VERSION_MAJOR})
    endif(UNIX AND QBrowseButton_BUILD_SHARED_LIBS)
    generate_export_header(${QBrowseButton_LIBRARY} BASE_NAME QBrowseButton
                                                    EXPORT_MACRO_NAME QBrowseButton_EXPORT
                                                    EXPORT_FILE_NAME QBrowseButton5_Export.h
                                                    STATIC_DEFINE QBrowseButton_BUILT_AS_STATIC)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QBrowseButton5_Export.h DESTINATION include/)
    install(TARGETS ${QBrowseButton_LIBRARY} ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)

    #
    # QBrowseButton5-test: Demo executable for Qt5
    if(QBrowseButton_WITH_EXAMPLE)
        add_executable(${QBrowseButton_LIBRARY}-test ../src/test.cc)
        target_compile_features(${QBrowseButton_LIBRARY}-test PRIVATE cxx_nullptr cxx_lambdas)
        target_link_libraries(${QBrowseButton_LIBRARY}-test QBrowseButton5)
        qt5_use_modules(${QBrowseButton_LIBRARY}-test Widgets)
        install(TARGETS ${QBrowseButton_LIBRARY}-test RUNTIME DESTINATION bin)
    endif(QBrowseButton_WITH_EXAMPLE)

    #
    # QBrowseButton5Plugin: Qt Designer plugin for Qt5
    if(QBrowseButton_WITH_DESIGNER_PLUGIN)
        list(APPEND ${QBrowseButton_LIBRARY}Plugin_DEFINITIONS ${QT_DEFINITIONS} QT_DLL QT_PLUGIN QT_SHARED)
        add_library(${QBrowseButton_LIBRARY}Plugin SHARED ../src/QBrowseButtonDesignerFactory.cc ../include/QBrowseButtonDesignerFactory.h)
        target_compile_features(${QBrowseButton_LIBRARY}Plugin PRIVATE cxx_nullptr)
        target_link_libraries(${QBrowseButton_LIBRARY}Plugin QBrowseButton5)
        set_target_properties(${QBrowseButton_LIBRARY}Plugin PROPERTIES COMPILE_DEFINITIONS ${QBrowseButton5Plugin_DEFINITIONS})
        qt5_use_modules(${QBrowseButton_LIBRARY}Plugin Widgets)
        install(TARGETS ${QBrowseButton_LIBRARY}Plugin ARCHIVE DESTINATION lib/qt5/plugins/designer LIBRARY DESTINATION lib/qt5/plugins/designer RUNTIME DESTINATION lib/qt5/plugins/designer)
    endif(QBrowseButton_WITH_DESIGNER_PLUGIN)
endif(Qt5Widgets_FOUND AND QBrowseButton_ENABLE_QT5)
