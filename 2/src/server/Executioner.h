#ifndef EXECUTIONER_H
#define EXECUTIONER_H

#include "Agent.h"
#include "Action.h"
#include "Result.h"

class Executioner {
public:
	Executioner( AdventData& p_ad );
	~Executioner();

	bool execute( Action* p_action, Result& io_result );
protected:
private:
	Agent* m_agent;
};

#endif // EXECUTIONER_H