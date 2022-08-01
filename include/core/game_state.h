//
// Created by ghoey on 5/3/2021.
//

#ifndef FINAL_PROJECT_GHOEY2_GAME_STATE_H
#define FINAL_PROJECT_GHOEY2_GAME_STATE_H

namespace euchre {
    enum class GameState {
        kDeal,
        kPickUpOrPass,
        kCallTrump,
        kStartRound,
        kRunningTricks,
        kTeam1Win,
        kTeam2Win,
    };
}

#endif //FINAL_PROJECT_GHOEY2_GAME_STATE_H
