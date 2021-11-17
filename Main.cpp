#include "Game.h"
#include <iostream>

int main()
{
    ScoreList score_list("highscore.txt");
    score_list.loadFile();

    srand(static_cast<unsigned>(time(0)));

    Game game(&score_list);

    game.run();
    score_list.saveFile();
    return 0;
}