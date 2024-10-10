#ifndef GAME_CORE_H
#define GAME_CORE_H
#include "candidate_words.h"
#include <iostream>
#include <vector>
#include <QColor>
#include <QObject>
#include <QDebug>

enum class CardType{
    RedSpy,
    BlueSpy,
    GreenSpy,
    People,
    Mine,

};
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
private:
};

class GameCore : public QObject {
    Q_OBJECT  // 添加這行

public:
    const int m_rowNum = 5;
    const int m_colNum = 5;
    int m_redScore = 0;
    int m_blueScore = 0;
    enum class Team { Blue, Red };

    explicit GameCore(QObject *parent = nullptr);
    ~GameCore();
    std::vector<CardInfo> randomGenerateCardInfos();
    void initGame();
    void setCardInfos();
    void onCodeCardClicked(const int id);
    Team getCurrentTurn() const { return m_currentTurn; }
    void switchTurn();
    bool checkIsCardAnswer(const CardInfo& cardInfo) const;
signals:
    void updateGameInfo();
    void showCardAnswer(const CardInfo& cardInfo);
    void turnNextRound(Team team);

private:
    friend class GameScreen;
    void processPlayerCardSelection(CardInfo& cardInfo);
    std::vector<CardInfo> m_cardInfos;
    size_t m_totalCardNum = 25;
    Team m_currentTurn;
};

#endif // GAME_CORE_H
















