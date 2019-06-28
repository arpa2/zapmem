cmake_minimum_required (VERSION 3.7)
project ("ARPA2 ZapMem" C)

# Pretty reporting of packages
include (FeatureSummary)

# Look for the module itself. Set properties here, because ARPA2CM
# might not be installed to set them itself.
find_package (ARPA2CM 0.5 QUIET NO_MODULE)
set_package_properties (ARPA2CM PROPERTIES
    DESCRIPTION "CMake modules for ARPA2 projects"
    TYPE REQUIRED
    URL "https://github.com/arpa2/arpa2cm/"
    PURPOSE "Required for the CMake build system for ${PROJECT}"
)

# If found, use it, otherwise report error and stop CMake.
if (ARPA2CM_FOUND)
    set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ARPA2CM_MODULE_PATH})
else()
    feature_summary (WHAT ALL)
    message (FATAL_ERROR "ARPA2CM is required.")
endif()

include (GNUInstallDirs)

#
# Build
#

include_directories (${CMAKE_SOURCE_DIR}/include)

add_library (arpa2zapmem SHARED ${CMAKE_SOURCE_DIR}/src/zapmem.c)

add_executable (testzap ${CMAKE_SOURCE_DIR}/test/testzap.c)
target_link_libraries (testzap arpa2zapmem)


#
# Builds for tests
#

add_library (wrap_dozapmem SHARED ${CMAKE_SOURCE_DIR}/test/wrap_dozapmem.c)
add_library (wrap_nozapmem SHARED ${CMAKE_SOURCE_DIR}/test/wrap_nozapmem.c)


#
# Test
#

enable_testing ()

add_test (NAME testzap
          COMMAND testzap)

add_test (NAME testzap-counted
          COMMAND testzap 0)

# Can we do this on Windows too?
add_test (NAME testzap-counted-dozap
    COMMAND ${CMAKE_COMMAND} -E env LD_PRELOAD=$<TARGET_FILE:wrap_dozapmem>
            ${CMAKE_COMMAND} -E env DYLD_INSERT_LIBRARIES=$<TARGET_FILE:wrap_dozapmem>
            $<TARGET_FILE:testzap> 0)

# Can we do this on Windows too?
add_test (NAME testzap-counted-dontzap
    COMMAND ${CMAKE_COMMAND} -E env LD_PRELOAD=$<TARGET_FILE:wrap_nozapmem>
            ${CMAKE_COMMAND} -E env DYLD_INSERT_LIBRARIES=$<TARGET_FILE:wrap_nozapmem>
            $<TARGET_FILE:testzap> 0)
#TODO# Last check should be much higher, 125 or so

#
# Install
#

install (FILES ${CMAKE_SOURCE_DIR}/include/arpa2/zapmem.h
         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/arpa2)

install (TARGETS arpa2zapmem
         DESTINATION ${CMAKE_INSTALL_LIBDIR}/arpa2)

#
# Packaging
#

set (CPACK_PACKAGE_NAME "zapmem")
set (CPACK_PACKAGE_VERSION ${zapmem_VERSION})
set (CPACK_PACKAGE_VENDOR "ARPA2.net")
set (CPACK_PACKAGE_CONTACT "Rick van Rein <rick@openfortress.nl>")
# License information for packaging. This uses the SPDX license
# identifiers from https://spdx.org/licenses/
set (CPACK_FREEBSD_PACKAGE_LICENSE "BSD-2-Clause")
include (PackAllPossible)
include (CPack)

