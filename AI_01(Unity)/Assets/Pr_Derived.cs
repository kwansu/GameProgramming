using System;
using System.Collections.Generic;
using UnityEngine;

public class Pr_Time : Property_Base
{
    public Ye_Time Ye_Time { get; set; }
    public Pr_Time() : base(EProperty_Type.Ye_Time) { }
    public Pr_Time(Ye_Time ye_Time) : base(EProperty_Type.Ye_Time)
    {
        Ye_Time = ye_Time;
    }
}

public sealed class DataTypeNumber
{
    public static DataTypeNumber Singleton_Instance { get; } = new DataTypeNumber();

    private int typeNumber = 0;
    private Dictionary<Type, int> hashData = new Dictionary<Type, int>();

    public int this[Type type]
    {
        get
        {
            if (hashData.ContainsKey(type) == false)
            {
                hashData.Add(type, typeNumber);
                ++typeNumber;
            }

            return hashData[type];
        }
    }

    private DataTypeNumber() { }
}

/// <summary>
/// 함축/복합 염소에서 변화/결과를 나타내기 위해서는 두 가지 이상의 같은 종류의 데이터가 필요하다.
/// 데이터 값을 가진 프로퍼티가 현재 제너릭 클래스로 만들어져 있어서 그것들을 함축/복합 염소에 담기 위해서 사용한다.
/// 대표적으로 Pr_Variation에 사용된다.
/// </summary>
public abstract class Pr_Data : Property_Base
{
    protected Pr_Data(EProperty_Type type = EProperty_Type.Data) : base(type)
    {

    }
}

public class Pr_Data<T> : Pr_Data
{
    //static protected EProperty_Type basePropertyType = EProperty_Type.Data;
    static public int TypeNumber { get; private set; }

    public T Data { get; set; }

    static Pr_Data()
    {
        TypeNumber = DataTypeNumber.Singleton_Instance[typeof(T)];
    }
    //public Pr_Data() : base(basePropertyType) { }
    //public Pr_Data(T data) : base(basePropertyType)
    //{
    //    Data = data;
    //}
}

public class Pr_Owner : Property_Base
{
    public Yeomso_Base Ye_Owner { get; set; }
    public Pr_Owner() : base(EProperty_Type.Owner) { }
    public Pr_Owner(Yeomso_Base owner) : base(EProperty_Type.Owner)
    {
        Ye_Owner = owner;
    }
}

//public class Pr_Vector3 : Pr_Data<Vector3>
//{
//    static Pr_Vector3()
//    {
//        basePropertyType = EProperty_Type.Vector3;
//    }
//}

//public class Pr_ActionState : Pr_Data<EActionState>
//{
//    static Pr_ActionState()
//    {
//        basePropertyType = EProperty_Type.ActionState;
//    }
//}

//public class Pr_Race : Pr_Data<ERace>
//{
//    static Pr_Race()
//    {
//        basePropertyType = EProperty_Type.Race;
//    }
//}

public class Pr_Cause : Property_Base
{
    public struct CauseInfo
    {
        public Yeomso_Base Ye_cause;
        public float weight;
    }

    private List<CauseInfo> causes = null;
    public List<CauseInfo> Causes
    {
        get
        {
            if (causes == null)
            {
                causes = new List<CauseInfo>();
            }
            return causes;
        }
    }

    public Pr_Cause() : base(EProperty_Type.Cause) { }
    public void AddCause(Yeomso_Base ye_cause)
    {
        // 실제로는 추가된 염소가 얼마나 이 염소의 원인에 영향을 끼치는지 판단하여
        // 그에 따른 가중치를 구해서 총 가중치가 1.0이 되도록 하여야한다.
        // 하지만, 현재는 여러가지 원인을 가지는 상황이 없으므로 그냥 구현하지 않았다.
        CauseInfo info;
        info.Ye_cause = ye_cause;
        info.weight = 1.0f;

        causes.Add(info);
    }
}

public class Pr_Variation : Property_Base
{
    public Pr_Data IVariationType { get; set; }

    public Ye_Dependent Ye_previousData;
    public Ye_Dependent Ye_FocusData;

    public Pr_Variation() : base(EProperty_Type.Variation) { }
}