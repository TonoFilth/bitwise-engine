#include <emscripten.h>
#include "Bw/Base/DefaultAssertHandler.h"
#include "Bw/Base/CharArray.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Class std functions
////////////////////////////////////////////////////////////////////////////////
DefaultAssertHandler::DefaultAssertHandler()
{
}

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void DefaultAssertHandler::operator()(const char* exp, const char* file, int line)
{
	char message[512];

	// Split the assert message in two alerts because
	// the character '\n' produces a Javascript exception
	CharArray::Format(message, 512, "alert('Assertion failed: ( %s )')", exp);
	emscripten_run_script(message);

	CharArray::Format(message, 512, "alert('File: %s:%d')", file, line);
	emscripten_run_script(message);
}

}	// namespace bw