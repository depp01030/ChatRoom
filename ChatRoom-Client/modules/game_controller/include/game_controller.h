#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H
#include <iostream>
#include <vector>
#include <QColor>
#include <QObject>
#include <QDebug>
 
#include "game_core/include/game_core.h"
#include "game_screen/include/game_screen.h"
#include "network_data_manager/include/network_data_manager.h"
 
 
class GameScreen;
class GameController : public QObject {
    Q_OBJECT  // 添加這行

public: 
    GameController(QObject *parent = nullptr, NetworkDataManager *server = nullptr);
    ~GameController();
    int getRowNum() const { return m_gameCore->m_rowNum; }
    int getColNum() const { return m_gameCore->m_colNum; }

    void initGame(); 
     
 

private:
    friend class MainWindow;
    friend class GameScreen;
    GameScreen *m_gameScreen;
    GameCore *m_gameCore;
    NetworkDataManager *m_server;
    void setupConnections();
private slots:
    void onCodeCardClicked(const int id);
    void onCardOpened(const CardInfo& cardInfo);
    void onTurnSwitched(const GameCore::Team team);
    void onTeamScoreUpdated(const GameCore::Team team, const int score);
};

#endif // GAME_CORE_H
















