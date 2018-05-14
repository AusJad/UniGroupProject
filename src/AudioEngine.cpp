#include "AudioEngine.h"



AudioEngine::AudioEngine()
{
	activesubgroup = 0;
	id.setName("AE");
	id.setId(AUDIOENG_ID);
}


AudioEngine::~AudioEngine()
{
}

void CALLBACK AudioEngine::ChannelFinishedCallback(HSYNC handle, DWORD channel, DWORD data, void* user) {
	std::cout << "Channel: " << channel << " has finished playing." << std::endl;
}

void AudioEngine::setActiveChannelSubGroup(unsigned nchannel) {
	pauseActiveChannels();

	activesubgroup = nchannel;

	if(channellistenersources[activesubgroup].id != -1) setListenerPosition(channellistenersources[activesubgroup].pos);
	unpauseChannels();
}

void AudioEngine::addChannelSubgroup(unsigned groupno) {
	std::map<std::string, std::vector<SoundSourceWrapper> > tmp;
	ListenerSourceWrapper tmpls;
	activechannels[groupno] = tmp;
	channellistenersources[groupno] = tmpls;
}

bool AudioEngine::pauseActiveChannels() {

	bool good = true;

	for (std::map<std::string, std::vector<SoundSourceWrapper> >::const_iterator mapit = activechannels.at(activesubgroup).begin(); mapit != activechannels.at(activesubgroup).end(); ++mapit) {
		for (unsigned i = 0; i < mapit->second.size(); i++) {
			if (BASS_ChannelIsActive(mapit->second.at(i).channel)) {
				if (!BASS_ChannelPause(mapit->second.at(i).channel)) {
					if (DEBUGMODE) std::cerr << "Error Pausing Sound! Code: " << BASS_ErrorGetCode() << std::endl;
					good = false;
				}
			}
		}
	}

	return good;
}

bool AudioEngine::unpauseChannels() {
	bool good = true;

	for (std::map<std::string, std::vector<SoundSourceWrapper> >::const_iterator mapit = activechannels.at(activesubgroup).begin(); mapit != activechannels.at(activesubgroup).end(); ++mapit) {
		for (unsigned i = 0; i < mapit->second.size(); i++) {
			if (!BASS_ChannelPlay(mapit->second.at(i).channel, false)) {
				if (DEBUGMODE) std::cerr << "Error Pausing Sound! Code: " << BASS_ErrorGetCode() << std::endl;
				good = false;
			}
		}
	}

	return good;
}

bool AudioEngine::initalise(const HWND & window) {
	if (!BASS_Init(-1, 44100, BASS_DEVICE_3D, window, NULL)) {
		if (DEBUGMODE) std::cerr << "Error Initalising Audio Engine! Code: " << BASS_ErrorGetCode() << std::endl;
		return false;
	}

	if (!BASS_Set3DFactors(0, 0.001f, 0)) {
		if (DEBUGMODE) std::cerr << "Error Initalising Audio Engine! Code: " << BASS_ErrorGetCode() << std::endl;
		return false;
	}

	BASS_Apply3D();

	return true;
}

bool AudioEngine::loadSound(std::string path, std::string type, std::string name, bool Loop) {
	if (type != "WAV") return false;
	HSAMPLE tmp;

	if(!Loop) tmp = BASS_SampleLoad(false, path.c_str(), 0, 0, 50, BASS_SAMPLE_3D);
	else tmp = BASS_SampleLoad(false, path.c_str(), 0, 0, 50, BASS_SAMPLE_3D | BASS_SAMPLE_LOOP);

	if (tmp != 0) {
		loadedsounds[name] = tmp;
	}
	else {
		if (DEBUGMODE) std::cerr << "Error Loading Sound! Code: " << BASS_ErrorGetCode() << std::endl;
		return false;
	}

	return true;
}

