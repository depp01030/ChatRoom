#include "code_card.h"
#include <QPainter>
#include <QDebug>



CodeCard::CodeCard(CardInfo cardInfo, QWidget *parent)
    : m_cardInfo(cardInfo),
    QPushButton(parent), 
    m_backgroundColor(m_normalColor)
{
    setText(m_cardInfo.m_word);
    setStyleSheet("background-color: " + m_backgroundColor.name() + "; color: white;");
    initializeCard();
    setupConnections();
}

void CodeCard::initializeCard()
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // 可以在這裡添加其他共同的初始化代碼
}

void CodeCard::setupConnections()
{
    connect(this, &CodeCard::clicked, this, &CodeCard::onCardClicked);
}
void CodeCard::onCardClicked()
{
    if (m_cardInfo.is_answer) {
        setStyleSheet("background-color: " + m_answerColor.name() + "; color: white;");
        qDebug() << text() + "is answer";
    }
    else {
        qDebug() << text() + "is not answer";
    }
    
}

// void CodeCard::paintEvent(QPaintEvent *event) {
//     qDebug() << "CodeCard::paintEvent called for card with text:";
//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing);

//     // Draw background
//     painter.fillRect(rect(), m_backgroundColor);

//     // Draw marker color with semi-transparency
//     QColor semiTransparentMarker = m_markerColor;
//     semiTransparentMarker.setAlpha(128);
//     painter.fillRect(rect(), semiTransparentMarker);

//     // Draw text
//     painter.setPen(Qt::black);
//     painter.drawText(rect(), Qt::AlignCenter, m_text);

//     QPushButton::paintEvent(event);
// }