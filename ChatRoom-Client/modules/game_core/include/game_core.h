#ifndef GAME_CORE_H
#define GAME_CORE_H
#include "candidate_words.h"
#include <vector>
#include <QColor>

class CardInfo {
public:
    CardInfo(const QString& word, bool is_answer = false);
    QString m_word;
    bool is_answer;
    QColor markedColor = QColor("green");
private:
};

class GameCore {
public:
    GameCore();
    ~GameCore();
    void randomGenerateCardInfos();
    friend class GameScreen;
private:
    std::vector<CardInfo> m_cardInfos;
    size_t m_totalCardNum = 25;
};

#endif // GAME_CORE_H