bool AudioEngine::playSound(std::string sound) {
	if (loadedsounds.count(sound) == 0) return false;

	if (activechannels.at(activesubgroup).count(sound) == 0) {
		std::vector<SoundSourceWrapper> tmp;
		
		HCHANNEL channel = BASS_SampleGetChannel(loadedsounds[sound], FALSE);
		if (channel == 0) {
			if (DEBUGMODE) std::cerr << "Error Creating Channel! Code: " << BASS_ErrorGetCode() << std::endl;
			return false;
		}
		else {
			if (BASS_ChannelPlay(channel, FALSE)) {
				tmp.push_back(SoundSourceWrapper(channel));
				activechannels[activesubgroup][sound] = tmp;
				return true;
			}
			else {
				if (DEBUGMODE) std::cerr << "Error Playing Sound! Code: " << BASS_ErrorGetCode() << std::endl;
				return false;
			}
		}
	}
	else{
		int actind = -1;
		for (unsigned i = 0; i < activechannels.at(activesubgroup).at(sound).size() && actind == -1; i++) {
			if (BASS_ChannelIsActive(activechannels.at(activesubgroup).at(sound).at(i).channel) == false) {
				actind = i;
			}
		}

		if (actind != -1) {
			if (BASS_ChannelPlay(activechannels.at(activesubgroup).at(sound).at(actind).channel, TRUE)) {
				return true;
			}
			else {
				if (DEBUGMODE) std::cerr << "Error Playing Sound! Code: " << BASS_ErrorGetCode() << std::endl;
				return false;
			}
		}
		else {
			HCHANNEL channel = BASS_SampleGetChannel(loadedsounds[sound], FALSE);
			if (channel == 0) {
				if (DEBUGMODE) std::cerr << "Error Creating Channel! Code: " << BASS_ErrorGetCode() << std::endl;
				return false;
			}
			else {
				if (BASS_ChannelPlay(channel, FALSE)) {
					activechannels.at(activesubgroup).at(sound).push_back(SoundSourceWrapper(channel));
					return true;
				}
				else {
					if (DEBUGMODE) std::cerr << "Error Playing Sound! Code: " << BASS_ErrorGetCode() << std::endl;
					return false;
				}
			}
		}

	}

}

bool AudioEngine::stopSound(std::string sound){
	if (activechannels.at(activesubgroup).count(sound) == 0) return false;

	for (unsigned i = 0; i < activechannels.at(activesubgroup).at(sound).size(); i++) {
		if (BASS_ChannelIsActive(activechannels.at(activesubgroup).at(sound).at(i).channel) == TRUE) {
			if (!BASS_ChannelStop(activechannels.at(activesubgroup).at(sound).at(i).channel)) {
				if (DEBUGMODE) std::cerr << "Error Stopping Channel! Code: " << BASS_ErrorGetCode() << std::endl;
				return false;
			}
		}
	}

	return true;
}

bool AudioEngine::playSoundatSource(std::string sound, int gameobject, vec3 & pos) {
	if (gameobject == -1) return false;
	if (loadedsounds.count(sound) == 0) return false;

	int insind;

	if (activechannels.at(activesubgroup).count(sound) == 0) {
		HCHANNEL channel = BASS_SampleGetChannel(loadedsounds[sound], FALSE);
		if (channel == 0) {
			if (DEBUGMODE) std::cerr << "Error Creating Channel! Code: " << BASS_ErrorGetCode() << std::endl;
			return false;
		}
		else {
			if (BASS_ChannelPlay(channel, FALSE)) {
				std::vector<SoundSourceWrapper> tmp;
				tmp.push_back(SoundSourceWrapper(channel, true));
				activechannels[activesubgroup][sound] = tmp;
				insind = 0;
			}
			else {
				if (DEBUGMODE) std::cerr << "Error Playing Sound! Code: " << BASS_ErrorGetCode() << std::endl;
				return false;
			}
		}
	}
	else {
		int actind = -1;
		for (unsigned i = 0; i < activechannels.at(activesubgroup).at(sound).size() && actind == -1; i++) {
			if (BASS_ChannelIsActive(activechannels.at(activesubgroup).at(sound).at(i).channel) == false) {
				actind = i;
			}
		}

		if (actind != -1) {
			if (BASS_ChannelPlay(activechannels.at(activesubgroup).at(sound).at(actind).channel, TRUE)) {
				activechannels.at(activesubgroup).at(sound).at(actind).positional = true;
				insind = actind;
			}
			else {
				if (DEBUGMODE) std::cerr << "Error Playing Sound! Code: " << BASS_ErrorGetCode() << std::endl;
				return false;
			}
		}
		else {
			HCHANNEL channel = BASS_SampleGetChannel(loadedsounds[sound], FALSE);
			if (channel == 0) {
				if (DEBUGMODE) std::cerr << "Error Creating Channel! Code: " << BASS_ErrorGetCode() << std::endl;
				return false;
			}
			else {
				if (BASS_ChannelPlay(channel, FALSE)) {
					activechannels.at(activesubgroup).at(sound).push_back(SoundSourceWrapper(channel, true));
					insind = activechannels.at(activesubgroup).at(sound).size() - 1;
				}
				else {
					if (DEBUGMODE) std::cerr << "Error Playing Sound! Code: " << BASS_ErrorGetCode() << std::endl;
					return false;
				}
			}
		}
	}


	BASS_3DVECTOR tmppos(pos.x(), pos.y(), pos.z());

	activechannels[activesubgroup][sound].at(insind).pos = pos;
	activechannels[activesubgroup][sound].at(insind).associatedgameobject = gameobject;

	if (!BASS_ChannelSet3DPosition(activechannels.at(activesubgroup).at(sound).at(insind).channel, &tmppos, NULL, NULL)) {
		if (DEBUGMODE) std::cerr << "Error Playing Sound! Code: " << BASS_ErrorGetCode() << std::endl;
		return false;
	}

	return true;
}

