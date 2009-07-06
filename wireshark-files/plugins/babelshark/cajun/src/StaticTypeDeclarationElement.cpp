#include "StaticTypeDeclarationElement.h"
namespace PDI
{
   StaticTypeDeclaration::StaticTypeDeclaration(const std::string& label, int size)
   {
      _Label = label;
      _Size = size;
   }
   const std::string& StaticTypeDeclaration::GetLabel() const { return _Label; }

}
