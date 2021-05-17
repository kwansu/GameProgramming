using UnityEngine;
using System.Collections.Generic;
using UnityEditor.Experimental.UIElements.GraphView;

public class Ye_Time : Yeomso_Frame
{
    public float Time { get; }

    public Ye_Time(float time)
        : base(YeomsoTypeNumber.EYeomsoType.Time)
    {
        Time = time;
    }
}

public class BehaviourOverTime
{
    private Dictionary<BehaviorTypeNumber, Ye_Dependent> hash_Behaviors = null;

    /// <summary>
    /// 독립체 염소가 시간당 하나의 행동집합체(BehaviorOverTime)을 가지고 있고,
    /// 행동집합체에서는 중복되는 행동이 없다고 가정하고 사용한다.
    /// 중복되는 행동타입이 없으면 해쉬에서 키로 int를 사용하면 성능도 괜찮을 것이다.
    /// 나중에 SortedList와의 성능 비교를 한번 해보는 것이 좋을 것이다.
    /// </summary>
    public Dictionary<BehaviorTypeNumber, Ye_Dependent> Hash_Behaviors
    {
        get
        {
            if (hash_Behaviors == null)
            {
                hash_Behaviors = new Dictionary<BehaviorTypeNumber, Ye_Dependent>();
            }
            return hash_Behaviors;
        }
    }
    public Ye_Time Ye_time { get; set; }
}

public class YeomsosPerTime
{
    /// <summary>
    /// 현재는 해쉬(딕셔너리)의 생성을 미리 해놓지만, 해쉬의 초기 크기를 어느정도 잡아 놓은 뒤 생성하는게
    /// 이후에 추가하는 시간을 줄일 수 있을 것이다. 이전 시간의 시간당 염소집합체의 해쉬크기를 참고하면 좋을 것이다.
    /// </summary>
    public Dictionary<YeomsoTypeNumber, Ye_Dependent> Hash_Yeomsos { get; }
        = new Dictionary<YeomsoTypeNumber, Ye_Dependent>();

    public void Add(Ye_Dependent ye_target)
    {
        Hash_Yeomsos.Add(YeomsoTypeNumber.GetTypeNumber(ye_target.GetType()), ye_target);
    }
}

public class Ye_Entity : Yeomso_Base
{
    public Entity RealEntity;
    public Ye_Position Ye_position { get; set; }
    public Ye_ActionState Ye_actionState { get; set; }

    public Ye_Move Ye_move { get; set; }
    public Ye_Action Ye_action { get; set; }

    public Ye_Race Race { get; set; }

    /// <summary>
    /// 한정된 길이(변화의 최대 기억갯수)에서 최근 기억이 들어오면,
    /// 가장 오래된 기억이 사라지는 형태로 서클 버퍼를 이용하는게 좋을 것 같다.
    /// 다만, 현재 기본 콜렉션에는 deque가 없어서 임시로 링크리스트를 사용한다.
    /// </summary>
    public LinkedList<YeomsosPerTime> ListYeomsosPerTime { get; } = new LinkedList<YeomsosPerTime>();
    public YeomsosPerTime RecentYeomsos
    {
        get
        {
            if (ListYeomsosPerTime.Count == 0)
            {
                return null;
            }

            return ListYeomsosPerTime.Last.Value;
        }
    }

    public Ye_Entity(Entity entity)
        : base(YeomsoTypeNumber.EYeomsoType.Entity)
    {
        RealEntity = entity;
    }

    public bool IsFirstJudgmentEvaluation()
    {
        return ListYeomsosPerTime.Count == 0;
    }
}

public class Ye_Dependent : Yeomso_Base
{
    public Yeomso_Base Owner { get; set; }
    public Ye_Time Time { get; set; }

    public Ye_Dependent() : base(YeomsoTypeNumber.EYeomsoType.Undefined) { Initialize(); }

    public Ye_Dependent(YeomsoTypeNumber typeNumber) : base(typeNumber) { Initialize(); }

    private void Initialize()
    {
        Properties.Add(new Pr_Time());
        Properties.Add(new Pr_Owner());
    }

    public void Setup(DependentYeomsoSetupStruct data)
    {
        if (data.owner == null || data.time == null)
        {
            Debug.Log("빈 자료로 초기화 시도.");
        }

        Owner = data.owner;
        Time = data.time;
    }
}

public struct DependentYeomsoSetupStruct
{
    public Yeomso_Base owner;
    public Ye_Time time;
}

public class Ye_Continuity<T> : Ye_Dependent where T : Ye_Continuity<T>
{
    // 연결 리스트 처럼 구성한다.
    public T Ye_previous { get; set; }
    public Ye_Continuity<T> Ye_next { get; set; }

    public Ye_Continuity() : base(YeomsoTypeNumber.EYeomsoType.Undefined) { }

    public void LinkPreviouYeomso(T previous)
    {
        if (previous == null || Ye_previous != null || previous.Ye_next != null)
        {
            Debug.Log("뭔가 잘못됬음2");
        }

        Ye_previous = previous;
        previous.Ye_next = this;
    }
}


public class Ye_Position : Ye_Continuity<Ye_Position>
{
    public Vector3 Pos { get; set; }
}

public class Ye_ActionState : Ye_Continuity<Ye_ActionState>
{
    public EActionState State { get; set; }
}

public class Ye_Race : Ye_Continuity<Ye_Race>
{
    public ERace Race { get; set; }
}


public class Ye_Implication : Yeomso_Base
{
    public Ye_Time Ye_previousTime { get; set; }
    public Ye_Time Ye_focusTime { get; set; }
    public Pr_Cause Pr_Cause { get; }
}

public class Ye_Move : Ye_Dependent
{
    public bool IsMove { get; set; }
    public Ye_Time Ye_previousTime { get; set; }
    public Ye_Time Ye_focusTime { get; set; }

    public Vector3 DirectionMove { get; set; }

    public Pr_Variation Pr_VariationPos { get; set; } = new Pr_Variation();
}

public class Ye_Action : Ye_Dependent
{
    public EActionState ActionState { get; set; }
    public Ye_Time Ye_previousTime { get; set; }
    public Ye_Time Ye_focusTime { get; set; }

    public Pr_Variation Pr_VariationAction { get; set; } = new Pr_Variation();
}

public class Ye_Walk : Ye_Dependent
{

}