bool AudioEngine::setListenerPosition(vec3 & pos) {
	BASS_3DVECTOR listnerpos(pos.x(), pos.y(), pos.z());

	if (!BASS_Set3DPosition(&listnerpos, NULL, NULL, NULL)) {
		if (DEBUGMODE) std::cerr << "Error Playing Sound! Code: " << BASS_ErrorGetCode() << std::endl;
		return false;
	}
	else BASS_Apply3D();

	return true;
}

bool AudioEngine::freeAllSounds() {

	bool good = true;

	for (std::map<std::string, int>::const_iterator mapit = loadedsounds.begin(); mapit != loadedsounds.end(); ++mapit) {
		if (!BASS_SampleFree(mapit->second)) {
			if (DEBUGMODE) std::cerr << "Error Freeing Sound! Code: " << BASS_ErrorGetCode() << std::endl;
			good = false;
		}
	}

	loadedsounds.clear();
	activechannels.clear();

	return good;
}

bool AudioEngine::setListenerSource(int id, vec3 startpos){
	if (id == -1) return false;
	channellistenersources[activesubgroup].id = id;
	setListenerPosition(startpos);

	return true;
}

bool AudioEngine::getListenerPosition() {
	return true;
}

void AudioEngine::update() {
	msgrcvr();
	msgsndr();
}

bool AudioEngine::updateChannelPos(std::string sound, int id, vec3 & newpos) {
	for (unsigned i = 0; i < activechannels.at(activesubgroup).at(sound).size(); i++) {
		if (activechannels.at(activesubgroup).at(sound).at(i).associatedgameobject == id) {
			activechannels[activesubgroup][sound].at(i).pos = newpos;
			BASS_3DVECTOR tmp(activechannels[activesubgroup][sound].at(i).pos.x(), activechannels[activesubgroup][sound].at(i).pos.y(), activechannels[activesubgroup][sound].at(i).pos.z());

			if (!BASS_ChannelSet3DPosition(activechannels[activesubgroup][sound].at(i).channel, &tmp, NULL, NULL)) {
				if (DEBUGMODE) std::cerr << "Error Playing Sound! Code: " << BASS_ErrorGetCode() << std::endl;
				return false;
			}
		}
	}
	return true;
}

bool AudioEngine::setListenerPosition(vec3 & pos, vec3& front, vec3& top) {
	BASS_3DVECTOR listnerpos(pos.x(), pos.y(), pos.z());
	BASS_3DVECTOR lfront(-front.x(), -front.y(), -front.z());
	BASS_3DVECTOR ltop(top.x(), top.y(), top.z());

	if (!BASS_Set3DPosition(&listnerpos, NULL, &lfront, &ltop)) {
		if (DEBUGMODE) std::cerr << "Error Playing Sound! Code: " << BASS_ErrorGetCode() << std::endl;
		return false;
	}
	else BASS_Apply3D();

	return true;
}

