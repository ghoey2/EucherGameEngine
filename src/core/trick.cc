//
// Created by ghoey on 4/20/2021.
//

#include "core/trick.h"
namespace euchre {
    void Trick::AddCard(euchre::CardPlayAction played_card) {
        if (played_cards_.empty()) {
            lead_suit_ = played_card.card.GetSuit();
        }
        played_cards_.push_back(played_card);
    }

    Trick::Trick(Suit trump) : trump_(trump){ }

    size_t Trick::EvaluateTrick() {
       CardPlayAction best_action = {Card(Suit::kNoSuit, Value::k9), 0};

       for (size_t i = 0; i < played_cards_.size(); ++i) {
           if (EvaluateCard(best_action.card) < EvaluateCard(played_cards_.at(i).card)) {
               best_action = played_cards_.at(i);
           }
       }

       return best_action.player_id;
    }

    bool Trick::IsLeftBauer(Card card) {
        Suit left_suit = Suit::kNoSuit;
        switch (trump_) {
            case Suit::kDiamond :
                left_suit = Suit::kHeart;
                break;
            case Suit::kSpade :
                left_suit = Suit::kClub;
                break;
            case Suit::kHeart :
                left_suit = Suit::kDiamond;
                break;
            case Suit::kClub :
                left_suit = Suit::kSpade;
                break;
        }

        if (card.GetValue() == Value::kJ && card.GetSuit() == left_suit) {
            return true;
        } else {
            return false;
        }
    }

    size_t Trick::EvaluateCard(Card card) {
        if (IsLeftBauer(card)) {
            return 99;
        }
        if (card.GetSuit() == trump_ && card.GetValue() == Value::kJ) {
            return 100;
        }
        if (card.GetSuit() == lead_suit_) {
            return static_cast<size_t>(card.GetValue());
        }
        if (card.GetSuit() == trump_) {
            return 10 +  static_cast<size_t>(card.GetValue());
        }
        if (card.GetSuit() != trump_ || card.GetSuit() != lead_suit_) {
            return 0;
        }
        return 0;

    }

    std::vector<CardPlayAction> Trick::GetPlayedCards() {
        return played_cards_;
    }

    Suit Trick::GetLeadSuit() {
        return lead_suit_;
    }

}
