#ifndef STATIC_TYPE_DECLARATION_H
#define STATIC_TYPE_DECLARATION_H

#include <string>
#include "elements.h"

namespace PDI
{

   /** The StaticTypeDefinition class holds one "statictype" read in from a PDI file.
   * An example dynamictype in PDI file format follows:
   * statictype HEADER {
   *    "MessageID" : "UINT 8 $MSG_ID",
   *    "Pad"       : "PAD 8",
   *    "EventID"   : "UINT 16",
   *    "Name"      : "ASCII 16",
   *    "Pad2"      : "PAD 32"
   * }
   * where MessageID has a special mapping to our DataDictionary
   * through the alias $MSG_ID
   ***/

	class StaticTypeDeclaration : public Array
	{
		public:
			StaticTypeDeclaration(const std::string& label, int size);

			//member variable Set functions
         void SetLabel(const std::string& input){_Label = input;}
			void SetSize(int size){_Size = size;}

			//member variable Get functions
         const std::string& GetLabel() const;
			int GetSize() { return _Size;}

		private:
			std::string _Label;
			int _Size;
	};
}

#endif //STATIC_TYPE_DEFINITION_H
