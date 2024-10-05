#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <vector>
#include "server_utils/include/server_utils.h"
#include "game_core/include/game_core.h"
#include "code_card.h"
namespace Ui {
    class GameScreen;
}

class GameScreen : public QWidget {
    Q_OBJECT

public: 
    explicit GameScreen(QWidget *parent = nullptr, ServerUtils *server = nullptr);
    ~GameScreen();

private: 

    std::vector<CodeCard*> m_codeCards;
    ServerUtils *m_server;
    GameCore *m_gameCore;
    Ui::GameScreen *ui;
    void setupUI();
    void setupWordCards();
};



#endif // GAME_SCREEN_H
