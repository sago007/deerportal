#include "cardsdeck.h"

CardsDeck::CardsDeck(TextureHolder *textures, sf::Font *gameFont, Command *command)
{


    commandManager=command;
    std::array<std::array<int,2>,4> cardsPos = {
        {
            {{1087,95}}, {{1225, 95}}, {{1225, 277}}, {{1087, 277}}
    }
    };

    this->textures = textures;
    for (int i=0;i<=3;i++)
    {
//        spriteCardBases[i].setTexture(this->textures->textureCardBases[i]);
        spriteCardBases[i].setPosition(cardsPos[i][0],cardsPos[i][1]);

        textPileTitle[i].setFont(*gameFont);
        textPileTitle[i].setCharacterSize(16);
        textPileTitle[i].setPosition(cardsPos[i][0]+10,cardsPos[i][1]+100);

        for (unsigned int j=0;j<efc::cardsDistribution.size();j++)
        {

            int cardTypeInt = efc::cardsDistribution[j];

            cardsList[i].cardsPile[j].cardType = efc::cardsTypes[cardTypeInt];
            cardsList[i].cardsPile[j].cardTypeInt = cardTypeInt;
            spriteCardBases[i].setTexture(this->textures->cardsTextures[i][cardTypeInt]);

        }



    }
    reloadCards();

}

void CardsDeck::reloadCards(){
     for (int i=0;i<=3;i++)
     {

        cardsList[i].shufflePile();
        setTitles(i);
     }
}

void CardsDeck::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for (int i=0;i<=3;i++)
    {
        if ((cardsList[i].invisibleLeft==0.0f) and (cardsList[i].active))
        {
            target.draw(spriteCardBases[i], states);
            target.draw(textPileTitle[i], states);
        }
    }
}

void CardsDeck::setTitles(int number)
{
      int cardTypeInt = getCardTypeInt(number);

        textPileTitle[number].setString(efc::cardsTypes[cardTypeInt]);
//        int val = getCardTypeInt(number);


        spriteCardBases[number].setTexture(textures->cardsTextures[number][cardTypeInt]);

}



void CardsDeck::setFonts(sf::Font *gameFont)
{
    for (int i=0;i<=3;i++)
    {
        textPileTitle[i].setFont(*gameFont);
    }
}

void CardsDeck::nextCard(int pileNumber)
{
    if (cardsList[pileNumber].active)
    {
        cardsList[pileNumber].invisibleLeft = 0.75f;
        unsigned int currentCard = getCurrentCard(pileNumber);

        if (currentCard>=efc::cardsDistribution.size()-1)
        {
            cardsList[pileNumber].active = false;
            commandManager->removeAllCardElement(pileNumber);

        } else
        {
            currentCard += 1;
            if (currentCard>3)
                currentCard = 0;
            cardsList[pileNumber].currentCard = currentCard;
            setTitles(pileNumber);
        }
    }
//    setSprites(pileNumber);
}

int CardsDeck::getCurrentCard(int pileNumber)
{
    int currentCard = cardsList[pileNumber].currentCard;
    return currentCard;
}

std::string CardsDeck::getTitle(int pileNumber)
{
    std::string currentText = efc::cardsTypes[getCardTypeInt(pileNumber)];
    return currentText;
}

int CardsDeck::getCardTypeInt(int pileNumber)
{
    int result = cardsList[pileNumber].cardsPile[getCurrentCard(pileNumber)].cardTypeInt;
    return result;
}

void CardsDeck::update(sf::Time deltaTime)
{
    for (int i=0;i<=3;i++)
    {
        if (cardsList[i].invisibleLeft>0.0f)
        {
            cardsList[i].invisibleLeft -= deltaTime.asSeconds();

        }
        if (cardsList[i].invisibleLeft<0.0f)
        {
            cardsList[i].invisibleLeft = 0.0f;
        }
    }

}
