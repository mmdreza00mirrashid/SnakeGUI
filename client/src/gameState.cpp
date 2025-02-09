#include "state.h"
#include <SFML/Network.hpp>
#include "parameters.h"
#include <SFML/Graphics.hpp>
#include "draw.h"
#include "food.h"
#include "player.h"

int timer=0;

void GameState::init() {
	_communication->init();

	_controller.resetInput();
    
    if (!_texture.loadFromFile("build/static/bg45.jpg")) {
		// error when load file
		exit(1);
	}

	if (!_font.loadFromFile("build/static/Dosis-Regular.ttf")) {
		// error when load file
		exit(1);
	}
}

void GameState::getServerData() {
    // Receive Data from server
	sf::Packet data;
	sf::Socket::Status status;
	int header;
	_communication->receivePacket(header, data, status);

	if (status == sf::Socket::Done || status == sf::Socket::NotReady) {
		switch (header) {
		case END:
			_snake.die();
			std::cout << "END : " << header << '\n';
			State::setNextState("home", "Your score : " + std::to_string(_snake.getBody().getLength()));
			break;

		case GAME_FULL:
			_communication->disconnect();
			std::cout << "GAME FULL !!!!!" << '\n';
			State::setNextState("home", "Game full ! Please try again later.");
			break;

		case OK:
			_has_received_data = true;
			_serverData.extract(data);
			break;

		default:
			break;
		}
	} else {
		// std::cout << "STATUT : " << status << '\n';
		State::setNextState("home", "Error ! Unable to connect to the server.");
	}
}

void GameState::handleEvents() {
    sf::Event event;
	while (_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			// Disconnect from server
			quit();
			// Close window
			_window->close();
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				State::setNextState("home");
			}

			if(isBoosted==true){
				_controller.setSpeed(BOOST_SPEED);
				timer++;
				if(timer==2){
					isBoosted=false;
					timer=0;
				}
			}
			else if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up) {
				_controller.setSpeed(HIGH_SPEED);
			}
			if (event.key.code == sf::Keyboard::Right) {
				_controller.rotateRight(true);
			}
			if (event.key.code == sf::Keyboard::Left) {
				_controller.rotateLeft(true);
			}
		}
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up) {
				if(isBoosted==false){
					_controller.setSpeed(LOW_SPEED);
				}
				
			}
			if (event.key.code == sf::Keyboard::Right) {
				_controller.rotateRight(false);
			}
			if (event.key.code == sf::Keyboard::Left) {
				_controller.rotateLeft(false);
			}
		}
	}
}



void GameState::update() {
	if (_has_received_data) {

		// Get server Data
		auto data = _serverData.getData();

		// Update client snake
		_snake.updateBody(data.my_snake.parts);
		
		// Update all the other snakes
		for (size_t i = 0; i < data.snakes.size(); i++) {
			// If the user does not already exist ...
			if (_snakes.find(data.snakes[i].id) == _snakes.end())
				_snakes[data.snakes[i].id] = Snake(data.snakes[i].parts);

			// The user already exists --> Update his coordinates
			else
				_snakes[data.snakes[i].id] = data.snakes[i].parts;
		}

		// std::cout << "SIZE: " << data.my_snake.parts.size() << '\n';
		// std::cout << "MY SNAKE COORD : " << data.my_snake.parts[0].getCoordinates().x << ' ' << data.my_snake.parts[0].getCoordinates().y << '\n';

		if (data.my_snake.parts[0].getCoordinates().x != data.my_snake.parts[0].getCoordinates().x) { // NaN
			State::setNextState("home", "Server error, please retry");
		}

		// Delete all the deleted snakes
		std::map<unsigned int, Snake>::iterator it_snake;
		for (it_snake = _snakes.begin(); it_snake != _snakes.end();) {
			bool flag = false;
			for (size_t i = 0; i < data.snakes.size(); i++) {
				if (it_snake->first == data.snakes[i].id) {
					flag = true;
					break;
				}
			}
			if (!flag) {
				_snakes.erase(it_snake++);
			} else {
				it_snake++;
			}
		}

		// Update foods
		_foods.clear();
		for (size_t i = 0; i < data.food_vector.size(); i++) {
			if(i%6==0){
				Food temp=Food(data.food_vector[i]);
				temp.setFoodType(FoodType::SPEED);
				_foods.push_back(temp);
			}
			else{
				Food temp=Food(data.food_vector[i]);
				temp.setFoodType(FoodType::SIZE);
				_foods.push_back(temp);
			}
			
			
		}
	}
}

void GameState::sendClientInput() {
    if (_has_received_data) {
		_communication->send(OK, _controller.getInput());
		_has_received_data = false;
	}
}

void GameState::display() {
	sf::Vector2f origin = _snake.getBody().getHead().getCoordinates();

	_window->clear();

	drawTexture(_window, origin, _texture);

	// Draw foods
	for (std::list<Food>::iterator it = _foods.begin(); it != _foods.end(); it++) {
		drawFoods(_window, origin, *it);
	}
	
	// Draw my snake
	drawSnakeBody(_window, origin, _snake.getBody());

	// Draw all the other snakes
	for (std::map<unsigned int, Snake>::iterator it = _snakes.begin(); it != _snakes.end(); it++) {
		drawSnakeBody(_window, origin, it->second.getBody());
	}

	// draw minimap
	drawMinimap(_window);
	for (std::map<unsigned int, Snake>::iterator it = _snakes.begin(); it != _snakes.end(); it++) {
		drawSnakeBodyMinimap(_window, it->second.getBody());
	}
	drawSnakeBodyMinimap(_window, _snake.getBody(), true); // true to draw my snake head in Yellow

	drawCurrentScore(_window, _font, _snake.getBody().getLength());

	// Display Result
	_window->display();
}

void GameState::quit() {
	// Disconnect from server
	_communication->send(DISCONNECT);
	_communication->disconnect();
}


    
