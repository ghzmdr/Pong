#include "../inc/Game.h"


//TODO: Add pixel-perfected collision detection
Game::Game(Window *win, Mode mod, Difficulty diff)
:done(false), window(win), scored(false), mode(mod), difficulty(diff),
font(nullptr), scoreTexture(nullptr), background(nullptr), lPad(nullptr), rPad(nullptr), ball(nullptr), hitEffect(nullptr), bounceEffect(nullptr), pointEffect(nullptr), field(nullptr){

	init();
	waitForPlayers();

	while(!done){
		handleInput();
		updateLogic();
		drawGame();
	}
}

Game::~Game(){
	Mix_FreeChunk(hitEffect);
	Mix_FreeChunk(bounceEffect);
	Mix_FreeChunk(pointEffect);
	TTF_CloseFont(font);
	SDL_DestroyTexture(scoreTexture);
	SDL_DestroyTexture(background);
	delete field;
	delete lPad;
	delete rPad;
	delete ball;
}

void Game::init(){
	//Load resources and game objects
	hitEffect = Mix_LoadWAV("res/hit.wav");
	bounceEffect = Mix_LoadWAV("res/bounce.wav");
	pointEffect = Mix_LoadWAV("res/score.wav");
	checkMem(hitEffect);
	checkMem(bounceEffect);
	checkMem(pointEffect);

	background = image2Texture(window->getRenderer(), "res/background.png");
	font = TTF_OpenFont("res/font.ttf", 20);
	SDL_Texture *lPadTexture = image2Texture(window->getRenderer(), "res/paddle.png");
	SDL_Texture *rPadTexture = lPadTexture;
	SDL_Texture *ballTexture = image2Texture(window->getRenderer(), "res/ball.png");
	SDL_Texture *fieldTexture = image2Texture(window->getRenderer(), "res/field.png");
	checkMem(font);
	checkMem(background);
	checkMem(lPadTexture);
	checkMem(rPadTexture);
	checkMem(ballTexture);
	checkMem(fieldTexture);

	lPad = new Paddle(lPadTexture, window->getBounds().w, window->getBounds().h, POSITION_LEFT);
	rPad = new Paddle(rPadTexture, window->getBounds().w, window->getBounds().h, POSITION_RIGHT);
	
	SDL_Rect fieldBounds; 
	fieldBounds.x = window->getBounds().x +30;
	fieldBounds.y = window->getBounds().y +30;
	fieldBounds.w = window->getBounds().w -60;
	fieldBounds.h = window->getBounds().h -60;
	field = new RenderableObject(fieldTexture, fieldBounds);

	int ballSpeedX = 3, ballSpeedY = 3;
	if(difficulty == Difficulty::EASY) 		 ballSpeedX = 8; ballSpeedY =  6;
	if(difficulty == Difficulty::NORMAL) 	 ballSpeedX = 10; ballSpeedY = 8;
	if(difficulty == Difficulty::HARD) 		 ballSpeedX = 12; ballSpeedY = 10;
	if(difficulty == Difficulty::UNBEATABLE) ballSpeedX = ballSpeedY = 20;
	ball = new Ball(ballTexture, window->getBounds().w, ballSpeedX, ballSpeedY);

	logInfo("Game init success");
}

void Game::handleInput(){
	//If someone has taken point wait for spacebar press
	if(scored){ waitForPlayers();	scored = false; }

	//Up and Down arrows to move the right paddle, W and S keys to move the right one
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type){
		case SDL_QUIT:
			done = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym){
			case SDLK_UP:
				if(mode == Mode::MULTIPLAYER) if(rPad->getBounds().y > 0)		rPad->moveUp();
				break;
			case SDLK_DOWN:
				if(mode == Mode::MULTIPLAYER) if(rPad->getBounds().y+rPad->getBounds().h < window->getBounds().h)	rPad->moveDown();
				break;
			case SDLK_w:
				if(lPad->getBounds().y > 0)		lPad->moveUp();
				break;
			case SDLK_s:
				if(lPad->getBounds().y+lPad->getBounds().h < window->getBounds().h)	lPad->moveDown();
				break;
			case SDLK_F1:
				reset();
			}	
			break;
	}
}

void Game::waitForPlayers(){
	std::string wait = "Press SPACE to continue";
	SDL_Color white = { .r = 255, .g = 255, .b = 255};

	SDL_Texture *waitTexture = text2Texture(window->getRenderer(), font, wait, white);
	checkMem(waitTexture);

	SDL_QueryTexture(waitTexture, NULL, NULL, &scorePosition.w, &scorePosition.h);
	scorePosition.x = window->getBounds().w/2 -scorePosition.w/2;
	scorePosition.y = 100;
	//Render the text 100px under the score

	if(!scored) window->clean();
	if(!scored) window->render(background);
	window->render(waitTexture, scorePosition);

	if(!scored) displayInstructions();
	window->present();

	while(true){
		SDL_Event event;
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) { Mix_PlayChannel(-1, bounceEffect, 0); break;}
		else if (event.type == SDL_QUIT){ done = true; break;}
	}
	SDL_DestroyTexture(waitTexture);
}

