#include <players/computer_player.h>
#include "core/game.h"
#include <core/euchre_exception.h>
#include <players/human_player.h>

namespace euchre {

    Game::Game() {
        Strategy *human = new HumanStrategy();
        Strategy *computer = new ComputerRandomStrategy();
        Player player_1 = Player(human, true, 0);
        Player player_2 = Player(computer, false, 1);
        Player player_3 = Player(computer, true, 2);
        Player player_4 = Player(computer, false, 3);

        players_.push_back(player_1);
        players_.push_back(player_2);
        players_.push_back(player_3);
        players_.push_back(player_4);

        state_ = GameState::kDeal;

    }

    void Game::Deal(Deck &deck) {
        for (size_t i = 0; i < kNumberOfTricks; ++i) {
            for (size_t j = 0; j < kNumberOfPlayers; ++j) {
                Card top_card = deck.TakeTopCard();
                players_.at(j).AddCard(top_card);
            }
        }

    }

    void Game::Update() {
        switch (state_) {
            case GameState::kDeal :
                UpdateDeal();
                return;
            case GameState::kPickUpOrPass:
                UpdatePickUpOrPass();
                return;
            case GameState::kCallTrump :
                UpdateCallTrump();
                return;
            case GameState::kRunningTricks :
                UpdateRunTricks();
                return;

        }
    }


    Player Game::GetPlayer(size_t position) const {
        return players_.at(position);
    }


    size_t Game::GetDealerPosition() const {
        return dealer_position_;
    }

    Card Game::GetTopCard() const {
        return top_card_;
    }

    size_t Game::GetTeam1Points() const {
        return team_1_score;
    }

    GameState Game::GetState() const {
        return state_;
    }

    size_t Game::GetTeam2Points() const {
        return team_2_score;
    }

    Round Game::GetCurrentRound() const {
        return current_round_;
    }

