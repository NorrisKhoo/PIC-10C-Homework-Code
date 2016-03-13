/**	@mainpage PIC 10C Homework 1 Particles
	@title PIC 10C Homework 1 Particles
	@author Norris Khoo
	@date 01-11-2016

	This program models particles on a line. The base Thing object carries an int position value while the derived ThingA and ThingB
	objects carry additional string and double properties respectively. Stored on a Board object, behavior of the particles are constrained
	by the requirement that ThingB objects may not inhabit the same position as other particles of either type.
*/

/**	@file hw1.cpp
	@brief This file contains code expanding upon the provided Thing, ThingA, ThingB and Board classes. The goal of this assignment
	is to review PIC 10B concepts and practice proper commenting procedure

	Functionality of the provided classes has been expanded by overloading the <<, [] and () operators to print out particles on
	the board, to determine if any particles on the board are at the input position and to determine if any particles on the board
	share the same position respectively. The code is called and tested in main to ensure that the new functions work properly in
	all scenarios. Although the revised requirements for hw1 omit question 2, I have included my original work for the problem
*/

#include <iostream>
#include <string>
#include <vector>

/**	@class Thing
	@brief The Thing class creates a base particle and stores its position as an int
	The Thing class serves as the base class for the ThingA and ThingB derived classes which store particles with added string and
	double properties respectively. Virtual has been included on its get_position(), print and destructor functions to ensure that
	the right version is called (if equivalent functions are implemented in the derived class)
*/
class Thing {
public:
	/** Constructs the base Thing object with an int value
		@param pos is the int value serving as the particle's position
	*/
	Thing(int pos) : position(pos) {};
	
	/**	Returns the position value of the base Thing object. Virtual is included to make sure the correct form of the function is called
		in derived classes
		@return the position value of the base Thing object
	*/
	virtual int get_position() const { return position; };
	
	/**	Function does not generate output but rather is included so that the virtual keyword may direct versions of print in derived classes
		to the correct form
		@param out is the ostream object being output to
	*/
	virtual void print(std::ostream& out) const {};
	
	/**	Destructor. Virtual is included to ensure that correct form of destructor is called for derived classes
	*/
	virtual ~Thing() {};
protected:
	int position;
};

//Forward declaration
class Board;

/**	@class ThingA
	@brief The ThingA class creates a particle derived from Thing with an added string property
	The ThingA class is derived from the Thing class but adds a string property and a const reference to the board to which it belongs. Its
	own print and destructor functions have been implemented
*/
class ThingA : public Thing {
public:
	/**	Constructs the derived ThingA object with an int position value, a string property and a const reference to the board to which it
		belongs
		@param pos is the int value serving as the particle's position
		@param prop is the string serving as the particle's property
		@param b is the board to which the ThingA object belongs
	*/
	ThingA(int pos, std::string prop, const Board& b) : Thing(pos), property(prop), board(b) {};
	
	/**	Outputs the ThingA object to the referenced ostream
		@param out is the ostream object being output to
	*/
	void print(std::ostream& out) const { out << "A:" << get_position() << ":" << property; };
	
	/**	Destructor for the derived ThingA object
	*/
	~ThingA() {};
private:
	std::string property;
	const Board& board;
};

/**	@class ThingB
	@brief The ThingB class creates a particle derived from Thing with an added double property
	The ThingB class is derived from the Thing class but adds a double property and a const reference to the board to which it belongs. Its
	own print and destructor functions have been implemented. In addition, the propose_new_position function determines whether a new
	position is suitable (ThingB objects cannot share the same position with other particles) and if so changes its value to the input
*/
class ThingB : public Thing {
public:
	/**	Constructs the derived ThingB object with an int position value, a double property and a const reference to the board to which it
		belongs
		@param pos is the int value serving as the particle's position
		@param prop is the double value serving as the particle's property
		@param b is the board to which the ThingB object belongs
	*/
	ThingB(int pos, double prop, const Board& b) : Thing(pos), property(prop), board(b) {};
	
	bool propose_new_position(int a);
	
	/**	Outputs the ThingB object to the referenced ostream
		@param out is the ostream object being output to
	*/
	void print(std::ostream& out) const { out << "B:" << get_position() << ":" << property; };
	
	/**	Destructor for the derived ThingB object
	*/
	~ThingB() {};
private:
	double property;
	const Board& board;
};

/**	@class Board
	@brief The Board class contains Thing particles by storing pointers to the objects in a vector
	The Board class is confined by the requirement that ThingA particles may share the same position with ThingB particles but ThingB
	particles cannot share the same position with objects of either type. Functions have been included to add ThingA and ThingB particles
	to the board. In addition, functions have been included and operators [] () overloaded to perform tasks related to whether objects
	are located at various positions. The operator << has been overloaded to output the Board object
*/
class Board {
public:
	friend std::ostream& operator<<(std::ostream& out, const Board& b);
	
	/**	Determines whether a particle exists at a particular position
		@param pos is the int value being compared with positions of the particles
		@return a bool value: true if a particle exists at the position and false otherwise
	*/
	bool ParticleInPosition(int pos) const {
		//for loop cycles through the things vector storing pointers to the particles
		for (size_t i = 0; i < things.size(); ++i) {
			//get_position() is called from pointer
			//if position at things[i] equals input pos return true (there is an object at the position)
			if (things[i]->get_position() == pos) {
				return true;
			}
		}
		return false;
	}
	
	/**	Creates a new ThingA particle in the heap and adds a pointer directed to it to the board
		@param pos is the int position value for the new ThingA object
		@param prop is the string property for new ThingA object
	*/
	void AddAParticle(int pos, std::string prop) {
		ThingA* thing = new ThingA(pos, prop, *this);
		things.push_back(thing);
	}
	
