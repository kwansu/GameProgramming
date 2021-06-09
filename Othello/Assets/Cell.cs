using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

using TEAM = COLOR;

public enum COLOR
{
	BLACK, WHITE
}

public static class ExCOLOR
{
	public static COLOR Reverse(this COLOR color)
	{
		return color == COLOR.BLACK ? COLOR.WHITE : COLOR.BLACK;
	}
}

public struct Direction
{
	public static readonly Direction TOP_LEFT;
	public static readonly Direction TOP_CENTER;
	public static readonly Direction TOP_RIGHT;
	public static readonly Direction MIDDLE_LEFT;
	public static readonly Direction MIDDLE_RIGHT;
	public static readonly Direction BOTTOM_LEFT;
	public static readonly Direction BOTTOM_CENTER;
	public static readonly Direction BOTTOM_RIGHT;

	int bitValue;

	private Direction(int val)
	{
		bitValue = val;
	}

	static Direction()
	{
		TOP_LEFT = new Direction(0x0001);
		TOP_CENTER = new Direction(0x0002);
		TOP_RIGHT = new Direction(0x0004);
		MIDDLE_LEFT = new Direction(0x0008);
		MIDDLE_RIGHT = new Direction(0x0010);
		BOTTOM_LEFT = new Direction(0x0020);
		BOTTOM_CENTER = new Direction(0x0040);
		BOTTOM_RIGHT = new Direction(0x0080);
	}

	public int BitValue
	{
		get
		{
			return bitValue;
		}
	}

	public int Row
	{
		get
		{
			switch (bitValue)
			{
				case 1: case 8: case 32:
					return -1;
				case 2: case 64:
					return 0;
				default:
					return 1;
			}
		}
	}

	public int Col
	{
		get
		{
			switch (bitValue)
			{
				case 1: case 2: case 4:
					return 1;
				case 8: case 16:
					return 0;
				default:
					return -1;
			}
		}
	}

	public Direction Reverse
	{
		get
		{
			switch (bitValue)
			{
				case 0x0001:
					return BOTTOM_RIGHT;
				case 0x0002:
					return BOTTOM_CENTER;
				case 0x0004:
					return BOTTOM_LEFT;
				case 0x0008:
					return MIDDLE_RIGHT;
				case 0x0010:
					return MIDDLE_LEFT;
				case 0x0020:
					return TOP_RIGHT;
				case 0x0040:
					return TOP_CENTER;
				case 0x0080:
					return TOP_LEFT;
			}

			return new Direction();
		}
	}

	public static Direction operator +(Direction left, Direction right)
	{
		return new Direction(left.bitValue | right.bitValue);
	}

	public static Direction operator -(Direction left, Direction right)
	{
		return new Direction(left.bitValue & ~right.bitValue);
	}

	public static Direction operator ++(Direction self)
	{
		self.bitValue <<= 1;
		return self;
	}

	public static bool operator ==(Direction left, Direction right)
	{
		return (left.bitValue & right.bitValue) != 0;
	}

	public static bool operator !=(Direction left, Direction right)
	{
		return (left.bitValue & right.bitValue) == 0;
	}
}

public partial class Cell
{
	static GameObject cellPrefab;

	public readonly Renderer renderer;
	public readonly Direction[] around;
	public readonly int row, col;
	public readonly int feature;

	COLOR color;
	bool enable;

	private Cell(int row, int col, int feature)
	{
		this.row = row;
		this.col = col;
		this.feature = feature;

		if (cellPrefab == null)
		{
			cellPrefab = GameObject.Find("Cell");
		}

		GameObject cellObject = GameObject.Instantiate(cellPrefab,
			new Vector3(row, col, 0), Quaternion.identity) as GameObject;

		renderer = cellObject.GetComponentInChildren<Renderer>();

		around = new Direction[2];
	}

	public Direction this[COLOR color]
	{
		get
		{
			return around[(int)color];
		}
	}

	public Direction Around
	{
		get
		{
			return around[(int)color.Reverse()];
		}
	}

	void Reset()
	{
		SetEnable(false);

		around[0] = new Direction();
		around[1] = new Direction();
	}

	void SetEnable(bool isEnable)
	{
		renderer.enabled = isEnable;
		enable = isEnable;
	}

	public void SetGray()
	{
		if (enable)
		{
			if (renderer.material.color == Color.gray)
			{
				renderer.material.color =
					(color == COLOR.BLACK) ? Color.black : Color.white;
			}
			else
			{
				renderer.material.color = Color.gray;
			}

			return;
		}

		if (renderer.enabled)
		{
			renderer.enabled = false;
		}
		else
		{
			renderer.enabled = true;
			renderer.material.color = Color.gray;
		}
	}

	void SetColor(COLOR color)
	{
		around[0] = new Direction();
		around[1] = new Direction();

		this.color = color;

		if (color == COLOR.BLACK)
		{
			renderer.material.color = Color.black;
		}
		else
		{
			renderer.material.color = Color.white;
		}
	}

	void AddDirection(Direction dir, COLOR colro)
	{
		around[(int)colro] += dir;
		around[(int)colro.Reverse()] -= dir;
	}

	void AddDirection(Direction dir)
	{
		around[(int)color] -= dir;
		around[(int)color.Reverse()] += dir;
	}

	void RemoveDirection(Direction dir)
	{
		around[0] -= dir;
		around[1] -= dir;
	}
}