void AudioEngine::msgrcvr() {
	MessagingBus* tmpmsgbus = Singleton<MessagingBus>::getInstance();

	Message tmpmsg;

	while (tmpmsgbus->hasIMessage(AUDIOENG_ID)) {
		tmpmsg = tmpmsgbus->getIMessage(AUDIOENG_ID);

		if (tmpmsg.getInstruction() == "PR") {
			if (activechannels[activesubgroup].count(tmpmsg.getData().sdata) == 1) {
				updateChannelPos(tmpmsg.getData().sdata, tmpmsg.getFrom().getId(), tmpmsg.getData().vdata);
			}
		}
		else
		if (tmpmsg.getInstruction() == "LPR") {
			if (channellistenersources[activesubgroup].id != -1) {
				channellistenersources[activesubgroup].pos = tmpmsg.getData().vdata;
				if(tmpmsg.getData().mvdata.size() == 0)
					setListenerPosition(channellistenersources[activesubgroup].pos);
				else
					setListenerPosition(tmpmsg.getData().mvdata.at(0), tmpmsg.getData().mvdata.at(1), tmpmsg.getData().mvdata.at(2));
			}
		}
	}

	while (tmpmsgbus->hasMessage(this->id)) {
		tmpmsg = tmpmsgbus->getMessage(this->id);
		//Request to play sound at source
		if (tmpmsg.getInstruction() == "PSS") {
			if (tmpmsg.getData().idata == -1)
				playSoundatSource(tmpmsg.getData().sdata, channellistenersources[activesubgroup].id, channellistenersources[activesubgroup].pos);
			else
				playSoundatSource(tmpmsg.getData().sdata, tmpmsg.getData().idata, tmpmsg.getData().vdata);
		}
		else
		//Request to play sound without source defined
		//Avoid using - will play sound at position 0,0,0
		if (tmpmsg.getInstruction() == "PS") {
			playSound(tmpmsg.getData().sdata);
		}
		else
		if (tmpmsg.getInstruction() == SND_PLAYING) {
			tmpmsg.setInstruction(SND_PLAYING_R);
			
			int ret;
			
			if (soundPlaying(tmpmsg.getsData())) ret = 1;
			else ret = -1;

			tmpmsg.setIData(ret);

			MSGBS->postMessage(tmpmsg, tmpmsg.getFrom());
		}
	}
}

bool AudioEngine::soundPlaying(std::string totest) {
	if (activechannels.at(activesubgroup).count(totest) == 0) return false;

	for (unsigned i = 0; i < activechannels.at(activesubgroup).at(totest).size(); i++) {
		if (BASS_ChannelIsActive(activechannels.at(activesubgroup).at(totest).at(i).channel) == TRUE) {
			return true;
		}
	}
	
	return false;
}

void AudioEngine::msgsndr() {
	MessagingBus* tmpmsgbus = Singleton<MessagingBus>::getInstance();
	Message tmpm;

	for (std::map<std::string, std::vector<SoundSourceWrapper> >::const_iterator mapit = activechannels.at(activesubgroup).begin(); mapit != activechannels.at(activesubgroup).end(); ++mapit) {
		for (unsigned i = 0; i < mapit->second.size(); i++) {
			if (mapit->second.at(i).positional) {
				tmpm.setInstruction("POS");
				tmpm.setData(mapit->first);
				tmpm.setFrom(id);
				tmpmsgbus->postIMessage(tmpm, mapit->second.at(i).associatedgameobject);
			}
		}
	}

	if (channellistenersources[activesubgroup].id != -1) {
		tmpm.setInstruction("LPOS");
		tmpm.setFrom(id);
		tmpmsgbus->postIMessage(tmpm, channellistenersources[activesubgroup].id);
	}
}

bool AudioEngine::hasSound(std::string sound) {
	return loadedsounds.count(sound) == 1;
}