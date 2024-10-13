#include "game_controller.h"
#include <algorithm>
#include <random>
#include <functional>

 
GameController::GameController(QObject *parent, NetworkDataManager *server): 
QObject(parent),
m_server(server), m_gameCore(new GameCore(this)),
m_gameScreen(new GameScreen(nullptr, this))
{
    initGame();
    setupConnections();
}

GameController::~GameController() {
    delete m_gameCore;
    delete m_gameScreen;
} 

void GameController::initGame() {
    // 
    m_gameCore->initGame();
    std::vector<CardInfo> cardsInfo = m_gameCore->getCardsInfo();
    m_gameScreen->setupCodeCards(cardsInfo);
    //setup connections.
    setupConnections();
    // set score 
    m_gameCore->setTeamScore(GameCore::Team::Red, 0); 
    m_gameCore->setTeamScore(GameCore::Team::Blue, 0);
    
    // set current team 
    m_gameScreen->setCurrentTurn(
        m_gameCore->getCurrentTurn()
        );
    
} 

void GameController::setupConnections() {
    //card 點擊
    //直接方法調用 : this->onCodeCardClicked(codeCard->m_id);
    m_gameScreen->setupConnections(); //card clicked connection
    //翻牌
    connect(m_gameCore, &GameCore::cardOpened, this, &GameController::onCardOpened);
    
    //換回合
    connect(m_gameCore, &GameCore::turnSwitched, this, &GameController::onTurnSwitched);
    //更新分數
    connect(m_gameCore, &GameCore::teamScoreUpdated, this, &GameController::onTeamScoreUpdated);


    // connect(m_gameController, &GameController::showCardAnswer, this, &GameScreen::onShowCardAnswer);
    // connect(m_gameController, &GameController::turnNextRound, this, &GameScreen::onTurnNextRound);
    // connect(m_gameController, &GameController::updateGameInfo, this, &GameScreen::onUpdateGameInfo);
}
 

 
void GameController::onCodeCardClicked(const int id) {
    //get cardinfo by id
    CardInfo &cardInfo = m_gameCore->m_cardsInfo[id];
    if (cardInfo.m_state == CardState::Open) {
        qDebug() << "Card already open";
        return;
    }
    m_gameCore->openCard(cardInfo);  
    if (!m_gameCore->checkIsCardAnswer(cardInfo)){
        m_gameCore->switchTurn();
    }  
    else{
        m_gameCore->addTeamScore(m_gameCore->getCurrentTurn(), 1);
         
    } 
   
}
void GameController::onCardOpened(const CardInfo &cardInfo) {
    m_gameScreen->showCardAnswer(cardInfo);
}

void GameController::onTurnSwitched(const GameCore::Team team) {
    m_gameScreen->setCurrentTurn(team);
}

void GameController::onTeamScoreUpdated(const GameCore::Team team, const int score) {
    m_gameScreen->setTeamScore(team, score);

 
    
}
