find_package(Qt4 COMPONENTS QtGui QtCore)
if(Qt4_FOUND AND QBrowseButton_ENABLE_QT4)
    #
    # QBrowseButton4: Qt4 version of QBrowseButton widget
    add_library(QBrowseButton4 ${LIB_TYPE} ../src/QBrowseButton.cc ../include/QBrowseButton.h ../src/qbrowsebutton.qrc)
    target_compile_features(QBrowseButton4 PRIVATE cxx_nullptr)
    target_link_libraries(QBrowseButton4 Qt4::QtGui Qt4::QtCore)
    if(UNIX AND QBrowseButton_BUILD_SHARED_LIBS)
        set_target_properties(QBrowseButton4 PROPERTIES SONAME "QBrowseButton4"
                                                        VERSION ${QBrowseButton_VERSION_MAJOR}.${QBrowseButton_VERSION_MINOR}
                                                        SOVERSION ${QBrowseButton_VERSION_MAJOR})
    endif(UNIX AND QBrowseButton_BUILD_SHARED_LIBS)
    generate_export_header(QBrowseButton4 BASE_NAME QBrowseButton
                                          EXPORT_MACRO_NAME QBrowseButton_EXPORT
                                          EXPORT_FILE_NAME QBrowseButton4_Export.h
                                          STATIC_DEFINE QBrowseButton_BUILT_AS_STATIC)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QBrowseButton4_Export.h DESTINATION include/)
    install(TARGETS QBrowseButton4 ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)

    #
    # QBrowseButton4-test: Demo executable for Qt4
    if(QBrowseButton_WITH_EXAMPLE)
        add_executable(QBrowseButton4-test ../src/test.cc)
        target_compile_features(QBrowseButton4-test PRIVATE cxx_nullptr cxx_lambdas)
        target_link_libraries(QBrowseButton4-test QBrowseButton4 Qt4::QtCore Qt4::QtGui)
        install(TARGETS QBrowseButton4-test RUNTIME DESTINATION bin)
    endif(QBrowseButton_WITH_EXAMPLE)

    #
    # QBrowseButton4Plugin: Qt Designer plugin for Qt4
    if(QBrowseButton_WITH_DESIGNER_PLUGIN)
        add_definitions(${QT_DEFINITIONS})
        if(WIN32)
            add_definitions(-DQT_DLL)
        endif(WIN32)
        add_definitions(-DQT_PLUGIN)
        add_definitions(-DQT_SHARED)
        add_library(QBrowseButton4Plugin SHARED ../src/QBrowseButtonDesignerFactory.cc ../include/QBrowseButtonDesignerFactory.h)
        target_compile_features(QBrowseButton4Plugin PRIVATE cxx_nullptr)
        target_link_libraries(QBrowseButton4Plugin QBrowseButton4 Qt4::QtGui Qt4::QtCore)
        install(TARGETS QBrowseButton4Plugin ARCHIVE DESTINATION lib/qt4/plugins/designer LIBRARY DESTINATION lib/qt4/plugins/designer RUNTIME DESTINATION lib/qt4/plugins/designer)
    endif(QBrowseButton_WITH_DESIGNER_PLUGIN)
endif(Qt4_FOUND AND QBrowseButton_ENABLE_QT4)
