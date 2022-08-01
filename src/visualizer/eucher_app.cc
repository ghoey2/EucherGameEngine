#include <visualizer/euchre_app.h>
#include <players/human_player.h>


namespace euchre {
    EuchreApp::EuchreApp() {
        ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
    }

    void EuchreApp::draw() {
        ci::Color8u background_color(255, 246, 148);  // light yellow
        ci::gl::clear(background_color);
        DrawHands();
        if (game_.GetState() == GameState::kPickUpOrPass) {
            DrawDeck();
        }
        DrawTrump();
        DrawPointTotals();
        if (game_.GetState() == GameState::kRunningTricks) {
            DrawCurrentTrick();
        }
        if (game_.GetState() == GameState::kPickUpOrPass) {
            DrawPickItUpOrPass();
        }
        if (game_.GetState() == GameState::kCallTrump) {
            DrawSuits();
        }

    }

    void EuchreApp::update() {
        game_.Update();
    }

    void EuchreApp::mouseDown(ci::app::MouseEvent event) {
        cinder::vec2 position = event.getPos();
        switch (game_.GetState()) {
            case GameState::kPickUpOrPass :
                if (position.x >= 250 && position.x <= 750 && position.y >= 575 && position.y <= 725) {
                    game_.GetPlayer(0).strategy_->SetIsCallingPickItUp(IsPickItUpClicked(position));
                }
                return;
            case GameState::kCallTrump :
                if (position.y >= 700 && position.y <= 750 && position.x >= 200 && position.x <= 500) {
                    game_.GetPlayer(0).strategy_->SetTrumpCall(FindSuitClicked(position));
                }
                return;
            case GameState::kRunningTricks :
                if (position.y >= 769 && position.x >= 106 && position.x <= 675 )
                    game_.GetPlayer(0).strategy_->SetCardIndex(FindCardClicked(position));
                return;
        }

    }

    void EuchreApp::setup() {
        font_ = cinder::Font("helvetica", 40);

        vertical_back_ = cinder::gl::Texture::create(loadImage(loadAsset("purple_back.png")));
        horizontal_back_ = cinder::gl::Texture::create(loadImage( loadAsset("purple_back_h.png")));
        spade_ = cinder::gl::Texture::create(loadImage( loadAsset("Spade.png")));
        heart_ = cinder::gl::Texture::create(loadImage( loadAsset("Heart.png")));
        club_ = cinder::gl::Texture::create(loadImage( loadAsset("club.png")));
        diamond_ = cinder::gl::Texture::create(loadImage( loadAsset("diamond.png")));

        cards_with_textures_.push_back(Card(Suit::kClub, Value::k9,  "9C.png","9CH.png" ));
        cards_with_textures_.push_back(Card(Suit::kHeart, Value::k9,  "9H.png","9HH.png" ));
        cards_with_textures_.push_back(Card(Suit::kDiamond, Value::k9,  "9D.png","9DH.png" ));
        cards_with_textures_.push_back(Card(Suit::kSpade, Value::k9,  "9S.png","9SH.png" ));
        cards_with_textures_.push_back(Card(Suit::kClub, Value::k10,  "10C.png","10CH.png" ));
        cards_with_textures_.push_back(Card(Suit::kHeart, Value::k10,  "10H.png","10HH.png" ));
        cards_with_textures_.push_back(Card(Suit::kDiamond, Value::k10,  "10D.png","10DH.png" ));
        cards_with_textures_.push_back(Card(Suit::kSpade, Value::k10,  "10S.png","10SH.png" ));
        cards_with_textures_.push_back(Card(Suit::kClub, Value::kJ,  "JC.png","JCH.png" ));
        cards_with_textures_.push_back(Card(Suit::kHeart, Value::kJ,  "JH.png","JHH.png" ));
        cards_with_textures_.push_back(Card(Suit::kDiamond, Value::kJ,  "JD.png","JDH.png" ));
        cards_with_textures_.push_back(Card(Suit::kSpade, Value::kJ,  "JS.png","JSH.png" ));
        cards_with_textures_.push_back(Card(Suit::kClub, Value::kQ,  "QC.png","QCH.png" ));
        cards_with_textures_.push_back(Card(Suit::kHeart, Value::kQ,  "QH.png","QHH.png" ));
        cards_with_textures_.push_back(Card(Suit::kDiamond, Value::kQ,  "QD.png","QDH.png" ));
        cards_with_textures_.push_back(Card(Suit::kSpade, Value::kQ,  "QS.png","QSH.png" ));
        cards_with_textures_.push_back(Card(Suit::kClub, Value::kK,  "KC.png","KCH.png" ));
        cards_with_textures_.push_back(Card(Suit::kHeart, Value::kK,  "KH.png","KHH.png" ));
        cards_with_textures_.push_back(Card(Suit::kDiamond, Value::kK,  "KD.png","KDH.png" ));
        cards_with_textures_.push_back(Card(Suit::kSpade, Value::kK,  "KS.png","KSH.png" ));
        cards_with_textures_.push_back(Card(Suit::kClub, Value::kA,  "AC.png","ACH.png" ));
        cards_with_textures_.push_back(Card(Suit::kHeart, Value::kA,  "AH.png","AHH.png" ));
        cards_with_textures_.push_back(Card(Suit::kDiamond, Value::kA,  "AD.png","ADH.png" ));
        cards_with_textures_.push_back(Card(Suit::kSpade, Value::kA,  "AS.png","ASH.png" ));


    }

