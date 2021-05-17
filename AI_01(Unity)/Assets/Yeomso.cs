using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// 생각/사고/상념/지식/개념 을 이루는 가장 작은 형태
/// 염소가 연결되고 모여서 생각이 만들어 진다고 가정하고 있다.
/// 일단 염소를 연결, 분류된 그래프로 만들 생각이다.
/// </summary>
public class Yeomso
{
    /// <summary>
    /// 일단 염소는 한개의 타입만은 가진다고 가정한다.
    /// 실제로 속성적인 측면에서는 여러개를 가질 수도 있다.
    /// </summary>
    public EYeomsoType Type { get;}

    /// <summary>
    /// 일단 단순하게 관계가 있는 모든 염소들을 연결시켜서 생각해보자.
    /// 어쩌면 관계에 대한 설명이 필요할 지도 모르지만, 현재는 생략한다.
    /// 그리고 이 연결이 쌍방인지, 계층이 있는지 이런 문제도 있다.
    /// 우선 기본적으로 쌍방 연결을 하는 것으로 해서 만든다.
    /// 그러므로 새로운 노드 추가는 메서드를 통해 처리하는 것으로 하자.
    /// 아니 변경이 불가하게 노출하는게 좋을 것 같다.
    /// </summary>
    public List<Yeomso> ConnetedYeomsos { get; } = new List<Yeomso>();

    public Yeomso(EYeomsoType type)
    {
        Type = type;
    }

    public void InsertYeomso(Yeomso yeomso)
    {
        if (yeomso == null)
        {
            Debug.Log("Yeomso.InsertYeomso : yeomso == null!!");
        }

        if (ConnetedYeomsos.Contains(yeomso))
        {
            Debug.Log("Yeomso.InsertYeomso : 이미 연결되어있음.");
            return;
        }

        ConnetedYeomsos.Add(yeomso);
    }

    public void ConnectYeomso(Yeomso yeomso)
    {
        Yeomso.ConnectYeomso(this, yeomso);
    }

    static public void ConnectYeomso(Yeomso yeomso1, Yeomso yeomso2)
    {
        if (yeomso1 == null || yeomso2 == null)
        {
            Debug.Log("Yeomso.ConnectYeomso : yeomso == null!!");
        }

        if (yeomso1.ConnetedYeomsos.Contains(yeomso2))
        {
            Debug.Log("Yeomso.ConnectYeomso : 이미 연결되어있음.");
            return;
        }

        yeomso1.ConnetedYeomsos.Add(yeomso2);
        yeomso2.ConnetedYeomsos.Add(yeomso1);
    }
}

/// <summary>
/// 염소가 나타내는 정보(최소 개념,생각등)를 구분하기 위한 분류
/// 염소의 속성이라고도 볼 수 있다. 하나의 염소는 여러 가지 타입/속성을 가질 수 있는가?
/// 일단은 열거형으로 나타내지만, 이것도 하나의 정보/개념/지식에 속한다고 볼 수있다.
/// </summary>
public enum EYeomsoType
{
    UNKNOWN,
    ENTITY,
    BEHAVIOR,
    ACTION,
    ACTION_STATE,
    LOCATION,
    SHAPE,
    TIME,
    OBJECT,
    RACE,

}
