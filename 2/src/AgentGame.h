#ifndef AGENTGAME_H
#define AGENTGAME_H

#include "Action.h"
#include "Result.h"

class AgentGame {
public:
	AgentGame();
	~AgentGame();

	static bool execute( ActionGame* p_action, Result& io_result );
protected:
private:
};

#endif // AGENTGAME_H