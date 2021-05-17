using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Yeomso_Time : Yeomso
{
    public float Time { get; }

    public Yeomso_Time(float time)
        : base(EYeomsoType.TIME)
    {
        Time = time;
    }
}


public class Yeomso_Dependent : Yeomso
{
    public Yeomso Owner { get; set; }
    public Yeomso_Time Time { get; set; }

    public Yeomso_Dependent(EYeomsoType type)
        :base (type)
    {

    }
}


public class Yeomso_IntData : Yeomso_Dependent
{
    public int Data { get; set; }

    public Yeomso_IntData(EYeomsoType type)
        : base(type)
    {
    }

    public Yeomso_IntData(EYeomsoType type, int data)
    : base(type)
    {
        Data = data;
    }
}


public class Yeomso_Location : Yeomso_Dependent
{
    public Vector3 PosData { get; set; } = new Vector3(0, 0, 0);

    public Yeomso_Location()
        : base(EYeomsoType.LOCATION)
    {

    }
}


public class Yeomso_Behavior : Yeomso_Dependent
{
    public string Data;
    public EActionState AS;

    public Yeomso_Behavior()
        : base(EYeomsoType.BEHAVIOR)
    {

    }
}


public class Yeomso_Object : Yeomso
{
    public Entity RealEntity { get; }
    public Yeomso_Location Pos { get; set; }
    public Yeomso_IntData AS { get; set; }
    public Yeomso_Race Race { get; set; }

    public Yeomso_Object(Entity realEntity)
        : base(EYeomsoType.OBJECT)
    {
        RealEntity = realEntity;
    }

    public bool IsFirstJudgmentEvaluation()
    {
        // ConnetedYeomsos가 오직 판/평을 위해서 사용된다고 가정한다.
        return ConnetedYeomsos.Count == 0;
    }
}


public class Yeomso_Race : Yeomso_Dependent
{
    public ERace Race { get; set; }

    public Yeomso_Race()
        : base(EYeomsoType.RACE)
    {

    }
}