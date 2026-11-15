#include <catch2/catch_test_macros.hpp>
#include "Player.h"

TEST_CASE("Player manages lives, game-over state") {
    SECTION("New player starts with 3 lives, 0 score, level 1, and active game state") {
        Player player;

        CHECK(player.getLives() == 3);
        CHECK(player.getScore() == 0);
        CHECK(player.getLevel() == 1);
        CHECK_FALSE(player.gameOver());
    }

    SECTION("Player triggers game over only when all lives are lost") {
        Player player(2);

        player.loseLife();
        CHECK_FALSE(player.gameOver());

        player.loseLife();
        CHECK(player.gameOver());
    }

    SECTION("Player lives clamp at zero after losing more lives than available") {
        Player player(1);

        player.loseLife();
        player.loseLife();

        CHECK(player.getLives() == 0);
    }
}