#pragma once
class ControlContext
{
public:
	ControlContext();
	~ControlContext();

	bool hasKeyCallBack();
	bool hasMouseCallBack();
	bool hasMouseButtonCallBack();

};

