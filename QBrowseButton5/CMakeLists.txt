find_package(Qt5Widgets)

if(Qt5Widgets_FOUND AND QBrowseButton_ENABLE_QT5)
    #
    # QBrowseButton5: Qt5 version of QBrowseButton widget
    add_library(QBrowseButton5 ${LIB_TYPE} ../src/QBrowseButton.cc ../include/QBrowseButton.h ../src/qbrowsebutton.qrc)
    qt5_use_modules(QBrowseButton5 Widgets)
    set_target_properties(QBrowseButton5 PROPERTIES COMPILE_DEFINITIONS "QBrowseButton_EXPORTS" ${QT_DEFINITIONS})
    if(UNIX AND QBrowseButton_BUILD_SHARED_LIBS)
        set_target_properties(QBrowseButton5 PROPERTIES SONAME "QBrowseButton5"
                                                        VERSION ${QBrowseButton_VERSION_MAJOR}.${QBrowseButton_VERSION_MINOR}
                                                        SOVERSION ${QBrowseButton_VERSION_MAJOR})
    endif(UNIX AND QBrowseButton_BUILD_SHARED_LIBS)
    generate_export_header(QBrowseButton5 BASE_NAME QBrowseButton
                                          EXPORT_MACRO_NAME QBrowseButton_EXPORT
                                          EXPORT_FILE_NAME QBrowseButton5_Export.h
                                          STATIC_DEFINE QBrowseButton_BUILT_AS_STATIC)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QBrowseButton5_Export.h DESTINATION include/)
    install(TARGETS QBrowseButton5 ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)

    #
    # QBrowseButton5-test: Demo executable for Qt5
    if(QBrowseButton_WITH_EXAMPLE)
        add_executable(QBrowseButton5-test ../src/test.cc)
        target_link_libraries(QBrowseButton5-test QBrowseButton5)
        qt5_use_modules(QBrowseButton5-test Widgets)
        install(TARGETS QBrowseButton5-test RUNTIME DESTINATION bin)
    endif(QBrowseButton_WITH_EXAMPLE)

    #
    # QBrowseButton5Plugin: Qt Designer plugin for Qt5
    if(QBrowseButton_WITH_DESIGNER_PLUGIN)
        list(APPEND QBrowseButton5Plugin_DEFINITIONS ${QT_DEFINITIONS} QT_DLL QT_PLUGIN QT_SHARED)
        add_library(QBrowseButton5Plugin SHARED ../src/QBrowseButtonDesignerFactory.cc ../include/QBrowseButtonDesignerFactory.h)
        target_link_libraries(QBrowseButton5Plugin QBrowseButton5)
        set_target_properties(QBrowseButton5Plugin PROPERTIES COMPILE_DEFINITIONS ${QBrowseButton5Plugin_DEFINITIONS})
        qt5_use_modules(QBrowseButton5Plugin Widgets)
        install(TARGETS QBrowseButton5Plugin ARCHIVE DESTINATION lib/qt5/plugins/designer LIBRARY DESTINATION lib/qt5/plugins/designer RUNTIME DESTINATION lib/qt5/plugins/designer)
    endif(QBrowseButton_WITH_DESIGNER_PLUGIN)
endif(Qt5Widgets_FOUND AND QBrowseButton_ENABLE_QT5)