void Game::displayInstructions(){ 
	SDL_Color white = { .r = 255, .g = 255, .b = 255};
	std::string instructions = "W and S to move left pad";
	
	SDL_Texture *instructionTexture = text2Texture(window->getRenderer(), font, instructions, white);
	checkMem(instructionTexture);
	
	SDL_QueryTexture(instructionTexture, NULL, NULL, &scorePosition.w, &scorePosition.h);
	scorePosition.x = window->getBounds().w/2 -scorePosition.w/2;
	scorePosition.y = 200;
	
	window->render(instructionTexture, scorePosition);
	SDL_DestroyTexture(instructionTexture);
	
	if(mode == Mode::MULTIPLAYER){
		std::string instructions = "UP and DOWN to move right pad";
		
		instructionTexture = text2Texture(window->getRenderer(), font, instructions, white);
		checkMem(instructionTexture);
		
		SDL_QueryTexture(instructionTexture, NULL, NULL, &scorePosition.w, &scorePosition.h);
		scorePosition.x = window->getBounds().w/2 -scorePosition.w/2;
		scorePosition.y = 220+scorePosition.h;
		
		window->render(instructionTexture, scorePosition);
		SDL_DestroyTexture(instructionTexture);
	}
}

void Game::updateLogic(){
	if(mode == Mode::SINGLEPLAYER){
		if(difficulty == Difficulty::NO) 			rPad->follow(ball->getBounds().y, 20, 0);
		if(difficulty == Difficulty::EASY) 			rPad->follow(ball->getBounds().y, 20, 7);
		if(difficulty == Difficulty::NORMAL) 		rPad->follow(ball->getBounds().y, 25, 9);
		if(difficulty == Difficulty::HARD)			rPad->follow(ball->getBounds().y, 20, 9);
		if(difficulty == Difficulty::UNBEATABLE) 	rPad->follow(ball->getBounds().y, 0, 20);
	}

	//Check for collision and update ball's direction
	if(ballCollidesRight()) {ball->changeXDirection(DIR_LEFT);  Mix_PlayChannel(-1, hitEffect, 0);}
	if(ballCollidesLeft())	{ball->changeXDirection(DIR_RIGHT); Mix_PlayChannel(-1, hitEffect, 0);}

	//If the ball is going out of the bounds change it's direction
	if(ball->getBounds().y <= field->getBounds().y) {ball->changeYDirection(DIR_DOWN); Mix_PlayChannel(-1, bounceEffect, 0);}
	if(ball->getBounds().y +ball->getBounds().h >= field->getBounds().y+field->getBounds().h) {ball->changeYDirection(DIR_UP); Mix_PlayChannel(-1, bounceEffect, 0);}   

	//Check for point on both directions
	int outDirection = ballIsOut();
	if(outDirection == 1){	ball->reset(); 	rPad->addScore(); 	lPad->flick(); scored = true;	Mix_PlayChannel(-1, pointEffect, 0);}
	if(outDirection == 2){	ball->reset();	lPad->addScore();	rPad->flick(); scored = true;	Mix_PlayChannel(-1, pointEffect, 0);}

	//Check for winning condition
	if(lPad->getScore() == 7 || rPad->getScore() == 7)	displayGameOver();

	ball->move();
}

bool Game::ballCollidesRight(){
	int ballTop = ball->getBounds().y;
	int ballBottom = ball->getBounds().y + ball->getBounds().w;
	//If the ball's bottom is higher (less than) the paddle's top OR the ball's top is lower (more than) the paddle's top they can't collide
	if(ballTop > rPad->getBounds().y+rPad->getBounds().h || ballBottom < rPad->getBounds().y) return false;
	//If the right side of the ball is far from the left side of the paddle or after it's middle they can't collide
	int ballRight = ball->getBounds().x+ball->getBounds().w;
	if(ballRight < rPad->getBounds().x || ballRight > rPad->getBounds().x+rPad->getBounds().w) return false;

	int ballAngle = calcBallAngle(rPad);
	if(ballAngle < 0) ballAngle*=-1;
	ball->setSpeed(NULL, ballAngle);
	logInfo("BallAng: %d", ballAngle);
	return true;
}

