#include "StaticTypeDeclarationElement.h"
namespace PDI
{
	StaticTypeDeclaration::StaticTypeDeclaration(char* label, int size)
	{
		_Label = label;
		_Size = size;
	}
}