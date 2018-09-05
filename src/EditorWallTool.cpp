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

std::string EditorWallTool::selectionwalltex;
Wall* EditorWallTool::selectionWall = NULL;
bool EditorWallTool::inselectmode = false;

int EditorWallTool::camnearoffset = 100;

vec3 EditorWallTool::wallposref;
bool EditorWallTool::inplacemode = false;

ButtonComponent * EditorWallTool::colEnable = NULL;
ButtonComponent * EditorWallTool::boundsDraw = NULL;

TextInputComponent * EditorWallTool::texrepeatx = NULL;
TextInputComponent * EditorWallTool::texrepeaty = NULL;

void EditorWallTool::toggle() {
	if (walltool->isVis()) hide();
	else {
		show();
		walltool->centerInDisplay();
	}
}

void EditorWallTool::show() {
	walltool->show();
}

void EditorWallTool::hide() {
	walltool->hide();
}

void EditorWallTool::render() {
	if (!inplacemode && !inselectmode) {
		if (walltool->isVis()) {
			walltool->render();
			wall->render();
		}
	}
	if(inplacemode) wall->render();
}

void EditorWallTool::update(float time) {
	if(walltool->isVis()) walltool->update(time);
	if (inplacemode) wall->setPos(vec3(wall->getPos()) + (vec3(CAM->getActiveCam()->getPos()) + CAM->getActiveCam()->GetCamZ() * (float) camnearoffset - vec3(wall->getPos())) * time * 10);
	if(inselectmode) selectItem(0);
}

bool EditorWallTool::testClick(int x, int y) {
	if(walltool->isVis()) return walltool->testClick(x, y);
	else return false;
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
		l->setLabel("Texturing Disabled.");
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
	positionrin->addSelection(PLACE);

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
	l->setLabel("Position    X/Y/Z: ");
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
	l->setLabel("Rotation    X/Y/Z: ");
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

	//texture repeat editor
	l = new LabelComponent();
	l->setLabel("Tex Repeat    X/Y: ");
	walltool->addComponent(l, 50, 10);

	texrepeatx = new TextInputComponent();
	if (texrepeatx == NULL) return false;
	texrepeatx->setCallback(updateTexRepeatXCallBack);
	walltool->addComponent(texrepeatx, 20, 10);

	texrepeaty = new TextInputComponent();
	if (texrepeaty == NULL) return false;
	texrepeaty->setCallback(updateTexRepeatYCallBack);
	walltool->addComponent(texrepeaty, 20, 10);
	//end tex repeat editor

	//collision toggle button
	colEnable = new ButtonComponent();
	if (colEnable == NULL) return false;
	colEnable->setTitle(COL_ON);
	colEnable->setCallback(toggleCollisionCallback);
	walltool->addComponent(colEnable, 100, 10);

	//end col toggle

	//select item button
	ButtonComponent * b = new ButtonComponent();
	b->setTitle("Select Wall to Edit");
	b->setCallback(confirmSelectItem);
	walltool->addComponent(b, 100, 10);


	//create button
	b = new ButtonComponent();
	b->setTitle("Place Wall");
	b->setCallback(addToGameCallBack);
	walltool->addComponent(b, 100, 10);
	walltool->FitToContent();


	boundsDraw = new ButtonComponent();
	if (boundsDraw == NULL) return false;
	boundsDraw->setTitle(BOUNDS_OFF);
	boundsDraw->setCallback(toggleDrawWallBounds);
	walltool->addComponent(boundsDraw, 100, 14);
	
	walltool->FitToContent();

	resetWallPos(0);

	return true;
}

void EditorWallTool::placeWall(int code) {
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
	else
	if (relativeselection == PLACE) {
		CONT->switchContextItemPlace(onWallPlace, mouseScroll);
		wallpos = vec3(CAM->getActiveCam()->getPos()) + CAM->getActiveCam()->GetCamZ() * (float) camnearoffset;
		inplacemode = true;
	}

	wall->setPos(wallpos);

	setInputsFromWall();
}

void EditorWallTool::addToGameCallBack(int code) {
	wall->updateBounds();

	SM->addObjectToCurScene(wall);
	
	//todo: not the condition we should be checking. Fix!
	if (!positionrin->hasSelection(PREV_WALL)) {
		positionrin->addSelection(PREV_WALL);
	}

	relativeselection = CAMERA;
	
	prevwall = wall;
	wall = new Wall();

	if (wall == NULL) {
		std::cerr << "Memory Depleted, Closing Gracefully." << std::endl;
		RNDR->killProgram();
	}

	wall->setID(GOF->getNextId());
	
	camnearoffset = 100;

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

	placeWall(0);
}

void EditorWallTool::resetWallPos(int code) {
	placeWall(0);

	wall->setWidth(10);
	wall->setHeight(10);
	wall->setDepth(10);

	wall->setAngleX(0);
	wall->setAngleY(0);
	wall->setAngleZ(0);

	posxin->setValue(std::to_string((int)wall->getPos().x()));
	posyin->setValue(std::to_string((int)wall->getPos().y()));
	poszin->setValue(std::to_string((int)wall->getPos().z()));

	rotxin->setValue("0");
	rotyin->setValue("0");
	rotzin->setValue("0");

	widthin->setValue("10");
	depthin->setValue("10");
	heightin->setValue("10");

	texrepeatx->setValue(std::to_string(wall->getTexRepX()));
	texrepeaty->setValue(std::to_string(wall->getTexRepY()));

	if (wall->isCollidable()) {
		colEnable->setTitle(COL_ON);
	}
	else {
		colEnable->setTitle(COL_OFF);
	}
}

