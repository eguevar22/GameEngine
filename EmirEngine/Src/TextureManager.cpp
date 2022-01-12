#include "TextureManager.h"
#include "collision.h"
#include "Game.h"
#include "../ECS/ECS.h"

extern Entity& werewolf;



SDL_Texture * TextureManager::LoadTexture(const char * fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

	SDL_FreeSurface(tempSurface);
	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip Rflip)
{


	SDL_RenderCopyEx(Game::renderer, tex, &src, &dst, 0, 0, Rflip);


}
