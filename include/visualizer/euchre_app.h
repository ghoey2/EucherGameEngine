#pragma once
#ifndef FINAL_PROJECT_GHOEY2_EUCHRE_APP_H
#define FINAL_PROJECT_GHOEY2_EUCHRE_APP_H

#include <core/card.h>
#include <core/game.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace euchre {

class EuchreApp : public ci::app::App {
  public:
     EuchreApp();

     void setup() override;
     void draw() override;
     void update() override;
     void mouseDown(ci::app::MouseEvent event) override;


     const double kWindowSize = 875;
     const double kMargin = 100;
     const size_t kImageDimension = 28;
     const size_t kCardWidth = 69;
     const size_t kCardHeight = 106;




  private:
    cinder::gl::Texture2dRef vertical_back_;
    cinder::gl::Texture2dRef horizontal_back_;
    std::vector<Card> cards_with_textures_;
    cinder::Font font_;

    cinder::gl::Texture2dRef spade_;
    cinder::gl::Texture2dRef heart_;
    cinder::gl::Texture2dRef club_;
    cinder::gl::Texture2dRef diamond_;

    Game game_;
    void DrawCard(Card card, cinder::vec2 top_right_corner, bool is_vertical);
    void DrawCardBack(cinder::vec2 top_right_corner, bool is_vertical);
    void DrawHands();
    void DrawDeck();
    void DrawPointTotals();
    void DrawCurrentTrick();
    void DrawTrump();

    size_t FindCardClicked(cinder::vec2 position);
    euchre::Suit FindSuitClicked(cinder::vec2 position);
    bool IsPickItUpClicked(cinder::vec2 position);

    void DrawPickItUpOrPass();
    void DrawSuits();

    };


} // namespace euchre
#endif //FINAL_PROJECT_GHOEY2_EUCHRE_APP_H
