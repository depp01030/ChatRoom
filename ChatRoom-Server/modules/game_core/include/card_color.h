#ifndef CARD_COLOR_H
#define CARD_COLOR_H

#include <QColor>
#include "game_core/include/game_core.h"   

enum class CardType{
    RedSpy,
    BlueSpy,
    GreenSpy,
    People,
    Mine, 
};
enum class CardColor{
    Normal,
    Answer,
    Death,
    Back,
} ;

inline QColor getCardColor(const CardType cardType) {
    switch (cardType) {
        case CardType::RedSpy:
            return QColor(219, 115, 89);
        case CardType::BlueSpy:
            return QColor(0, 0, 255);
        case CardType::GreenSpy:
            return QColor(70, 184, 108);
        case CardType::People:  
            return QColor(38, 32, 60);
        case CardType::Mine:
            return QColor(219, 185, 89);
        default:
            return QColor(255, 255, 255);
    }
}
 

#endif // CARD_COLOR_H  