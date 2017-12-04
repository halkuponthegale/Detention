#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "GameView.h"


class AudioManager{
public:
	static void play_launch(){
		printf("playing launch\n");
		if(!buffer.loadFromFile("../include/Sounds/woohoo.wav")){
			printf("no file\n");
		}


		sound.setBuffer(buffer);
		sound.setVolume(50);
		sound.setPitch(1.4);

		sound.play();
	}

	static void play_builder_box(){
		printf("playing builder\n");
		if(!buffer.loadFromFile("../include/Sounds/builder_box.wav")){
			printf("no file\n");
		}


		sound.setBuffer(buffer);
		sound.setVolume(20);
		sound.setPitch(0.8);
		sound.setPlayingOffset(sf::milliseconds(500));

		// sound.setPitch(0.8);
		sound.play();
		// sound.setVolume(1.2);
		// sound.setPitch(1.2);
	}
};



#endif
