#ifndef OSS_SOUNDEFFECT_H
#define OSS_SOUNDEFFECT_H

#include "../general.h"
#include "coreobject.h"
#include "../resources/sound.h"


namespace OSS {
	class SoundEffect : public CoreObject {
	public:
		typedef enum {
			kBackgroundLayer,
			kTransportLayer,
			kTopLayer
		} Layer;
		
		Pointer<Sound> sound;
		Layer layer;
		ALuint sourceID;
		
		/**
		 * Tells the AudioTask to duplicate the SoundEffect before playback. Set this to true if
		 * you intend to create a template SoundEffect which is kept around in your class and sent
		 * to the AudioTask multiple times.
		 */
		bool copyBeforeUse;
		
		/**
		 * Specifies how many instances of this effect may be played concurrently. 0 means unlimited.
		 */
		unsigned int maxConcurrentPlaybacks;
		
		/**
		 * Specifies for how many seconds a previous instance of this effect had to be playing in
		 * order to allow the next instance to be played.
		 */
		double minIntervalBetweenPlaybacks;
		
		/**
		 * Specifies how many times the sound effect is played until it is stopped.
		 */
	private:
		unsigned int loopsLeft;
		double cachedSecondsPlayed;
	public:
		unsigned int loopCount;
		
		//Initialization
		SoundEffect();
		SoundEffect(Sound * sound, Layer layer);
		~SoundEffect();
		std::string instanceName();
		
		//Playback
		void play();
		void pause();
		void stop();
		
		//State
		ALint getSourceState();
		bool isPlaying();
		bool isStopped();
		double getSecondsPlayed();
		
		//Heartbeat
		void update(); //keeps various internal processes running
	};
}


#endif