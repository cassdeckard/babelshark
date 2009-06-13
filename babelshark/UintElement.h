#ifndef UNIT_ELEMENT_H
#define UINT_ELEMENT_H

#include <bitset>
#include "InstructionElement.h"



namespace BabelShark
{
	class UintElement: public InstructionElement
	{
		public:
			UintElement(unsigned int size, char* name);
			~UintElement();
			
			//TODO -- Implement this
			//Will be used to read in data from packet (I think??)
			void Interpret(char* buffer);
			
			//TODO -- Implement this
			//will be used to Display data to the WireShark output
			char* Display();
			
			//Creates a NullIterator because an InstructionElement
			//should have no children.
			void CreateIterator();

			std::bitset<64> GetBitMask(){ return _BitMask;}
		private:
			void SetupBitMask(unsigned int val);
			std::bitset<64> _BitMask;
			//NullIterator has not been implented yet.
			//when it is, this class is to construct an object
			//of type NullIterator
			//NullIterator* nullIterator;	
	};
}


#endif //UINT_ELEMENT_H