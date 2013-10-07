#ifndef SINGLETON_H
#define SINGLETON_H

template<class T>
/*! \brief A Singleton-pattern template
* ...to allow for multiple Singletons from the same class. Neat. */
class Singleton {
private:
	Singleton()		{}
	~Singleton()	{}
public:
/*! Retrieves the single instance of the selected (template) class
* \return Returns the unique instance */
	static T& get() {
		static T singleInstance;
		return singleInstance;
	}
};

#endif //SINGLETON_H