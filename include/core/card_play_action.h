#ifndef FINAL_PROJECT_GHOEY2_CARD_PLAY_ACTION_H
#define FINAL_PROJECT_GHOEY2_CARD_PLAY_ACTION_H

#include <core/card.h>

namespace euchre {
    struct CardPlayAction {
        Card card;
        size_t player_id;
    };
}

#endif //FINAL_PROJECT_GHOEY2_CARD_PLAY_ACTION_H
