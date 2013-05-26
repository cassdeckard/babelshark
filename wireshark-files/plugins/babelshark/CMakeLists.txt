cmake_minimum_required(VERSION 2.8)
project(babelshark)

# TODO: find this rather than hardcoding it
include_directories(../../../../wireshark)

# TODO: remove this from #ifdef directives
add_definitions(-DHAVE_CONFIG_H)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB_PKG glib-2.0)
include_directories(${GLIB_PKG_INCLUDE_DIRS})
include_directories(include)
include_directories(cajun/include)

add_library(babelshark SHARED
	    packet-babelshark.cpp
            src/AliasedInstruction.cpp
            src/AsciiElement.cpp
            src/BoolElement.cpp
            src/DataDictionary.cpp
            src/Dissector.cpp
            src/DynamicDefinition.cpp
            src/FloatElement.cpp
            src/Instruction.cpp
            src/InstructionElement.cpp
            src/InstructionSet.cpp
            src/IntElement.cpp
            src/Iterator.cpp
            src/ListIterator.cpp
            src/NullIterator.cpp
            src/PadElement.cpp
            src/StaticDefinition.cpp
            src/Subject.cpp
            src/UintElement.cpp
            cajun/src/BabelSharkSupport.cpp
            cajun/src/DynamicTypeDeclarationCollection.cpp
            cajun/src/DynamicTypeDeclarationElement.cpp
            cajun/src/elements.cpp
            cajun/src/reader.cpp
            cajun/src/StaticTypeDeclarationCollection.cpp
            cajun/src/StaticTypeDeclarationElement.cpp
)
