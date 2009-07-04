#include "StaticTypeDeclarationElement.h"
namespace PDI
{
	StaticTypeDeclaration::StaticTypeDeclaration(std::string label, int size)
	{
		_Label = label;
		_Size = size;
	}

   StaticTypeDeclaration::StaticTypeDeclaration(const std::string& label, int size)
	{
		_Label = label;
		_Size = size;
	}

	// MDD - added to prevent link error
	StaticTypeDeclaration::StaticTypeDeclaration(const StaticTypeDeclaration& value)
	{
		// TODO
		_Label = value.GetLabel();
		_Size = value.GetSize();
	}

	// MDD - added to prevent link error
	StaticTypeDeclaration::~StaticTypeDeclaration()
	{
		// TODO
	}
}
