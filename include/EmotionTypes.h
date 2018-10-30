#pragma once
#include "Maths.h"

/* This struct simply holds "default" emotional values for emotion class's "Defaults" variable */
struct emo_defaults
{
	vec4 love = vec4(0.2f, 0.2f, 0.0f, 0.0f);
	vec4 submission = vec4(0.0f, 0.2f, 0.0f, -0.2f);
	vec4 awe = vec4(0.0f, 0.0f, -0.2f, -0.2f);
	vec4 disapproval = vec4(-0.2f, 0.0f, -0.2f, 0.0f);
	vec4 remorse = vec4(-0.2f, -0.2f, 0.0f, 0.0f);
	vec4 contempt = vec4(0.0f, -0.2f, 0.0f, 0.2f);
	vec4 agressiveness = vec4(0.0f, 0.0f, 0.2f, 0.2f);
	vec4 optimism = vec4(0.2f, 0.0f, 0.2f, 0.0f);
};

struct emo_mods
{
	vec4 love = vec4(1.2f, 1.2f, 1.0f, 1.0f);
	vec4 submission = vec4(1.0f, 1.2f, 1.0f, -1.2f);
	vec4 awe = vec4(1.0f, 1.0f, -1.2f, -1.2f);
	vec4 disapproval = vec4(-1.2f, 1.0f, -1.2f, 1.0f);
	vec4 remorse = vec4(-1.2f, -1.2f, 1.0f, 1.0f);
	vec4 contempt = vec4(1.0f, -1.2f, 1.0f, 1.2f);
	vec4 agressiveness = vec4(1.0f, 1.0f, 1.2f, 1.2f);
	vec4 optimism = vec4(-1.2f, 1.0f, 1.2f, 1.0f);
};

struct emo_emo
{
	vec4 love = vec4(0.3f, 0.4f, 0.0f, 0.0f);
	vec4 submission = vec4(0.0f, 0.35f, 0.0f, -0.3f);
	vec4 awe = vec4(0.0f, 0.0f, -0.3f, -0.46f);
	vec4 disapproval = vec4(-0.8f, 0.0f, -0.3f, 0.0f);
	vec4 remorse = vec4(-0.52f, -0.3f, 0.0f, 0.0f);
	vec4 contempt = vec4(0.0f, -0.6f, 0.0f, 0.25f);
	vec4 agressiveness = vec4(0.0f, 0.0f, 0.28f, 0.8f);
	vec4 optimism = vec4(0.1f, 0.0f, 0.59f, 0.0f);
};