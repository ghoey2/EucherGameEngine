#include "players/computer_player.h"

namespace euchre {
    Suit ComputerRandomStrategy::CallTrump(std::vector<Card> hand, size_t dealer_position, size_t your_position,
                                           Suit turned_down_suit) {

        if (dealer_position == your_position && turned_down_suit != Suit::kSpade) {
            return Suit::kSpade;
        }
        if (dealer_position == your_position) {
            return Suit::kDiamond;
        }
        return Suit::kNoSuit;
    }
    size_t ComputerRandomStrategy::PickUpCard(Card card, std::vector<Card> hand, size_t who_called_it) {
        return 0;
    }

    size_t
    ComputerRandomStrategy::PlayCard(std::vector<CardPlayAction> played_cards, std::vector<Card> hand, Suit lead_suit,
                                     Suit trump) {
        Card left = GetLeftBauer(trump);
        size_t card_index = 0;
        for (size_t i = 0; i < hand.size(); ++i) {
            if (lead_suit == trump && hand.at(i) == left) {
                card_index = i;
                break;
            }
            if (lead_suit == left.GetSuit() && hand.at(i) == left) {
                continue;
            }
            if (hand.at(i).GetSuit() == lead_suit) {
                card_index = i;
                break;
            }
        }

        return card_index;
    }

    ComputerRandomStrategy::ComputerRandomStrategy() {

    }

    bool ComputerRandomStrategy::OrderDealerUp(Card top_card, std::vector<Card> your_hand, size_t dealer_position, size_t your_position) {
        return false;
    }

    Card ComputerRandomStrategy::GetLeftBauer(Suit trump) {
        Suit suit = Suit::kNoSuit;
        switch(trump) {
            case Suit::kSpade:
                suit = Suit::kClub;
                break;
            case Suit::kClub:
                suit = Suit::kSpade;
                break;
            case Suit::kDiamond:
                suit = Suit::kHeart;
                break;
            case Suit::kHeart:
                suit = Suit::kDiamond;
                break;
        }
        return Card(suit, Value::kJ);
    }

    void ComputerRandomStrategy::SetIsReady(bool is_ready) {
        is_ready_ = is_ready;

    }

    bool ComputerRandomStrategy::IsReady() {
        return true;
    }

    void ComputerRandomStrategy::SetCardIndex(size_t card) {
        return;
    }
    void ComputerRandomStrategy::SetTrumpCall(Suit trump_call) {
        return;
    }
    void ComputerRandomStrategy::SetIsCallingPickItUp(bool is_calling) {
        return;
    }
}


