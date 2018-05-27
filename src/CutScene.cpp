#include "CutScene.h"



CutScene::CutScene(){
	culmtime = 0;
	currentAnimation = 0;
	finishedflag = false;
	maxy = 30;
	nextscene = -1;
}

CutScene::~CutScene() {
	for (unsigned i = 0; i < scenes.size(); i++) {
		for (unsigned j = 0; j < scenes.at(i).sounds.size(); j++) {
			AE->stopSound(cutsceneAudio.at(scenes.at(i).sounds.at(j).sound).file);
			scenes.at(i).sounds.at(j).playing = false;
		}
	}
}

CutScene::CutScene(const CutScene & tocpy){
	this->culmtime = tocpy.culmtime;
	this->currentAnimation = tocpy.currentAnimation;
	this->cutsceneAudio = tocpy.cutsceneAudio;
	this->cutsceneObjects = tocpy.cutsceneObjects;
	this->cutsceneText = tocpy.cutsceneText;
	this->scenes = tocpy.scenes;
	this->finishedflag = tocpy.finishedflag;
	this->maxy = tocpy.maxy;
	this->nextscene = tocpy.nextscene;
}

CutScene * CutScene::create() const {
	return new CutScene(*this);
}

bool CutScene::loadModel(std::string filename) {
	std::ifstream infile(filename.c_str());
	if (!infile) return false;

	try {
		if (!getHeader(infile)) return false;
		if (!parseFrames(infile)) return false;
	}
	catch (...) {
		infile.close();
		return false;
	}

	infile.close();
	return true;
}

