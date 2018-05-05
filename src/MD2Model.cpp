#include "MD2Model.h"



MD2Model::MD2Model() : scale(1, 1, 1)
{
	curframe = 0;
	nextframe = 1;
	curinerpolation = 0;
	loop = false;
	animationplaying = false;
	child = NULL;
}

MD2Model::~MD2Model()
{
	for (unsigned i = 0; i < frames.size(); i++) {
		for (unsigned j = 0; j < (unsigned) header.numVerts; j++) {
			delete[] frames.at(i).verticies;
		}
	}

	if (child != NULL) delete child;
}

MD2Model * MD2Model::create() const {
	MD2Model * tmp = NULL;
	tmp = new MD2Model();
	
	if (!tmp) return tmp;

	tmp->activeanimation = this->activeanimation;
	tmp->animationplaying = this->animationplaying;
	tmp->animations = this->animations;
	tmp->curframe = this->curframe;
	tmp->curinerpolation = this->curinerpolation;
	tmp->header = this->header;
	tmp->id = this->id;
	tmp->skins = this->skins;
	tmp->texcoords = this->texcoords;
	tmp->triangles = this->triangles;
	tmp->loop = this->loop;
	tmp->nextframe = this->nextframe;
	tmp->maxx = this->maxx;
	tmp->maxy = this->maxz;
	tmp->maxz = this->maxy;
	tmp->minx = this->minx;
	tmp->miny = this->minz;
	tmp->minz = this->miny;
	tmp->scale = this->scale;

	for (unsigned i = 0; i < (unsigned) header.numFrames; i++) {
		tmp->frames.push_back(md2animframe());
		tmp->frames.at(i).verticies = NULL;
		tmp->frames.at(i).verticies = (md2vertex *)malloc(sizeof(md2vertex) *header.numVerts);
		if (!tmp->frames.at(i).verticies) return NULL;
	}

	for (unsigned i = 0; i < frames.size(); i++) {
		tmp->frames.at(i).name = frames.at(i).name;
		tmp->frames.at(i).scale = frames.at(i).scale;
		tmp->frames.at(i).trans = frames.at(i).trans;
		tmp->frames.at(i).minx = frames.at(i).minx;
		tmp->frames.at(i).miny = frames.at(i).miny;
		tmp->frames.at(i).minz = frames.at(i).minz;
		tmp->frames.at(i).maxx = frames.at(i).maxx;
		tmp->frames.at(i).maxy = frames.at(i).maxy;
		tmp->frames.at(i).maxz = frames.at(i).maxz;

		for (unsigned j = 0; j < (unsigned) header.numVerts; j++) {
			tmp->frames.at(i).verticies[j] = frames.at(i).verticies[j];
		}
	}

	return tmp;
}

bool MD2Model::loadModel(std::string filename) {
	std::ifstream infile(filename.c_str(), std::ios::binary);
	if (!infile)return false;


	infile.read((char*) &header, sizeof(MD2header));

	//Not MD2 Model
	if (header.id != 844121161) return false;

	md2skin tmps;

	infile.seekg(header.offsetSkins);
	for (unsigned i = 0; i < (unsigned) header.numSkins; i++) {
		infile.read((char*) &tmps, sizeof(md2skin));
		skins = std::string(tmps.name);
	}

	if (!TXMAN->loadNewTexture(skins, "TGA", skins, RNDR)) {
		skins.clear();
	}

	md2texcord tmptx;

	infile.seekg(header.offsetTexCoord);
	for (unsigned i = 0; i < (unsigned) header.numTexCoords; i++) {
		infile.read((char*) &tmptx, sizeof(md2texcord));
		texcoords.push_back(md2texcord(tmptx.x, tmptx.y));
	}

	md2Tri tmptri;

	infile.seekg(header.offsetTri);
	for (unsigned i = 0; i < (unsigned) header.numTri; i++) {
		infile.read((char*)& tmptri, sizeof(tmptri));
		triangles.push_back(tmptri);
	}


	for (unsigned i = 0; i < (unsigned) header.numFrames; i++) {
		frames.push_back(md2animframe());
		frames.at(i).verticies = NULL;
		frames.at(i).verticies = (md2vertex *) malloc(sizeof(md2vertex) *header.numVerts);
		if (!frames.at(i).verticies) return false;
	}

	infile.seekg(header.offsetFrame);

	char nametmp[16];
	for (unsigned i = 0; i < (unsigned) header.numFrames; i++) {
		infile.read((char*) &frames.at(i).scale, sizeof(md2vec3));
		infile.read((char*) &frames.at(i).trans, sizeof(frames.at(i).trans));
		infile.read((char*) &nametmp, 16);
		frames.at(i).name = nametmp;
		for (unsigned j = 0; j < (unsigned)header.numVerts; j++) {
			infile.read((char*) &frames.at(i).verticies[j], sizeof(md2vertex));
		}
	}

	infile.close();
	
	buildAnimationList();

	return true;
}

