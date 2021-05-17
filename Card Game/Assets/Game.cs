using UnityEngine;
using System.Collections;

public class Game : MonoBehaviour
{
	public GameObject textObject;
	public float cardInterval = 3;

	Card.CardPack cardPack;

	Player playerOne;
	Player playerTwo;
	Player curTurnPlayer;

	Text[] playerOneTexts;
	Text[] playerTwoTexts;

	bool isAutoMode = false;
	int totalGame = 0;
	int numWinOne = 0;
	int numWinTwo = 0;

	void Awake()
	{
		cardPack = new Card.CardPack();

		playerOne = new Player();
		playerTwo = new Player();

		curTurnPlayer = playerOne;

		playerOneTexts = new Text[Player.MAX_CARD_NUM];
		playerTwoTexts = new Text[Player.MAX_CARD_NUM];

		int halfSize = Player.MAX_CARD_NUM / 2;

		for (int i = 0; i < Player.MAX_CARD_NUM; ++i)
		{
			GameObject obj1 = Instantiate(textObject);
			GameObject obj2 = Instantiate(textObject);

			obj1.transform.position = new Vector3((i - halfSize) * cardInterval, 4);
			obj2.transform.position = new Vector3((i - halfSize) * cardInterval, -4);

			playerOneTexts[i] = obj1.GetComponent<Text>();
			playerTwoTexts[i] = obj2.GetComponent<Text>();
		}
	}

	void Update()
	{
		if (Input.GetKeyDown(KeyCode.Space))
		{
			isAutoMode = !isAutoMode;
		}

		if (isAutoMode)
		{
			AutoMode();

			Debug.Log("total : " + totalGame + " , one : " + numWinOne + " , two : " + numWinTwo);

			if (totalGame >= 10000)
			{
				isAutoMode = false;
				Debug.Log(numWinOne / (float)totalGame);
			}
		}
		else
		{
			if (Input.GetKeyDown(KeyCode.Return))
			{
				PlayTurn();
			}
		}
	}

	void Reset()
	{
		playerOne.Reset();
		playerTwo.Reset();
		cardPack.Reset();

		for (int i = 0; i < Player.MAX_CARD_NUM; ++i)
		{
			playerOneTexts[i].Reset();
			playerTwoTexts[i].Reset();
		}
	}

	void Compare()
	{
		//Debug.Log(playerOne.hand/* + playerOne.highCard.Symbol.ToString2() + playerOne.highCard.Value.ToString2()*/);
		//Debug.Log(playerTwo.hand/* + playerTwo.highCard.Symbol.ToString2() + playerTwo.highCard.Value.ToString2()*/);

		if (playerOne.IsWin(playerTwo))
		{
			Debug.Log("player one win");
			++numWinOne;
		}
		else
		{
			Debug.Log("player two win");
			++numWinTwo;
		}

		++totalGame;

		Reset();
	}

	void PlayTurn()
	{
		if (curTurnPlayer.cardNum == Player.MAX_CARD_NUM)
		{
			Compare();
		}
		else
		{
			Card drawCard = cardPack.DrawCard();

			curTurnPlayer.PickCard(drawCard);

			if (curTurnPlayer == playerOne)
			{
				playerOneTexts[curTurnPlayer.cardNum - 1].SetText(drawCard);
				curTurnPlayer = playerTwo;
			}
			else
			{
				playerTwoTexts[curTurnPlayer.cardNum - 1].SetText(drawCard);
				curTurnPlayer = playerOne;
			}
		}
	}

	float winRate = 62;

	void SetControllWin()
	{
		winRate += Random.Range(-5.0f, 5.0f);

		if (playerOne.hand >= POKER_HAND.TWO_PAIR && numWinOne/(float)totalGame < winRate + 5)
		{
			
		}
		else
		{

		}
	}

	void AutoMode()
	{
		float elapseTime = 0;
		float curTime = Time.realtimeSinceStartup;

		while (elapseTime <= Time.smoothDeltaTime / 2)
		{
			PlayTurn();

			elapseTime = Time.realtimeSinceStartup - curTime;
		}

	}
}