bool CutScene::getHeader(std::ifstream & toread) {
	std::string curline, linehead, tmpstr1, tmpstr2;
	vec2 tmpvec;
	float tmpf1;
	SceneObject tmpSO;
	SceneText tmpST;
	SceneAudio tmpSA;

	getline(toread, curline);
	
	//No header included - invalid file.
	if (curline != FILE_HEAD) return false;

	while (toread.peek() != EOF && curline != FILE_HEAD_END) {
		getline(toread, curline);
		cleanLine(curline);

		if (curline == OBJECT_START) {
			while (toread.peek() != EOF && curline != ACTOR_END) {
				getline(toread, curline);
				cleanLine(curline);

				if (curline.find(',') != std::string::npos) linehead = curline.substr(0, curline.find(','));
				else linehead = curline;

				if (linehead == ENTITY_NAME) {
					tmpSO.name = curline.substr(curline.find(',') + 1);
				}
				else
				if (linehead == TOP_LEFT) {
					curline = curline.substr(curline.find(',') + 1);
					tmpf1 = (float) atof(curline.substr(0, curline.find(",")).c_str());
					tmpSO.top.sx(tmpf1);
					curline = curline.substr(curline.find(",") + 1);
					tmpf1 = (float) atof(curline.c_str());
					tmpSO.top.sy(tmpf1);
				}
				else
				if (linehead == BOTTOM_RIGHT) {
					curline = curline.substr(curline.find(",") + 1);
					tmpf1 = (float)atof(curline.substr(0, curline.find(",")).c_str());
					tmpSO.bottom.sx(tmpf1);
					curline = curline.substr(curline.find(",") + 1);
					tmpf1 = (float)atof(curline.c_str());
					tmpSO.bottom.sy(tmpf1);
				}
				else
				if (linehead == Z_OFFSET) {
					curline = curline.substr(curline.find(",") + 1);
					tmpf1 = (float)atof(curline.c_str());
					tmpSO.zdistance = tmpf1;
				}
				else
				if (linehead == ACTOR_TEXTURE) {
					curline = curline.substr(curline.find(",") + 1);
					tmpstr1 = curline.substr(0, curline.find(","));
					curline = curline.substr(curline.find(",") + 1);
					tmpstr2 = curline;
					if (TXMAN->loadNewTexture(tmpstr1, tmpstr2, tmpstr1, RNDR)) {
						tmpSO.texture = tmpstr1;
					}
				}
				else
				if (linehead == ACTOR_ALPHA) {
					tmpSO.alphaflag = true;
				}
				else
				if (linehead == SCENE_TO_CHANGE) {
					nextscene = atoi(curline.substr(curline.find(',') + 1).c_str());
				}
			}
			
			if (!tmpSO.name.empty()) cutsceneObjects[tmpSO.name] = tmpSO;

			tmpSO.clear();
		}
		else
		if (curline == TEXT_START) {
			while (toread.peek() != EOF && curline != ACTOR_END) {
				getline(toread, curline);
				cleanLine(curline);

				if (curline.find(',') != std::string::npos) linehead = curline.substr(0, curline.find(','));
				else linehead = curline;

				if (linehead == ENTITY_NAME) {
					tmpST.name = curline.substr(curline.find(",") + 1);
				}
				else
				if (linehead == TOP_LEFT) {
					curline = curline.substr(curline.find(",") + 1);
					tmpf1 = (float)atof(curline.substr(0, curline.find(",")).c_str());
					tmpST.startlocation.sx(tmpf1);
					curline = curline.substr(curline.find(",") + 1);
					tmpf1 = (float)atof(curline.c_str());
					tmpST.startlocation.sy(tmpf1);
				}
				else
				if (linehead == Z_OFFSET) {
					curline = curline.substr(curline.find(",") + 1);
					tmpf1 = (float)atof(curline.c_str());
					tmpST.zdistance = tmpf1;
				}
				else
				if (linehead == TEXT_VALUE) {
					tmpST.value = curline.substr(curline.find(",") + 1);
				}
				else
				if (linehead == TEXT_FONT) {
					curline = curline.substr(curline.find(",") + 1);
					tmpstr1 = curline.substr(0, curline.find(","));
					curline = curline.substr(curline.find(",") + 1);
					tmpstr2 = curline;
					if (!FNT_ENG->hasFont(tmpstr2)) {
						if(FNT_ENG->loadFont(tmpstr1, tmpstr2)) tmpST.font = tmpstr2;

					}
					else {
						tmpST.font = tmpstr2;
					}
				}
			}

			if (!tmpST.name.empty()) cutsceneText[tmpST.name] = tmpST;

			tmpST.clear();
		}
		else
		if (curline == AUDIO_START) {
			while (toread.peek() != EOF && curline != ACTOR_END) {
				getline(toread, curline);
				cleanLine(curline);

				if (curline.find(',') != std::string::npos) linehead = curline.substr(0, curline.find(','));
				else linehead = curline;

				if (linehead == ENTITY_NAME) {
					tmpSA.name = curline.substr(curline.find(",") + 1);
				}
				else
				if (linehead == SOUND_FILE) {
					curline = curline.substr(curline.find(",") + 1);
					tmpstr1 = curline.substr(0, curline.find(","));
					curline = curline.substr(curline.find(",") + 1);
					tmpstr2 = curline;

					if (!AE->hasSound(tmpstr2)) {
						if (AE->loadSound(tmpstr1, "WAV", tmpstr2, tmpSA.loop) == true) tmpSA.file = tmpstr2;
					}
					else {
						tmpSA.file = tmpstr2;
					}
				}
				else 
				if (linehead == LOOP_AUDIO) {
					curline = curline.substr(curline.find(",") + 1);
					if (curline == CSTRUE) {
						tmpSA.loop = true;
					}
				}
			}


			if (!tmpSA.name.empty()) cutsceneAudio[tmpSA.name] = tmpSA;
			tmpSA.clear();
		}
	}
	return true;
}

