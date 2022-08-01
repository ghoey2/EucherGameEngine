//
// Created by ghoey on 5/5/2021.
//

#ifndef FINAL_PROJECT_GHOEY2_HUMAN_PLAYER_H
#define FINAL_PROJECT_GHOEY2_HUMAN_PLAYER_H

#include "strategy.h"

namespace euchre {
class HumanStrategy : public Strategy {
public :
    Suit CallTrump(std::vector<Card> hand, size_t dealer_position, size_t your_position, Suit turned_down_suit) override;

    size_t PlayCard(std::vector<CardPlayAction> played_cards, std::vector<Card> hand, Suit lead_suit, Suit trump) override;

    bool OrderDealerUp(Card top_card, std::vector<Card> your_hand, size_t dealer_position, size_t your_position) override;

    size_t PickUpCard(Card card, std::vector<Card> hand, size_t who_called_it) override;

    void SetIsReady(bool is_ready) override;

    bool IsReady() override;

    void SetCardIndex(size_t card) override;

    void SetTrumpCall(Suit trump_call) override;

    void SetIsCallingPickItUp(bool is_calling) override;



private :
    bool is_ready_ = false;
    size_t card_index_;
    Suit trump_call_;
    bool is_calling_pick_it_up_;

};

}

#endif //FINAL_PROJECT_GHOEY2_HUMAN_PLAYER_H
