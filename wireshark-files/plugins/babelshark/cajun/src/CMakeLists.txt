include_directories(../include)
include_directories(../../include)

add_library(cajun SHARED
            BabelSharkSupport.cpp
            DynamicTypeDeclarationCollection.cpp
            DynamicTypeDeclarationElement.cpp
            elements.cpp
            reader.cpp
            StaticTypeDeclarationCollection.cpp
            StaticTypeDeclarationElement.cpp
)
