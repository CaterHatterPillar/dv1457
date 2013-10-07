#ifndef EXECUTIONER_H
#define EXECUTIONER_H

#include <vector>

#include "Action.h"
#include "Result.h"

class Executioner {
public:
	Executioner();
	~Executioner();

	bool execute( Action* p_action, Result& io_result );
protected:
private:

};

#endif // EXECUTIONER_H