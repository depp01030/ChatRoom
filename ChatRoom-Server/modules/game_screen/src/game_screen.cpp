#include "game_screen.h"
#include "ui_game_screen.h"
#include <QPainter>



GameScreen::GameScreen(QWidget *parent, GameController *gameController):
    QWidget(parent),
    ui(new Ui::GameScreen),
    m_gameController(gameController)
{
    setupUI();  // 添加這行來調用setupUI()方法
}

GameScreen::~GameScreen()
{
    delete ui;
    delete m_gameController;
}


void GameScreen::setupUI() {   
    ui->setupUi(this);
}
void GameScreen::setupCodeCards(const std::vector<CardInfo>& cardsInfo) {    
    for (const auto& cardInfo : cardsInfo){
        CodeCard *card = new CodeCard(
            cardInfo.m_id,
            cardInfo.m_word,
            this
        ); 
        size_t row = cardInfo.m_index / m_gameController->getRowNum();    
        size_t col = cardInfo.m_index % m_gameController->getColNum();
        ui->gridLayout_cards->addWidget(card, row, col);
        m_codeCards[cardInfo.m_id] = card;
    }
}
void GameScreen::setCurrentTurn(const GameCore::Team team) {
    if (team == GameCore::Team::Blue){
        this->ui->label_round->setStyleSheet("background-color: lightblue;");
        this->ui->label_round->setText("藍方回合");
    }
    else{
        this->ui->label_round->setStyleSheet("background-color: lightpink;");
        this->ui->label_round->setText("紅方回合");
    }
}
void GameScreen::setTeamScore(const GameCore::Team team, const int score) {
    QString round_msg = QString("%1隊分數 %2");
    if (GameCore::Team::Red == team){
        this->ui->label_redScore->setText(round_msg.arg("紅").arg(score) );
    }
    else if (GameCore::Team::Blue == team){
        this->ui->label_blueScore->setText(round_msg.arg("藍").arg(score) );
    }

    
}
void GameScreen::setupConnections() { 
    // set up the connection between the card and the game screen
    for (auto &pair : m_codeCards){ 
        disconnect(pair.second, &CodeCard::clicked, this, nullptr); // Disconnect any existing connections
        connect(pair.second, &CodeCard::clicked, this, [this, pair](){
            this->onCodeCardClicked(pair.second);
        }); 
    }
}
void GameScreen::onCodeCardClicked(const CodeCard* codeCard) {
    qDebug() << "Card clicked:" << codeCard->m_word;
    m_gameController->onCodeCardClicked(codeCard->m_id);   

}

void GameScreen::showCardAnswer(const CardInfo& cardInfo) {
    if (m_codeCards.find(cardInfo.m_id) == m_codeCards.end()){
        qDebug() << "Card not found";
        return;
    }
    CodeCard *card = m_codeCards[cardInfo.m_id];
    card->turnOpen(cardInfo.m_answerColor);
    qDebug() << "Card answer:" << std::to_string(cardInfo.m_isAnswer);
}



