#pragma once
#include "globals.h"
#include "BasicState.h"

class MainState : public BasicState
{
	//StateMachine machine;
public:
	MainState(/*StateMachine&*/);
	virtual void enter() override;
	virtual void exit() override;
	virtual void update() override;
	virtual void render() override;
};

