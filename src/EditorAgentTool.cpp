#include "EditorAgentTool.h"

Window * EditorAgentTool::agenttool = NULL;

SelectionComponent * EditorAgentTool::modelin = NULL;

//TextInputComponent * EditorAgentTool::scalexin = NULL;
//TextInputComponent * EditorAgentTool::scaleyin = NULL;
//TextInputComponent * EditorAgentTool::scalezin = NULL;

TextInputComponent * EditorAgentTool::posxin = NULL;
TextInputComponent * EditorAgentTool::posyin = NULL;
TextInputComponent * EditorAgentTool::poszin = NULL;

//TextInputComponent * EditorAgentTool::rotxin = NULL;
//TextInputComponent * EditorAgentTool::rotyin = NULL;
//TextInputComponent * EditorAgentTool::rotzin = NULL;


NPC * EditorAgentTool::agent = NULL;

bool EditorAgentTool::inplacemode = false;

float EditorAgentTool::camnearoffset = 100;

EditorAgentTool::EditorAgentTool() {
}

EditorAgentTool::~EditorAgentTool() {
	if (agenttool != NULL) delete agenttool;
	if (agent != NULL) delete agent;
}

void EditorAgentTool::toggle() {
	if (agenttool->isVis()) hide();
	else {
		show();
		agenttool->centerInDisplay();
	}
}

void EditorAgentTool::show() {
	agenttool->show();
}

bool EditorAgentTool::isVis() {
	return agenttool->isVis();
}

void EditorAgentTool::hide() {
	agenttool->hide();
}

void EditorAgentTool::render() {
	if (agenttool->isVis()) {
		agenttool->render();
		if (agent != NULL) agent->render();
	}
	else
		if (inplacemode) agent->render();

}

void EditorAgentTool::update(float time) {
	if (agenttool->isVis()) agenttool->update(time);
	if (inplacemode) agent->setPos(vec3(agent->getPos()) + (vec3(CAM->getActiveCam()->getPos()) + CAM->getActiveCam()->GetCamZ() * (float)camnearoffset - vec3(agent->getPos())) * time * 5);
}

bool EditorAgentTool::testClick(int x, int y) {
	if (agenttool->isVis()) return agenttool->testClick(x, y);
	else return false;
}

