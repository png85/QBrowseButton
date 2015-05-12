find_package(Qt4 COMPONENTS QtGui QtCore)
if(Qt4_FOUND AND QBrowseButton_ENABLE_QT4)
    if(WIN32)
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(QBrowseButton_LIBRARY QBrowseButton4d)
        else(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(QBrowseButton_LIBRARY QBrowseButton4)
        endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    else(WIN32)
        set(QBrowseButton_LIBRARY QBrowseButton4)
    endif(WIN32)

    #
    # QBrowseButton4: Qt4 version of QBrowseButton widget
    set(QBrowseButton_SRCS ../src/QBrowseButton.cc ../include/QBrowseButton.h ../src/qbrowsebutton.qrc)
    if(WIN32)
        list(APPEND QBrowseButton_SRCS ../src/QBrowseButton.rc)
    endif(WIN32)
    add_library(${QBrowseButton_LIBRARY} ${LIB_TYPE} ${QBrowseButton_SRCS})
    target_compile_features(${QBrowseButton_LIBRARY} PRIVATE cxx_nullptr)
    target_link_libraries(${QBrowseButton_LIBRARY} Qt4::QtGui Qt4::QtCore)
    if(UNIX AND QBrowseButton_BUILD_SHARED_LIBS)
        set_target_properties(${QBrowseButton_LIBRARY} PROPERTIES SONAME "${QBrowseButton_LIBRARY}"
                                                       VERSION ${QBrowseButton_VERSION_MAJOR}.${QBrowseButton_VERSION_MINOR}
                                                       SOVERSION ${QBrowseButton_VERSION_MAJOR})
    endif(UNIX AND QBrowseButton_BUILD_SHARED_LIBS)
    generate_export_header(${QBrowseButton_LIBRARY} BASE_NAME QBrowseButton
                                                    EXPORT_MACRO_NAME QBrowseButton_EXPORT
                                                    EXPORT_FILE_NAME QBrowseButton4_Export.h
                                                    STATIC_DEFINE QBrowseButton_BUILT_AS_STATIC)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QBrowseButton4_Export.h DESTINATION include/)
    install(TARGETS ${QBrowseButton_LIBRARY} ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)

    #
    # QBrowseButton4-test: Demo executable for Qt4
    if(QBrowseButton_WITH_EXAMPLE)
        add_executable(${QBrowseButton_LIBRARY}-test ../src/test.cc)
        target_compile_features(${QBrowseButton_LIBRARY}-test PRIVATE cxx_nullptr cxx_lambdas)
        target_link_libraries(${QBrowseButton_LIBRARY}-test ${QBrowseButton_LIBRARY} Qt4::QtCore Qt4::QtGui)
        install(TARGETS ${QBrowseButton_LIBRARY}-test RUNTIME DESTINATION bin)
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
        set(Plugin_SRCS ../src/QBrowseButtonDesignerFactory.cc ../include/QBrowseButtonDesignerFactory.h)
        if(WIN32)
            list(APPEND Plugin_SRCS ../src/QBrowseButtonDesignerFactory.rc)
        endif(WIN32)
        add_library(${QBrowseButton_LIBRARY}Plugin SHARED ${Plugin_SRCS})
        target_compile_features(${QBrowseButton_LIBRARY}Plugin PRIVATE cxx_nullptr)
        target_link_libraries(${QBrowseButton_LIBRARY}Plugin QBrowseButton4 Qt4::QtGui Qt4::QtCore)
        install(TARGETS ${QBrowseButton_LIBRARY}Plugin ARCHIVE DESTINATION lib/qt4/plugins/designer LIBRARY DESTINATION lib/qt4/plugins/designer RUNTIME DESTINATION lib/qt4/plugins/designer)
    endif(QBrowseButton_WITH_DESIGNER_PLUGIN)
endif(Qt4_FOUND AND QBrowseButton_ENABLE_QT4)