bool CutScene::parseFrames(std::ifstream & toread) {
	Frame tmpframe;
	Animation tmpanim;
	FrameSound tmpFS;
	std::string curline, linehead, tmpstr1, tmpstr2;
	float tmpf1;
	int tmpi;

	getline(toread, curline);
	cleanLine(curline);

	//No frame data
	if (curline != FRAME_START) return false;

	while (toread.peek() != EOF) {
		if(curline == FRAME_END) getline(toread, curline);
		while (toread.peek() != EOF && curline != FRAME_END) {
			getline(toread, curline);

			cleanLine(curline);

			if (curline.find(',') != std::string::npos) linehead = curline.substr(0, curline.find(','));
			else linehead = curline;

			if (linehead == FRAME_ACTORS) {
				curline = curline.substr(curline.find(',') + 1);
				
				while (curline.find(',') != std::string::npos) {
					tmpframe.actors.push_back(curline.substr(0, curline.find(',')));
					curline = curline.substr(curline.find(',') + 1);
				}
				tmpframe.actors.push_back(curline);
			}
			else
			if (linehead == FRAME_DURATION) {
				tmpframe.duration = (float) atof(curline.substr(curline.find(',') + 1).c_str());
			}
			else 
			if (linehead == ANIMATION_START) {

				tmpanim.animatedentity = curline.substr(curline.find(',') + 1);

				while (linehead != ANIMATION_END) {
					getline(toread, curline);

					cleanLine(curline);

					if (curline.find(',') != std::string::npos) linehead = curline.substr(0, curline.find(','));
					else linehead = curline;

					if (linehead == ENTITY_NAME) {
						tmpanim.name = curline.substr(curline.find(',') + 1);
					}
					else
					if (linehead == ANIMATION_DURATION) {
						tmpanim.time = (float)atof(curline.substr(curline.find(',') + 1).c_str());
					}
					else
					if (linehead == ANIMATION_START_TIME) {
						tmpanim.starttime = (float)atof(curline.substr(curline.find(',') + 1).c_str());
					}
					else
					if (linehead == ANIMATION_FLAGS) {
						curline = curline.substr(curline.find(',') + 1);

						while (curline.find(',') != std::string::npos) {
							tmpi = stringToFlags(curline.substr(0, curline.find(',')));
							
							if (tmpi == GO_TO) {
								tmpanim.goto_ = curline.substr(curline.find(' ') + 1);
							}
							else
							if (tmpi != UNDEFINED_FLAG) {
								tmpanim.flags += tmpi;
							}
		
							curline = curline.substr(curline.find(',') + 1);
						}

						tmpi = stringToFlags(curline);

						if (tmpi == GO_TO) {
							tmpanim.goto_ = curline.substr(curline.find(' ') + 1);
						}
						else
						if (tmpi != UNDEFINED_FLAG) {
							tmpanim.flags += tmpi;
						}
					}
					else
					if (linehead == ANIMATION_X) {
						tmpf1 = (float)atof(curline.substr(curline.find(',') + 1).c_str());
						tmpanim.transamount.sx(tmpanim.transamount.x() + tmpf1);
					}
					else 
					if (linehead == ANIMATION_Y) {
						tmpf1 = (float)atof(curline.substr(curline.find(',') + 1).c_str());
						tmpanim.transamount.sy(tmpanim.transamount.y() + tmpf1);
					}
					else
					if (linehead == ANIMATION_Z) {
						tmpf1 = (float)atof(curline.substr(curline.find(',') + 1).c_str());
						tmpanim.transamount.sz(tmpanim.transamount.z() + tmpf1);
					}

				}

				tmpframe.animations.push_back(tmpanim);
				tmpanim.clear();
			}
			else
			if (linehead == FRAME_SOUND_START) {
				tmpFS.sound = curline.substr(curline.find(',') + 1);

				while (linehead != FRAME_SOUND_END) {
					getline(toread, curline);

					cleanLine(curline);

					if (curline.find(',') != std::string::npos) linehead = curline.substr(0, curline.find(','));
					else linehead = curline;
				
					if (linehead == ANIMATION_START_TIME) {
						tmpFS.starttime = (float)atof(curline.substr(curline.find(',') + 1).c_str());
					}
				
				}

				tmpframe.sounds.push_back(tmpFS);
				tmpFS.clear();
			}
		}

		scenes.push_back(tmpframe);
		tmpframe.clear();
	}
	
	return true;
}