bool EditorAgentTool::init() {
	//agent = new GenericObject();
	agent = new NPC();
	if (agent == NULL) return false;
	agent->setID(GOF->getNextId());

	agenttool = WindowFactory::getWindow(WINDOW_MEDIUM_SQUARE, "GENERIC", vec2(), "Agent Tool");
	if (agenttool == NULL) return false;

	LabelComponent * l = NULL;

	if (MMAN->hasModelGroup(MODEL_AGENT_GROUP)) {
		l = new LabelComponent();
		if (l == NULL) return false;
		l->setLabel("Select Agent:");
		l->setPadding(10);
		agenttool->addComponent(l, 50, 15);

		modelin = new SelectionComponent();
		if (modelin == NULL) return false;

		modelin->setCallback(updateModel);

		for (unsigned i = 0; i < MMAN->getModelGroup(MODEL_AGENT_GROUP).size(); i++) {
			modelin->addSelection(MMAN->getModelGroup(MODEL_AGENT_GROUP).at(i));
		}

		agenttool->addComponent(modelin, 55, 15);
	}
	else {
		l = new LabelComponent();
		if (l == NULL) return false;
		l->setLabel("No Models Found! Model Selection Disabled.");
		l->setPadding(10);
		agenttool->addComponent(l, 100, 15);
	}

	//begin scale editors
	/*
	l = NULL;
	l = new LabelComponent();
	if (l == NULL) return false;
	l->setLabel("Scale    X/Y/Z: ");
	agenttool->addComponent(l, 50, 10);

	scalexin = new TextInputComponent();
	if (scalexin == NULL) return false;
	scalexin->setCallback(setScaleXCallback);
	agenttool->addComponent(scalexin, 20, 10);

	scaleyin = new TextInputComponent();
	if (scaleyin == NULL) return false;
	scaleyin->setCallback(setScaleYCallback);
	agenttool->addComponent(scaleyin, 20, 10);

	scalezin = new TextInputComponent();
	if (scalezin == NULL) return false;
	scalezin->setCallback(setScaleZCallback);
	agenttool->addComponent(scalezin, 20, 10);
	//end scale editors
	*/

	//begin position editors
	l = NULL;
	l = new LabelComponent();
	if (l == NULL) return false;
	l->setLabel("Position X/Y/Z: ");
	agenttool->addComponent(l, 50, 10);

	posxin = new TextInputComponent();
	if (posxin == NULL) return false;
	posxin->setCallback(setPosXCallBack);
	agenttool->addComponent(posxin, 20, 10);

	posyin = new TextInputComponent();
	if (posyin == NULL) return false;
	posyin->setCallback(setPosYCallBack);
	agenttool->addComponent(posyin, 20, 10);

	poszin = new TextInputComponent();
	if (poszin == NULL) return false;
	poszin->setCallback(setPosZCallBack);
	agenttool->addComponent(poszin, 20, 10);
	//end position editors
	/*
	//begin rotation editors
	l = NULL;
	l = new LabelComponent();
	if (l == NULL) return false;
	l->setLabel("Rotation X/Y/Z: ");
	agenttool->addComponent(l, 50, 10);

	rotxin = new TextInputComponent();
	if (rotxin == NULL) return false;
	rotxin->setCallback(setRotXCallBack);
	agenttool->addComponent(rotxin, 20, 10);

	rotyin = new TextInputComponent();
	if (rotyin == NULL) return false;
	rotyin->setCallback(setRotYCallBack);
	agenttool->addComponent(rotyin, 20, 10);

	rotzin = new TextInputComponent();
	if (rotzin == NULL) return false;
	rotzin->setCallback(setRotZCallBack);
	agenttool->addComponent(rotzin, 20, 10);
	//end rotation editors
	*/

	ButtonComponent * b = NULL;
	b = new ButtonComponent();
	if (b == NULL) return false;
	b->setTitle("Place With Camera");
	b->setCallback(switchPlaceMode);
	agenttool->addComponent(b, 100, 10);

	b = NULL;
	b = new ButtonComponent();
	if (b == NULL) return false;
	b->setTitle("Add to Game");
	b->setCallback(addToGameCallback);
	agenttool->addComponent(b, 100, 10);

	agenttool->FitToContent();

	setInToObjVal();

	return true;
}

void EditorAgentTool::addToGameCallback(int code) {
	if (agent->getModel() == NULL) {
		ALERT->doNotify("Select a Model First!", NULL);
		return;
	}
		
	if (MMAN->hasMultiObb(agent->getModel()->getName())) {
		std::vector<OBB> tmpobb = MMAN->getMultiObb(agent->getModel()->getName());
		std::cout << "more than one obb found" << std::endl;
		agent->addMultiObb(tmpobb);
	}
	

	agent->updateBounds();
	//hack emotion placement

	if (agent->getModel()->getName() == "guard.md2") {
		std::cout << "guard detected" << std::endl;
		agent->addemotion(vec4(0.5, 0.5, 0.5, 0.5));
	}
	else if (agent->getModel()->getName() == "tris.md2") {
		std::cout << "tris detected" << std::endl;
		agent->addemotion(vec4(0.2, 0.4, 0.6, 0.8));
	}
	else {
		std::cout << "no specific model detected" << std::endl;
	}
	SM->addObjectToCurScene(agent);

	agent = new NPC();
	if (agent != NULL) agent->setID(GOF->getNextId());
	else {
		std::cerr << "Memory Depleted, Closing Gracefully." << std::endl;
		RNDR->killProgram();
	}

	camnearoffset = 100;

	setInToObjVal();
}

void EditorAgentTool::switchPlaceMode(int code) {
	if (agent->getModel() == NULL) {
		ALERT->doNotify("Select a Model First!", NULL);
		return;
	}

	agenttool->hide();
	CONT->switchContextItemPlace(onObjectPlace, mouseScroll);
	agent->setPos(vec3(CAM->getActiveCam()->getPos()) + CAM->getActiveCam()->GetCamZ() * (float)camnearoffset);
	inplacemode = true;
}
//M2 having an agent infront of a camera/"location".
void EditorAgentTool::onObjectPlace() {
	agenttool->show();
	CONT->switchContextGUIInteract();
	agent->setPos(vec3(CAM->getActiveCam()->getPos()) + CAM->getActiveCam()->GetCamZ() *  (float)camnearoffset);
	posxin->setValue(std::to_string((int)agent->getPos().x()));
	posyin->setValue(std::to_string((int)agent->getPos().y()));
	poszin->setValue(std::to_string((int)agent->getPos().z()));
	inplacemode = false;
}

