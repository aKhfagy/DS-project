#pragma once
#include "globals.h"
#include "BasicState.h"

class MainState : public BasicState
{
public:
	MainState();
	virtual void enter() override;
	virtual void exit() override;
	virtual void update() override;
	virtual void render() override;
};