    void EuchreApp::DrawCard(Card card, cinder::vec2 top_right_corner, bool is_vertical) {
        size_t card_index = 0;
        for (size_t i = 0; i < cards_with_textures_.size(); ++i) {
            if (card == cards_with_textures_.at(i)) {
                card_index = i;
                break;
            }
        }

        if (is_vertical) {
            ci::Rectf card_size(top_right_corner, top_right_corner + cinder::vec2(kCardWidth, kCardHeight));
            cinder::gl::draw(cards_with_textures_[card_index].GetVerticalTexture(), card_size );
        } else {
            ci::Rectf card_size(top_right_corner, top_right_corner + cinder::vec2(kCardHeight,kCardWidth));
            cinder::gl::draw(cards_with_textures_[card_index].GetHorizontalTexture(), card_size );
        }

    }

    void EuchreApp::DrawCardBack(cinder::vec2 top_right_corner, bool is_vertical) {
        if (is_vertical) {
            ci::Rectf card_size(top_right_corner, top_right_corner + cinder::vec2(kCardWidth, kCardHeight));
            cinder::gl::draw(vertical_back_, card_size );
        } else {
            ci::Rectf card_size(top_right_corner, top_right_corner + cinder::vec2(kCardHeight,kCardWidth));
            cinder::gl::draw(horizontal_back_, card_size );
        }

    }

    void EuchreApp::DrawHands() {
        for (size_t player = 0; player < 4; ++player) {
            for(size_t card = 0; card < game_.GetPlayer(player).GetHand().size(); ++card) {
                if (player == 0) {
                    DrawCard(game_.GetPlayer(player).GetHand().at(card), cinder::vec2(106 + 100*card, kWindowSize - 106), true);
                }
                if (player == 1) {
                    DrawCardBack( cinder::vec2(kWindowSize - 106, kWindowSize - 106 - 69 - 100 * card), false);
                }
                if (player == 2) {
                    DrawCardBack(cinder::vec2(kWindowSize - 106 - 69 - 100*card, 0), true);
                }
                if (player == 3) {
                    DrawCardBack(cinder::vec2(0 , 106 + 100 * card), false);
                }
            }
        }

    }

    void EuchreApp::DrawDeck() {
        ci::Color8u font_color_(0,0,0);
        switch(game_.GetDealerPosition() % 4) {

            case 0:
                cinder::gl::drawStringRight("Deck", cinder::vec2(700, kWindowSize - 200), font_color_, font_);
                DrawCard(game_.GetTopCard(), cinder::vec2(700, (kWindowSize - 106)) , true);
                break;
            case 1:
                cinder::gl::drawStringRight("Deck", cinder::vec2(kWindowSize - 106, 100), font_color_, font_);
                DrawCard(game_.GetTopCard(), cinder::vec2(kWindowSize - 106, 200) , false);
                break;
            case 2:
                cinder::gl::drawStringRight("Deck", cinder::vec2(100, 200), font_color_, font_ );
                DrawCard(game_.GetTopCard(), cinder::vec2(100, 0) , true);
                break;
            case 3:
                cinder::gl::drawStringRight("Deck", cinder::vec2(0, 800), font_color_, font_);
                DrawCard(game_.GetTopCard(), cinder::vec2(0, 700) , false);
                break;
        }

    }

