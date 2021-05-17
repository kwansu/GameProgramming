using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// 행동/목적/의도/원인 등을 나타내기 위한 요소.
/// 생각/상념을 나타내기 위한 염소와 비슷하다. 일단은 사용되는 목적이 다른것 같아 나누지만,
/// 알고보면 두 가지는 완전 같은 것이 수도 있다. 물론, 다를 수도 있지만, 지금 같이 따로
/// 나누어진 클래스가 아니라 공통된 부분이 있다는 것만은 분명 할 것이다.
/// 처음 이름으로는 '개념소'라고 지을려고 했지만, 영문인 'Gaenyeomso'라는게 왠지 마음에 안들어
/// 일단 관소(kwanso)라고 하지만, 좀 아닌 것 같으면 concept(이건 너무 포괄적이고 이 클래스와
/// 어울리지 않는것같다.)은 단어를 생각해보자.
/// </summary>
public class Kwanso
{
    /// <summary>
    /// 일단 개념소 자체가 얼마든지 새롭게 생성 될 수 있고, 나중에는 학습을 통해 새로운
    /// 개념을 만들어서 자체적으로 추가하는 기능이 있을 수 있지만, 기본적으로 사람이 만든것의
    /// 의미를 쉽게 알아볼 수 있게 한글이나, 영어로 대강의 뜻을 이름으로 붙이자.
    /// 새로 생성된 것은 '새로 생섬됨'이나 '이동 + 은밀'처럼 어떤 의미를 내포하는지 알 수있게
    /// 이름이 만들어지도록 하는게 좋을 것이다.
    /// </summary>
    public string Name { get; }
    public int KwansoID { get; }
    private static int idCount = 0;

    /// <summary>
    /// 이 개념소가 가지고?(연상되는?) 있는 구성요소.
    /// 구성요소라는 의미에서 Component를 뜻 할 수도 있지만, 기본적으로 이건 개념의 관계이기에
    /// 소유 하는게 아니라, 연관되어서 그 개념에서 떠올릴 수 있는 것이다.
    /// 예를 들자면 사람,토끼,새 등은 위치와 다리를 가지고 있다고 할 수 있다.
    /// 하지만, 그 반대로 위치와 다리라는 개념에서는 사람/토끼/새 등을 떠올릴 수 없다.
    /// 굳이 다리가 있는 독립체를 생각한다면, 알고 있는 독립체를 하나하나 검색/탐색해야 할 것이다.
    /// </summary>
    private List<Kwanso> CompositionKwansoList { get; set; } = null;

    // 사실 이 소유 관계 없는 것도 생각해 봤지만, 일단 사용해보고, 필요없으면 없애자.
    public Kwanso OwnerKwanso { get; } = null;

    public Kwanso(string name, Kwanso ownerKwanso = null)
    {
        KwansoID = idCount;
        idCount++;

        Name = name;

        OwnerKwanso = ownerKwanso;
    }

    public void AddCompositionKwanso(Kwanso compositionKwanso)
    {
        if (CompositionKwansoList == null)
        {
            CompositionKwansoList = new List<Kwanso>();
        }

        if (CompositionKwansoList.Contains(compositionKwanso) == true)
        {
            Debug.Log("Kwanso.AddCompositionKwanso : 이미 있는데, 또 추가 하려고 하네.");
            return;
        }

        CompositionKwansoList.Add(compositionKwanso);
    }
}