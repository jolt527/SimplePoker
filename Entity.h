#ifndef ENTITY_H_
#define ENTITY_H_

#include <SDL2/SDL.h>



/**
 * This is an interface that defines an entity that can render itself and
 * be updated using the change in time since the last update.
 */
class Entity {

public:

    virtual void update(Uint32 current_time_ms) = 0;

    virtual void render(SDL_Renderer* renderer_p) = 0;

};



#endif
