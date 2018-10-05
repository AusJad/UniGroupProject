#include "EditorObjectTool.h"

Window * EditorObjectTool::objecttool = NULL;

SelectionComponent * EditorObjectTool::modelin = NULL;

TextInputComponent * EditorObjectTool::scalexin = NULL;
TextInputComponent * EditorObjectTool::scaleyin = NULL;
TextInputComponent * EditorObjectTool::scalezin = NULL;

TextInputComponent * EditorObjectTool::posxin = NULL;
TextInputComponent * EditorObjectTool::posyin = NULL;
TextInputComponent * EditorObjectTool::poszin = NULL;

TextInputComponent * EditorObjectTool::rotxin = NULL;
TextInputComponent * EditorObjectTool::rotyin = NULL;
TextInputComponent * EditorObjectTool::rotzin = NULL;

GenericObject * EditorObjectTool::object = NULL;

bool EditorObjectTool::inplacemode = false;

float EditorObjectTool::camnearoffset = 100;

EditorObjectTool::EditorObjectTool() {
}

EditorObjectTool::~EditorObjectTool() {
	if (objecttool != NULL) delete objecttool;
	if (object != NULL) delete object;
}

void EditorObjectTool::toggle() {
	if (objecttool->isVis()) hide();
	else {
		show();
		objecttool->centerInDisplay();
	}
}

void EditorObjectTool::show() {
	objecttool->show();
}

bool EditorObjectTool::isVis(){
	return objecttool->isVis();
}

void EditorObjectTool::hide() {
	objecttool->hide();
}

void EditorObjectTool::render() {
	if (objecttool->isVis()) {
		objecttool->render();
		if (object != NULL) object->render();
	}
	else
	if (inplacemode) object->render();

}

void EditorObjectTool::update(float time) {
	if (objecttool->isVis()) objecttool->update(time);
	if (inplacemode) object->setPos(vec3(object->getPos()) + (vec3(CAM->getActiveCam()->getPos()) + CAM->getActiveCam()->GetCamZ() * (float)camnearoffset - vec3(object->getPos())) * time * 5);
}

bool EditorObjectTool::testClick(int x, int y) {
	if (objecttool->isVis()) return objecttool->testClick(x, y);
	else return false;
}

bool EditorObjectTool::init() {
	object = new GenericObject();
	if (object == NULL) return false;
	object->setID(GOF->getNextId());

	objecttool = WindowFactory::getWindow(WINDOW_MEDIUM_SQUARE, "GENERIC", vec2(), "Object Tool");
	if (objecttool == NULL) return false;

	LabelComponent * l = NULL;

	if (MMAN->hasModelGroup(MODEL_MAIN_GROUP)) {
		l = new LabelComponent();
		if (l == NULL) return false;
		l->setLabel("Select Model:");
		l->setPadding(10);
		objecttool->addComponent(l, 50, 15);

		modelin = new SelectionComponent();
		if (modelin == NULL) return false;

		modelin->setCallback(updateModel);

		for (unsigned i = 0; i < MMAN->getModelGroup(MODEL_MAIN_GROUP).size(); i++) {
			modelin->addSelection(MMAN->getModelGroup(MODEL_MAIN_GROUP).at(i));
		}

		objecttool->addComponent(modelin, 55, 15);
	}
	else {
		l = new LabelComponent();
		if (l == NULL) return false;
		l->setLabel("No Models Found! Model Selection Disabled.");
		l->setPadding(10);
		objecttool->addComponent(l, 100, 15);
	}

	//begin scale editors
	l = NULL;
	l = new LabelComponent();
	if (l == NULL) return false;
	l->setLabel("Scale    X/Y/Z: ");
	objecttool->addComponent(l, 50, 10);

	scalexin = new TextInputComponent();
	if (scalexin == NULL) return false;
	scalexin->setCallback(setScaleXCallback);
	objecttool->addComponent(scalexin, 20, 10);

	scaleyin = new TextInputComponent();
	if (scaleyin == NULL) return false;
	scaleyin->setCallback(setScaleYCallback);
	objecttool->addComponent(scaleyin, 20, 10);

	scalezin = new TextInputComponent();
	if (scalezin == NULL) return false;
	scalezin->setCallback(setScaleZCallback);
	objecttool->addComponent(scalezin, 20, 10);
	//end scale editors

	//begin position editors
	l = NULL;
	l = new LabelComponent();
	if (l == NULL) return false;
	l->setLabel("Position X/Y/Z: ");
	objecttool->addComponent(l, 50, 10);

	posxin = new TextInputComponent();
	if (posxin == NULL) return false;
	posxin->setCallback(setPosXCallBack);
	objecttool->addComponent(posxin, 20, 10);

	posyin = new TextInputComponent();
	if (posyin == NULL) return false;
	posyin->setCallback(setPosYCallBack);
	objecttool->addComponent(posyin, 20, 10);

	poszin = new TextInputComponent();
	if (poszin == NULL) return false;
	poszin->setCallback(setPosZCallBack);
	objecttool->addComponent(poszin, 20, 10);
	//end position editors

	//begin rotation editors
	l = NULL;
	l = new LabelComponent();
	if (l == NULL) return false;
	l->setLabel("Rotation X/Y/Z: ");
	objecttool->addComponent(l, 50, 10);

	rotxin = new TextInputComponent();
	if (rotxin == NULL) return false;
	rotxin->setCallback(setRotXCallBack);
	objecttool->addComponent(rotxin, 20, 10);

	rotyin = new TextInputComponent();
	if (rotyin == NULL) return false;
	rotyin->setCallback(setRotYCallBack);
	objecttool->addComponent(rotyin, 20, 10);

	rotzin = new TextInputComponent();
	if (rotzin == NULL) return false;
	rotzin->setCallback(setRotZCallBack);
	objecttool->addComponent(rotzin, 20, 10);
	//end rotation editors


	ButtonComponent * b = NULL;
	b = new ButtonComponent();
	if (b == NULL) return false;
	b->setTitle("Place With Camera");
	b->setCallback(switchPlaceMode);
	objecttool->addComponent(b, 100, 10);

	b = NULL;
	b = new ButtonComponent();
	if (b == NULL) return false;
	b->setTitle("Add to Game");
	b->setCallback(addToGameCallback);
	objecttool->addComponent(b, 100, 10);

	objecttool->FitToContent();

	setInToObjVal();

	return true;
}	

