#ifndef DRIVER_H
#define DRIVER_H

#include <istream>
#include "../include/dictionnary.h"
#include "../include/ParseError.h"

namespace SimplexParser
{
	class Parser;
	class Lexer;
	class Driver
	{
		public:
			Driver();
			Driver(const Driver& other);
			Driver& operator= (const Driver& other);
			~Driver();
			Dictionnary parse(std::string& fileName);
			Dictionnary parse(std::istream& inputStream);
			void setResult(Dictionnary& result);

		private:
			Lexer* lexer;
			Parser* parser;
			Dictionnary result;
			friend class Parser;
			friend class Lexer;
	};
}

#endif // DRIVER_H
