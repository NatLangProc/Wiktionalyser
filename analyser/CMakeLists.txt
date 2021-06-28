cmake_minimum_required(VERSION 3.19)
project(analyser)

set(CMAKE_CXX_STANDARD 14)

include_directories(../SimpleSaxParser)

if(CMAKE_COMPILER_IS_GNUCXX)
    SET(GCC_COVERAGE_COMPILE_FLAGS "-Werror=return-type")
    add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
else()
    add_definitions(-DUSE64bit=true)
endif()

add_executable(analyser AnalyserTest.cpp
        Analyser.cpp Analyser.h Node.cpp Node.h
        GenericPayload.cpp GenericPayload.h
        Language.cpp Language.h Etymology.cpp Etymology.h Template.cpp Template.h
        Pronunciation.cpp Pronunciation.h Pos.cpp Pos.h Definition.cpp Definition.h
        Synonyms.cpp Synonyms.h Sense.cpp Sense.h
        Hyponyms.cpp Hyponyms.h DerivedTerms.cpp DerivedTerms.h
        Translations.cpp Translations.h
        ../SimpleSaxParser/SaxParser.cpp)