void CutScene::cleanLine(std::string & toclean) {
	int i = 0;

	toclean.erase(std::remove(toclean.begin(), toclean.end(), '\t'), toclean.end());

	if(toclean.find(COMMENT) != std::string::npos) toclean = toclean.substr(0, toclean.find(COMMENT));
}

int CutScene::stringToFlags(std::string totest) {
	if (totest == PLAY_AT_START_STR) {
		return PLAY_AT_START;
	}
	else
	if (totest == LOOP_STR) {
		return LOOP;
	}
	else
	if (totest.find(GO_TO_STR) != std::string::npos) {
		return GO_TO;
	}

	return UNDEFINED_FLAG;
}

void CutScene::update(float time) {
	msgrcvr();

	if(finishedflag == false) doActiveAnimations(time);
	else onDone();

	culmtime += time;
}

void CutScene::msgrcvr() {
	Message tmp;
	while (MSGBS->hasMessage(id)) {
		tmp = MSGBS->getMessage(id);

		if (tmp.getInstruction() == STOP_CUTSCNE) {
			finishedflag = true;
		}
	}
}

void CutScene::doActiveAnimations(float time) {
	for (unsigned i = 0; i < scenes.at(currentAnimation).animations.size(); i++) {
		if (scenes.at(currentAnimation).animations.at(i).starttime <= culmtime && (scenes.at(currentAnimation).animations.at(i).starttime + scenes.at(currentAnimation).animations.at(i).time) >= culmtime){
			doAnimation(scenes.at(currentAnimation).animations.at(i), scenes.at(currentAnimation).animations.at(i).animatedentity, time);
		}
	}
	for (unsigned i = 0; i < scenes.at(currentAnimation).sounds.size(); i++) {
		if (scenes.at(currentAnimation).sounds.at(i).starttime <= culmtime && scenes.at(currentAnimation).sounds.at(i).playing == false) {
			AE->playSound(cutsceneAudio.at((scenes.at(currentAnimation).sounds.at(i).sound)).file);
			scenes.at(currentAnimation).sounds.at(i).playing = true;
		}
	}
	if (culmtime > scenes.at(currentAnimation).duration) {
		if (currentAnimation + 1 < scenes.size()) changeScene();
		else finishedflag = true;
	}
}

void CutScene::changeScene() {
	currentAnimation++;
	culmtime = 0;
}

void CutScene::doAnimation(Animation & todo, std::string name, float time) {
	if (cutsceneObjects.count(name) != 0) {
		cutsceneObjects.at(name).curoffset += (todo.transamount * (time / todo.time)); 
	}
	else
	if (cutsceneText.count(name) != 0) {
		if (cutsceneText.at(name).curstring.size() < ((unsigned) (time / todo.time * cutsceneText.at(name).value.size())) % 1 == 0) {
			if (cutsceneText.at(name).curstring.size() < cutsceneText.at(name).value.size()) {
				int numpersec = (int) (cutsceneText.at(name).value.size() / todo.time);
				if (cutsceneText.at(name).curstring.size() > culmtime < numpersec) {
					cutsceneText.at(name).curstring += cutsceneText.at(name).value.at(cutsceneText.at(name).nextchar);
					cutsceneText.at(name).nextchar++;
				}
			}
		}
	}
}

void CutScene::render(const vec3 & transmat) {
	for (unsigned i = 0; i < scenes.at(currentAnimation).actors.size(); i++) {
		if (cutsceneObjects.count(scenes.at(currentAnimation).actors.at(i)) != 0) {
			if (cutsceneObjects.at(scenes.at(currentAnimation).actors.at(i)).alphaflag == false) {
				drawActor(cutsceneObjects.at(scenes.at(currentAnimation).actors.at(i)));
			}
		}
	}

	for (unsigned i = 0; i < scenes.at(currentAnimation).actors.size(); i++) {
		if (cutsceneText.count(scenes.at(currentAnimation).actors.at(i)) != 0) {
			drawText(cutsceneText.at(scenes.at(currentAnimation).actors.at(i)));
		}
	}

	for (unsigned i = 0; i < scenes.at(currentAnimation).actors.size(); i++) {
		if (cutsceneObjects.count(scenes.at(currentAnimation).actors.at(i)) != 0) {
			if (cutsceneObjects.at(scenes.at(currentAnimation).actors.at(i)).alphaflag == true) {
				drawActor(cutsceneObjects.at(scenes.at(currentAnimation).actors.at(i)));
			}
		}
	}

	if(culmtime/4 < 1) RenderFade((1 - (culmtime / 4)));
	else if (culmtime + 1 >= scenes.at(currentAnimation).duration) RenderFade(1 - (scenes.at(currentAnimation).duration - (culmtime)));
}