	/**	If there exists no other particle sharing the input position, creates a new ThingB particle in the heap and adds a pointer
		directed to it in the things vector of the Board
		@param pos is the int position value for the new ThingB object
		@param prop is the double property for the new ThingB object
		@return a bool value: true if ThingB object can be added and false otherwise
	*/
	bool AddBParticle(int pos, double prop) {
		//if no particle is at position pos, then add, otherwise don't add
		if (!ParticleInPosition(pos)) {
			ThingB* thing = new ThingB(pos, prop, *this);
			things.push_back(thing);
			return true;
		}
		return false;
	}
	
	bool operator[](int a) const;
	
	bool operator()() const;
	
	~Board();
private:
	std::vector<Thing*> things;
};

int main() {
	Board Z;
	Z.AddAParticle(0, "Red");
	Z.AddBParticle(9, 2.7128);
	Z.AddAParticle(7, "Yellow");
	Z.AddBParticle(12, 24601);
	std::cout << Z << std::endl;
	
	std::cout << "Are there any Particles in position 9? ";
	bool a = Z[9];
	if (a) { std::cout << "Yes" << std::endl; }
	else { std::cout << "No" << std::endl; }
	std::cout << std::endl;
	
	std::cout << "Are there any Particles in position 2? ";
	bool b = Z[2];
	if (b) { std::cout << "Yes" << std::endl; }
	else { std::cout << "No" << std::endl; }
	std::cout << std::endl;

	std::cout << "Are there any Particles that share the same position? ";
	bool c = Z();
	if (c) { std::cout << "Yes" << std::endl; }
	else { std::cout << "No" << std::endl; }
	std::cout << std::endl;

	Z.AddAParticle(12, "John Cena");
	std::cout << Z << std::endl;
	std::cout<<"After adding a Particle, now are there any Particles that share the same position? ";
	bool d = Z();
	if (d) { std::cout << "Yes" << std::endl; }
	else { std::cout << "No" << std::endl; }
	std::cout << std::endl;

	ThingB copy = ThingB(20, 12.5, Z);
	copy.print(std::cout);
	std::cout << std::endl << std::endl;
	
	std::cout << "We propose the change the Particle's position to 12. Will it work? ";
	bool e = copy.propose_new_position(12);
	if (e) { std::cout << "Yes" << std::endl; }
	else { std::cout << "No" << std::endl; }
	copy.print(std::cout);
	std::cout << std::endl << std::endl;

	std::cout << "We propose the change the Particle's position to 24. Will it work? ";
	bool f = copy.propose_new_position(24);
	if (f) { std::cout << "Yes" << std::endl; }
	else { std::cout << "No" << std::endl; }
	copy.print(std::cout);
	std::cout << std::endl << std::endl;

	return 0;
}

/**	Operator<< has been overloaded to output Board object to ostream. Particles of Board object are printed one line at the time using
	respective print functions (made possible by virtual keyword on void Thing::print(std::ostream& out) const)
	@param out is the ostream object being output to
	@param b is the Board object being printed
	@return a reference to the ostream object being output to
*/
std::ostream& operator<<(std::ostream& out, const Board& b) {
	//for loop cycles through things vector of pointers to call respective print function on each particle
	for (size_t i = 0; i < b.things.size(); ++i) {
		b.things[i]->print(out);
		out << std::endl;
	}
	return out;
}

/**	Determines whether a ThingB object can have its position changed to input int value (based on condition that ThingB objects cannot
	share position with other particles in its Board). If possible, position for the called ThingB object is changed to input int value.
	@param a is the input position being proposed
	@return a bool value: true if position is changed and false otherwise
*/
bool ThingB::propose_new_position(int a) {
	//uses overloaded [] operater to see if any other particles in board exist at the input position
	//if there exists another particle at the input position ([] returns true), ThingB position cannot be changed and function returns false
	if ((*this).board[a] == true) {
		return false;
	}
	//for all other cases (the Board does not contain a particle at input position), change position of called ThingB object and function returns true
	else {
		(*this).position = a;
		return true;
	}
}

/**	Operator[] has been overloaded to determine whether any particles on the Board have position same as the input value
	@param a is the input position being compared with position values for particles on the Board
	@return a bool value: true if there are any particles sharing the same input value position and false otherwise
*/
bool Board::operator[](int a) const {
	//for loop cycles through things vectors of pointers to call get_position() on each particle and compare with input position
	for (size_t i = 0; i < things.size(); ++i) {
		//calls get_position() on pointers to determine positions of their objects
		//if any positions equal input position returns true
		if (things[i]->get_position() == a) {
			return true;
		}
	}
	return false;
}

/**	Operator() has been overloaded to determine whether any particles on the Board share the same position
	@return a bool value: true if there are any particles sharing the same position and false otherwise.
*/
bool Board::operator()() const {
	//for loop cycles through things vector of pointers
	for (size_t i = 0; i < things.size(); ++i) {
		//at each iteration of above for loop, below for loop cycles through vector of pointers
		//each combination of i and k from 0 to things.size() will be reached
		//for loops combine to compare every position in the vector with each other
		for (size_t k = i + 1; k < things.size(); ++k) {
			//compares position at each value and returns true if they are equal
			if (things[i]->get_position() == things[k]->get_position()) {
				return true;
			}
		}
	}
	return false;
}

/**	Destructor for the Board class. Cycles through things vector of pointers to delete particle objects
*/
Board::~Board() {
	//for loop cycles through things vector of pointers to call delete on each particle object
	for (size_t i = 0; i < things.size(); ++i) {
		delete things[i];
	}
}
