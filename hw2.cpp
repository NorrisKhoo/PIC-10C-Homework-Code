/**	@mainpage PIC 10C Homework 2 Memory Leaks
	@title PIC 10C Homework 2 Memory Leaks
        @author Norris Khoo
	@date 01-15-2016

	For Homework 1
	This program models particles on a line. The base Thing object carries an int position value while the derived ThingA and ThingB
	objects carry additional string and double properties respectively. Stored on a Board object, behavior of the particles are constrained
	by the requirement that ThingB objects may not inhabit the same position as other particles of either type.

	For Homework 2
	Code has been updated to ensure that no memory leaks occur via implementation of a destructor and use of RAII. A confirmation that every new statement
	corresponds with a call to delete is printed by the destructor. Particles have been granted unique IDs particle count(type-position-property) and the 
	copy and swap idiom is implemented for the Board class
*/

/**	@file hw2.cpp
	@brief This file contains code expanding upon the provided Thing, ThingA, ThingB and Board classes. The goal of this assignment is to
	practice memory management and current C++ procedure (try/catch and copy/swap idiom)
	
	For Homework 1
	Functionality of the provided classes has been expanded by overloading the <<, [] and () operators to print out particles on
	the board, to determine if any particles on the board are at the input position and to determine if any particles on the board
	share the same position respectively. The code is called and tested in main to ensure that the new functions work properly in
	all scenarios. Although the revised requirements for hw1 omit question 2, I have included my original work for the problem

	For Homework 2
	Efficiency of the provided classes has been improved by implementation of RAII and the copy and swap idiom. The Board destructor
	prints a statement indicating the number of calls to new without a corresponding call to delete. According to this measure and use of Visual Leaks,
	the test code I included in main does not have any memory leaks. Functionality of the Particle classes has been expanded with implementation
	of an ID system that creates a unique label for each Particle object. The code (including the new copy and swap idiom) is called and tested in
	main to ensure that all functions work properly.
*/

#include <iostream>
#include <string>
#include <vector>
//#include <vld.h>
//Visual Leaks confirmed that no memory leaks occur. I commented it out just in case the grader's Visual Studio does not contain the program

class Thing {
public:
	Thing() : position(0), ID(std::to_string(0)) {
		++ID_counter;
	};
	
	Thing(int pos) : position(pos), ID(std::to_string(pos)) {
		++ID_counter;
	};

	virtual int get_position() const { return position; };

	virtual std::string get_ID() const { return ID; };
	
	virtual int get_ID_counter() const { return ID_counter; };

	virtual void print(std::ostream& out) const {};

	virtual int get_rank() const { return 0; };

	virtual ~Thing() {};
protected:
	int position;
	std::string ID;
	static int ID_counter;
};

//Forward declaration
class Board;

class ThingA : public Thing {
public:
	ThingA(int pos, std::string prop, const Board& b) : Thing(pos), property(prop), board(b) {
		ID = std::to_string(get_ID_counter()) + "(A-" + std::to_string(pos) + "-" + prop + ")";
	};

	void print(std::ostream& out) const { out << "A:" << get_position() << ":" << property << " ID:" << get_ID(); };

	int get_rank() const { return 1; };

	std::string get_property() const { return property; };

	~ThingA() {};
private:
	std::string property;
	const Board& board;
};

class ThingB : public Thing {
public:
	ThingB(int pos, double prop, const Board& b) : Thing(pos), property(prop), board(b) {
		ID = std::to_string(get_ID_counter()) + "(B-" + std::to_string(pos) + "-" + std::to_string(prop) + ")";
	};

	bool propose_new_position(int a);

	void print(std::ostream& out) const { out << "B:" << get_position() << ":" << property << " ID:" << get_ID(); };

	int get_rank() const { return 2; };

	double get_property() const { return property; };

	~ThingB() {};
private:
	double property;
	const Board& board;
};

class Board {
public:
	friend std::ostream& operator<<(std::ostream& out, const Board& b);

	Board() { things = std::vector<Thing*>(0); };

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

	void AddAParticle(int pos, std::string prop) {
		ThingA* thing = nullptr;
		//try to allocate heap memory safely
		//increment track because call to new deals with heap memory and thus requires corresponding delete at end of program
		try {
			thing = new ThingA(pos, prop, *this);
			++track;
		}
		//if error occurs print statement and set pointer to nullptr
		catch (std::exception& e) {
			std::cerr << "Failure at Board::AddAParticle(" << pos << ", " << prop << ", *this)" << std::endl;
			thing = nullptr;
		}
		//equivalent to if(thing != nullptr) ensures that pointer is not pushed back if pointer was not set to new object or catch statement occured
		if (thing) {
			things.push_back(thing);
		}
	}

	bool AddBParticle(int pos, double prop) {
		//if no particle is at position pos, then add, otherwise don't add
		if (!ParticleInPosition(pos)) {
			ThingB* thing = nullptr;
			//try to allocate heap memory safely
			//increment track because call to new deals with heap memory and thus requires corresponding delete at end of program
			try {
				thing = new ThingB(pos, prop, *this);
				++track;
			}
			//if error occurs print statement and set pointer to nullptr
			catch (std::exception& e) {
				std::cerr << "Failure at Board::AddBParticle(" << pos << ", " << prop << ", *this)" << std::endl;
				thing = nullptr;
			}
			//equivalent to if(thing != nullptr) ensures that pointer is not pushed back if pointer was not set to new object or catch statement occured
			if (thing) {
				things.push_back(thing);
				return true;
			}
		}
		return false;
	}

	bool operator[](int a) const;

