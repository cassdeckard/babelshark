// $Id$

#ifndef DATA_DICTIONARY_H
#define DATA_DICTIONARY_H

#include "Singleton.h"
#include "Instruction.h"
#include "InstructionElement.h"
#include "TypeDefinition.h"
#include "StaticDefinition.h"
#include "DynamicDefinition.h"
#include <map>
#include <list>

#define DATA_DICT BabelShark::DataDictionary::Instance()

namespace BabelShark
{
    /** DataDictionary acts as a single point of reference for globally
      * defined data Instructions depend upon. This includes:
      *  - Static type definitions
      *  - Dynamic type definitions
      *  - Protocol variables
      *
      * It implements the Singleton pattern, so its constructor is protected
      * and cannot be accessed directly. To make calls to the DataDictionary,
      * the static Instance() method is used to retrieve a reference to the
      * single instantiation of the class.
      *
      * <b>Pattern roles:</b>
      *  - Singleton::Singleton
      */
	class DataDictionary : public Singleton<DataDictionary>
	{
        public:

           /** AddVariable adds a declaration of a protocol variable
             * to the DataDictionary. A protocol variable is stored as
             * a pointer to the variable's associated InstructionElement.
             *
             * <b>Pattern roles:</b>
             *  - Singleton::SingletonOperation()
             *
             * @param alias
             *   the label given to the variable (usually starting with '$')
             * @param variable
             *   pointer to the InstructionElement the variable references
             */
           void AddVariable(std::string alias, InstructionElement* variable);

           /** AddStatic adds a declaration of a static type
             * to the DataDictionary. A static type is stored as
             * a pointer to the type's associated InstructionNode.
             *
             * <b>Pattern roles:</b>
             *  - Singleton::SingletonOperation()
             *
             * @param alias
             *   the label given to the type (usually starting with '&')
             * @param type
             *   pointer to the InstructionNode the type references
             */
           void AddStatic(std::string alias, InstructionNode* type);

           /** AddDynamic adds a part of the declaration of a dynamic type
             * to the DataDictionary. Each call to AddDynamic adds a new
             * value-type pair to the definition.
             *
             * <b>Pattern roles:</b>
             *  - Singleton::SingletonOperation()
             *
             * @param alias
             *   the label of the type we're adding to (usually starting with '&')
             * @param value
             *   the value half of the value-type pair being added
             * @param typeName
             *   the alias of the type half of the value-type pair being added
             *
             */
           void AddDynamic(std::string alias, std::string value, std::string typeName);

           /** LookupType looks up the requested type name and sets the supplied
             * InstructionNode* to point to the appropriate InstructionNode according
             * to the type's definition and, if the type is dynamic, its parameter.
             *
             * <b>Pattern roles:</b>
             *  - Singleton::GetSingletonData()
             *
             * @param target
             *   pointer to the Instruction* that should be set to the requested definition
             * @param alias
             *   the label of the requested type
             * @param parameter
             *   (only for dynamic types) the parameter of the requested dynamic type
             */
           void LookupType(InstructionNode** target, std::string alias, InstructionElement* parameter = NULL );

           /** LookupVariable looks up the requested variable name and returns the
             * InstructionElement associated with it.
             *
             * <b>Pattern roles:</b>
             *  - Singleton::GetSingletonData()
             *
             * @param label
             *   the label of the requested variable (usually starts with '$')
             * @return
             *   the variable's associated InstructionElement
             */
           InstructionElement* LookupVariable(std::string alias);

           /** ToInitialize adds an Instruction to the list of things
             * that need to be initialized after all Instruction objects
             * have been instantiated
             *
             * @param instruction
             *   instruction to add to the initialization list
             */
           void ToInitialize(Instruction* instruction);

           /** Initialize calls Initialize() on all of the Instructions
             * in our initialization list
             */
           void Initialize();

           /** NullInstruction() is the accessor for _NullInstruction
             * which represents an undefined static type
             */
           InstructionNode* NullInstruction() { return _NullInstruction; }

        protected:

        private:

           /** _Variables stores the mapping of aliases to protocol variables
             *
             * <b>Pattern roles:</b>
             *  - Singleton::singletonData
             */
           std::map<std::string, InstructionElement*> _Variables;

           /** _Types stores the mapping of aliases to type definitions.
             *
             * <b>Pattern roles:</b>
             *  - Singleton::singletonData
             */
           std::map<std::string, TypeDefinition*> _Types;

           /** _ToInitialize is a list of Instructions that need to be
             * initialized
             */
           std::list<Instruction*> _ToInitialize;

           /** _NullInstruction represents an undefined static type and
             * is returned whenever a type is requested that does not exist.
             */
           InstructionNode* _NullInstruction;
	};

}

#endif //DATA_DICTIONARY_H