void EditorWallTool::onWallPlace() {
	CONT->switchContextGUIInteract();
	wall->setPos(vec3(CAM->getActiveCam()->getPos()) + CAM->getActiveCam()->GetCamZ() *  (float) camnearoffset);
	posxin->setValue(std::to_string((int)wall->getPos().x()));
	posyin->setValue(std::to_string((int)wall->getPos().y()));
	poszin->setValue(std::to_string((int)wall->getPos().z()));
	inplacemode = false;
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

void EditorWallTool::mouseScroll(float offset) {
	if (offset < 0) {
		if (camnearoffset > ITEM_NEAR) {
			camnearoffset += (int) (offset * SCROLL_OFFSET_MODIFIER);
		}
	}
	else {
		if (camnearoffset < ITEM_FAR) {
			camnearoffset += (int) (offset * SCROLL_OFFSET_MODIFIER);
		}
	}
}

void EditorWallTool::selectItemStart(int code) {
	ALERT->done();
	CONT->switchContextItemPlace(onWallSelect, NULL);
	inselectmode = true;
}

void EditorWallTool::confirmSelectItem(int code) {
	ALERT->doAlert("This will delete active wall. Continue?", selectItemStart, NULL);
}

void EditorWallTool::setInputsFromWall() {
	posxin->setValue(std::to_string((int)wall->getPos().x()));
	posyin->setValue(std::to_string((int)wall->getPos().y()));
	poszin->setValue(std::to_string((int)wall->getPos().z()));

	rotxin->setValue(std::to_string((int)wall->getAngleX()));
	rotyin->setValue(std::to_string((int)wall->getAngleY()));
	rotzin->setValue(std::to_string((int)wall->getAngleZ()));

	widthin->setValue(std::to_string((int)wall->getWidth()));
	depthin->setValue(std::to_string((int)wall->getDepth()));
	heightin->setValue(std::to_string((int)wall->getHeight()));

	texrepeatx->setValue(std::to_string(wall->getTexRepX()));
	texrepeaty->setValue(std::to_string(wall->getTexRepY()));

	if (wall->isCollidable()) {
		colEnable->setTitle(COL_ON);
	}
	else {
		colEnable->setTitle(COL_OFF);
	}
}

void EditorWallTool::onWallSelect() {
	if (selectionWall != NULL) {
		if (!selectionwalltex.empty()) {
			selectionWall->setTex(selectionwalltex);
		}

		if (wall != NULL) delete wall;

		wall = selectionWall;

		selectionWall = NULL;

		prevwall = NULL;
		
		SM->getGOH().removeGameObject(wall);

		inselectmode = false;

		setInputsFromWall();

		CONT->switchContextGUIInteract();
	}
}

void EditorWallTool::selectItem(int code) {
	Ray tstray(CAM->getActiveCam()->getPos(), CAM->getActiveCam()->GetCamZ());

	if (selectionWall != NULL) {
		if (!selectionwalltex.empty()) selectionWall->setTex(selectionwalltex);
	}

	float mindist = -1;
	float curdist;
	vec3 dist;
	bool found = false;

	for (unsigned i = 0; i < SM->getGOH().getNumObjects(); i++) {
		if (SM->getGOH().getObject(i) != NULL) {
			if (SM->getGOH().getObject(i)->getType() == "WALL") {
				if (CollisionEngine::rayAABBTest(tstray, SM->getGOH().getObject(i), dist)) {
					curdist = (vec3(CAM->getActiveCam()->getPos()) - dist).getLength();

					found = true;

					if ((mindist == -1 || curdist < mindist) && curdist > 0) {
						selectionWall = (Wall*)SM->getGOH().getObject(i);
						mindist = curdist;
					}
				}
			}
		}
	}

	if (!found) selectionWall = NULL;
	else {
		selectionwalltex = selectionWall->getTex();
		selectionWall->setTex("sky.tga");
	}
}


void EditorWallTool::toggleCollisionCallback(int code) {
	if (colEnable->getTitle() == COL_ON) {
		colEnable->setTitle(COL_OFF);
		wall->setHasCol(false);
	}
	else {
		colEnable->setTitle(COL_ON);
		wall->setHasCol(true);
	}
}

void EditorWallTool::updateTexRepeatXCallBack(int code) {
	std::string val = texrepeatx->getValue();

	float valnum = (float) atof(val.c_str());

	wall->setTexRepX((float)valnum);

	texrepeatx->setValue(std::to_string(valnum));
}

void EditorWallTool::updateTexRepeatYCallBack(int code) {
	std::string val = texrepeaty->getValue();

	float valnum = (float) atof(val.c_str());

	wall->setTexRepY((float)valnum);

	texrepeaty->setValue(std::to_string(valnum));
}

void EditorWallTool::toggleDrawWallBounds(int code) {
	if (Wall::boundsVis()) boundsDraw->setTitle(BOUNDS_OFF);
	else boundsDraw->setTitle(BOUNDS_ON);

	Wall::toggleDrawBounds();
}