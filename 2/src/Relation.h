#ifndef RELATION_H
#define RELATION_H

/*
If subjector is 0 no object is needed?
*/

class Relation {
public:
	Relation();
	Relation( 
		unsigned p_idSubject, 
		unsigned p_idSubjector,
		unsigned p_idAction,
		unsigned p_influence );
	~Relation();

	unsigned getIdSubject()		const;
	unsigned getIdSubjector()	const;
	unsigned getIdAction()		const;
	unsigned getInfluence()		const;
protected:
private:
	unsigned m_idSubject;	// Object being subject to influence.
	unsigned m_idSubjector;	// The influencing object.
	unsigned m_idAction;	// The relevant action.
	unsigned m_influence;	// How property-value will be affected.
};

#endif // RELATION_H