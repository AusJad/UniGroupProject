#pragma once
#include "Maths.h"

class Emotions
{
public:
	Emotions();
	Emotions(vec4, vec4, vec4);
	~Emotions();

	void add_emotion(vec4);
	void add_modifier(vec4);
	void add_default(vec4);

	vec4 getEmotions();
	vec4 getModifiers();
	vec4 getDefaults();

	void setEmotions(const vec4 & e);
	void setModifiers(const vec4 & m);
	void setDefaults(const vec4 & d);

	void normalize_emotions();

	// Return emotion vector values;
	float x();
	float y();
	float z();
	float w();
private:
	vec4 emotions, modifiers, defaults;

	mat4 normalization = {
		1.0f, 1.1f, 1.1f, 1.0f,
		1.1f, 1.0f, 1.0f, 1.1f,
		1.1f, 1.0f, 1.0f, 1.1f,
		1.0f, 1.1f, 1.1f, 1.0f };
};

/*
+x = Exstasy
-x = Grief

+y = Admiration
-y = Loathing

+z = Vigilance
-z = Amazement

+w = Rage
-w = Terror
*/
