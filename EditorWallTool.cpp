#include "EditorWallTool.h"

Wall * EditorWallTool::wall = NULL;
Wall * EditorWallTool::prevwall = NULL;
TextInputComponent * EditorWallTool::widthin = NULL;
TextInputComponent * EditorWallTool::heightin = NULL;
TextInputComponent * EditorWallTool::depthin = NULL;

SelectionComponent * EditorWallTool::texturein = NULL;
SelectionComponent * EditorWallTool::positionrin = NULL;
std::string EditorWallTool::relativeselection = CAMERA;

TextInputComponent * EditorWallTool::posxin = NULL;
TextInputComponent * EditorWallTool::posyin = NULL;
TextInputComponent * EditorWallTool::poszin = NULL;

TextInputComponent * EditorWallTool::rotxin = NULL;
TextInputComponent * EditorWallTool::rotyin = NULL;
TextInputComponent * EditorWallTool::rotzin = NULL;

void EditorWallTool::toggle() {
	if (walltool->isVis()) hide();
	else show();
}

void EditorWallTool::show() {
	walltool->show();
}

void EditorWallTool::hide() {
	walltool->hide();
}

void EditorWallTool::render() {
	if (walltool->isVis()) {
		walltool->render();		
		wall->render();
	}
}

void EditorWallTool::update(float time) {
	walltool->update(time);
}

bool EditorWallTool::testClick(int x, int y) {
	return walltool->testClick(x, y);
}

bool EditorWallTool::init() {
	wall = new Wall();
	wall->setID(GOF->getNextId());

	if (!wall) return false;

	walltool = WindowFactory::getWindow(WINDOW_MEDIUM_SQUARE, "GENERIC", vec2(), "Wall Tool");
	if (walltool == NULL) return false;

	LabelComponent * l;

	if (TXMAN->hasTextureGroup(WALL_TEX_GROUP)) {
		l = new LabelComponent();
		l->setLabel("Select Texture:");
		l->setPadding(LABEL_PADDING);
		walltool->addComponent(l, 50, 15);

		texturein = new SelectionComponent();

		texturein->setCallback(updateTextureCallback);

		for (unsigned i = 0; i < TXMAN->getTextureGroup(WALL_TEX_GROUP).size(); i++) {
			texturein->addSelection(TXMAN->getTextureGroup(WALL_TEX_GROUP).at(i));
		}

		walltool->addComponent(texturein, 55, 15);
	}
	else {
		l = new LabelComponent();
		l->setLabel("Wall Textures Not Loaded!");
		l->setPadding(LABEL_PADDING);
		walltool->addComponent(l, 100, 15);
		l = new LabelComponent();
		l->setLabel("Textureing Disabled.");
		l->setPadding(LABEL_PADDING);
		walltool->addComponent(l, 100, 15);
	}
	
	l = new LabelComponent();
	l->setLabel("Place At:");
	l->setPadding(LABEL_PADDING);
	walltool->addComponent(l, 50, 15);

	positionrin = new SelectionComponent();

	positionrin->setCallback(updateRelativeSelection);
	positionrin->addSelection(CAMERA);
	positionrin->addSelection(ORIGIN);

	walltool->addComponent(positionrin, 55, 15);

	//begin dimension editors

	l = new LabelComponent();
	l->setLabel("Size     W/H/D: ");
	walltool->addComponent(l, 50, 10);

	widthin = new TextInputComponent();
	widthin->setCallback(setWidthCallback);
	walltool->addComponent(widthin, 20, 10);

	heightin = new TextInputComponent();
	heightin->setCallback(setHeightCallback);
	walltool->addComponent(heightin, 20, 10);

	depthin = new TextInputComponent();
	depthin->setCallback(setDepthCallback);
	walltool->addComponent(depthin, 20, 10);
	//end dimension editors

	//begin position editors

	l = new LabelComponent();
	l->setLabel("Position X/Y/Z: ");
	walltool->addComponent(l, 50, 10);

	posxin = new TextInputComponent();
	posxin->setCallback(setPosXCallBack);
	walltool->addComponent(posxin, 20, 10);

	posyin = new TextInputComponent();
	posyin->setCallback(setPosYCallBack);
	walltool->addComponent(posyin, 20, 10);

	poszin = new TextInputComponent();
	poszin->setCallback(setPosZCallBack);
	walltool->addComponent(poszin, 20, 10);
	//end position editors

	//begin rotation editors

	l = new LabelComponent();
	l->setLabel("Rotation X/Y/Z: ");
	walltool->addComponent(l, 50, 10);

	rotxin = new TextInputComponent();
	rotxin->setCallback(setRotXCallBack);
	walltool->addComponent(rotxin, 20, 10);

	rotyin = new TextInputComponent();
	rotyin->setCallback(setRotYCallBack);
	walltool->addComponent(rotyin, 20, 10);

	rotzin = new TextInputComponent();
	rotzin->setCallback(setRotZCallBack);
	walltool->addComponent(rotzin, 20, 10);
	//end rotation editors

	//reset button
	ButtonComponent * b = new ButtonComponent();
	b->setTitle("Reset");
	b->setCallback(resetWallPos);
	walltool->addComponent(b, 100, 10);

	//create button
	b = new ButtonComponent();
	b->setTitle("Add to Game");
	b->setCallback(addToGameCallBack);
	walltool->addComponent(b, 100, 10);
	walltool->FitToContent();

	resetWallPos(0);

	return true;
}

