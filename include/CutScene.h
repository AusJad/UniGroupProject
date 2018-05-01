#pragma once

#include "Model.h"
#include "TextureManager.h"
#include "FontEngine.h"
#include "AudioEngine.h"
#include <algorithm>
#include <map>
#include <stack>

//animation file keywords
#define FILE_HEAD					"HEADER"
#define FILE_HEAD_END				"ENDHEADER"
#define OBJECT_START				"DEFINEOBJ"
#define TEXT_START					"DEFINETEXT"
#define AUDIO_START					"DEFINEAUDIO"
#define ACTOR_END					"ENDDEF"
#define FRAME_START					"BEGINFRAME"
#define FRAME_END					"ENDFRAME"
#define ANIMATION_START				"DEFINEANIM"
#define ANIMATION_END				"ENDANIM"
#define	ENTITY_NAME					"NAME"
#define TOP_LEFT					"TOP"
#define BOTTOM_RIGHT				"BOTTOM"
#define Z_OFFSET					"DISTANCE"
#define ACTOR_TEXTURE				"TEXTURE"
#define	SOUND_FILE					"SOUNDHANDLE"
#define	LOOP_AUDIO					"LOOP"
#define TEXT_VALUE					"VALUE"
#define TEXT_FONT					"FONT"
#define	ANIMATION_DURATION			"TIME"
#define ANIMATION_X					"X"
#define	ANIMATION_Y					"Y"
#define ANIMATION_Z					"Z"
#define ANIMATION_FLAGS				"FLAGS"
#define COMMENT						'#'
#define FRAME_ACTORS				"FRAMEOBJECTS"
#define FRAME_DURATION				"FRAMEDURATION"
#define ANIMATION_START_TIME		"STARTIME"
#define ACTOR_ALPHA					"ALPHAFLAG"
#define FRAME_SOUND_START			"PLAYSOUND"
#define FRAME_SOUND_END				"ENDPLAYSOUND"

#define CSTRUE						"TRUE"
#define CSFALSE						"FALSE"

//Animation flags
#define UNDEFINED_FLAG				-1
#define PLAY_AT_START_STR			"PLAYATSTART"
#define PLAY_AT_START				1
#define LOOP_STR					"LOOP"
#define LOOP						2
#define GO_TO_STR					"GOTO"
#define GO_TO						3

struct SceneObject {
	std::string name;
	vec2 top;
	vec2 bottom;
	float zdistance;
	std::string texture;

	bool alphaflag;

	vec3 curoffset;
	
	SceneObject() {
		alphaflag = false;
		zdistance = 0;
	}
	void clear() {
		alphaflag = false;
		name.clear();
		top = vec2();
		bottom = vec2();
		curoffset = vec3();
		zdistance = 0;
		texture.clear();
	}
	void reset() {
		curoffset = vec3();
	}
};

struct SceneText {
	std::string name;
	vec2 startlocation;
	float zdistance;
	std::string value;
	std::string font;

	unsigned nextchar = 0;

	std::string curstring;

	SceneText(){
		zdistance = 0;
		nextchar = 0;
	}
	void clear() {
		name.clear();
		startlocation = vec2();
		zdistance = 0;
		nextchar = 0;
		value.clear();
		font.clear();
		curstring.clear();
	}
	void reset() {
		nextchar = 0;
		curstring.clear();
	}
};

struct SceneAudio {
	std::string name;
	std::string file;
	bool loop;

	SceneAudio() {
		loop = false;
	}
	void clear() {
		name.clear();
		file.clear();
		loop = false;
	}
};

struct Animation {
	std::string name;
	float time;
	float starttime;
	vec3 transamount;
	int flags;
	std::string goto_;
	std::string animatedentity;

	Animation() {
		time = 0;
		flags = 0;
		starttime = 0;
	}
	void clear() {
		name.clear();
		transamount = vec3();
		time = 0;
		flags = 0;
		starttime = 0;
		goto_.clear();
		animatedentity.clear();
	}
};

struct FrameSound {
	float starttime;
	bool playing;
	std::string sound;

	FrameSound() {
		starttime = 0;
		playing = false;
	}

	void clear() {
		starttime = 0;
		playing = false;
		sound.clear();
	}
};

struct Frame {
	float duration;
	std::vector<Animation> animations;
	std::vector<std::string> actors;
	std::vector<FrameSound> sounds;

	Frame() {
		duration = 0;
	}
	void clear() {
		duration = 0;
		animations.clear();
		actors.clear();
		sounds.clear();
	}
};

class CutScene : public Model
{
public:
	CutScene();
	CutScene(const CutScene & tocpy);

	/**
	* @brief Create a textured square.
	*
	* @return TexturedSquare* - The textured square data.
	*/
	CutScene * create() const;

	/**
	* @brief Load the model from file.
	*
	* @param filename - The file name.
	*
	* @return bool - If the file was loaded.
	*/
	bool loadModel(std::string filename);

	/**
	* @brief The update file.
	*/
	void update(float time);

	/**
	* @brief The render function.
	*
	* @param transmat - The translation matrix.
	*/
	void render(const vec3 & transmat);

	/**
	* @brief Set the center on point vector.
	*
	* @param point - The point vector.
	*/
	void centerOnPoint(vec3 & point);

	/**
	* @brief Get the verticies.
	*
	* @return vector<vec3> - The vector of verticies.
	*/
	std::vector<vec3>& getVerticies();

	/**
	* @brief Set the scale vector.
	*
	* @param toset - The scale vector.
	*/
	void setScale(vec3 & toset);

private:
	std::map<std::string, SceneObject> cutsceneObjects;
	std::map<std::string, SceneText> cutsceneText;
	std::map<std::string, SceneAudio> cutsceneAudio;
	std::vector<Frame> scenes;
	unsigned currentAnimation;
	float culmtime;
	bool finishedflag;

	void drawText(SceneText & todraw);
	void drawActor(SceneObject & todraw);

	void doActiveAnimations(float time);
	void doAnimation(Animation & todo, std::string name, float time);

	void RenderFade(float alpha);

	void changeScene();

	void onDone();

	bool getHeader(std::ifstream & toread);
	bool parseFrames(std::ifstream & toread);
	void cleanLine(std::string & toclean);
	int stringToFlags(std::string totest);
};

