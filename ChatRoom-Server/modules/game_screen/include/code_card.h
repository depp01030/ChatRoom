#ifndef CODE_CARD_H
#define CODE_CARD_H

#include <QPushButton> 
#include "game_core/include/game_core.h"
class CodeCard : public QPushButton {
    Q_OBJECT

public: 
    explicit CodeCard(CardInfo cardInfo, QWidget *parent = nullptr);
    void setupConnections();


private slots:
    void onCardClicked();
private: 
    void initializeCard();
    CardInfo m_cardInfo;
    QColor m_normalColor = QColor("#A8A8A8");
    QColor m_answerColor = QColor("#65C1A4");
    QColor m_backgroundColor;
    QColor m_markerColor;
};

#endif // CODE_CARD_H