    Card Game::GetLeftBauer() {
        Suit suit = Suit::kNoSuit;
        switch (current_round_.GetTrump()) {
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

    void Game::EvaluatePointsOfRound(Round &round) {
        size_t team_1_tricks = 0;
        size_t team_2_tricks = 0;

        for (size_t i = 0; i < kNumberOfTricks; ++i) {
            size_t trick_winner = round.GetTricks().at(i).EvaluateTrick();
            if (players_.at(trick_winner).GetIsTeamOne()) {
                ++team_1_tricks;
            } else {
                ++team_2_tricks;
            }
        }

        if (team_1_tricks == kNumberOfTricks) {
            team_1_score += 2;
            return;
        }
        if (team_2_tricks == kNumberOfTricks) {
            team_2_score += 2;
            return;
        }
        if (round.GetIsCalledByTeam1() && team_1_tricks > team_2_tricks) {
            ++team_1_score;
            return;
        }
        if (round.GetIsCalledByTeam1() && team_1_tricks < team_2_tricks) {
            team_2_score += 2;
            return;
        }
        if (!round.GetIsCalledByTeam1() && team_1_tricks > team_2_tricks) {
            team_1_score += 2;
            return;
        }
        if (!round.GetIsCalledByTeam1() && team_1_tricks < team_2_tricks) {
            ++team_2_score;
            return;
        }


    }


    bool Game::IsValidCardPlay(Suit lead_suit, CardPlayAction played_card) {
        Suit played_suit;
        if (played_card.card == GetLeftBauer()) {
            played_suit = current_round_.GetTrump();
        } else {
            played_suit = played_card.card.GetSuit();
        }

        if (lead_suit != played_suit) {
            for (size_t card = 0; card < players_.at(played_card.player_id).GetHand().size(); ++card) {
                if (players_.at(played_card.player_id).GetHand().at(card) ==
                    GetLeftBauer() &&
                    lead_suit == current_round_.GetTrump()) {
                    return false;
                }
                if (players_.at(played_card.player_id).GetHand().at(card).GetSuit() == lead_suit) {
                    return false;
                }
            }
        }
        return true;
    }

    void Game::UpdateDeal() {
        if (team_1_score >= kMaxScore) {
            state_ = GameState::kTeam1Win;
            return;
        }
        if (team_2_score >= kMaxScore) {
            state_ = GameState::kTeam2Win;
            return;
        }
        Deck deck;
        Deal(deck);
        top_card_ = deck.GetCards().back();
        state_ = GameState::kPickUpOrPass;
        current_player_ = dealer_position_ + 1;
        return;
    }

    void Game::UpdatePickUpOrPass() {
        if (players_.at(current_player_ % kNumberOfPlayers).strategy_->IsReady()) {
            if (players_.at(current_player_ % kNumberOfPlayers).OrderDealerUp(top_card_,
                                                                              dealer_position_ % kNumberOfPlayers)) {

                players_.at(dealer_position_ % kNumberOfPlayers).PickItUp(top_card_,
                                                                          current_player_ % kNumberOfPlayers);

                current_round_ = Round(top_card_.GetSuit(),
                                       players_.at(current_player_ % kNumberOfPlayers).GetIsTeamOne(),
                                       dealer_position_ % kNumberOfPlayers);

                state_ = GameState::kRunningTricks;
                current_player_ = (dealer_position_ + 1) % kNumberOfPlayers;
                return;
            }
            if (current_player_ % 4 == dealer_position_ % kNumberOfPlayers) {
                state_ = GameState::kCallTrump;
                current_player_ = (dealer_position_ + 1) % kNumberOfPlayers;

            } else {
                current_player_++;
            }
            return;
        }

    }

    void Game::UpdateCallTrump() {
        if (players_.at(current_player_ % kNumberOfPlayers).strategy_->IsReady()) {

            Suit called_suit = players_.at(current_player_ % 4).CallTrump(dealer_position_ % kNumberOfPlayers,
                                                                          top_card_.GetSuit());

            if (called_suit != Suit::kNoSuit && called_suit != top_card_.GetSuit()) {
                current_round_ = Round(called_suit, players_.at(current_player_ % kNumberOfPlayers).GetIsTeamOne(),
                                       dealer_position_ % kNumberOfPlayers);
                state_ = GameState::kRunningTricks;
                current_player_ = (dealer_position_ + 1) % kNumberOfPlayers;
                return;

            } else if (current_player_ % 4 == dealer_position_ % 4 || called_suit == top_card_.GetSuit()) {
                throw EuchreException((std::string &) "dealer must call a suit");
            }
            current_player_++;
            return;
        }

    }

    void Game::UpdateRunTricks() {
        if (current_round_.GetTricks().empty()) {
            current_round_.StartTrick();
        }
        if (current_round_.GetTricks().size() == kNumberOfTricks &&
            current_round_.GetTricks().at(0).GetPlayedCards().size() == kNumberOfPlayers
                ) {
            EvaluatePointsOfRound(current_round_);
            dealer_position_++;
            current_player_ = dealer_position_ % kNumberOfPlayers + 1;
            state_ = GameState::kDeal;
            return;
        }
        if (current_round_.GetTricks().at(0).GetPlayedCards().size() == kNumberOfPlayers) {
            current_round_.StartTrick();
            current_player_ = current_round_.GetTricks().at(0).EvaluateTrick();
            return;
        }

        if (players_.at(current_round_.GetCurrentPlayer() % kNumberOfPlayers).strategy_->IsReady()) {
            CardPlayAction play;
            play.player_id = current_round_.GetCurrentPlayer() % kNumberOfPlayers;

            play.card = players_.at(current_round_.GetCurrentPlayer() % kNumberOfPlayers).PlayCard(
                    current_round_.GetTricks().at(0).GetPlayedCards(), current_round_.GetTricks().at(0).GetLeadSuit(),
                    current_round_.GetTrump());

            if (IsValidCardPlay(current_round_.GetTricks().at(0).GetLeadSuit(), play)) {
                current_round_.AddCard(play);
            } else {
                throw EuchreException((std::string &) "you must follow suit");
            }
        }
    }
}