    void EuchreApp::DrawPointTotals() {
        ci::Color8u font_color(0,0,0);
        cinder::gl::drawString("team 1 points: " + std::to_string(game_.GetTeam1Points()), cinder::vec2(200,200), font_color, font_);
        cinder::gl::drawString("team 2 points: " + std::to_string(game_.GetTeam2Points()), cinder::vec2(200, 250), font_color, font_);
    }

    void EuchreApp::DrawCurrentTrick() {
        ci::Color8u font_color(0,0,0);
        if (game_.GetCurrentRound().GetTricks().empty()) {
            return;
        }
        for (size_t i = 0; i < game_.GetCurrentRound().GetTricks().at(0).GetPlayedCards().size(); ++i) {
            DrawCard(game_.GetCurrentRound().GetTricks().at(0).GetPlayedCards().at(i).card, cinder::vec2(200 + 100 * i, 300), true);
            cinder::gl::drawStringCentered(std::to_string(game_.GetCurrentRound().GetTricks().at(0).GetPlayedCards().at(i).player_id), cinder::vec2(230 + 100 * i, 425), font_color, font_);
        }
    }

    void EuchreApp::DrawTrump() {
        ci::Color8u font_color(0,0,0);
        switch (game_.GetCurrentRound().GetTrump()) {
            case Suit::kDiamond :
                cinder::gl::drawString("Trump is Diamond", cinder::vec2(500, 250), font_color, font_);
                return;
            case Suit::kHeart :
                cinder::gl::drawString("Trump is Heart", cinder::vec2(500, 250), font_color, font_);
                return;
            case Suit::kSpade :
                cinder::gl::drawString("Trump is Spade", cinder::vec2(500, 250), font_color, font_);
                return;
            case Suit::kClub :
                cinder::gl::drawString("Trump is Club", cinder::vec2(500, 250), font_color, font_);
                return;
            default :
                cinder::gl::drawString("Trump is not picked", cinder::vec2(500, 250), font_color, font_);

        }

    }

    void EuchreApp::DrawPickItUpOrPass() {
        ci::Color8u font_color(0,0,0);
        cinder::gl::drawString("Pick it up", cinder::vec2(250, 600), font_color, font_);
        cinder::gl::drawString("Pass", cinder::vec2(500, 600), font_color, font_);

    }

    void EuchreApp::DrawSuits() {

        ci::Rectf heart_size(cinder::vec2(200,700), cinder::vec2(250,750));
        cinder::gl::draw(heart_, heart_size );

        ci::Rectf club_size(cinder::vec2(250,700), cinder::vec2(300,750));
        cinder::gl::draw(club_, club_size );

        ci::Rectf spade_size(cinder::vec2(300,700), cinder::vec2(350,750));
        cinder::gl::draw(spade_, spade_size );

        ci::Rectf diamond_size(cinder::vec2(350,700), cinder::vec2(400,750));
        cinder::gl::draw(diamond_, diamond_size );

        ci::Color8u font_color(0,0,0);
        cinder::gl::drawString("None", cinder::vec2(400, 700), font_color, font_);


    }

    euchre::Suit EuchreApp::FindSuitClicked(cinder::vec2 position) {
        if (position.x >= 200 && position.x <= 250) {
            return Suit::kHeart;
        }
        if (position.x >= 250 && position.x <= 300) {
            return Suit::kClub;
        }
        if (position.x >= 300 && position.x <= 350) {
            return Suit::kSpade;
        }
        if (position.x >= 350 && position.x <= 400) {
            return Suit::kDiamond;
        }
        if (position.x >= 400 && position.x <= 500) {
            return Suit::kNoSuit;
        }
        return Suit::kNoSuit;
    }

    size_t EuchreApp::FindCardClicked(cinder::vec2 position) {

        if (position.x >= 106 && position.x <= 175) {
            return 0;
        }
        if (position.x >= 206 && position.x <= 275) {
            return 1;
        }
        if (position.x >= 306 && position.x <= 375) {
            return 2;
        }
        if (position.x >= 406 && position.x <= 475) {
            return 3;
        }
        if (position.x >= 506 && position.x <= 575) {
            return 4;
        }

        return 0;
    }

    bool EuchreApp::IsPickItUpClicked(cinder::vec2 position) {
        if (position.x >= 250 && position.x <= 500) {
            return true;
        }
        return false;
    }

}


