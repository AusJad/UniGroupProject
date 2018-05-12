#pragma once
#include "bass.h"
#include <map>
#include <string>
#include <iostream>
//#include "vec3.h"
#include "Maths.h"
#include "Singleton.h"
#include "MessagingBus.h"
#include "Identifiers.h"

#define DEBUGMODE true
#define AE Singleton<AudioEngine>::getInstance()

/**
* @struct SoundSourceWrapper
* @brief Wrapper for holding information about active channels.
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/

struct SoundSourceWrapper {
	///Wether or not channel uses 3d sound
	bool positional;
	///Game object SSW is bound too
	unsigned associatedgameobject;
	///Handle for channel (for use with BASS)
	int channel;
	///Position of the sound source
	vec3 pos;
	SoundSourceWrapper() : positional(false), channel(0), associatedgameobject(0) {};
	SoundSourceWrapper(int nchannel) : channel(nchannel), positional(false) {};
	SoundSourceWrapper(int nchannel, bool npos) : channel(nchannel), positional(npos) {};
};


/**
* @struct ListenerSourceWrapper
* @brief Wrapper for holding information about the global listener.
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
struct ListenerSourceWrapper {
	/// Bound game object id
	int id;
	/// Position of listener
	vec3 pos;
	ListenerSourceWrapper() : id(-1) {};
};

/**
* @struct
* @brief Contains FFT data.
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
struct FFTData {
	/// If the data is empty.
	bool empty;
	/// The data.
	float data[8];
	FFTData() : empty(true) {};
};

/**
* @class AudioEngine
* @brief Class for handling, storing, and playing sound files
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
class AudioEngine
{
public:
	AudioEngine();
	~AudioEngine();

	/**
	* @brief Initalises BASS library
	*
	* @return bool - Wether or not the library was successfully intalised.
	*/
	bool initalise(const HWND & window);

	/**
	* @brief Sets the active channel subgroup
	*
	* @param nchannel - The subgroup to switch to.
	*/
	void setActiveChannelSubGroup(unsigned nchannel);

	/**
	* @brief Adds a channel subgroup
	*
	* @param groupno - The id to be associated with the subgroup
	*/
	void addChannelSubgroup(unsigned groupno);

	/**
	* @brief Loads a new sound into memory
	*
	* @param path - Location of the sound file on disk.
	* @param type - The type of sound file to load.
	* @param name - The handle to be used in calls to utilise sound.
	* @return bool - Wether or not the sound was loaded correctly.
	*/
	bool loadSound(std::string path, std::string type, std::string name, bool Loop);

	/**
	* @brief Binds a game object to the module as the listener.
	*
	* @param id - The id of the game object to be bound
	* @param startpos - The starting position of the game object
	*/
	bool setListenerSource(int id, vec3 startpos);

	/**
	* @brief Depreciated - Plays sound at origon (0,0,0)
	*
	* @param sound - The name of the sound to play.
	* @return bool - Wether or not the sound was played correctly.
	*/
	bool playSound(std::string sound);

	/**
	* @brief Plays sound at a source.
	*
	* @param sound - The sound data.
	* @param gameobject - The object the sound is bound with.
	* @param pos - The position of the sound.
	*
	* @return bool - If the sound played.
	*/
	bool playSoundatSource(std::string sound, int gameobject, vec3 & pos);

	/**
	* @brief Stop playing the sound
	*
	* @param sound - The sound being stopped
	*
	* @return bool - If the sound was stopped.
	*/
	bool stopSound(std::string sound);

	/**
	* @brief Free all sound objects.
	*
	* @return bool - If all sound objects were freed.
	*/
	bool freeAllSounds();

	/**
	* @brief Pase all active channels.
	*
	* @return bool - If all active channels were paused.
	*/
	bool pauseActiveChannels();

	/**
	* @brief Unpause all channels.
	*
	* @return bool - If all channels were unpaused.
	*/
	bool unpauseChannels();

	/**
	* @brief Find if a sound is playing
	*
	* @param sound - The sound being searched for.
	*
	* @return bool - If the sound is playing.
	*/
	bool soundPlaying(std::string sound);

	/**
	* @brief Update method for the sound.
	*/
	void update();

	/**
	* @brief If the data has sound.
	*
	* @return bool - If it has sound.
	*/
	bool hasSound(std::string sound);

private:
	/// Identifier for the sound.
	Identifiers id;
	/// Map of loaded sounds.
	std::map<std::string, int> loadedsounds;
	/// Map of active channels.
	std::map<int, std::map<std::string, std::vector<SoundSourceWrapper> > > activechannels;
	/// Map of channel listener resources.
	std::map<int, ListenerSourceWrapper> channellistenersources;
	
	/**
	* @brief Work out when a channel has finished playing a sound.
	*
	* @param handle - The name of the sound
	* @param channel - The channel being looked at.
	* @param data - The data of the sound.
	* @param user - The user calling the data.
	*
	* @return bool - If the channel has finished its call back.
	*/
	static void CALLBACK ChannelFinishedCallback(HSYNC handle, DWORD channel, DWORD data, void* user);

	/**
	* @brief Set the listener position
	*
	* @param pos - The new position
	*
	* @return bool - If it was set.
	*/
	bool setListenerPosition(vec3 & pos);

	/**
	* @brief Set the listener position
	*
	* @param pos - The new position
	* @param front - The new front vec
	* @param top - The new top vec
	*
	* @return bool - If it was set.
	*/
	bool setListenerPosition(vec3 & pos, vec3& front, vec3& top);


	/**
	* @brief Get the listener Position
	*
	* @return bool - If it was obtained
	*/
	bool getListenerPosition();

	/// The active sub group that the sound belongs to.
	unsigned activesubgroup;

	/**
	* @brief Update the channel position
	*
	* @param sound - The sound being updated.
	*
	* @return bool - If the sound was updated.
	*/
	bool updateChannelPos(std::string sound, int id, vec3 & newpos);

	/**
	* @brief Receive any messages.
	*/
	void msgrcvr();

	/**
	* @brief Send any messages.
	*/
	void msgsndr();
};