void EditorWallTool::addToGameCallBack(int code) {
	wall->updateBounds();

	SM->addObjectToCurScene(wall);
	prevwall = wall;
	wall = new Wall();
	wall->setID(GOF->getNextId());
	positionrin->addSelection(PREV_WALL);
	relativeselection = PREV_WALL;

	resetWallPos(0);
}

void EditorWallTool::setHeightCallback(int code) {
	std::string val = heightin->getValue();

	int valnum = atoi(val.c_str());

	wall->setHeight((float) valnum);

	heightin->setValue(std::to_string(valnum));
}

void EditorWallTool::setWidthCallback(int code) {
	std::string val = widthin->getValue();

	int valnum = atoi(val.c_str());

	wall->setWidth((float) valnum);

	widthin->setValue(std::to_string(valnum));
}

void EditorWallTool::setDepthCallback(int code) {
	std::string val = depthin->getValue();

	int valnum = atoi(val.c_str());

	wall->setDepth((float) valnum);

	depthin->setValue(std::to_string(valnum));
}

void EditorWallTool::updateTextureCallback(int code) {
	std::string tex = texturein->getActiveSelection();

	wall->setTex(tex);
}

void EditorWallTool::updateRelativeSelection(int code) {
	relativeselection = positionrin->getActiveSelection();

	resetWallPos(0);
}

void EditorWallTool::resetWallPos(int code) {
	vec3 wallpos;

	if (relativeselection == CAMERA) {
		wallpos = vec3(CAM->getActiveCam()->getPos()) + CAM->getActiveCam()->GetCamZ() * 100;
		wallpos.sy(CAM->getActiveCam()->getPos().y() - CAM->getActiveCam()->getCenterOffset().y());
	}
	else
	if (relativeselection == ORIGIN) {
		wallpos = vec3();
	}
	else
	if (relativeselection == PREV_WALL) {
		if(prevwall != NULL) wallpos = prevwall->getPos();
		else wallpos = vec3();
	}

	wall->setPos(wallpos);

	wall->setWidth(10);
	wall->setHeight(10);
	wall->setDepth(10);

	wall->setAngleX(0);
	wall->setAngleY(0);
	wall->setAngleZ(0);

	posxin->setValue(std::to_string((int)wallpos.x()));
	posyin->setValue(std::to_string((int)wallpos.y()));
	poszin->setValue(std::to_string((int)wallpos.z()));

	rotxin->setValue("0");
	rotyin->setValue("0");
	rotzin->setValue("0");

	widthin->setValue("10");
	depthin->setValue("10");
	heightin->setValue("10");
}

vec3 EditorWallTool::calcOffset(int off, int axis) {
	vec3 relativepos;

	vec3 wallpos = wall->getPos();

	if (axis == X_AXIS) {
		relativepos = vec3((float) off, wallpos.y(), wallpos.z());
	}
	else
	if (axis == Y_AXIS) {
		relativepos = vec3(wallpos.x(), (float) off, wallpos.z());
	}
	else
	if (axis == Z_AXIS) {
		relativepos = vec3(wallpos.x(), wallpos.y(), (float) off);
	}

	return relativepos;
}

void EditorWallTool::setPosXCallBack(int code) {
	std::string val = posxin->getValue();

	int valnum = atoi(val.c_str());

	wall->setPos(calcOffset(valnum, X_AXIS));

	posxin->setValue(std::to_string(valnum));
}

void EditorWallTool::setPosYCallBack(int code) {
	std::string val = posyin->getValue();

	int valnum = atoi(val.c_str());

	wall->setPos(calcOffset(valnum, Y_AXIS));

	posyin->setValue(std::to_string(valnum));
}

void EditorWallTool::setPosZCallBack(int code) {
	std::string val = poszin->getValue();

	int valnum = atoi(val.c_str());

	wall->setPos(calcOffset(valnum, Z_AXIS));

	poszin->setValue(std::to_string(valnum));
}

void EditorWallTool::setRotXCallBack(int code) {
	std::string val = rotxin->getValue();

	int valnum = atoi(val.c_str());

	wall->setAngleX((float) valnum);

	rotxin->setValue(std::to_string(valnum));
}

void EditorWallTool::setRotYCallBack(int code) {
	std::string val = rotyin->getValue();

	int valnum = atoi(val.c_str());

	wall->setAngleY((float) valnum);

	rotyin->setValue(std::to_string(valnum));
}

void EditorWallTool::setRotZCallBack(int code) {
	std::string val = rotzin->getValue();

	int valnum = atoi(val.c_str());

	wall->setAngleZ((float) valnum);

	rotzin->setValue(std::to_string(valnum));
}