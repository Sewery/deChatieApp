
#include "LightEntity.h"

LightEntity::LightEntity(const std::string& textureFile, SDL_Renderer* ren, SDL_Rect texture,SDL_Rect collisionBox) : eRenderer(ren) {
	eTextures = new LightTexture(textureFile, texture, ren);
	eCollisionBox = new CollisionBox(collisionBox, collisionBox, texture.w, texture.h);
}
LightEntity::~LightEntity()
{
	eTextures->free();

}
