
find_path(Cec_INCLUDE_DIR libcec/cec.h)

find_library(Cec_LIBRARY NAMES cec)

set(Cec_LIBRARIES ${Cec_LIBRARY})
set(Cec_INCLUDE_DIRS ${Cec_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(Cec DEFAULT_MSG Cec_LIBRARY Cec_INCLUDE_DIR)
mark_as_advanced(Cec Cec_INCLUDE_DIR Cec_LIBRARY)

