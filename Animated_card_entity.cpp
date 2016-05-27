#include "Animated_card_entity.h"
#include "Card.h"



const int CARD_WIDTH = 100;
const int CARD_HEIGHT = 140;

const int DEFAULT_SCREEN_WIDTH = 640;
const int DEFAULT_SCREEN_HEIGHT = 480;



Animated_card_entity::Animated_card_entity(Card* card_p, int target_card_pos, SDL_Texture* back_texture_p, SDL_Texture* front_texture_p) {
    m_card_p = card_p;

    m_back_texture_p = back_texture_p;
    m_front_texture_p = front_texture_p;

    m_target_card_pos = target_card_pos;

    m_state = With_dealer;

    m_current_state_start_time = SDL_GetTicks();

    m_rotation_degrees = 180.0;

    int card_image_x = CARD_WIDTH * m_card_p->get_number();
    int card_image_y = CARD_HEIGHT * m_card_p->get_suit();
    m_src_rect.x = card_image_x;
    m_src_rect.y = card_image_y;
    m_src_rect.w = CARD_WIDTH;
    m_src_rect.h = CARD_HEIGHT;

    // centered offscreen, just above top of screen
    m_dst_rect.x = (DEFAULT_SCREEN_WIDTH - CARD_WIDTH) / 2;
    m_dst_rect.y = -CARD_HEIGHT - 10;
    m_dst_rect.w = CARD_WIDTH;
    m_dst_rect.h = CARD_HEIGHT;

    m_showing_back_of_card = true;
}

Animated_card_entity::~Animated_card_entity() {
    // do nothing
}

// updates the state of the card
void Animated_card_entity::update(Uint32 current_time_ms) {

    const static int SPACE_BETWEEN_CARDS = (DEFAULT_SCREEN_WIDTH - CARD_WIDTH * 5) / 6;

    const static Uint32 MOVING_TO_PLAYER_TIMEFRAME_MS = 500;

    if (With_dealer == m_state) {
        m_state = Moving_to_player;

        m_current_state_start_time = current_time_ms;
        m_current_state_target_time = current_time_ms + MOVING_TO_PLAYER_TIMEFRAME_MS;

        m_showing_back_of_card = true;

        m_current_state_start_rotation_degrees = 180.0;
        m_current_state_target_rotation_degrees = 0.0;
        m_current_state_start_position.x = (DEFAULT_SCREEN_WIDTH - CARD_WIDTH) / 2;
        m_current_state_start_position.y = -CARD_HEIGHT - 10;
        m_current_state_target_position.x = SPACE_BETWEEN_CARDS + (CARD_WIDTH + SPACE_BETWEEN_CARDS) * m_target_card_pos;
        m_current_state_target_position.y = (DEFAULT_SCREEN_HEIGHT - CARD_HEIGHT) / 2;
    }
    else if (Moving_to_player == m_state) {
        if (current_time_ms >= m_current_state_target_time) {
            m_state = On_table_face_down;

            m_rotation_degrees = m_current_state_target_rotation_degrees;
            m_dst_rect.x = m_current_state_target_position.x;
            m_dst_rect.y = m_current_state_target_position.y;
        }
        else {
            double time_ratio = (double)(current_time_ms - m_current_state_start_time) / (double)MOVING_TO_PLAYER_TIMEFRAME_MS;
            m_rotation_degrees = m_current_state_start_rotation_degrees + (m_current_state_target_rotation_degrees - m_current_state_start_rotation_degrees) * time_ratio;
            m_dst_rect.x = m_current_state_start_position.x + (m_current_state_target_position.x - m_current_state_start_position.x) * time_ratio;
            m_dst_rect.y = m_current_state_start_position.y + (m_current_state_target_position.y - m_current_state_start_position.y) * time_ratio;
        }
    }
    else if (On_table_face_down == m_state) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (m_dst_rect.x < x && x < m_dst_rect.x + CARD_WIDTH && m_dst_rect.y < y && y < m_dst_rect.y + CARD_HEIGHT) {
            m_showing_back_of_card = false;
        }
        else {
            m_showing_back_of_card = true;
        }
    }
}

// renders the card
void Animated_card_entity::render(SDL_Renderer* renderer_p) {

    SDL_Rect rect_to_render = m_src_rect;
    SDL_Texture* texture_to_render_p = m_front_texture_p;
    if (m_showing_back_of_card) {
        rect_to_render.x = 0;
        rect_to_render.y = 0;
        rect_to_render.w = CARD_WIDTH;
        rect_to_render.h = CARD_HEIGHT;
        texture_to_render_p = m_back_texture_p;
    }

    SDL_RenderCopyEx(renderer_p, texture_to_render_p, &rect_to_render, &m_dst_rect, m_rotation_degrees, NULL, SDL_FLIP_NONE);
}
