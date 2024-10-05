#include "game_core.h"
#include <algorithm>
#include <random>

CardInfo::CardInfo(const QString& word, bool is_answer):
m_word(word), is_answer(is_answer) 
{

}

GameCore::GameCore() {
    randomGenerateCardInfos();
}

GameCore::~GameCore() {

}

void GameCore::randomGenerateCardInfos() {
    std::vector<size_t> indices(CANDIDATE_WORDS.size()); //生成一個vector indices with length CANDIDATE_WORDS.size()
    std::iota(indices.begin(), indices.end(), 0); //將indices填入0到CANDIDATE_WORDS.size()的數字
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g); //將indices的數字打亂

    m_cardInfos.clear();
    for (size_t i = 0; i < m_totalCardNum; ++i) {
        m_cardInfos.emplace_back(CANDIDATE_WORDS[indices[i]], i < 8);
    }
    std::shuffle(m_cardInfos.begin(), m_cardInfos.end(), g);
}
