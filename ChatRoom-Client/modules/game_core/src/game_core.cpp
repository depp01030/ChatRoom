#include "game_core.h"
#include <algorithm>
#include <random>
#include <functional>

CardInfo::CardInfo(const QString& word, bool is_answer):
m_word(word), m_isAnswer(is_answer), m_state(CardState::Close) 
{
    m_cardType = m_isAnswer ? CardType::GreenSpy : CardType::People;

}

GameCore::GameCore(QObject *parent): QObject(parent) {
}

GameCore::~GameCore() {

} 
std::vector<CardInfo> GameCore::randomGenerateCardInfos() {
    std::vector<size_t> indices(CANDIDATE_WORDS.size()); //生成一個vector indices with length CANDIDATE_WORDS.size()
    std::iota(indices.begin(), indices.end(), 0); //將indices填入0到CANDIDATE_WORDS.size()的數字
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g); //將indices的數字打亂
    std::vector<CardInfo> cardInfos;
    
    for (size_t i = 0; i < m_totalCardNum; ++i) {
        cardInfos.emplace_back(CANDIDATE_WORDS[indices[i]], i < 8);
    }
    std::shuffle(cardInfos.begin(), cardInfos.end(), g);
    size_t index = 0;
    for (CardInfo &cardInfo : cardInfos){
        cardInfo.m_id = index;
        cardInfo.m_index = index;
        index ++;
    }
    return cardInfos;
} 

void GameCore::initGame() {
    m_currentTurn = Team::Blue;   
    setCardInfos();
}
void GameCore::setCardInfos()
{
    m_cardInfos = randomGenerateCardInfos();
}
 
void GameCore::onCodeCardClicked(const int id) {
    processPlayerCardSelection(m_cardInfos[id]); 
}
void GameCore::processPlayerCardSelection(CardInfo& cardInfo) {
    if (cardInfo.m_state == CardState::Open) {
        qDebug() << "Card already open";
        return;
    }
    cardInfo.m_state = CardState::Open;
    // postCardSelectionToServer(cardInfo);
    emit showCardAnswer(cardInfo); 
    bool is_answer = checkIsCardAnswer(cardInfo);
    if (!is_answer) {
        switchTurn();
    }  
    else{
        m_currentTurn == Team::Blue ? m_blueScore++ : m_redScore++;
        emit updateGameInfo();
    }
}
void GameCore::switchTurn() {
    m_currentTurn = (m_currentTurn == Team::Blue) ? Team::Red : Team::Blue;
    emit turnNextRound(m_currentTurn);
    std::cout << "Turn switched to: " << (m_currentTurn == Team::Blue ? "Blue" : "Red") << std::endl;
}

bool GameCore::checkIsCardAnswer(const CardInfo& cardInfo) const {
    if (cardInfo.m_isAnswer) {
        return true;
    }
    // for (const auto& card : m_cardInfos){
    //     if (card.m_word == cardInfo.m_word){
    //         return true;
    //     }
    // }
    return false;
}

    