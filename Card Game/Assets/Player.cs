using UnityEngine;
using System.Collections;

enum POKER_HAND
{
	HIGH_CARD = 0x0000,
	ONE_PAIR = 0x0001,
	TWO_PAIR = 0x0002,
	THREE_OF_A_KIND = 0x0004,
	STRAIGHT = 0x0008,
	BACK_STRAIGHT = 0x0010,
	MOUNTAIN = 0x0020,
	FLUSH = 0x0040,
	FULL_HOUSE = 0x0080,
	FOUR_OF_A_KIND = 0x0100,
	STRAIGHT_FLUSH = 0x0200,
	BACK_STRAIGHT_FLUSH = 0x0400,
	ROYAL_FLUSH = 0x0800
}

class Player
{
	struct HandTable
	{
		public int num;
		public int kind;

		public void AddCard(SYMBOL kind)
		{
			++num;

			this.kind |= (int)kind;
		}

		public void Init()
		{
			num = 0;
			kind = 0;
		}
	}

	public const int MAX_CARD_NUM = 7;

	public int cardNum;
	readonly Card[] pickupCards;
	readonly HandTable[] handTable;

	int cloverNum = 0;
	int diamondNum = 0;
	int heartNum = 0;
	int spadeNum = 0;

	int allHand;
	public POKER_HAND hand;
	public Card highCard;
	public Card secondCard;

	public Player()
	{
		pickupCards = new Card[MAX_CARD_NUM];
		handTable = new HandTable[13];

		Reset();
	}

	public void Reset()
	{
		for (int i = 0; i < pickupCards.Length; ++i)
		{
			pickupCards[i] = null;
		}

		for (int i = 0; i < handTable.Length; ++i)
		{
			handTable[i].Init();
		}

		cardNum = 0;

		hand = POKER_HAND.HIGH_CARD;
		allHand = 0;
		highCard = null;
		secondCard = null;

		cloverNum = 0;
		diamondNum = 0;
		heartNum = 0;
		spadeNum = 0;
	}

	public void PickCard(Card card)
	{
		if (cardNum < MAX_CARD_NUM)
		{
			pickupCards[cardNum++] = card;

			UpdateHand(card);
		}
	}

	Card SearchCard(SYMBOL symbol, VALUE value)
	{
		for (int i = 0; i < cardNum; ++i)
		{
			if (pickupCards[i].Value == value && pickupCards[i].Symbol == symbol)
			{
				return pickupCards[i];
			}
		}

		return null;
	}

	Card SearchCard(VALUE value)
	{
		Card result = null;

		for (int i = 0; i < cardNum; ++i)
		{
			if (pickupCards[i].Value == value && pickupCards[i].IsGreater(result))
			{
				result = pickupCards[i];
			}
		}

		return result;
	}

	void UpdateHand(Card card)
	{
		handTable[(int)card.Value].AddCard(card.Symbol);

		int flushCount = 0;

		switch (card.Symbol)
		{
			case SYMBOL.CLOVER:
				flushCount = ++cloverNum;
				break;
			case SYMBOL.DIAMOND:
				flushCount = ++diamondNum;
				break;
			case SYMBOL.HEART:
				flushCount = ++heartNum;
				break;
			case SYMBOL.SPADE:
				flushCount = ++spadeNum;
				break;
		}

		if (flushCount >= 5)
		{
			Flush(card);
		}

		switch (handTable[(int)card.Value].num)
		{
			case 1:
				HighCard(card);
				break;

			case 2:
				Pair(card);
				break;

			case 3:
				ThreeOfAKind(card);
				break;

			case 4:
				FourOfAKind(card);
				break;
		}

		CheckHand(card);
	}

	void HighCard(Card card)
	{
		if (hand == POKER_HAND.HIGH_CARD)
		{
			if (card.IsGreater(highCard))
			{
				highCard = card;
			}
		}
	}

	void Pair(Card card)
	{
		if ((allHand & (int)POKER_HAND.FULL_HOUSE) != 0)
		{
			if (hand == POKER_HAND.FULL_HOUSE && secondCard.Value < card.Value)
			{
				secondCard = card;
			}
		}
		else if ((allHand & (int)POKER_HAND.THREE_OF_A_KIND) != 0)
		{
			allHand |= (int)POKER_HAND.FULL_HOUSE;

			if (hand < POKER_HAND.FULL_HOUSE)
			{
				hand = POKER_HAND.FULL_HOUSE;
				highCard = secondCard;
				secondCard = card;
			}
		}
		else if ((allHand & (int)POKER_HAND.ONE_PAIR) != 0)
		{
			allHand |= (int)POKER_HAND.TWO_PAIR;

			if (hand < POKER_HAND.TWO_PAIR)
			{
				hand = POKER_HAND.TWO_PAIR;
				highCard = card;

				if (secondCard.IsGreater(highCard))
					Card.Swap(ref secondCard, ref highCard);
			}
		}
		else
		{
			if (hand < POKER_HAND.ONE_PAIR)
			{
				hand = POKER_HAND.ONE_PAIR;
				highCard = card;
				secondCard = card;
			}
		}

		allHand |= (int)POKER_HAND.ONE_PAIR;
	}

	void TwoPairCancle()
	{
		if (hand == POKER_HAND.TWO_PAIR)
		{
			Card.Swap(ref highCard, ref secondCard);
		}
	}

