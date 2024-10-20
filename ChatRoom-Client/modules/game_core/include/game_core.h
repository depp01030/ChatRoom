#ifndef GAME_CORE_H
#define GAME_CORE_H
#include "candidate_words.h"
#include "card_color.h"
#include <iostream>
#include <vector>
#include <QColor>
#include <QObject>
#include <QDebug>


enum class CardState{
    Open,
    Close,
};
class CardInfo {
public:
    CardInfo(const QString& word, bool is_answer = false);
    QString m_word;
    bool m_isAnswer; 
    int m_id;
    size_t m_index;
    CardState m_state;
    CardType m_cardType;
    QColor m_answerColor;
private:
};

class GameCore : public QObject {
    Q_OBJECT  // 添加這行
public:
    const int m_rowNum = 5;
    const int m_colNum = 5;
    enum class Team { Blue, Red };
private:
    int m_redScore = 0;
    int m_blueScore = 0;
    friend class GameController; 
    std::vector<CardInfo> m_cardsInfo;
    size_t m_totalCardNum = 25;
    size_t m_answerCardNum = 9;
    Team m_currentTurn;

public: 
    GameCore(QObject *parent = nullptr);
    ~GameCore();
    void initGame();
    std::vector<CardInfo> getCardsInfo() const {
         return m_cardsInfo; 
        }
    Team getCurrentTurn() const { return m_currentTurn; } 
    int getTeamScore(Team team) const;
    void openCard(CardInfo& cardInfo);
    void switchTurn();
    bool checkIsCardAnswer(const CardInfo& cardInfo) const;
    void updateTeamScore(Team team, int score);
    void setTeamScore(Team team, int score);
    void addTeamScore(Team team, int score);
private:
    void setCardsInfo(); 
    std::vector<CardInfo> randomGenerateCardInfos();
signals:
    void updateGameInfo();
    void cardOpened(const CardInfo& cardInfo);
    void turnSwitched(Team team);
    void teamScoreUpdated(Team team, int score);


};

#endif // GAME_CORE_H
















