#pragma once

#ifndef FINAL_PROJECT_GHOEY2_COMPUTER_PLAYER_H
#define FINAL_PROJECT_GHOEY2_COMPUTER_PLAYER_H

#include <core/card.h>
#include "strategy.h"

namespace euchre {
class ComputerRandomStrategy : public Strategy {
  public :
    explicit ComputerRandomStrategy();
    Suit CallTrump(std::vector<Card> hand, size_t dealer_position, size_t your_position, Suit turned_down_suit) override;
    size_t
    PlayCard(std::vector<CardPlayAction> played_cards, std::vector<Card> hand, Suit lead_suit, Suit trump) override;
    size_t PickUpCard(Card card, std::vector<Card> hand, size_t who_called_it) override;
    bool OrderDealerUp(Card top_card, std::vector<Card> your_hand, size_t dealer_position, size_t your_position) override;

    bool IsReady() override;
    void SetIsReady(bool is_ready) override;

    void SetCardIndex(size_t card) override;

    void SetTrumpCall(Suit trump_call) override;

    void SetIsCallingPickItUp(bool is_calling) override;

  private:
    bool is_ready_ = true;
    Card GetLeftBauer(Suit trump);
};

}

#endif //FINAL_PROJECT_GHOEY2_COMPUTER_PLAYER_H
