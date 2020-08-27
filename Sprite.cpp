#include "Sprite.h"

void Sprite::LoadTexture(std::string path, SDL_Renderer* renderer, b2World* world) {

	//loads our image to a temp surface
	SDL_Surface* tempSurface = NULL;
	tempSurface = IMG_Load(path.c_str());


	if (tempSurface == NULL) {
		std::cout << "Failed to create sprite\n";
	}
	else {
		std::cout << "Succesfully loaded sprite at " << path.c_str() << "\n\n";

		STexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
	}

	this->world = world;


}
void Sprite::Render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, STexture, NULL, &SRect);
}

void Sprite::Set(int xpos, int ypos, int height, int width) {
	SRect.x = xpos;
	SRect.y = ypos;
	SRect.h = height;
	SRect.w = width;

	//our sprite half witdh and height
	float h, w;

	h = SRect.h / 2;
	w = SRect.w / 2;

	//sets the position for the ground body def
	Sbody_def.position.Set(float(SRect.x + SRect.w / 2), -float(SRect.y + SRect.h / 2 ));

	//creates a ground body inside our world
	SBody = world->CreateBody(&Sbody_def);

	//sets the ground shape as a box , 
	SBox.SetAsBox(w, h);

	//creates a fixture between the body of the ground and it's shape ,basically stiches them toghether
	SBody->CreateFixture(&SBox, 0.0f);

	pos = SBody->GetPosition();

	std::cout << pos.x - w << ' ' << pos.y - h << '\n';
	std::cout << SRect.x << ' ' << SRect.y << '\n';
	std::cout << (SRect.x + SRect.w / 2) << ' ' << (SRect.y + SRect.h / 2) << '\n';

}
void Sprite::Destroy() {
	SDL_DestroyTexture(STexture);
}
