#include <QPainter>
#include <QDebug>

#include "../include/game_screen.h"
#include "code_card.h"


CodeCard::CodeCard(int id, QString word, QWidget *parent):
    m_id(id), m_word(word),
    QPushButton(parent) 
{
    initializeCard();    
}
void CodeCard::initializeCard()
{
    setText(m_word); 
    setStyleSheet("background-color: " + m_backgroundColor.name() + "; color: white;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
void CodeCard::turnOpen(const QColor &color){
    setStyleSheet("background-color: " + color.name() + "; color: white;"); 
}
