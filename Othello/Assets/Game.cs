using UnityEngine;
using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

public sealed class Game : MonoBehaviour, IBoardManager
{
	const string path = @"c:\Temp\test.txt";
	public const int COUNT_AREA = 9;
	public const int COUNT_TEAM = 2;
	public const int COUNT_FEATURE = 9;

	// 나중에 AI, Record기능은 따로 클래스로 나눌 것.
	List<Aspect> recordList;
	readonly Area[] areas;

	public Renderer cellRenderer;

	readonly Cell.Board board;
	readonly List<Cell> blackList;
	readonly List<Cell> whiteList;

	bool autoMode;
	bool isRandom = true;
	COLOR team;
	int totalGame;

	Game()
	{
		board = Cell.Board.Singleton;

		blackList = new List<Cell>();
		whiteList = new List<Cell>();

		areas = new Area[COUNT_AREA];
		recordList = new List<Aspect>();
	}

	void Awake()
	{
		board.Initialize(this);
		Load();
	}

	public void Update()
	{
		if (autoMode)
		{
			AutoMove();
		}
		else if (Input.GetMouseButtonDown(0))
		{
			ManualMove();
		}
		else if (Input.GetKeyDown(KeyCode.Space))
		{
			VisibleAble();
		}
		else if (Input.GetKeyDown(KeyCode.R))
		{
			Reset();
		}
		else if (Input.GetMouseButtonDown(1))
		{
			PrintCellInfo();
		}
		else if (Input.GetKeyDown(KeyCode.S))
		{
			Save();
		}
		else if (Input.GetKeyDown(KeyCode.E))
		{
			isRandom = !isRandom;
			Debug.Log(isRandom);
		}
		else if (isRandom == false && team == COLOR.BLACK)
		{
			AutoMove();
		}
		else if (Input.GetKeyDown(KeyCode.Return))
		{
			autoMode = !autoMode;
		}

	}

	void Reset()
	{
		for (int i = 0; i < COUNT_AREA; ++i)
		{
			areas[i].FeatureNum = 0;
		}

		blackList.Clear();
		whiteList.Clear();

		team = COLOR.BLACK;

		board.Reset();
	}

	void EndGame()
	{
		++totalGame;
		bool isWin = false;

		int numBlack;
		int numWhite;

		board.CalculateCount(out numBlack, out numWhite);

		switch (numBlack.CompareTo(numWhite))
		{
			case 0:
				Debug.Log("draw");
				break;
			case 1:
				Debug.Log("black win");
				isWin = true;
				break;
			case -1:
				Debug.Log("white win");
				break;
		}

		for (int i = 0; i < COUNT_AREA; ++i)
		{
			areas[i].Calculate(isWin);
		}

		Reset();
	}

	void Save()
	{
		FileStream fileStream
			= new FileStream(path, FileMode.Create, FileAccess.Write);

		BinaryWriter writer = new BinaryWriter(fileStream);

		foreach (Area val in areas)
		{
			for (int i = 0; i < COUNT_FEATURE; ++i)
			{
				writer.Write(val.GetTotal(i));
				writer.Write(val.GetWin(i));
			}
		}

		writer.Close();
	}

	void Load()
	{
		int[] total = new int[COUNT_FEATURE];
		int[] win = new int[COUNT_FEATURE];

		if (File.Exists(path))
		{
			FileStream fileStream
			= new FileStream(path, FileMode.Open);

			BinaryReader reader = new BinaryReader(fileStream);

			for (int i = 0; i < COUNT_AREA; ++i)
			{
				for (int f = 0; f < COUNT_FEATURE; ++f)
				{
					total[f] = reader.ReadInt32();
					win[f] = reader.ReadInt32();
				}

				StringBuilder str = new StringBuilder();

				str.Append("total : ");
				foreach (int val in total)
				{
					str.AppendFormat("{0} , ", val);
				}
				Debug.Log(str);

				str.Length = 0;
				str.Append("win   : ");
				foreach (int val in win)
				{
					str.AppendFormat("{0} , ", val);
				}
				Debug.Log(str);

				areas[i] = new Area(total, win);
			}

			reader.Close();
		}
		else
		{
			for (int i = 0; i < COUNT_AREA; ++i)
			{
				areas[i] = new Area(total, win);
			}
		}
	}