bool MD2Model::playAnimation(std::string toplay, bool loop) {
	if (animations.count(toplay) == 0) return false;

	animationplaying = true;
	activeanimation = toplay;
	curframe = animations.at(activeanimation).at(0);
	nextframe = curframe + 1;

	if (loop) this->loop = true;
	else this->loop = false;

	return true;
}

void MD2Model::update(float time) {
	msgrcvr();

	if (animationplaying) {
		curinerpolation += time * 10;
		linInterpolate();
	}
}

void MD2Model::msgrcvr() {
	Message tmp;
	while (MSGBS->hasMessage(id)) {
		tmp = MSGBS->getMessage(id);
		if (tmp.getInstruction() == PLAY_ANIM) {
			if(tmp.getData().sdata != activeanimation)
				if (tmp.getData().idata == -1) playAnimation(tmp.getData().sdata, false);
				else playAnimation(tmp.getData().sdata, true);
		}
		else
		if (tmp.getInstruction() == STOP_ANIM) {
			stopAnimation();
		}
	}
}

void MD2Model::stopAnimation() {
	animationplaying = false;
}

void MD2Model::render(const vec3 & transmat) {
	GeoStream << BEGIN_STREAM;

	lasttrans = transmat;

	//GeoStream << trans_3(lasttrans) << rot_4(90, 0, 1, 0);

	if (animationplaying) renderAnimated();
	else renderStatic();

	GeoStream << END_STREAM;
 }

void MD2Model::renderAnimated() {
	vec2 texcoordtmp;

	vec3 vertc;
	vec3 vertn;
	vec3 vert;

	if (!skins.empty()) TXMAN->useTexture(skins, RNDR);

	GeoStream << START_PRIMITIVE_TRI;

	for (unsigned i = 0; i < triangles.size(); i++) {
		for (unsigned j = 0; j < 3; j++) {
			texcoordtmp.sx( (float) texcoords.at(triangles.at(i).txcoordind[j]).x / header.skinWidth);
			texcoordtmp.sy( (float) texcoords.at(triangles.at(i).txcoordind[j]).y / header.skinHeight);

			vertc.sx((scale.x() * frames.at(curframe).scale.data[0] * frames.at(curframe).verticies[triangles.at(i).faces[j]].pos[0]) + frames.at(curframe).trans.data[0] * scale.x());
			vertc.sz((scale.z() * frames.at(curframe).scale.data[1] * frames.at(curframe).verticies[triangles.at(i).faces[j]].pos[1]) + frames.at(curframe).trans.data[1] * scale.z());
			vertc.sy((scale.y() * frames.at(curframe).scale.data[2] * frames.at(curframe).verticies[triangles.at(i).faces[j]].pos[2]) + frames.at(curframe).trans.data[2] * scale.y());

			vertn.sx((scale.x() * frames.at(nextframe).scale.data[0] * frames.at(nextframe).verticies[triangles.at(i).faces[j]].pos[0]) + frames.at(nextframe).trans.data[0] * scale.x());
			vertn.sz((scale.z() * frames.at(nextframe).scale.data[1] * frames.at(nextframe).verticies[triangles.at(i).faces[j]].pos[1]) + frames.at(nextframe).trans.data[1] * scale.z());
			vertn.sy((scale.y() * frames.at(nextframe).scale.data[2] * frames.at(nextframe).verticies[triangles.at(i).faces[j]].pos[2]) + frames.at(nextframe).trans.data[2] * scale.y());
	
			vert = (vertc + ((vertn - vertc) * curinerpolation));

			GeoStream << texCoord_2(texcoordtmp.x(), texcoordtmp.y()) << vertex_3(vert.x(), vert.y(), vert.z());
		}
	}

	GeoStream << END_PRIMITIVES;

	TXMAN->disableTexture(RNDR);
}

