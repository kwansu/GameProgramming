using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Yeomso_Frame
{
    private static int num_Ye = 0;

    private readonly int id_Number;

    public YeomsoTypeNumber TypeNumber { get; set; }
    public UI_Yeomso UIYeomso { get; set; }

    public Yeomso_Frame(YeomsoTypeNumber typeNumber)
    {
        if (YeomsoTypeNumber.GetTypeNumber(this.GetType()) == YeomsoTypeNumber.EYeomsoType.Null)
        {
            YeomsoTypeNumber.RegisterYeomsoType(this.GetType());
        }

        id_Number = num_Ye;
        num_Ye++;

        TypeNumber = typeNumber;
    }
}

/// <summary>
/// 실제로 염소가 어떻게 사용되는지를 생각해봐야한다.
/// 1.우선 시간을 나타내는 염소가 있어야한다. 이걸 염소라고 불러야하는지 조차도 애매하지만,
/// 어째든 상념속 시간을 나타내는 절대적인 지표가 필요하다. 그 시간에 다른 염소들이 연결될텐데,
/// 그게 시간에서 다른 염소를 검색 할 수 있는지 어떤지 그런건 아직 정해지지 않았다.
/// 2.두번째로 객체/인스턴스/독립체를 나타내는 염소가 필요하다. 이 염소가 시간에 종속될 필요는
/// 없지만, 종속되더라도 크게 문제는 없을 것이다. 중요한건 이 염소는 하나의 독립체에 대한
/// 관찰자의 생각의 집합체라는 것이다.
/// 여기서 갑자기 떠오른 의문은 독립체에 대한 관찰정보나 행동들이 그 독립체 염소에 종속된 염소
/// 집합이라는것은 이해가지만, 그 물체에 대한 관찰자의 개인적인 감정이나, 연관성등은 어떻게
/// 연결되어야 하는지 헷갈린다. 이건 나중에 여러 물체의 복합된 상황을 연속된 상념으로 구현하면서
/// 정하는게 좋을 듯 싶다.
/// 3.시간과 독립체 염소에 종속된 염소들이다. 쉽게 말해 관찰중인 독립체에 대한 관찰자의 생각을
/// 시간에 따라 나열한 것이라고 볼 수 있다. 위치, 행동, 의도, 목표, 성격, 관심등이 전부
/// 여기에 포함 될 것이다. 한가지 나눌 수 있는 부분은 시간에 연속된 것인지 아닌지 여부 일 것이다.
/// 위치, 액션, 모습등 기본적인 관찰정보는 시간에 연속적이다. 즉 관찰되는 내내 각 시간에서
/// 변화하는 순간이 연결된 리스트라고 볼 수있다. 하지만, 행동, 의도 처럼 기본정보로 부터
/// 유추해낸 주관적인 염소들은 매 시간마다 존재야 하겠지만, 이게 시간에서 연속되게 연결 될 수 
/// 있는지는 알 수 없다. 일단은 기본적인 관찰정보, 즉 원초적 정보와 주관이 들어가서 해석된
/// 가공 정보를 나누어서 구분짓는거로 생각해야 겠다. 3_1:원초적/관찰 정보 , 3_2:가공/주관 정보
/// 
/// 4.컴포넌트형으로 관리. 이전 염소와는 다르게 구성요소와 연결염소를 나누어서 구분한다.
/// 한 염소에서 특정 값들을 나타내는 구성요소(property)를 따로 만들어서 리스트로 관리한다.
/// 그 외 연결된 염소들은 따로 리스트로 모아서 관리한다고 가정하자.
/// </summary>
public class Yeomso_Base : Yeomso_Frame
{
    public Yeomso_Base(YeomsoTypeNumber typeNumber) : base(typeNumber) { }
    public Yeomso_Base() : base(YeomsoTypeNumber.EYeomsoType.Error) { }

    private List<Property_Base> properties = null;
    public List<Property_Base> Properties
    {
        get
        {
            if (properties == null)
            {
                properties = new List<Property_Base>();
            }
            return properties;
        }
    }
}