	void ThreeOfAKind(Card card)
	{
		TwoPairCancle();

		if ((allHand & ((int)POKER_HAND.FULL_HOUSE + (int)POKER_HAND.THREE_OF_A_KIND)) != 0)
		{
			if (hand == POKER_HAND.FULL_HOUSE && card.IsGreater(highCard))
			{
				highCard = card;
			}
			else if (hand == POKER_HAND.THREE_OF_A_KIND && card.IsGreater(highCard))
			{
				highCard = card;
				secondCard = card;
			}
		}
		else if ((allHand & (int)POKER_HAND.TWO_PAIR) != 0)
		{
			if (hand < POKER_HAND.FULL_HOUSE)
			{
				hand = POKER_HAND.FULL_HOUSE;
				highCard = card;
			}
		}
		else
		{
			secondCard = card;

			if (hand < POKER_HAND.THREE_OF_A_KIND)
			{
				hand = POKER_HAND.THREE_OF_A_KIND;
				highCard = card;
			}
		}

		allHand |= (int)POKER_HAND.THREE_OF_A_KIND;
	}

	void FourOfAKind(Card card)
	{
		if (hand < POKER_HAND.FOUR_OF_A_KIND)
		{
			hand = POKER_HAND.FOUR_OF_A_KIND;
			highCard = card;
		}
		else if (hand == POKER_HAND.FOUR_OF_A_KIND && card.IsGreater(highCard))
		{
			highCard = card;
		}

		allHand |= (int)POKER_HAND.FOUR_OF_A_KIND;
	}

	void Straight(Card card)
	{
		TwoPairCancle();

		POKER_HAND straightHand = POKER_HAND.STRAIGHT;

		switch (card.Value)
		{
			case VALUE.A:
				straightHand = POKER_HAND.MOUNTAIN;
				break;
			case VALUE.FIVE:
				straightHand = POKER_HAND.BACK_STRAIGHT;
				break;
		}

		if (hand < straightHand)
		{
			hand = straightHand;
			highCard = card;
		}
		else if (hand == straightHand && card.IsGreater(highCard))
		{
			highCard = card;
		}

		allHand |= (int)straightHand;
	}

	void Flush(Card card)
	{
		TwoPairCancle();

		if (hand < POKER_HAND.FLUSH)
		{
			hand = POKER_HAND.FLUSH;
			allHand |= (int)POKER_HAND.FLUSH;

			for (int i = 0; i < cardNum; ++i)
			{
				if (pickupCards[i].Symbol == card.Symbol && pickupCards[i].IsGreater(highCard))
				{
					highCard = pickupCards[i];
				}
			}
		}
		else if (hand == POKER_HAND.FLUSH)
		{
			if (card.IsGreater(highCard))
			{
				highCard = card;
			}
		}
	}

	void StraightFlush(Card card)
	{
		POKER_HAND straightHand = POKER_HAND.STRAIGHT_FLUSH;

		switch (card.Value)
		{
			case VALUE.A:
				straightHand = POKER_HAND.ROYAL_FLUSH;
				break;
			case VALUE.FIVE:
				straightHand = POKER_HAND.BACK_STRAIGHT_FLUSH;
				break;
		}

		if (hand < straightHand)
		{
			hand = straightHand;
			highCard = card;
		}
		else if (hand == straightHand && card.IsGreater(highCard))
		{
			highCard = card;
		}

		allHand |= (int)straightHand;
	}

	void CheckHand(Card card)
	{
		int i = (int)card.Value;
		int straightCount = 1;
		int flushCount = 1;
		bool isChainFlush = true;

		i = i == 0 ? 12 : i - 1;

		while (handTable[i].num > 0)
		{
			++straightCount;
			
			if(isChainFlush && (handTable[i].kind & (int)card.Symbol) != 0)
			{
				++flushCount;
			}
			else
			{
				isChainFlush = false;
			}

			if (i == 12)
			{
				break;
			}

			i = i == 0 ? 12 : i - 1;
		}

		isChainFlush = true;
		i = (int)card.Value;
		VALUE highFlushValue = card.Value;

		while (++i < 12 && handTable[i].num > 0)
		{
			++straightCount;

			if (isChainFlush && (handTable[i].kind & (int)card.Symbol) != 0)
			{
				++flushCount;
				++highFlushValue;
			}
			else
			{
				isChainFlush = false;
			}
		}

		if (straightCount >= 5)
		{
			Card highStraightCard;

			if (flushCount >= 5)
			{
				highStraightCard = SearchCard(card.Symbol, highFlushValue);
				StraightFlush(highStraightCard);
			}
			else
			{
				highStraightCard = SearchCard((VALUE)(i - 1));
				Straight(highStraightCard);
			}
		}
	}

	public bool IsWin(Player other)
	{
		if (hand < other.hand)
		{
			return false;
		}
		else if (hand == other.hand)
		{
			if (highCard.Value < other.highCard.Value)
			{
				return false;
			}
			else if (highCard.Value == other.highCard.Value)
			{
				if (hand == POKER_HAND.TWO_PAIR || hand == POKER_HAND.FULL_HOUSE)
				{
					if (secondCard.Value < other.secondCard.Value)
					{
						return false;
					}
					else if (secondCard.Value == other.secondCard.Value)
					{
						if (highCard.Symbol < other.highCard.Symbol)
						{
							return false;
						}
					}
				}
				else if (highCard.Symbol < other.highCard.Symbol)
				{
					return false;
				}
			}
		}

		return true;
	}
}
