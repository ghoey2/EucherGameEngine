//
// Created by ghoey on 4/17/2021.
//

#ifndef FINAL_PROJECT_GHOEY2_CARD_H
#define FINAL_PROJECT_GHOEY2_CARD_H

#include <cinder/gl/Texture.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"


namespace euchre {
  enum class Suit {
      kSpade = 0,
      kHeart = 1,
      kClub = 2,
      kDiamond = 3,
      kNoSuit = 100,
  };
  enum class Value {
      k9,
      k10,
      kJ,
      kQ,
      kK,
      kA,
  };
  class Card {
    public:
        Suit GetSuit() const;
        Value GetValue() const;
        Suit GetLeftBauerSuit() const;
        friend bool operator==(Card card_1, Card card_2);
        Card &operator=(const Card &source);
        Card (Suit suit, Value value);
        Card ();
        Card(Suit suit, Value value, std::string vertical_texture, std::string horizontal_texture);
        cinder::gl::Texture2dRef GetVerticalTexture();
        cinder::gl::Texture2dRef GetHorizontalTexture();




  private:
      Suit suit_;
      Value value_;
      cinder::gl::Texture2dRef vertical_texture_;
      cinder::gl::Texture2dRef horizontal_texture_;
  };

}

#endif //FINAL_PROJECT_GHOEY2_CARD_H
