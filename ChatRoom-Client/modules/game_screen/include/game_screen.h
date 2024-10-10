#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <vector>
#include <unordered_map>
// #include "network_data_manager/include/network_data_manager.h"
#include "game_core/include/game_core.h"
#include "code_card.h"
#include "card_color.h"


namespace Ui {
    class GameScreen;
} 

class GameScreen : public QWidget {
    Q_OBJECT

public: 
    explicit GameScreen(QWidget *parent = nullptr);
    ~GameScreen();

private: 
    std::unordered_map<int, CodeCard*> m_codeCards; //id, card
    GameCore *m_gameCore;
    Ui::GameScreen *ui;
    void setupUI();
    void setupCodeCards();
    void setupConnections();
    void setRoundLabel(const GameCore::Team team);
private slots:
    
    void onCodeCardClicked(const CodeCard* codeCard);
    void onShowCardAnswer(const CardInfo& cardInfo);
    void onTurnNextRound(const GameCore::Team team);
    void onUpdateGameInfo();
};

#endif // GAME_SCREEN_H
