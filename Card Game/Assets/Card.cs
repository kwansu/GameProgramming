using UnityEngine;
using System.Collections;

public enum SYMBOL
{
	CLOVER = 0x0001,
	HEART = 0x0002,
	DIAMOND = 0x0004,
	SPADE = 0x0008,
}

public enum VALUE
{
	TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, Q, K, A
}

public static class ExtexdClass
{
	static public SYMBOL Next(this SYMBOL symbol)
	{
		symbol = (SYMBOL)((int)symbol << 1);

		return symbol;
	}

	static public string ToString2(this SYMBOL symbol)
	{
		string str = null;

		switch (symbol)
		{
			case SYMBOL.CLOVER:
				str = "♣";
				break;
			case SYMBOL.DIAMOND:
				str = "◇";
				break;
			case SYMBOL.HEART:
				str = "♡";
				break;
			case SYMBOL.SPADE:
				str = "♠";
				break;
		}

		return str;
	}

	static public string ToString2(this VALUE value)
	{
		if (value < VALUE.J)
		{
			return ((int)value + 2).ToString();
		}

		return value.ToString();
	}
}

public partial class Card
{
	readonly SYMBOL symbol;
	readonly VALUE value;

	public SYMBOL Symbol
	{
		get
		{
			return symbol;
		}
	}

	public VALUE Value
	{
		get
		{
			return value;
		}
	}

	Card(SYMBOL symbol, VALUE value)
	{
		this.symbol = symbol;
		this.value = value;
	}

	public bool IsGreater(Card card)
	{
		if (card == null)
		{
			return true;
		}

		return this.value > card.value ||
			(this.value == card.value && this.symbol > card.symbol);
	}

	static public void Swap(ref Card left, ref Card right)
	{
		Card temp = left;

		left = right;
		right = temp;
	}
}
