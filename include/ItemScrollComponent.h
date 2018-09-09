#pragma once

#include "ButtonComponent.h"
#include "movementInfo.h"
#include "Controls.h"

class ItemScrollComponent : public WndComponent
{
public:
	ItemScrollComponent();
	ItemScrollComponent(int width, int height, vec2 pos);

	void update(float time);
	void render();
	bool testClick(int x, int y);

	void setWidth(int toset);
	void setHeight(int toset);
	void setPos(vec2 toset);
	void move(float x, float y);

	void addOption(std::string title, onClick callback);
	std::string getOptionvalue(int index);

	void removeOption(std::string toremove);

	unsigned getNumOptions() { return options.size(); };

	void clear();

private:
	void optionsAdded();
	void recalcDimensions();
	void setButtonPositions();

	void getVisibleComponents();

	int calcFirstVis();
	int calcLastVis();

	float getCulmHeight();

	float calcScrollbarHeight();

	std::vector<ButtonComponent> options;
	std::vector<onClick> callbacks;
	
	vec2 scrollbarpos;

	unsigned visiblestart;
	unsigned visibleend;

	const float padding = 10.0f;
	const float componentheight = 40.0f;
	const float scrollbarwidth = 20.0f;
	float scrollbarheight;

	movementInfo scrolldat;
};

