#include "game_screen.h"
#include "ui_game_screen.h"
#include <QPainter>



GameScreen::GameScreen(QWidget *parent):
    QWidget(parent),
    ui(new Ui::GameScreen),
    m_gameCore(new GameCore(this))
{
    m_gameCore->initGame();
    

    setupUI();  // 添加這行來調用setupUI()方法
}

GameScreen::~GameScreen()
{
    delete ui;
    delete m_gameCore;
}


void GameScreen::setupUI() {   
    ui->setupUi(this);
    setRoundLabel(m_gameCore->getCurrentTurn());
    setupCodeCards();
    setupConnections();
    onUpdateGameInfo();
 
}
void GameScreen::setupCodeCards() {
    
    for (const auto& cardInfo : m_gameCore->m_cardInfos){
        CodeCard *card = new CodeCard(
            cardInfo.m_id,
            cardInfo.m_word,
            this
        );
        card->setAnswerColor(cardInfo.m_cardType);
        size_t row = cardInfo.m_index / m_gameCore->m_colNum;    
        size_t col = cardInfo.m_index % m_gameCore->m_colNum;
        ui->gridLayout_cards->addWidget(card, row, col);
        m_codeCards[cardInfo.m_id] = card;
    }
}
void GameScreen::setupConnections() {
    connect(m_gameCore, &GameCore::showCardAnswer, this, &GameScreen::onShowCardAnswer);
    connect(m_gameCore, &GameCore::turnNextRound, this, &GameScreen::onTurnNextRound);
    connect(m_gameCore, &GameCore::updateGameInfo, this, &GameScreen::onUpdateGameInfo);
    // set up the connection between the card and the game screen
    for (auto &pair : m_codeCards){ 
        connect(pair.second, &CodeCard::clicked, this, [this, pair](){
            this->onCodeCardClicked(pair.second);
        });
    }
}
void GameScreen::onCodeCardClicked(const CodeCard* codeCard) {
    qDebug() << "Card clicked:" << codeCard->m_word;
    m_gameCore->onCodeCardClicked(codeCard->m_id);   

}

void GameScreen::onShowCardAnswer(const CardInfo& cardInfo) {
    if (m_codeCards.find(cardInfo.m_id) == m_codeCards.end()){
        qDebug() << "Card not found";
        return;
    }
    m_codeCards[cardInfo.m_id]->showAnswer();
    qDebug() << "Card answer:" << std::to_string(cardInfo.m_isAnswer);
}

void GameScreen::onTurnNextRound(const GameCore::Team team) {
    setRoundLabel(team);
    
    qDebug() << "Turn next round";
}
void GameScreen::setRoundLabel(const GameCore::Team team) {
    if (team == GameCore::Team::Blue){
        this->ui->label_round->setStyleSheet("background-color: lightblue;");
        this->ui->label_round->setText("藍方回合");
    }
    else{
        this->ui->label_round->setStyleSheet("background-color: lightpink;");
        this->ui->label_round->setText("紅方回合");
    }
}
void GameScreen::onUpdateGameInfo() {
    QString round_msg = QString("紅隊分數 %1    藍隊分數 %2").arg(m_gameCore->m_redScore).arg(m_gameCore->m_blueScore   );
    this->ui->label_round_info->setText(round_msg);
}