void EditorAgentTool::mouseScroll(float offset) {
	if (offset < 0) {
		if (camnearoffset > ITEM_NEAR) {
			camnearoffset += (int)(offset * SCROLL_OFFSET_MODIFIER);
		}
	}
	else {
		if (camnearoffset < ITEM_FAR) {
			camnearoffset += (int)(offset * SCROLL_OFFSET_MODIFIER);
		}
	}
}

void EditorAgentTool::setInToObjVal() {
	posxin->setValue(std::to_string((int)agent->getPos().x()));
	posyin->setValue(std::to_string((int)agent->getPos().y()));
	poszin->setValue(std::to_string((int)agent->getPos().z()));

	//rotxin->setValue(std::to_string((int)agent->getAngleX()));
	//rotyin->setValue(std::to_string((int)agent->getAngleY()));
	//rotzin->setValue(std::to_string((int)agent->getAngleZ()));

	//scalexin->setValue(std::to_string((int)agent->getScaleX()));
	//scaleyin->setValue(std::to_string((int)agent->getScaleY()));
	//scalezin->setValue(std::to_string((int)agent->getScaleZ()));
}

vec3 EditorAgentTool::calcOffset(int off, int axis) {
	vec3 relativepos;

	vec3 wallpos = agent->getPos();

	if (axis == X_AXIS) {
		relativepos = vec3((float)off, wallpos.y(), wallpos.z());
	}
	else
		if (axis == Y_AXIS) {
			relativepos = vec3(wallpos.x(), (float)off, wallpos.z());
		}
		else
			if (axis == Z_AXIS) {
				relativepos = vec3(wallpos.x(), wallpos.y(), (float)off);
			}

	return relativepos;
}
/*
void EditorAgentTool::setScaleXCallback(int code) {
	std::string val = scalexin->getValue();

	float valnum = (float)atof(val.c_str());

	agent->setScaleX(valnum);

	scalexin->setValue(std::to_string(valnum));
}

void EditorAgentTool::setScaleYCallback(int code) {
	std::string val = scaleyin->getValue();

	float valnum = (float)atof(val.c_str());

	agent->setScaleY(valnum);

	scaleyin->setValue(std::to_string(valnum));
}

void EditorAgentTool::setScaleZCallback(int code) {
	std::string val = scalezin->getValue();

	float valnum = (float)atof(val.c_str());

	agent->setScaleZ(valnum);

	scalezin->setValue(std::to_string(valnum));
}
*/
void EditorAgentTool::setPosXCallBack(int code) {
	std::string val = posxin->getValue();

	int valnum = atoi(val.c_str());

	agent->setPos(calcOffset(valnum, X_AXIS));

	posxin->setValue(std::to_string(valnum));
}

void EditorAgentTool::setPosYCallBack(int code) {
	std::string val = posyin->getValue();

	int valnum = atoi(val.c_str());

	agent->setPos(calcOffset(valnum, Y_AXIS));

	posyin->setValue(std::to_string(valnum));
}

void EditorAgentTool::setPosZCallBack(int code) {
	std::string val = poszin->getValue();

	int valnum = atoi(val.c_str());

	agent->setPos(calcOffset(valnum, Z_AXIS));

	poszin->setValue(std::to_string(valnum));
}

/*
void EditorAgentTool::setRotXCallBack(int code) {
	std::string val = rotxin->getValue();

	int valnum = atoi(val.c_str());

	agent->setAngleX((float)valnum);

	rotxin->setValue(std::to_string(valnum));
}
*/
/*void EditorAgentTool::setRotYCallBack(int code) {
	std::string val = rotyin->getValue();

	int valnum = atoi(val.c_str());

	agent->setAngleY((float)valnum);

	rotyin->setValue(std::to_string(valnum));
}
*/
/*void EditorAgentTool::setRotZCallBack(int code) {
	std::string val = rotzin->getValue();

	int valnum = atoi(val.c_str());

	agent->setAngleZ((float)valnum);

	rotzin->setValue(std::to_string(valnum));
}
*/

void EditorAgentTool::updateModel(int code) {
	if (agent != NULL) {
		
		agent->setModel(MMAN->useModel(modelin->getActiveSelection(), modelin->getActiveSelection()));
	}
}