#include "parameters.h"
#include <thread>
#include "backend.h"
#include "clientProgram.h"
#include <SFML/Audio.hpp>

void runInBackground() {
    run();
}

int main(int argc, char *argv[]) {

	std::string server_hostname;

	if (argc == 2) {
		server_hostname = argv[1];
	}
	else if (argc == 1) {
		server_hostname = SERVER_ADDRESS;
	}
	else {
		std::cout << "Expected 0 or 1 argument : hostname" << '\n';
		return 1;
	}
	


    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("build/static/game-start.wav")) { // play sound while starting the game
        // Handle error loading sound file
        return -1;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
	while (sound.getStatus() == sf::Sound::Playing)
    {
        // Do nothing while the sound is playing
    }

	std::thread backgroundThread(runInBackground);
	if (!buffer.loadFromFile("build/static/bgm.wav")) { // play sound while starting the game
        // Handle error loading sound file
        return -1;
    }
	
	initSettings();
	Program program(server_hostname);
	program.init();
	sound.setBuffer(buffer);
    sound.play();

	program.run();
    
	
	// backgroundThread.join();

	return 0;
}
