#pragma once
#include "BasicState.h"
#include "MainState.h"
#include <map>
#include <string>

class StateMachine
{
	std::map <std::string, BasicState*> states;
	BasicState* current;
public:
	StateMachine();
	void change(std::string);
	void update();
	void render();
	~StateMachine();
};
