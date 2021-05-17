using UnityEngine;
using System.Collections;

public partial class Card
{
	public class CardPack
	{
		Card[] cards;
		int curCardNum;

		public CardPack()
		{
			cards = new Card[52];
			curCardNum = 51;

			int i = 0;

			for (SYMBOL curSymbol = SYMBOL.CLOVER; curSymbol <= SYMBOL.SPADE; curSymbol = curSymbol.Next())
			{
				for (VALUE curValue = VALUE.TWO; curValue <= VALUE.A; ++curValue, ++i)
				{
					cards[i] = new Card(curSymbol, curValue);
				}
			}
		}

		public void Reset()
		{
			curCardNum = 51;
		}

		public Card DrawCard()
		{
			if (curCardNum >= 0 && curCardNum < 52)
			{
				int r = Random.Range(0, curCardNum);

				Card.Swap(ref cards[r], ref cards[curCardNum]);

				return cards[curCardNum--];
			}

			return null;
		}
	}
}
