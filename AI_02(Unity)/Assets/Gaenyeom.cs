using System;
using System.Collections.Generic;

/// <summary>
/// 일부러 Concept이 아니 개념이라고 이름 지었다. 조금 더 그 의미가 접합하다고 생각되고,
/// 개념의 인스턴스로 만들어지는 염소(Yeomso)도 연관되어 있기 때문이다.
/// </summary>
public class Gaenyeom
{
    protected GaenyeomTypeNumber typeNumber;

    protected Gaenyeom()
    {

    }

    virtual public Gaenyeom CreateGaenyeom()
    {
        return null;
    }

    public struct GaenyeomTypeNumber
    {
        static int typeCount = 0;

        int typeID;

        static GaenyeomTypeNumber()
        {
            typeCount = (int)EGaenyeomTypePreset.Last + 1;
        }

        public int RegisterNewType()
        {
            return typeCount++;
        }

        public static implicit operator int(GaenyeomTypeNumber typeNumber)
        {
            return typeNumber.typeID;
        }

        public static implicit operator GaenyeomTypeNumber(int typeNumber)
        {
            return new GaenyeomTypeNumber { typeID = typeNumber };
        }

        public static implicit operator GaenyeomTypeNumber(EGaenyeomTypePreset preset)
        {
            return new GaenyeomTypeNumber { typeID = (int)preset };
        }
    }

    /// <summary>
    /// 미리 정의해야하는 개념들의 타입.
    /// 일단 기본적인 세계관을 형성하고 이해하기 위해서는 게임 세상의 법칙과
    /// 현재 게임 세상에서 캐릭터가 관찰하고, 인식하고, 이용할 수 있는 모든 수치와
    /// 기능들을 알고 있어야한다.
    /// 물론, 이 기초적인 개념들도 주관적인 것으로 경험이나 논리적 고찰등을 통해서
    /// 얼마든지 수정될 수 있게 만들어야 할 것이다.
    /// 즉, 기초 개념이란 절대적인 지식이 아니라, 세대를 거친 경험과 적응 등을 통해
    /// 만들어진 본능같은 것이다. 이게 항상 옳다고 는 할 수없다.
    /// 그저 현재 세상을 이해하는데 기초적인 지식들을 본능처럼 미리 만들어 놓는것이다.
    /// 여기에는 값,선,물체와 같은 기초적인 것부터 인지,관찰,보다,이동 처럼 개인의
    /// 행동이나 사고/생각에서만 존재하는 것들까지 방금 만들어진 캐릭터가 세상을
    /// 받아들이고 이해하는데 필요한 필수적인 것들을 모두 정의한다.
    /// 당연히 캐릭터가 게임세상에서 인지 할 수 있는 정보들(생명력,힘,속도,장비정보,
    /// 그룹정보,주거지의 수치들 등) 또한 모두 정의 되어야한다.
    /// </summary>
    public enum EGaenyeomTypePreset
    {
        Error,
        Object,
        Value,
        Field,
        Position,
        Shape, //Form,Model 2차원 필드에서 시야에 보이는 것. 모양이나 형태를 가진것(점,선,다각형). 캐릭터 생김새와는 다른것.
        Point,
        Line,
        Polygon, //필드는 다각형 환경으로 이루어져 있다. 그리고 필드오브젝트도 다각형일수 있다.(주거지/성/도시/마을등)
        Area, //환경을 나타내는데는 다각형으로 충분할것 같지만 혹시 몰라서 넣었다.
        Environment,
        FieldObject,

        Eat,

        Last
    }
}


