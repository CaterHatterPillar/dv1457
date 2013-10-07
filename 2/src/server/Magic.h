#ifndef MAGIC_H
#define MAGIC_H

class Magic
{
public:
	Magic();
	~Magic();

	void setXyzzy(	bool p_xyzzy 	);
	void setPlugh(	bool p_plugh 	);
	void setPlover(	bool p_plover 	);
	void setFee(	bool p_fee 		);

	bool getXyzzy();
	bool getPlugh();
	bool getPlover();
	bool getFee();
private:
	bool m_xyzzy;
	bool m_plugh;
	bool m_plover;
	bool m_fee;
};

#endif // MAGIC_H