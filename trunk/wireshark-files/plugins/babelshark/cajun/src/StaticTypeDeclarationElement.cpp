#include "StaticTypeDeclarationElement.h"
namespace PDI
{
	StaticTypeDeclaration::StaticTypeDeclaration(char* label, int size)
	{
		_Label = label;
		_Size = size;
	}

	// MDD - added to prevent link error
	StaticTypeDeclaration::StaticTypeDeclaration(const StaticTypeDeclaration& value)
	{
		// TODO
	}

	// MDD - added to prevent link error
	StaticTypeDeclaration::~StaticTypeDeclaration()
	{
		// TODO
	}
}
