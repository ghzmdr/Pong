#include "../inc/MainMenu.h"

MainMenu::MainMenu(Window *win):window(win), font(nullptr), buttonPress(nullptr), background(nullptr), done(false){
	initResources();
	while(!done){
		handleInput();
		if(!done)draw();
	}
}

MainMenu::~MainMenu(){
	Mix_FreeChunk(buttonPress);
	TTF_CloseFont(font);
	SDL_DestroyTexture(background);
	for(auto i : buttons) delete i;
}

void MainMenu::initResources(){
	font = TTF_OpenFont("res/font.ttf", 20);
	buttonPress = Mix_LoadWAV("res/hit.wav");
	background = image2Texture(window->getRenderer(), "res/background.png");
	SDL_Texture *buttonBg = image2Texture(window->getRenderer(), "res/buttonbg.png");
	checkMem(buttonBg);
	checkMem(background);
	checkMem(font);
	SDL_Color white = { .r = 255, .g = 255, .b = 255};
	
	title = text2Texture(window->getRenderer(), font, "PONG", white);
	SDL_QueryTexture(title, NULL, NULL, &titleBounds.w, &titleBounds.h);
	titleBounds.w *=4;
	titleBounds.h *=4;
	titleBounds.x = window->getBounds().w/2 -titleBounds.w/2;
	titleBounds.y = 150;
	buttons[0] = new Button(130, 40, window->getBounds().w/3-130,  	window->getBounds().h-200, "1P", 	font, buttonBg, window->getRenderer());
	buttons[1] = new Button(130, 40, window->getBounds().w/3+65,  	window->getBounds().h-200, "2P", 	font, buttonBg, window->getRenderer());
	buttons[2] = new Button(130, 40, 2*window->getBounds().w/3,		window->getBounds().h-200, "Quit",  font, buttonBg, window->getRenderer());


	logInfo("MainMenu init success.");
}

void MainMenu::handleInput(){
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type){
		case SDL_QUIT:
			done = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			handleClick(event.button);
			break;
		case SDL_MOUSEMOTION:
			handleMouse();
			break;
	}
}

void MainMenu::handleClick(SDL_MouseButtonEvent event){
	if(buttons[0]->isMouseOver(event.x, event.y)) { 
		Difficulty diff = chooseDifficulty();
		if(!done){
			Game *game = new Game(window, Mode::SINGLEPLAYER, diff); 
			window->clean(); 
			window->present(); 
			delete game; 
			done = true;
		}
	}		

	if(buttons[1]->isMouseOver(event.x, event.y)) { 
		Difficulty diff = chooseDifficulty();
		if(!done){
			Game *game = new Game(window, Mode::MULTIPLAYER, diff);
			window->clean(); 
			window->present(); 
			delete game; 
			done = true; 
		}
	}
	
	if(buttons[2]->isMouseOver(event.x, event.y)) done = true;
}

Difficulty MainMenu::chooseDifficulty(){
	bool quit = false; 
	SDL_Event event;
	Difficulty diff;

	//Setup Buttons
	for(auto i : buttons) delete i;
	SDL_Texture *buttonBg = image2Texture(window->getRenderer(), "res/buttonbg.png");
	buttons[0] = new Button(130, 40, window->getBounds().w/3-130, 300, "EASY",   font, buttonBg, window->getRenderer());
	buttons[1] = new Button(130, 40, window->getBounds().w/3+65,  300, "NORMAL", font, buttonBg, window->getRenderer());
	buttons[2] = new Button(130, 40, 2*window->getBounds().w/3,   300, "HARD",   font, buttonBg, window->getRenderer());

	//Setup Message
	SDL_Color white = {.r=255, .g=255, .b=255};
	SDL_Texture *message = text2Texture(window->getRenderer(), font, "CHOSE DIFFICULTY", white);
	SDL_Rect messageBounds;
	SDL_QueryTexture(message, NULL, NULL, &messageBounds.w, &messageBounds.h);
	messageBounds.h*=2;
	messageBounds.w*=2;
	messageBounds.y = window->getBounds().h/3;
	messageBounds.x = window->getBounds().w/2 -messageBounds.w/2;

	while(!quit){

		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)	quit = done = true;
		else if(event.type == SDL_MOUSEMOTION){
			int x, y; SDL_GetMouseState(&x, &y);
			for(auto i : buttons){
				bool alreadySelected = i->getSelected();
				if(alreadySelected) i->unselect();
				if(i->isMouseOver(x, y)){i->select(); if(!alreadySelected) Mix_PlayChannel(-1, buttonPress, 0);}
			}
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN){
			if(buttons[0]->isMouseOver(event.button.x, event.button.y)) {diff = Difficulty::EASY; 	quit = true;}
			if(buttons[1]->isMouseOver(event.button.x, event.button.y)) {diff = Difficulty::NORMAL; quit = true;}
			if(buttons[2]->isMouseOver(event.button.x, event.button.y)) {diff = Difficulty::HARD; 	quit = true;}
		}

		logInfo("BTNS SELECTED:%d", buttons[0]->getSelected() + buttons[1]->getSelected() + buttons[2]->getSelected());
		window->clean();
		window->render(background);
		window->render(message, messageBounds);
		for(auto i : buttons)  {window->render(i->getTexture(), i->getBounds()); window->render(i->getText(), i->getTextBounds());}
		window->present();
	}

	SDL_DestroyTexture(message);
	return diff;
}

void MainMenu::handleMouse(){
	int x, y;
	SDL_GetMouseState(&x, &y);
	for(auto i : buttons){
		bool alreadySelected = i->getSelected();
		if(alreadySelected) i->unselect();
		if(i->isMouseOver(x, y)){i->select(); if(!alreadySelected) Mix_PlayChannel(-1, buttonPress, 0);}
	}
}

void MainMenu::draw(){
	window->clean();
	window->render(background);
	for(auto i : buttons){
		window->render(i->getTexture(), i->getBounds());
		window->render(i->getText(), i->getTextBounds());
	}
	window->render(title, titleBounds);
	window->present();
}