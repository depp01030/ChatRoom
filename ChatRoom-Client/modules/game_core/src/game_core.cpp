#include "game_core.h"
#include <algorithm>
#include <random>
#include <functional>

CardInfo::CardInfo(const QString& word, bool is_answer):
m_word(word), m_isAnswer(is_answer), m_state(CardState::Close) 
{
    m_cardType = m_isAnswer ? CardType::GreenSpy : CardType::People;
    m_answerColor = getCardColor(m_cardType);

}

GameCore::GameCore(QObject *parent): QObject(parent) {
}

GameCore::~GameCore() {

} 
void GameCore::initGame() {
    m_currentTurn = Team::Blue;   
    setCardsInfo();
}
void GameCore::setCardsInfo()
{
    m_cardsInfo = randomGenerateCardInfos();
}
std::vector<CardInfo> GameCore::randomGenerateCardInfos() {
    std::vector<size_t> indices(CANDIDATE_WORDS.size()); //生成一個vector indices with length CANDIDATE_WORDS.size()
    std::iota(indices.begin(), indices.end(), 0); //將indices填入0到CANDIDATE_WORDS.size()的數字
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g); //將indices的數字打亂
    std::vector<CardInfo> cardsInfo;
    
    for (size_t i = 0; i < m_totalCardNum; ++i) {
        cardsInfo.emplace_back(CANDIDATE_WORDS[indices[i]], i < m_answerCardNum);
    }
    std::shuffle(cardsInfo.begin(), cardsInfo.end(), g);
    size_t index = 0;
    for (CardInfo &cardInfo : cardsInfo){
        cardInfo.m_id = index;
        cardInfo.m_index = index;
        index ++;
    }
    return cardsInfo;
} 



void GameCore::openCard(CardInfo& cardInfo) {
    if (cardInfo.m_state == CardState::Open) {
        qDebug() << "GameCore : Card already open";
        return;
    }
    cardInfo.m_state = CardState::Open;
    emit cardOpened(cardInfo);
}
 
void GameCore::switchTurn() {
    m_currentTurn = (m_currentTurn == Team::Blue) ? Team::Red : Team::Blue;
    emit turnSwitched(m_currentTurn);
    std::cout << "Turn switched to: " << (m_currentTurn == Team::Blue ? "Blue" : "Red") << std::endl;
}
int GameCore::getTeamScore(Team team) const {
    if (team == Team::Blue) {
        return m_blueScore;
    }
    else if (team == Team::Red){    
        return m_redScore;
    }
    else{
        qDebug() << "Invalid team";
        return 0;
    }
}
void GameCore::addTeamScore(GameCore::Team team, int score){
    int teamScore = getTeamScore(team);
    int newScore = teamScore + score;
    setTeamScore(team, newScore);
}
void GameCore::setTeamScore(GameCore::Team team, int score){
    if (team == Team::Blue){
        m_blueScore = score;
    }
    else if (team == Team::Red){
        m_redScore = score;
    }
    else{
        qDebug() << "Invalid team";
    }
    
    emit teamScoreUpdated(team, score);
}

    
bool GameCore::checkIsCardAnswer(const CardInfo& cardInfo) const {
    if (cardInfo.m_isAnswer) {
        return true;
    }
    return false;
}
