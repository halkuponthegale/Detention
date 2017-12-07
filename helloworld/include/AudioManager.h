#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "GameView.h"
#include <sstream>

/*
	This class handles all Audio played throughout the application's lifetime (through the use
	of static functions). This class is not to be instantiated.
*/

class AudioManager{
public:
	// play cannon and 'wahoo' sound
	static void play_launch(){

		if(!buffer.loadFromFile("../include/Sounds/woohoo.wav")){
			printf("no file\n");
		}


		sound.setBuffer(buffer);
		sound.setVolume(60);
		sound.setPitch(2);

		sound.play();

		if(!buffer2.loadFromFile("../include/Sounds/cannon.wav")){
			printf("no file\n");
		}


		sound2.setBuffer(buffer2);
		sound2.setVolume(80);
		sound2.setPitch(.8);

		sound2.play();
	}

	// play sound for picking up/placing down boxes with builder
	static void play_builder_box(){

		if(!buffer.loadFromFile("../include/Sounds/builder_box.wav")){
			printf("no sound file\n");
		}

		sound.setBuffer(buffer);
		sound.setVolume(10);
		sound.setPitch(0.8);
		sound.setPlayingOffset(sf::milliseconds(500));

		sound.play();

	}

	// play music during the levels
	static void play_level(int level){
		// stop song currently playing
		music.stop();
		
		std::stringstream lvlString;
		lvlString << "../include/Sounds/level" << level << ".wav";
		
		if(!music.openFromFile(lvlString.str())){
			printf("no sound file\n");
		}
		
		// lower sound for louder tracks
		if(level == 3 || level == 4 || level == 6 || level == 7 || level == 9)
			music.setVolume(20);
		else
			music.setVolume(50);
		
		music.setLoop(true);
		music.play();
	}

	// play exciting "congratulations!" music (when completing final level)
	static void play_end(){
		// stop song currently playing
		music.stop();
		
		if(!buffer.loadFromFile("../include/Sounds/coin_sound.wav")){
			printf("no sound file\n");
		}
		sound.setBuffer(buffer);
		sound.setPitch(1);
		sound.setVolume(20);
		sound.play();

	}

	// play a buzzer sound when player tries to do something that's not possible (ex. pick up a box thats unmovable)
	static void play_buzz(){
		if(!buffer.loadFromFile("../include/Sounds/buzzer.wav")){
			printf("no sound file\n");
		}
		sound.setBuffer(buffer);
		sound.setPitch(1);
		sound.setVolume(30);
		sound.play();

	}

	// play a buzzer sound when player tries to do something that's not possible (ex. pick up a box thats unmovable)
	static void play_cheers(){
		music.stop();
		if(!buffer.loadFromFile("../include/Sounds/cheers.wav")){
			printf("no sound file\n");
		}
		sound.setBuffer(buffer);
		sound.setPitch(1);
		sound.setVolume(50);
		sound.play();

	}




};



#endif