void MD2Model::renderStatic() {
	vec2 texcoordtmp;

	vec3 vert;

	if (!skins.empty()) TXMAN->useTexture(skins, RNDR);

	GeoStream << START_PRIMITIVE_TRI;

	for (unsigned i = 0; i < triangles.size(); i++) {
		for (unsigned j = 0; j < 3; j++) {
			texcoordtmp.sx((float)texcoords.at(triangles.at(i).txcoordind[j]).x / header.skinWidth);
			texcoordtmp.sy((float)texcoords.at(triangles.at(i).txcoordind[j]).y / header.skinHeight);

			vert.sx(scale.x() * frames.at(curframe).scale.data[0] * frames.at(curframe).verticies[triangles.at(i).faces[j]].pos[0] + frames.at(curframe).trans.data[0] * scale.x());
			vert.sz(scale.z() * frames.at(curframe).scale.data[1] * frames.at(curframe).verticies[triangles.at(i).faces[j]].pos[1] + frames.at(curframe).trans.data[1] * scale.z());
			vert.sy(scale.y() * frames.at(curframe).scale.data[2] * frames.at(curframe).verticies[triangles.at(i).faces[j]].pos[2] + frames.at(curframe).trans.data[2] * scale.y());

			GeoStream << texCoord_2(texcoordtmp.x(), texcoordtmp.y()) << vertex_3(vert.x(), vert.y(), vert.z());
		}
	}

	GeoStream << END_PRIMITIVES;

	TXMAN->disableTexture(RNDR);
}


bool MD2Model::hasAnimation(std::string animation) {
	return animations.count(animation) != 0;
}

void MD2Model::linInterpolate() {
	if (curinerpolation >= 1.0f) {
		curinerpolation = 0.0f;
		incFrame();
	}
}

void MD2Model::buildAnimationList() {
	
	if (frames.size() == 0) return;

	std::string curanim = frames.at(0).name.substr(0, getNumInd(frames.at(0).name));
	activeanimation = curanim;

	std::vector<unsigned> tmp;

	animations[curanim] = tmp;

	animations.at(curanim).push_back(0);

	for (unsigned i = 1; i < frames.size(); i++) {
		if (curanim == frames.at(i).name.substr(0, getNumInd(frames.at(i).name))) {
			animations.at(curanim).push_back(i);
		}
		else {
			curanim = frames.at(i).name.substr(0, getNumInd(frames.at(i).name));
			animations[curanim] = tmp;
			animations.at(curanim).push_back(i);
		}
	}
}

int MD2Model::getNumInd(std::string & tosearch) {
	for (unsigned i = 0; i < tosearch.size(); i++) {
		if (tosearch.at(i) >= '0' && tosearch.at(i) <= '9') {
			return i;
		}
	}

	return -1;
}