	public void AddAbleList(Cell cell, COLOR color)
	{
		List<Cell> list = color == COLOR.BLACK ? blackList : whiteList;

		foreach (Cell val in list)
		{
			if (val == cell)
			{
				return;
			}
		}

		list.Add(cell);
	}

	public void RemoveAbleList(Cell cell, COLOR color)
	{
		List<Cell> list = color == COLOR.BLACK ? blackList : whiteList;

		foreach (Cell val in list)
		{
			if (val == cell)
			{
				if (cell[color].BitValue == 0)
				{
					list.Remove(cell);
				}

				break;
			}
		}
	}

	public void RemoveAbleList(Cell cell)
	{
		blackList.Remove(cell);
		whiteList.Remove(cell);
	}

	void PrintCellInfo()
	{
		Ray mouseRay = Camera.main.ScreenPointToRay(Input.mousePosition);
		RaycastHit hit;

		if (Physics.Raycast(mouseRay, out hit))
		{
			Cell cell = board.cells[(int)hit.point.x, (int)hit.point.y];

			Debug.Log(cell.row + ", " + cell.col + " : " + cell.feature);
			StringBuilder str = new StringBuilder();

			Debug.Log("interval : " + areas[cell.feature].Interval);

			str.Append("winRate : ");
			foreach (float val in areas[cell.feature].winRate)
			{
				str.AppendFormat("{0} , ", val);
			}
			Debug.Log(str);
		}
	}

	void TurnChange()
	{
		team = team.Reverse();
		cellRenderer.material.color = team == COLOR.BLACK ? Color.black : Color.white;
	}

	void RepeatAuto()
	{
		float time = Time.realtimeSinceStartup;
		float maxTime = Time.smoothDeltaTime * 0.8f;

		while (Time.realtimeSinceStartup - time < maxTime)
		{
			AutoMove();
		}

		if (isRandom && totalGame >= 10000)
		{
			autoMode = false;
		}
	}

	void AutoMove()
	{
		List<Cell> list = team == COLOR.BLACK ? blackList : whiteList;

		if (list.Count == 0)
		{
			EndGame();
			return;
		}

		Cell cell = null;

		if (isRandom == false && team == COLOR.BLACK)
		{
			cell = GetCalcuateBestCell();
		}
		else
		{
			int r = UnityEngine.Random.Range(0, list.Count);
			cell = list[r];
		}

		Move(cell);
	}

	void Move(Cell cell)
	{
		if (board.CheckMove(cell, team))
		{
			if (team == COLOR.BLACK)
			{
				++areas[cell.feature].FeatureNum;
			}

			TurnChange();
		}
	}

	void Move(int row, int col)
	{
		//recordList.Add(new Aspect(row, col));

		Move(board.cells[row, col]);
		//else
		//{
		//	recordList.ForEach((Aspect val) => Debug.Log(val.row + ", " + val.col));
		//	autoMode = false;
		//}
	}

	void VisibleAble()
	{
		List<Cell> list = team == COLOR.BLACK ? blackList : whiteList;

		foreach (Cell val in list)
		{
			val.SetGray();
		}
	}

	void ManualMove()
	{
		Ray mouseRay = Camera.main.ScreenPointToRay(Input.mousePosition);
		RaycastHit hit;

		if (Physics.Raycast(mouseRay, out hit))
		{
			Move((int)hit.point.x, (int)hit.point.y);
		}
	}

	// 임시로 검정색 기준으로만 설계함.
	Cell GetCalcuateBestCell()
	{
		Cell cell = null;

		float interval = -1;

		foreach (Cell val in blackList)
		{
			if (areas[val.feature].Interval > interval)
			{
				cell = val;
				interval = areas[val.feature].Interval;
			}
		}

		return cell;
	}
}
