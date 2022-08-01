//
// Created by ghoey on 4/18/2021.
//

#ifndef FINAL_PROJECT_GHOEY2_GAME_H
#define FINAL_PROJECT_GHOEY2_GAME_H

#include <players/strategy.h>
#include <players/player.h>
#include "round.h"
#include "game_state.h"

namespace euchre {
    class Game {
    public :
        Game();

        void Deal(Deck &deck);

        void Update();

        size_t GetDealerPosition() const;

        Card GetTopCard() const;

        Player GetPlayer(size_t position) const;

        GameState GetState() const;

        size_t GetTeam1Points() const;

        size_t GetTeam2Points() const;

        Round GetCurrentRound() const;


        const size_t kNumberOfTricks = 5;
        const size_t kMaxScore = 10;
        const size_t kNumberOfPlayers = 4;


    private :

        std::vector<Player> players_;
        size_t team_1_score = 0;
        size_t team_2_score = 0;
        size_t dealer_position_ = 1;

        Round current_round_;
        GameState state_;
        size_t current_player_;
        Card top_card_;


        bool IsValidCardPlay(Suit lead_suit, CardPlayAction played_card);

        void EvaluatePointsOfRound(Round &round);

        void UpdateDeal();

        void UpdatePickUpOrPass();

        void UpdateCallTrump();

        void UpdateRunTricks();

        Card GetLeftBauer();


    };
}


#endif //FINAL_PROJECT_GHOEY2_GAME_H