void MD2Model::calcXminYmin() {
	for (unsigned i = 0; i < frames.size(); i++) {
		frames.at(i).minx = scale.x() * frames.at(i).scale.data[0] * frames.at(i).verticies[0].pos[0] + scale.x() * frames.at(i).trans.data[0];
		frames.at(i).miny = scale.y() * frames.at(i).scale.data[2] * frames.at(i).verticies[0].pos[2] + scale.y() * frames.at(i).trans.data[2];
		frames.at(i).minz = scale.z() * frames.at(i).scale.data[1] * frames.at(i).verticies[0].pos[1] + scale.z() * frames.at(i).trans.data[1];
		frames.at(i).maxx = scale.x() * frames.at(i).scale.data[0] * frames.at(i).verticies[0].pos[0] + scale.x() * frames.at(i).trans.data[0];
		frames.at(i).maxy = scale.y() * frames.at(i).scale.data[2] * frames.at(i).verticies[0].pos[2] + scale.y() * frames.at(i).trans.data[2];
		frames.at(i).maxz = scale.z() * frames.at(i).scale.data[1] * frames.at(i).verticies[0].pos[1] + scale.z() * frames.at(i).trans.data[1];

		for (unsigned j = 1; j < (unsigned) header.numVerts; j++) {
			if (scale.x() * frames.at(i).scale.data[0] * frames.at(i).verticies[j].pos[0] + scale.x() * frames.at(i).trans.data[0] < frames.at(i).minx) {
				frames.at(i).minx = scale.x() * frames.at(i).scale.data[0] * frames.at(i).verticies[j].pos[0] + scale.x() * frames.at(i).trans.data[0];
			}
			if (scale.x() * frames.at(i).scale.data[0] * frames.at(i).verticies[j].pos[0] + scale.x() * frames.at(i).trans.data[0] > frames.at(i).maxx) {
				frames.at(i).maxx = scale.x() * frames.at(i).scale.data[0] * frames.at(i).verticies[j].pos[0] + scale.x() * frames.at(i).trans.data[0];
			}
			if (scale.y() * frames.at(i).scale.data[2] * frames.at(i).verticies[j].pos[2] + scale.y() * frames.at(i).trans.data[2] < frames.at(i).miny) {
				frames.at(i).miny = scale.y() * frames.at(i).scale.data[2] * frames.at(i).verticies[j].pos[2] + scale.y() * frames.at(i).trans.data[2];
			}
			if (scale.y() * frames.at(i).scale.data[2] * frames.at(i).verticies[j].pos[2] + scale.y() * frames.at(i).trans.data[2] > frames.at(i).maxy) {
				frames.at(i).maxy = scale.y() * frames.at(i).scale.data[2] * frames.at(i).verticies[j].pos[2] + scale.y() *  frames.at(i).trans.data[2];
			}
			if (scale.z() * frames.at(i).scale.data[1] * frames.at(i).verticies[j].pos[1] + scale.z() * frames.at(i).trans.data[1] < frames.at(i).minz) {
				frames.at(i).minz = scale.z() * frames.at(i).scale.data[1] * frames.at(i).verticies[j].pos[1] + scale.z() * frames.at(i).trans.data[1];
			}
			if (scale.z() * frames.at(i).scale.data[1] * frames.at(i).verticies[j].pos[1] + scale.z() * frames.at(i).trans.data[1] > frames.at(i).maxz) {
				frames.at(i).maxz = scale.z() * frames.at(i).scale.data[1] * frames.at(i).verticies[j].pos[1] + scale.z() * frames.at(i).trans.data[1];
			}
		}
	}
}

void MD2Model::incFrame() {
	curframe = (curframe + 1);
	if(curframe > animations.at(activeanimation).at(animations.at(activeanimation).size() - 1)) curframe = animations.at(activeanimation).at(0);
	else if (curframe < animations.at(activeanimation).at(0)) curframe = animations.at(activeanimation).at(0);
	
	nextframe = (nextframe + 1);
	if (nextframe > animations.at(activeanimation).at(animations.at(activeanimation).size() - 1)) {
		if(loop) nextframe = animations.at(activeanimation).at(0);
		else animationplaying = false;
	}
	else if (nextframe < animations.at(activeanimation).at(0)) nextframe = animations.at(activeanimation).at(0);
}

void MD2Model::centerOnPoint(vec3 & point) {
	calcXminYmin();
	
	lasttrans = point;
 }

std::vector<vec3>& MD2Model::getVerticies() {
	return std::vector<vec3>();
 }

void MD2Model::setScale(vec3 & toset) {
	scale = toset;
	calcXminYmin();
}