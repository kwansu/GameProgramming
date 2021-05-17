using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Property_Base
{
    public EProperty_Type PropertyType { get; } = EProperty_Type.Undefined;

    public Property_Base(EProperty_Type type)
    {
        PropertyType = type;
    }
}

public enum EProperty_Type
{
    Undefined,
    Ye_Time,
    Data,
    Int,
    Float,
    Vector3,
    Owner, //소유자 = 주체 인가? 주체(subject)를 따로 만들어야하는가?
    ActionState,
    Race,
    Cause,
    Variation,
    Purpose,
}