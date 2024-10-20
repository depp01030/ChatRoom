#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <vector>
#include <unordered_map>
// #include "network_data_manager/include/network_data_manager.h"
#include "game_controller/include/game_controller.h" 
#include "code_card.h" 


namespace Ui {
    class GameScreen;
} 
class GameController; // 前向聲明
class GameScreen : public QWidget {
    Q_OBJECT

public: 
    explicit GameScreen(QWidget *parent = nullptr, GameController *gameController = nullptr);
    ~GameScreen();

private: 
    friend class GameController;
    std::unordered_map<int, CodeCard*> m_codeCards; //id, card
    GameController *m_gameController;
    Ui::GameScreen *ui;
    void setupUI();
    void setupCodeCards(const std::vector<CardInfo>& cardsInfo);
    void setCurrentTurn(const GameCore::Team team);
    void setTeamScore(const GameCore::Team team, const int score);
    void showCardAnswer(const CardInfo& cardInfo);
    void setupConnections(); 
private slots:
    
    void onCodeCardClicked(const CodeCard* codeCard); 
};

#endif // GAME_SCREEN_H
