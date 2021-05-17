using System;
using UnityEngine;

public class Condition_Prerequisite
{
    public ECondition_Type ConditionType { get; protected set; }

    public Condition_Prerequisite(ECondition_Type type = ECondition_Type.Undifined)
    {
        ConditionType = type;
    }

    public virtual bool SatisfyCondition(Ye_Dependent ye_target)
    {
        return false;
    }

    public virtual bool SatisfyCondition2(Ye_Dependent ye_main, Ye_Dependent ye_reference)
    {
        return false;
    }
}

public enum ECondition_Type
{
    Undifined,
    YeomsoType,
    Data,
}

public enum ERelationalOperator
{
    Equal,
    Not_Equal,
    Less,
    Greater,
    Less_Equal,
    Greater_Equal,
}

public class Condition_YeomsoType : Condition_Prerequisite
{
    /// <summary>
    /// 현재는 염소 자체의 타입을 받지만, 실제로는 염소에 포함된 구성요소(property)를
    /// 가지고 있는지를 확인하고, 비교하는게 더 좋을 것이다.
    /// 그리고 set부분에서는 특정 클래스(ye_depedent)의 파생 클래스인지 확인하는 코드를 추가하면 좋을듯.
    /// </summary>
    public Type Type_Yeomso { get; private set; }

    public Condition_YeomsoType(Type type_ye)
        : base(ECondition_Type.YeomsoType)
    {
        Type_Yeomso = type_ye;
    }

    public override bool SatisfyCondition(Ye_Dependent ye_target)
    {
        return (ye_target.GetType() == Type_Yeomso);
    }
}

public class Condition_Data<T> : Condition_Prerequisite where T : IComparable<T>
{
    public int TypeNumber { get; private set; }

    public Pr_Data<T> Pr_MainData { get; set; }
    public T ReferenceData { get; set; }
    public ERelationalOperator RelationOperator { get; set; }

    public Condition_Data() : base(ECondition_Type.Data)
    {
        TypeNumber = DataTypeNumber.Singleton_Instance[typeof(T)];
    }

    public override bool SatisfyCondition2(Ye_Dependent ye_main, Ye_Dependent ye_reference)
    {
        T main = ReferenceData, reference =ReferenceData;

        switch (RelationOperator)
        {
            case ERelationalOperator.Equal:
                return main.CompareTo(reference) == 0;
            case ERelationalOperator.Greater:
                return main.CompareTo(reference) == 1;
            case ERelationalOperator.Greater_Equal:
                return main.CompareTo(reference) >= 0;
            case ERelationalOperator.Less:
                return main.CompareTo(reference) == -1;
            case ERelationalOperator.Less_Equal:
                return main.CompareTo(reference) <= 0;
            case ERelationalOperator.Not_Equal:
                return main.CompareTo(reference) != 0;
        }

        Debug.LogError("뭔가 잘못됨.");

        return false;
    }
}