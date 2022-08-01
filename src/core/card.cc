//
// Created by ghoey on 4/17/2021.
//
#include "core/card.h"

namespace euchre {

    Card::Card(Suit suit, Value value) : suit_(suit), value_(value) {

    }

    Suit Card::GetSuit() const {
        return suit_;
    }

    Value Card::GetValue() const {
        return value_;
    }

    bool operator==(Card card_1, Card card_2) {
        return (card_1.GetSuit() == card_2.GetSuit() && card_1.GetValue() == card_2.GetValue());
    }

    Suit Card::GetLeftBauerSuit() const {
        switch (suit_) {
            case Suit::kDiamond :
                return Suit::kHeart;
            case Suit::kSpade :
                return Suit::kClub;
            case Suit::kHeart :
                return Suit::kDiamond;
            case Suit::kClub :
                return Suit::kSpade;
            default :
                return Suit::kNoSuit;
        }
    }

    Card &Card::operator=(const Card &source) {
        this->suit_ = source.suit_;
        this->value_ = source.value_;
        this->vertical_texture_ = source.vertical_texture_;
        return *this;
    }

    Card::Card() {
        this->suit_ = Suit::kNoSuit;
        this->value_ = Value::k9;
    }

    Card::Card(Suit suit, Value value, std::string vertical_texture,
               std::string horizontal_texture) : suit_(suit), value_(value) {
        this->vertical_texture_ = cinder::gl::Texture::create(loadImage(cinder::app::loadAsset(vertical_texture)));
        this->horizontal_texture_ = cinder::gl::Texture::create(loadImage(cinder::app::loadAsset(horizontal_texture)));


    }

    cinder::gl::Texture2dRef Card::GetVerticalTexture() {
        return vertical_texture_;
    }

    cinder::gl::Texture2dRef Card::GetHorizontalTexture() {
        return horizontal_texture_;
    }

}

