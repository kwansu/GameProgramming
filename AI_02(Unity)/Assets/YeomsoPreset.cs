using System;
using System.Collections.Generic;
using UnityEngine;

public struct SelfStateData
{
    public float sight;
    public float moveSpeed;
    public Vector2 position;
    public Vector2 direction;
    public EActionState actionState;

    static public bool operator !=(SelfStateData a, SelfStateData b)
    {
        return !(a.actionState != b.actionState || !a.sight.Equels(b.sight) || !a.moveSpeed.Equals(b.moveSpeed)
             || a.position != b.position || a.direction != b.direction);
    }

    static public bool operator ==(SelfStateData a, SelfStateData b)
    {
        return a.actionState != b.actionState || !a.sight.Equels(b.sight) || !a.moveSpeed.Equals(b.moveSpeed)
             || a.position != b.position || a.direction != b.direction;
    }
}

public class Ye_SelfState : Yeomso
{
    public YTime YTime { get; }
    public float Sight { get; }
    public Vector2 Position { get; }
    public Vector2 Direction { get; }
    public float MoveSpeed { get; }
    public EActionState ActionState { get; }

    public Ye_SelfState(YTime ytime, SelfStateData data)
    {
        YTime = ytime;
        Sight = data.sight;
        Position = data.position;
        Direction = data.direction;
        MoveSpeed = data.moveSpeed;
        ActionState = data.actionState;
    }
}