void CutScene::drawText(SceneText & todraw) {
	GeoStream << ENABLE_ALPHA;

	std::string tmpstr;
	float culmheight = todraw.startlocation.y();
	if (todraw.curstring.find('$') == std::string::npos) {
		FNT_ENG->RenderString(todraw.curstring, FNT_SIZE_SMALL, 30, 30, todraw.startlocation.x(), todraw.startlocation.y(), todraw.zdistance);
	}
	else {
		tmpstr = todraw.curstring;
		while (tmpstr.find('$') != std::string::npos) {
			FNT_ENG->RenderString(tmpstr.substr(0, tmpstr.find('$')), FNT_SIZE_SMALL, 30, 30, todraw.startlocation.x(), culmheight, todraw.zdistance);
			tmpstr = tmpstr.substr(tmpstr.find('$') + 1);
			culmheight -= FNT_SIZE_SMALL;
		}
		FNT_ENG->RenderString(tmpstr, FNT_SIZE_SMALL, 30, 30, todraw.startlocation.x(), culmheight, todraw.zdistance);
	}

	GeoStream << DISABLE_ALPHA;
}

void CutScene::onDone() {
	for (std::map<std::string, SceneObject>::iterator mapit = cutsceneObjects.begin(); mapit != cutsceneObjects.end(); ++mapit) {
		mapit->second.reset();
	}

	for (std::map<std::string, SceneText>::iterator mapit = cutsceneText.begin(); mapit != cutsceneText.end(); ++mapit) {
		mapit->second.reset();
	}
	for (unsigned i = 0; i < scenes.size(); i++) {
		for (unsigned j = 0; j < scenes.at(i).sounds.size(); j++) {
			AE->stopSound(cutsceneAudio.at(scenes.at(i).sounds.at(j).sound).file);
			scenes.at(i).sounds.at(j).playing = false;
		}
	}

	AE->destroyActiveChannels();

	currentAnimation = 0;
	culmtime = 0;
	Message tmp(CHNG_SCENE_REQUEST);

	if (nextscene == -1) tmp.setIData(1);
	else tmp.setIData(nextscene);

	MSGBS->postMessage(tmp, Identifiers("", "SM"));
	finishedflag = false;
}

void CutScene::drawActor(SceneObject & todraw) {

	if (todraw.alphaflag) GeoStream << ENABLE_ALPHA;

	if (!todraw.texture.empty()) TXMAN->useTexture(todraw.texture, RNDR);


	RNDR->DrawQuad(point(todraw.top.x() + todraw.curoffset.x(), todraw.top.y() + todraw.curoffset.y()), point(todraw.bottom.x() + todraw.curoffset.x(), todraw.bottom.y() + todraw.curoffset.y()), todraw.zdistance + todraw.curoffset.z());

	if (!todraw.texture.empty()) TXMAN->disableTexture(RNDR);

	GeoStream << DISABLE_ALPHA;
}

void CutScene::RenderFade(float alpha) {
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GeoStream << ENABLE_TRANSPARENCY << START_ATTRIB << color_4(0, 0, 0, alpha);

	RNDR->DrawQuad(point(-1.5, 1), point(1.5, -1), -1);
	
	GeoStream << END_ATTRIB << DISABLE_TRANSPARENCY;
}

void CutScene::centerOnPoint(vec3 & point) {

}

std::vector<vec3>& CutScene::getVerticies() {
	return std::vector<vec3>();
}

void CutScene::setScale(vec3 & toset) {

}