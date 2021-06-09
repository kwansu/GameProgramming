using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public partial class Cell
{
	public partial class Board
	{
		static readonly Board instance;
		const int sideLenth = 8;

		IBoardManager manager;

		public readonly Cell[,] cells;

		static public Board Singleton
		{
			get
			{
				return instance;
			}
		}

		static Board()
		{
			instance = new Board();
		}

		private Board()
		{
			cells = new Cell[sideLenth, sideLenth];
		}

		public void Initialize(IBoardManager manager)
		{
			this.manager = manager;

			for (int i = 0; i < sideLenth; ++i)
			{
				for (int j = 0; j < sideLenth; ++j)
				{
					cells[i, j] = new Cell(i, j, CalculateFeature(i, j));
				}
			}

			Reset();
		}

		// incomplete feature
		int CalculateFeature(int row, int col)
		{
			row = row < 4 ? row : 7 - row;
			col = col < 4 ? col : 7 - col;

			int sum = row + col;

			if (row == col)
			{
				return sum * 2;
			}
			else if (row == 0 || col == 0)
			{
				return sum;
			}
			else
			{
				return sum + 2;
			}
		}

		public void Reset()
		{
			for (int i = 0; i < sideLenth; ++i)
			{
				for (int j = 0; j < sideLenth; ++j)
				{
					cells[i, j].Reset();
				}
			}

			int h = sideLenth / 2;

			SetColor(cells[h - 0, h - 0], COLOR.BLACK);
			SetColor(cells[h - 1, h - 1], COLOR.BLACK);
			SetColor(cells[h - 0, h - 1], COLOR.WHITE);
			SetColor(cells[h - 1, h - 0], COLOR.WHITE);
		}

		public void CalculateCount(out int numBlack, out int numWhite)
		{
			numBlack = 0;
			numWhite = 0;

			foreach (Cell cell in cells)
			{
				if (cell.enable)
				{
					if (cell.color == COLOR.BLACK)
					{
						++numBlack;
					}
					else
					{
						++numWhite;
					}
				}
			}
		}

		Cell GetNeighborCell(Cell cell, Direction dir)
		{
			int row = cell.row + dir.Row;
			int col = cell.col + dir.Col;

			if (CheckArrayRange(row, col))
			{
				return null;
			}

			return cells[row, col];
		}

		// correct row, col is false;
		bool CheckArrayRange(int row, int col)
		{
			return row < 0 || row >= sideLenth || col < 0 || col >= sideLenth;
		}

		public bool CheckMove(int row, int col, COLOR team)
		{
			if (CheckArrayRange(row, col))
			{
				return false;
			}

			return CheckMove(cells[row, col], team);
		}

		public bool CheckMove(Cell cell, COLOR team)
		{
			if (!cell.enable)
			{
				if (cell[team].BitValue != 0)
				{
					SetMove(cell, team);
					return true;
				}
			}

			return false;
		}

		void SetMove(Cell cell, COLOR color)
		{
			cell.SetEnable(true);
			cell.color = color;

			for (Direction dir = Direction.TOP_LEFT; dir.BitValue < 0x0100; ++dir)
			{
				if (cell[color] == dir)
				{
					ChangeCellChain(GetNeighborCell(cell, dir), dir);
				}
			}

			SetColor(cell, color);
			manager.RemoveAbleList(cell);
		}

		void SetColor(Cell cell, COLOR color)
		{
			cell.SetEnable(true);
			cell.SetColor(color);

			for (Direction dir = Direction.TOP_LEFT; dir.BitValue < 0x0100; ++dir)
			{
				UpdateDirection(cell, dir);
			}
		}

		void ChangeCellChain(Cell cell, Direction dir)
		{
			SetColor(cell, cell.color.Reverse());

			Cell neighbor = GetNeighborCell(cell, dir);

			if (neighbor.color != cell.color)
			{
				ChangeCellChain(neighbor, dir);
			}
		}

		void UpdateDirection(Cell cell, Direction dir)
		{
			COLOR reverse = cell.color.Reverse();
			Cell negihbor = GetNeighborCell(cell, dir);

			if (negihbor == null)
			{
				return;
			}

			if (!negihbor.enable)
			{
				if (cell.Around == dir.Reverse)
				{
					negihbor.AddDirection(dir.Reverse, reverse);
					manager.AddAbleList(negihbor, reverse);

					if (negihbor[cell.color].BitValue == 0)
					{
						manager.RemoveAbleList(negihbor, cell.color);
					}
				}
				else
				{
					negihbor.RemoveDirection(dir.Reverse);
					manager.RemoveAbleList(negihbor, cell.color);
				}
			}
			else if (cell.color == negihbor.color)
			{
				if (negihbor.Around == dir)
				{
					AddUpdateDirectionChain(cell, dir.Reverse);
				}

				if (cell.Around != dir.Reverse)
				{
					RemoveUpdateDirectionChain(negihbor, dir);
				}
			}
			else
			{
				AddUpdateDirectionChain(negihbor, dir);
				AddUpdateDirectionChain(cell, dir.Reverse);
			}
		}

		void AddUpdateDirectionChain(Cell cell, Direction dir)
		{
			if (cell.Around != dir.Reverse)
			{
				cell.AddDirection(dir.Reverse);

				Cell neighbor = GetNeighborCell(cell, dir);

				if (neighbor == null)
				{
					return;
				}

				if (neighbor.enable == false)
				{
					COLOR reverse = cell.color.Reverse();

					neighbor.AddDirection(dir.Reverse, reverse);
					manager.AddAbleList(neighbor, reverse);
				}
				else if (neighbor.color == cell.color)
				{
					AddUpdateDirectionChain(neighbor, dir);
				}
			}
		}

		void RemoveUpdateDirectionChain(Cell cell, Direction dir)
		{
			if (cell.Around == dir.Reverse)
			{
				cell.RemoveDirection(dir.Reverse);

				Cell neighbor = GetNeighborCell(cell, dir);

				if (neighbor == null)
				{
					return;
				}

				if (neighbor.enable == false)
				{
					neighbor.RemoveDirection(dir.Reverse);
					manager.RemoveAbleList(neighbor, cell.color.Reverse());
				}
				else if (neighbor.color == cell.color)
				{
					RemoveUpdateDirectionChain(neighbor, dir);
				}
			}
		}
	}
}