bool Game::ballCollidesLeft(){
	int ballTop = ball->getBounds().y;
	int ballBottom = ball->getBounds().y + ball->getBounds().w;
	//If the ball's bottom is higher (less than) the paddle's top OR the ball's top is lower (more than) the paddle's top they can't collide
	if(ballTop > lPad->getBounds().y+lPad->getBounds().h || ballBottom < lPad->getBounds().y) return false;
	//If the left side of the ball is far from the right side of the paddle or after it's middle they can't collide
	int ballLeft = ball->getBounds().x;
	if(ballLeft > lPad->getBounds().x+lPad->getBounds().w || ballLeft < lPad->getBounds().x-lPad->getBounds().w) return false;

	int ballAngle = calcBallAngle(lPad);
	if(ballAngle < 0) ballAngle*=-1;
	ball->setSpeed(NULL, ballAngle);
	logInfo("BallAng: %d", ballAngle);
	return true;
}

int Game::calcBallAngle(Paddle *pad){
	return 5*((ball->getBounds().y -pad->getBounds().y)/25);
}

int Game::ballIsOut(){
	if(ball->getBounds().x < lPad->getBounds().x-lPad->getBounds().w) return 1;
	if(ball->getBounds().x > rPad->getBounds().x+rPad->getBounds().w) return 2;
	return 0;
}

void Game::displayGameOver(){
	Mix_PlayChannel(-1, bounceEffect, 1);
	std::string winner;
	SDL_Color white = {.r =255, .g =255, .b =255};
	SDL_Texture *buttonBg = image2Texture(window->getRenderer(), "res/buttonbg.png");
	Button *retryBtn =	new Button(140, 40, window->getBounds().w/3-70, 300, 	"RETRY", font, buttonBg, window->getRenderer());
	Button *exitBtn  = 	new Button(140, 40, 2*window->getBounds().w/3-70, 300,  "EXIT",  font, buttonBg, window->getRenderer());

	if(mode == Mode::SINGLEPLAYER)
		if(lPad->getScore() == 7) winner = "YOU WIN!";
		else winner = "CPU WINS";	
	else 
		if(lPad->getScore() == 7) winner = "P1 WINS";
		else winner = "P2 WINS"; 

	SDL_Texture *winTexture = text2Texture(window->getRenderer(), font, winner, white);
	SDL_Rect winBounds;
	SDL_QueryTexture(winTexture, NULL, NULL, &winBounds.w, &winBounds.h);
	winBounds.w *= 3;
	winBounds.h *= 3;
	winBounds.x = window->getBounds().w/2- winBounds.w/2;
	winBounds.y = 200;

	bool quit = false;
	SDL_Event event;
	while(!quit){
		SDL_PollEvent(&event);
		if(event.type == SDL_MOUSEBUTTONDOWN){
			if(retryBtn->isMouseOver(event.button.x, event.button.y)) {reset(); quit = true;}
			if(exitBtn->isMouseOver(event.button.x, event.button.y)) quit = done = true;
		}

		if(event.type == SDL_MOUSEMOTION){
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			bool retryAlreadySel = retryBtn->getSelected();
			bool exitAlreadySel = exitBtn->getSelected();
			retryBtn->unselect();
			exitBtn->unselect();
			if(retryBtn->isMouseOver(mouseX, mouseY)) {retryBtn->select(); if(!retryAlreadySel) Mix_PlayChannel(-1, hitEffect, 0);}
			if(exitBtn->isMouseOver(mouseX, mouseY)) {exitBtn->select(); if(!exitAlreadySel) Mix_PlayChannel(-1, hitEffect, 0);}
		}
	
		if(event.type == SDL_QUIT) quit = done = true;

		window->clean();
		window->render(background);
		window->render(winTexture, winBounds);

		window->render(retryBtn->getTexture(), retryBtn->getBounds());
		window->render(retryBtn->getText(), retryBtn->getTextBounds());
		window->render(exitBtn->getTexture(), exitBtn->getBounds());
		window->render(exitBtn->getText(), exitBtn->getTextBounds());
		
		window->present();
	}

	SDL_DestroyTexture(winTexture);
	delete exitBtn;
	delete retryBtn;
}

void Game::drawGame(){
	window->clean();
	if(!done){
		window->render(background);
		if(!scored)window->render(ball->getTexture(), ball->getBounds());
		window->render(rPad->getTexture(), rPad->getBounds());
		window->render(lPad->getTexture(), lPad->getBounds());
		window->render(field->getTexture(), field->getBounds());

		elaborateScore();
		window->render(scoreTexture, scorePosition);
	}
	window->present();
}

void Game::elaborateScore(){
	std::stringstream score;
	SDL_Color white = { .r = 255, .g = 255, .b = 255};

	score << "Score: ";
	score << lPad->getScore() << " - " << rPad->getScore();

	scoreTexture = text2Texture(window->getRenderer(), font, score.str(), white);
	checkMem(scoreTexture);

	SDL_QueryTexture(scoreTexture, NULL, NULL, &scorePosition.w, &scorePosition.h);
	scorePosition.x = window->getBounds().w/2 -scorePosition.w/2;
	scorePosition.y = 5;
}

void Game::reset(){
	ball->reset();
	lPad->reset();
	rPad->reset();
}
