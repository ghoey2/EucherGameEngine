//
// Created by ghoey on 4/20/2021.
//

#ifndef FINAL_PROJECT_GHOEY2_ROUND_H
#define FINAL_PROJECT_GHOEY2_ROUND_H

#include "card.h"
#include "deck.h"
#include "trick.h"

namespace euchre {
class Round {
  public :
    explicit Round(Suit Trump, bool is_trump_called_by_team_1, size_t dealer_position);
    Suit GetTrump() const;
    Round();

    void StartTrick();

    void AddCard(CardPlayAction play);

    bool GetIsCalledByTeam1() const;

    size_t GetCurrentPlayer();


    size_t GetStartingPlayer();
    std::vector<Trick> GetTricks() const;


private :
    size_t starting_player_;
    Suit trump_;
    size_t current_player_;
    bool is_called_by_team_1;
    std::vector<Trick> tricks_;
};

}


#endif //FINAL_PROJECT_GHOEY2_ROUND_H
