#ifndef EXECUTIONER_H
#define EXECUTIONER_H

#include <vector>

#include "Action.h"
#include "Result.h"
#include "Location.h"
#include "Destination.h"

class Executioner {
public:
	Executioner();
	~Executioner();

	bool execute( Action* p_action, Result& io_result );
protected:
private:
	bool executeTravel( 	ActionTravel* 	p_action, Result& io_result );
	// Currently we assume that all interactions are either picking up, or dropping movable objects:
	bool executeInteract( 	ActionInteract* p_action, Result& io_result );
	bool executeGame( 		ActionGame*		p_action, Result& io_result );

	bool interactTake(Verb p_target, Result& io_result);
	bool interactDrop(Verb p_target, Result& io_result);
	bool interactSay(Verb p_target, Result& io_result);

	bool sayXyzzy(Verb p_target, Result& io_result);
	bool sayPlugh(Verb p_target, Result& io_result);
	bool sayPlover(Verb p_target, Result& io_result);

	bool teleport(Verb p_target, bool p_canTeleport, Result& io_result);
	void discoverMagicWords(int p_locationId);
	bool feefie(unsigned p_wordIndex, Result& io_result);
	std::vector<bool> m_feefie;

	bool m_xyzzy;
	bool m_plugh;
	bool m_plover;
	bool m_fee;
};

#endif // EXECUTIONER_H