#pragma once
#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

#include <iostream>
#include "state.h"

template <class entity_type>
class stateMachine
{
private:
	entity_type* owner; //owner of the FSM
	State<entity_type> *previousState;
	State<entity_type> *currentState;
	State<entity_type> *globalState;
public:
		stateMachine(entity_type* FSMowner) {
		owner = FSMowner;
		previousState = NULL;
		currentState = NULL;
		globalState = NULL;
		}
		//use the following methods to intialise the FSM
		void setPreviousState(State<entity_type>* st) { previousState = st; }
		void setCurrentState(State<entity_type>* st) { currentState = st; }
		void setGlobalState(State<entity_type>* st) { globalState = st; }
		void update()const
		{
			if (globalState)
				globalState->Execute(owner);
			if (currentState)
				currentState->Execute(owner);
		}
		void changeState(State<entity_type>* newState)
		{
			previousState = currentState;
			currentState->Exit(owner);
			currentState = newState;
			currentState->Enter(owner);
		}
		void revertToPreviousState()
		{
			currentState = previousState;
		}
		//accessor methods
		State<entity_type>* getPreviousState() { return previousState; }
		State<entity_type>* getCurrentState() { return currentState; }
		State<entity_type>* getGlobalState() { return globalState; }
		//returns true if the current state's type is equal to the type of the
		//class passed as a parameter.
		bool isInState(const State<entity_type>& st)const
		{
			return typeid(*currentState) == typeid(st);
		}
		virtual ~stateMachine() {}
	};
#endif