	bool operator()() const;

	Board(const Board& copy);

	void swap(Board& other) {
		std::swap(things, other.things);
	}

	Board& operator=(Board copy) {
		copy.swap(*this);
		return *this;
	}

	virtual ~Board();
private:
	static int track;
	std::vector<Thing*> things;
};

int Board::track = 0;
int Thing::ID_counter = 0;

int main() {
	Board Z;
	Z.AddAParticle(0, "Red");
	Z.AddBParticle(9, 2.7128);
	Z.AddAParticle(7, "Yellow");
	Z.AddBParticle(12, 24601);
	std::cout << "Board Z is" << std::endl << Z << std::endl;

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
	std::cout << "After adding a Particle, now are there any Particles that share the same position? ";
	bool d = Z();
	if (d) { std::cout << "Yes" << std::endl; }
	else { std::cout << "No" << std::endl; }
	std::cout << std::endl;

	std::cout << "Board Y is a copy of Z" << std::endl;
	Board Y(Z);
	std::cout << Y << std::endl << std::endl;
	Y.AddAParticle(619, "Rey Mysterio");
	Y.AddBParticle(5, 12.34);
	std::cout << "After adding 2 Particles, Y is now:" << std::endl << Y << std::endl << std::endl;

	std::cout << "We will swap Y and Z:" << std::endl;
	Y.swap(Z);
	std::cout << "Y is now:" << std::endl << Y << "Z is now:" << std::endl << Z << std::endl << std::endl;

	Board X;
	std::cout << "We will assign the empty Board X the values of Board Z using operator=. X is now:" << std::endl;
	X = Z;
	std::cout << X << std::endl << std::endl;

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

}

std::ostream& operator<<(std::ostream& out, const Board& b) {
	//for loop cycles through things vector of pointers to call respective print function on each particle
	for (size_t i = 0; i < b.things.size(); ++i) {
		b.things[i]->print(out);
		out << std::endl;
	}
	return out;
}

bool ThingB::propose_new_position(int a) {
	//uses overloaded [] operater to see if any other particles in board exist at the input position
	//if there exists another particle at the input position ([] returns true), ThingB position cannot be changed and function returns false
	if ((*this).board[a] == true) {
		return false;
	}
	//for all other cases (the Board does not contain a particle at input position), change position (and correspondingly ID) of called ThingB object and function returns true
	else {
		(*this).position = a;
		(*this).ID = std::to_string(get_ID_counter()) + "(B-" + std::to_string(a) + "-" + std::to_string((*this).property) + ")";
		return true;
	}
}

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

Board::~Board() {
	//for loop cycles through things vector of pointers to call delete on each particle object
	//decrements track with every call to delete
	for (size_t i = 0; i < things.size(); ++i) {
		delete things[i];
		--track;
	}
	std::cout << track << " calls to new unaccounted for" << std::endl;
}

Board::Board(const Board& copy) {
	//iterates through copy's things vector to access pointers, determine type of object (Thing, ThingA, ThingB)
	//and access position/property to initialize appropriate new Particle object
	for (size_t i = 0; i < copy.things.size(); ++i) {
		//if rank is 0 pointer is to Thing object and appropriate constructor is called
		if (copy.things[i]->get_rank() == 0) {
			Thing* storage = nullptr;
			//try to allocate heap memory safely
			//increment track because call to new deals with heap memory and thus requires corresponding delete at end of program
			try {
				storage = new Thing(copy.things[i]->get_position());
				++track;
			}
			//if error occurs print statement and set pointer to nullptr
			catch (std::exception& e) {
				std::cerr << "Board(copy) failed to allocate memory" << std::endl;
				storage = nullptr;
			}
			//equivalent to if(thing != nullptr) ensures that pointer is not pushed back if pointer was not set to new object or catch statement occured
			if (storage) {
				things.push_back(storage);
			}
		}
		//if rank is 1 pointer is to ThingA object and appropriate constructor is called
		if (copy.things[i]->get_rank() == 1) {
			ThingA* storage_A = nullptr;
			//try to allocate heap memory safely
			//increment track because call to new deals with heap memory and thus requires corresponding delete at end of program
			try {
				storage_A = new ThingA(static_cast<ThingA*>(copy.things[i])->get_position(), static_cast<ThingA*>(copy.things[i])->get_property(), *this);
				++track;
			}
			//if error occurs print statement and set pointer to nullptr
			catch (std::exception& e) {
				std::cerr << "Board(copy) failed to allocate memory" << std::endl;
				storage_A = nullptr;
			}
			//equivalent to if(thing != nullptr) ensures that pointer is not pushed back if pointer was not set to new object or catch statement occured
			if (storage_A) {
				things.push_back(storage_A);
			}
		}
		//if rank is 2 pointer is to ThingB object and appropriate constructor is called
		if (copy.things[i]->get_rank() == 2) {
			ThingB* storage_B = nullptr;
			//try to allocate heap memory safely
			//increment track because call to new deals with heap memory and thus requires corresponding delete at end of program
			try {
				storage_B = new ThingB(static_cast<ThingB*>(copy.things[i])->get_position(), static_cast<ThingB*>(copy.things[i])->get_property(), *this);
				++track;
			}
			//if error occurs print statement and set pointer to nullptr
			catch (std::exception& e) {
				std::cerr << "Board(copy) failed to allocate memory" << std::endl;
				storage_B = nullptr;
			}
			//equivalent to if(thing != nullptr) ensures that pointer is not pushed back if pointer was not set to new object or catch statement occured
			if (storage_B) {
				things.push_back(storage_B);
			}
		}
	}
}

