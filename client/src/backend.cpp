#include "parameters.h"
#include "serverProgram.h"

serverProgram serverProgram::serverprogram(SERVER_PORT);

int run() {
	
	std::srand(time(NULL)); // use current time as seed for random generator
	serverProgram::instance().init();
	serverProgram::instance().run();
	return 0;
}
