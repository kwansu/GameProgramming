using System;
using System.Collections.Generic;
using UnityEngine;

public struct YeomsoTypeNumber
{
    private static Dictionary<Type, int> hashRegisteredTypes = new Dictionary<Type, int>();
    private static Dictionary<int, Type> debugValue = new Dictionary<int, Type>();
    private static int typeCount;

    private int typeNumber;

    static YeomsoTypeNumber()
    {
        typeCount = (int)EYeomsoType.LastType;
    }

    public static implicit operator int(YeomsoTypeNumber data)
    {
        return data.typeNumber;
    }

    public static implicit operator YeomsoTypeNumber(int data)
    {
        YeomsoTypeNumber result;
        result.typeNumber = data;

        return result;
    }

    public static implicit operator YeomsoTypeNumber(EYeomsoType eType)
    {
        YeomsoTypeNumber result;
        result.typeNumber = (int)eType;

        return result;
    }

    public static implicit operator EYeomsoType(YeomsoTypeNumber data)
    {
        return (EYeomsoType)data.typeNumber;
    }

    public override int GetHashCode()
    {
        return typeNumber;
    }

    /// <summary>
    /// 존재하지 않는 타입(key)일 경우 -1을 리턴한다.
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    public static YeomsoTypeNumber GetTypeNumber(Type type)
    {
        if (hashRegisteredTypes.ContainsKey(type) == false )
        {
            return EYeomsoType.Null;
        }

        return hashRegisteredTypes[type];
    }

    public static int RegisterYeomsoType(Type type)
    {
        if (type == null || type.IsAssignableFrom(typeof(Yeomso_Frame)) == false)
        {
            Debug.DebugBreak();
        }

        if (hashRegisteredTypes.ContainsKey(type) == false)
        {
            Debug.DebugBreak();
        }

        debugValue.Add(typeCount, type);
        hashRegisteredTypes.Add(type, typeCount);

        return typeCount++;
    }

    public void DebugLogType()
    {
        if (debugValue.ContainsKey(typeNumber) == false)
        {
            Debug.Log("hash count : " + debugValue.Count);
            Debug.Log(typeNumber);
            return;
        }

        Debug.Log(debugValue[typeNumber]);
    }

    public enum EYeomsoType
    {
        Error,
        Null,
        Undefined,
        Time,
        Entity,

        LastType
    }
}
