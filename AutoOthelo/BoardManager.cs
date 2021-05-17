using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

public class BoardManager
{
	const string path = @"c:\Temp\test.txt";
	const int COUNT_AREA = 9;
	const int COUNT_TEAM = 2;
	const int COUNT_FEATURE = 9;

	static readonly object thisLock = new object();
	public static int total;
	public static int win;

	// 나중에 AI, Record기능은 따로 클래스로 나눌 것.
	List<Aspect> recordList;
	readonly Area[] areas;

	readonly Cell.Board board;
	readonly List<Cell> blackList;
	readonly List<Cell> whiteList;

	int game;
	int victory;
	bool autoMode;
	bool isRandom = true;
	COLOR team;
	Random rand;

	public BoardManager()
	{
		blackList = new List<Cell>();
		whiteList = new List<Cell>();

		board = new Cell.Board(this);
		rand = new Random();

		areas = new Area[COUNT_AREA];
		recordList = new List<Aspect>();

		Load();
	}

	public void Process()
	{
		while (game < 10000)
		{
			AutoMove();
		}

		lock(thisLock)
		{
			win += victory;
		}

		Save();
	}

	void Save()
	{
		lock(thisLock)
		{
			Area[] temp = new Area[COUNT_AREA];

			for (int i = 0; i < COUNT_AREA; ++i)
			{
				temp[i] = areas[i];
			}

			Load();

			FileStream fileStream
				= new FileStream(path, FileMode.Create, FileAccess.Write);

			BinaryWriter writer = new BinaryWriter(fileStream);

			for (int j = 0; j < COUNT_AREA; ++j)
			{
				for (int i = 0; i < COUNT_FEATURE; ++i)
				{
					writer.Write(areas[j].GetTotal(i) + temp[j].GetTotal(i));
					writer.Write(areas[j].GetWin(i) + temp[j].GetWin(i));
				}
			}

			writer.Close();
		}
	}

	void Load()
	{
		int[] total = new int[COUNT_FEATURE];
		int[] win = new int[COUNT_FEATURE];

		lock (thisLock)
		{
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
	}

	void Reset()
	{
		for (int i = 0; i < COUNT_AREA; ++i)
		{
			areas[i].FeatureNum = 0;
		}

		blackList.Clear();
		whiteList.Clear();

		team = COLOR.WHITE;

		board.Reset();
	}

	void EndGame()
	{
		bool isWin = false;

		int numBlack;
		int numWhite;

		board.CalculateCount(out numBlack, out numWhite);

		if (numBlack > numWhite)
		{
			isWin = true;
			++victory;
		}

		for (int i = 0; i < COUNT_AREA; ++i)
		{
			areas[i].Calculate(isWin);
		}

		++game;

		if (game % 100 == 0)
		{
			lock(thisLock)
			{
				total += 100;
				Console.WriteLine(total);
			}
		}

		Reset();
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

	void TurnChange()
	{
		team = team.Reverse();
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
			cell = list[rand.Next(0, list.Count)];
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

	// 임시로 검정색 기준으로만 설계함.
	Cell GetCalcuateBestCell()
	{
		Cell cell = null;

		float rate = -float.MaxValue;

		foreach (Cell val in blackList)
		{
			if (areas[val.feature].Interval > rate)
			{
				cell = val;
				rate = areas[val.feature].Interval;
			}
		}

		return cell;
	}
}

