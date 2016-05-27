#ifndef ANIMATED_CARD_ENTITY_H_
#define ANIMATED_CARD_ENTITY_H_

#include "Entity.h"
#include <SDL2/SDL.h>

class Card;



enum Card_animation_state { With_dealer, Moving_to_player, On_table_face_down };



class Animated_card_entity : public Entity {

public:

    Animated_card_entity(Card* card_p, int target_card_pos, SDL_Texture* back_texture_p, SDL_Texture* front_texture_p);
    ~Animated_card_entity();

    void update(Uint32 current_time_ms);

    void render(SDL_Renderer* renderer_p);

private:

    Card* m_card_p;

    int m_x_pos;
    int m_y_pos;

    int m_target_card_pos;

    SDL_Texture* m_back_texture_p;
    SDL_Texture* m_front_texture_p;

    SDL_Rect m_src_rect;
    SDL_Rect m_dst_rect;

    double m_rotation_degrees;

    Card_animation_state m_state;

    bool m_showing_back_of_card;

    Uint32 m_current_state_start_time;
    Uint32 m_current_state_target_time;
    double m_current_state_start_rotation_degrees;
    double m_current_state_target_rotation_degrees;
    SDL_Rect m_current_state_start_position;
    SDL_Rect m_current_state_target_position;
};



#endif
