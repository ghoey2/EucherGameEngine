//
// Created by ghoey on 4/20/2021.
//

#ifndef FINAL_PROJECT_GHOEY2_TRICK_H
#define FINAL_PROJECT_GHOEY2_TRICK_H
#include <vector>
#include <core/card_play_action.h>

namespace euchre {


class Trick {
  public:
    explicit Trick(Suit trump);
    void AddCard(CardPlayAction played_card);
    /**
     * looks at the cards played in the trick, determines who is winning, called by the game when all 4 cards have been added.
     * the round needs tis information to advance the starting player
     */
    size_t EvaluateTrick();
    std::vector<CardPlayAction> GetPlayedCards();
    Suit GetLeadSuit();


  private :
    std::vector<CardPlayAction> played_cards_;
    Suit trump_;
    Suit lead_suit_ = Suit::kNoSuit;
    bool IsLeftBauer(Card card);
    size_t EvaluateCard(Card card);

};

}


#endif //FINAL_PROJECT_GHOEY2_TRICK_H
