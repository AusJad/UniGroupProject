#pragma once

class State
{
public:
	virtual ~State() {}

	virtual void Enter() = 0;
	virtual void Execute() = 0;
	virtual void Exit() = 0;
};