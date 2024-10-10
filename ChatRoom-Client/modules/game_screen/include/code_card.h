#ifndef CODE_CARD_H
#define CODE_CARD_H

#include <QPushButton> 
#include "game_core/include/game_core.h" 
#include "card_color.h"
class CodeCard : public QPushButton {
    Q_OBJECT

public: 
    explicit CodeCard(int id, QString word, QWidget *parent = nullptr);
    // void setupConnections();
    int m_id;
    QString m_word;
    CardState m_state;
    void showAnswer();
    void setAnswerColor(const CardType cardType);
private slots:
    // void onCardClicked();
private: 
    void initializeCard(); 
    QColor m_answerColor;
    QColor m_backgroundColor = QColor(87, 83, 72);
};
#endif // CODE_CARD_H