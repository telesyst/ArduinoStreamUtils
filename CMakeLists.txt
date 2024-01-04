set(includedirs src)

set(req arduino)

idf_component_register(
	INCLUDE_DIRS ${includedirs} 
	SRC_DIRS src
	SRCS ${SOURCES}
	REQUIRES ${req})