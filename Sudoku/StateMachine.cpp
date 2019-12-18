#include "StateMachine.h"
#include "assert.h"

StateMachine::StateMachine() {
	states["basic"] = new BasicState();
	states["main"] = new MainState();
	current = states["basic"];
}

void StateMachine::change(std::string newStateName) {
	current->exit();
	assert(states.find(newStateName) != states.end());
	current = states[newStateName];
	current->enter();
}

void StateMachine::update() {
	current->update();
}

void StateMachine::render() {
	current->render();
}

StateMachine::~StateMachine() {
	for (auto state : states)
		delete state.second;
}
