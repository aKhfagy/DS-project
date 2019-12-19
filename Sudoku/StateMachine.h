#pragma once
#include "BasicState.h"
#include "MainState.h"
#include <map>
#include <string>
#include "globals.h"

typedef std::map <std::string, BasicState*> table;

using std::string;

class StateMachine
{
	table states;
	BasicState* current;
public:
	StateMachine();
	void change(string);
	void update();
	void render();
	~StateMachine();
};