include_directories(../include)
include_directories(../cajun/include)

add_library(babelshark SHARED
            AliasedInstruction.cpp
            AsciiElement.cpp
            BoolElement.cpp
            DataDictionary.cpp
            Dissector.cpp
            DynamicDefinition.cpp
            FloatElement.cpp
            Instruction.cpp
            InstructionElement.cpp
            InstructionSet.cpp
            IntElement.cpp
            Iterator.cpp
            ListIterator.cpp
            NullIterator.cpp
            PadElement.cpp
            StaticDefinition.cpp
            Subject.cpp
            UintElement.cpp
)
