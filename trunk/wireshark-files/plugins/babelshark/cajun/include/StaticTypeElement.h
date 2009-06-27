#ifndef STATIC_TYPE_ELEMENT_H
#define STATIC_TYPE_ELEMENT_H

#include <string>
#include "Elements.h"

namespace PDI
{
	class StaticType : public Array
	{
		public:
			StaticType(char* label, int size);
			char* GetLabel(){ return _Label;}
			int GetSize() { return _Size;}
		private:
			std::string _Label;
			int _Size;
	}
}

#endif //STATIC_TYPE_ELEMENT_H