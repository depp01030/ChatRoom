#include "game_screen.h"
#include "ui_game_screen.h"
#include <QPainter>



GameScreen::GameScreen(QWidget *parent, ServerUtils *server):
    QWidget(parent),
    ui(new Ui::GameScreen),
    m_gameCore(new GameCore()),
    m_server(server)
{
    m_gameCore->randomGenerateCardInfos();
    setupUI();  // 添加這行來調用setupUI()方法
}

GameScreen::~GameScreen()
{
    delete ui;
}


void GameScreen::setupUI() {   
    ui->setupUi(this);
    setupWordCards();

 
}
void GameScreen::setupWordCards() {
    size_t idx = 0;
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            CodeCard *card = new CodeCard(
                m_gameCore->m_cardInfos[idx],
                this
            );
            idx ++;
            ui->gridLayout_cards->addWidget(card, row, col);
            m_codeCards.push_back(card);
        }
    }
}