void EditorObjectTool::addToGameCallback(int code) {
	if (object->getModel() == NULL) {
		ALERT->doNotify("Select a Model First!", NULL);
		return;
	}

	object->updateBounds();

	SM->addObjectToCurScene(object);

	object = new GenericObject();
	if(object != NULL) object->setID(GOF->getNextId());
	else {
		std::cerr << "Memory Depleted, Closing Gracefully." << std::endl;
		RNDR->killProgram();
	}

	camnearoffset = 100;

	setInToObjVal();
}

void EditorObjectTool::switchPlaceMode(int code) {
	if (object->getModel() == NULL) {
		ALERT->doNotify("Select a Model First!", NULL);
		return;
	}

	objecttool->hide();
	CONT->switchContextItemPlace(onObjectPlace, mouseScroll);
	object->setPos(vec3(CAM->getActiveCam()->getPos()) + CAM->getActiveCam()->GetCamZ() * (float)camnearoffset);
	inplacemode = true;
}
//M2 having an object infront of a camera/"location".
void EditorObjectTool::onObjectPlace() {
	objecttool->show();
	CONT->switchContextGUIInteract();
	object->setPos(vec3(CAM->getActiveCam()->getPos()) + CAM->getActiveCam()->GetCamZ() *  (float) camnearoffset);
	posxin->setValue(std::to_string((int) object->getPos().x()));
	posyin->setValue(std::to_string((int) object->getPos().y()));
	poszin->setValue(std::to_string((int) object->getPos().z()));
	inplacemode = false;
}

void EditorObjectTool::mouseScroll(float offset) {
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

void EditorObjectTool::setInToObjVal() {
	posxin->setValue(std::to_string((int)object->getPos().x()));
	posyin->setValue(std::to_string((int)object->getPos().y()));
	poszin->setValue(std::to_string((int)object->getPos().z()));

	rotxin->setValue(std::to_string((int)object->getAngleX()));
	rotyin->setValue(std::to_string((int)object->getAngleY()));
	rotzin->setValue(std::to_string((int)object->getAngleZ()));

	scalexin->setValue(std::to_string((int)object->getScaleX()));
	scaleyin->setValue(std::to_string((int)object->getScaleY()));
	scalezin->setValue(std::to_string((int)object->getScaleZ()));
}

vec3 EditorObjectTool::calcOffset(int off, int axis) {
	vec3 relativepos;

	vec3 wallpos = object->getPos();

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

void EditorObjectTool::setScaleXCallback(int code) {
	std::string val = scalexin->getValue();

	float valnum = (float) atof(val.c_str());

	object->setScaleX(valnum);

	scalexin->setValue(std::to_string(valnum));
}

void EditorObjectTool::setScaleYCallback(int code) {
	std::string val = scaleyin->getValue();

	float valnum = (float) atof(val.c_str());

	object->setScaleY(valnum);

	scaleyin->setValue(std::to_string(valnum));
}

void EditorObjectTool::setScaleZCallback(int code) {
	std::string val = scalezin->getValue();

	float valnum = (float) atof(val.c_str());

	object->setScaleZ(valnum);

	scalezin->setValue(std::to_string(valnum));
}

void EditorObjectTool::setPosXCallBack(int code) {
	std::string val = posxin->getValue();

	int valnum = atoi(val.c_str());

	object->setPos(calcOffset(valnum, X_AXIS));

	posxin->setValue(std::to_string(valnum));
}

void EditorObjectTool::setPosYCallBack(int code) {
	std::string val = posyin->getValue();

	int valnum = atoi(val.c_str());

	object->setPos(calcOffset(valnum, Y_AXIS));

	posyin->setValue(std::to_string(valnum));
}

void EditorObjectTool::setPosZCallBack(int code) {
	std::string val = poszin->getValue();

	int valnum = atoi(val.c_str());

	object->setPos(calcOffset(valnum, Z_AXIS));

	poszin->setValue(std::to_string(valnum));
}

void EditorObjectTool::setRotXCallBack(int code) {
	std::string val = rotxin->getValue();

	int valnum = atoi(val.c_str());

	object->setAngleX((float)valnum);

	rotxin->setValue(std::to_string(valnum));
}

void EditorObjectTool::setRotYCallBack(int code) {
	std::string val = rotyin->getValue();

	int valnum = atoi(val.c_str());

	object->setAngleY((float)valnum);

	rotyin->setValue(std::to_string(valnum));
}

void EditorObjectTool::setRotZCallBack(int code) {
	std::string val = rotzin->getValue();

	int valnum = atoi(val.c_str());

	object->setAngleZ((float)valnum);

	rotzin->setValue(std::to_string(valnum));
}

void EditorObjectTool::updateModel(int code) {
	if (object != NULL) {
		object->setModel(MMAN->useModel(modelin->getActiveSelection(), modelin->getActiveSelection()));
	}
}