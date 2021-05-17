using System;
using System.Collections.Generic;
using UnityEngine;
using ConceptList = System.Collections.Generic.List<Concept>;

public class TemporaryAI : MonoBehaviour
{
    public UIManager_Thought UIManager;

    // Situation객체가 가질 필드다.
    LinkedList<SituationObject> SituationObjects { get; } = new LinkedList<SituationObject>();

    LinkedList<Entity> ObservedEntities { get; } = new LinkedList<Entity>();
    /// 이 객체들은 매 프레임마다 추가되고 비워지고 반복되므로,
    /// 나중에는 벡터로 만들어 실제 메모리공간을 비우지 않게 하는게 좋을것 같다.
    LinkedList<Entity> EnterObservedEntities { get; } = new LinkedList<Entity>();
    LinkedList<Entity> ExitObservedEntities { get; } = new LinkedList<Entity>();


    /// 현재 생각/상념을 나타내는 염소들의 저장공간(storage,bank)
    /// 염소들은 직/간접적으로 연결된 그래프지만 추가/삭제가 많을 것으로 예상되므로
    /// 배열화된 링크드리스트로 관리하는게 좋을 것 같다.(어디까지나 추측)
    /// 일단은 성능에 관계없으므로 그냥 링크드리스트로 만들어서 관리한다.
    /// 이건 단순한 저장공간일 뿐이므로 상념/생각(Thought)보다는 저장공간으로 이름을 지었다.
    LinkedList<Yeomso> YeomsosStorage { get; } = new LinkedList<Yeomso>();

    /// <summary>
    /// 관찰자가 가지고 있는 개념소들을 보관하기 위한 저장공간.
    /// 행/목/의/원을 나타내기 위한 지식/개념 자체는 개념소들의 관계 그래프로 만들어 지지만,
    /// 일단 생성된 개념소 자체는 이 곳에 배열처럼 보관된다.
    /// 염소와는 달리 새롭게 생성되고, 관계자체는 변하더라도 기존의 개념소가 삭제되는 경우는
    /// 별로 없을 것이라 판단하여 리스트를 사용하였다.
    /// </summary>
    List<Kwanso> KwansosStorage { get; } = new List<Kwanso>();


    // 단기기억/상황/상념 을 구현하기 위해 필요한 염소들 저장공간 분류? 핵심은 Thought(상념/생각)의 구현

    /// 단기기억에서 변화가 감지된 순간을 시간순으로 연결해서 관리한다.
    /// 첫번째가 가장 최근이라고 정의한다.
    LinkedList<Yeomso> ThoughtTimeTable { get; } = new LinkedList<Yeomso>();
    LinkedList<Yeomso_Object> ThoughtObjectsTable { get; } = new LinkedList<Yeomso_Object>();


    // revision된 염소로 구성된 저장공간
    LinkedList<Ye_Time> StorageTimeTable { get; } = new LinkedList<Ye_Time>();
    LinkedList<Ye_Entity> StorageEntitiesTable { get; } = new LinkedList<Ye_Entity>();

    /// <summary>
    /// 장기기억/경험/지식/상식 등을 구현하기 위해 보관하는 저장공간
    /// 일단은 언어적/관념적 표현과 구분을 떠나서 전부 '개념'이라는 것으로 이루어진 하나의 저장공간에 보관한다.
    /// 현재 기억에서 검색하는 것은 'action' 단 한종류 이므로 키가 행위로 이루어진 해쉬테이블을 사용한다.
    /// </summary>
    public Dictionary<EActionState, ConceptList> ConceptMemory { get; } = new Dictionary<EActionState, ConceptList>();

    void Start()
    {
        // 초기 생각/상념 배치
        Thought_Setup2();
    }

    /// <summary>
    /// 상황에 따른 생각의 변화를 구현하고, 생각을 전체적인 모델을 완성하기 위해서는
    /// 기본적으로 어느정도 생각이 만들어져 있어야한다.
    /// 즉, Setup이 필요하다. 따로, 초기 생각구성을 위한 장치를 만들지 않고,
    /// 편의상 이 곳에서 모든 초기 생각구성을 완성시킨다.
    /// </summary>
    void Thought_Setup()
    {
        /// 어디서 부터 어느 정도까지 그래프를 만들어 놓아야 하는지 모르겠다.
        /// 그렇다면, 우선 어느정도 상념이 구성돼 있다고 가정하고 시야에 새로운 단일체가
        /// 들어오는 순간에 생겨날 염소들에 대해 구현해보자.

        // 임시로 기본적인 염소 그래프(생각/상념)이 만들어져 있다고 가정한다.
        Yeomso yeomso_base_graph = new Yeomso(EYeomsoType.UNKNOWN);

        /// 일단 기존 염소 그래프가 상념이라는 형태라면 새로운 변화에 대한 반응은 
        /// 곧바로 기존 그래프에서 추가되는 형태일 수도 있지만,
        /// 일단은 새로운 염소 그래프를 만들어서 연결한다고 가정하고 만들어보자.

        /// '발견/관찰됨/나타남'같은 형태의 염소가 먼저 나와야 하지 않을까?
        /// 그렇다면 '발견/나타남'의 염소는 무슨 타입인가? 아니 어떻게 구성돼 있는가?

        // 새로운 독립체(토끼)를 발견함 -> 트리 노드
        Yeomso yeomso_discover_entity = new Yeomso(EYeomsoType.UNKNOWN);

        /// 독립체에 대한 발견은 감지처리에서 어느정도 판별이 나서 오는가?
        /// 아니면, 여기서 판/평을 거쳐서 새로운 것이 entity라는 것을 찾아내는가?
        /// 애초에 새로운 물체 감지에서 entity외의 것을 발견 할 수가 있나?
        /// 예를 들면 해결법이나, 새로운 개념의 발견같은것?
        /// 생각해보면 정해진 게임 월드에서 독립체는 독립체와 지형 두가지 만 발견 가능한것 같다.
        /// 그렇다면 일반적으로 감지/관측에서 얻을 수 있는 정보는 '지형발견'과 '독립체발견'
        /// 만 가능하다고 법칙 설정을 해놓는 것도 하나의 방법일 것이다.

        /// 그래서 발견한 독립체('토끼'지만 관찰자는 모르는 처음보는 생명체라고 가정)에 대한
        /// 정보를 어디에 어떻게 염소 그래프에 추가 할 것인가?
        /// 당장 독립체에 대해 표현하기 위해 생각나는 염소들은
        /// '위치(fuzzy)', '형태/생김새', '행위(action)', '속도(추측/fuzzy)', '질량', '행동'
        /// 여기서 '행동(behavior)'등은 곧바로 알 수 있는게 아니라,
        /// 시간을 두고 추측/추론등을 해야한다.
        /// 그에 반해 물체(entity)를 나타내기 위해선 '위치', '형태', '행위'는 필수라고 할 수있다.

        /// 그렇다면 위의 물체를 나타내는 속성?등의 염소들을 어떻게 연결/구성 할 것인가?
        /// 단순하게 독립체에 위의 속성들이 연결되어 있다고 가정하자.
        /// 실제로 염소하나에는 여러개의 정보/염소들이 연결 될 수 있을 것이다.
        /// 중요한건 그 연결이 된 '관계'이다.
        /// 연결을 어떻게 시킬 것인가? 단순히 그래프로 생각할 수도 있지만,
        /// 이게 생각/상념이 되기 위해선 그 연결들 사이의 관계를 알 수 있어야 할 것 같다.

        /// 왜 '관계'가 중요하다고 생각 되는 걸까? 그리고 정말 중요할까?
        /// 어떤 독립체에 연결된 '위치','형태'등의 정보는 결국 그 독립체에 대한 정보라는 것을
        /// 굳이 설명하지 않아도 알 수 있지않나?
        /// 그렇다면 단순히 연관된 것을 그래프처럼 연결만 하는 방법을 사용해보고, 문제가 있으면
        /// 고치면 되는것 아닌가.

        Yeomso yeomso_entity = new Yeomso(EYeomsoType.ENTITY);

        Yeomso.ConnectYeomso(yeomso_entity, yeomso_discover_entity);

        // 위치, 형태, 행위에 대한 정보/염소는 관측을 통해 생성되었다고 가정하자.
        Yeomso yeomso_point = new Yeomso(EYeomsoType.LOCATION);
        Yeomso yeomso_shape = new Yeomso(EYeomsoType.SHAPE);
        Yeomso yeomso_action = new Yeomso(EYeomsoType.ACTION_STATE);

        Yeomso.ConnectYeomso(yeomso_entity, yeomso_point);
        Yeomso.ConnectYeomso(yeomso_entity, yeomso_shape);
        Yeomso.ConnectYeomso(yeomso_entity, yeomso_action);

        Yeomso yeomso_not_memory = new Yeomso(EYeomsoType.UNKNOWN);

        /// 위의 처음봄/기억없음/정보없음 등을 나타내는 염소가 있다.
        /// 문제는 저 염소가 어떻게 그런것을 나타내는지 알 수가 없다는 것이다.
        /// 결국 염소를 나타내기 위해선 타입처럼 뭔가 나타내는 정보가 필요한데,
        /// 독립체가 살아가면서 새로운 타입의 염소가 나타나지 않을까?
        /// 아니면 정말 기본적인 염소들(대충 3자리 수 예상)로 모든 정보/상념/생각을 표현할수 있나?

        Yeomso.ConnectYeomso(yeomso_entity, yeomso_not_memory);

        /// 자, 이제 나름 주관적인 정보를 그래프로서 연결했다.
        /// 그래서 이게 생각/사고/상념 이라고 할 수 있나?
        /// 뭘 해야지 상황을 이해/해석 하고 생각/상념 할 수 있다고 할 수 있을까?
        /// 애초에 무슨 생각/상념을 해야하는지도 모르겠다. 결과를 모르는데 만들어 질 수가 있나.
        /// 만약 내가 관찰자라면, 그 순간 무슨 생각/상념을 하고 있을까?
        /// 아무 생각없이 어느 곳을 보고 있는데, 시야의 끝에서 갑자기 처음보는 생물이
        /// 나타나서 걸어다닌다. 시야에서 생물이 나타나는 순간부터 어떤 생각이 어떤 순서로 드는가?
        /// "어, 저건 뭐지?" -> "???(관찰/검색/판/평 중)" -> "뭐랑 비슷하네 / ~보이네(곁생각들)"
        /// "어, 움직이네" -> "느리네 / ~어떻네(곁생각/감상들)" -> "그냥 걷네."
        /// "저건 뭐지?" 이런 생각을 할까? 아마 저런 문자로된 생각을 하지는 않겠지만,
        /// 정체 뭘지에 대해 고민은 할 것이다. 시각정보에 대한 의미 인지에 대한 영상을 보면
        /// 시각정보->단순한 위치/ 단순한 모양 이 먼저이고, 이걸 뇌 여러부분에 퍼뜨려서
        /// 생각한다고 말하고 있다. '무엇인지?', '실제 공간상의 어디에 위치하는지?', '감정적으로'
        /// 동시인지 아닌지는 모르겠지만, 서로 다른부분에서 저런 것들을 처리한다는 것이다.
        /// 즉, 새로운 물체에 대한 감지는 기본 형태와 위치를 받아 들이고, 이것으로 다음 의문들을
        /// 처리 하는게 아닌가 싶다.
        /// 그렇다면 처음보는 생명체에 대한 머릿속 처리를 상상해보자.
        /// 처음 프레임에 물체를 발견하고, 그 모양과 위치를 염소로서 상념/생각 그래프에 추가했다.
        /// 그 다음으로 '무엇인지?'에 대한 것을 처리해야 하는데, 이게 상념/생각 그래프와의 관계가
        /// 모호하다. 애초에 상념/생각 그래프는 심리적으로 사람이 생각한다는 추상적인 것이고,
        /// 위에서 말한 '무엇인지?', '감정적 느끼는것' 등은 인지학적인 뇌과학 분야에서 뇌가
        /// 여러가지 다른 부위에서 정보들을 처리한다는 것이다. 즉, 분야가 다르다.
        /// 그렇다면 나는 여기서 어떤 방법을 사용해서 결국 '생각한다'는 것을 구현할 것인가?
        /// 일단 여기는 초기 배치 부분이므로 다음은 생각을 하거나, 변화에 대한 반응을 하는 곳에서
        /// 나머지 처리를 찾자.

        /// 행동/목적/의도/원인을 나타내기 위해 처음부터 가지고 있는 지식/개념들을 초기화하자.
        /// 이것은 임시이고, 실제로 독립체들은 어느정도 공유되는 지식/개념들을 가지고 있고,
        /// 그것은 게임 시작과 동시에 저장된 데이터를 가지고오는 오면 될 것이다.

        // 안 쓰느 코드 주석처리 요약
        {
            //// 이것은 필수적인 개념이 아닌가?
            //Kwanso kwanso_entity = new Kwanso("독립체/물체");
            //Kwanso kwanso_location = new Kwanso("위치");
            //Kwanso kwanso_vary = new Kwanso("다르다/변하다, variance");

            //KwansosStorage.Add(kwanso_entity);
            //KwansosStorage.Add(kwanso_location);
            //KwansosStorage.Add(kwanso_vary);

            //Kwanso kwanso_action = new Kwanso("행위");
            //Kwanso kwanso_behavior = new Kwanso("행동");

            //KwansosStorage.Add(kwanso_action);
            //KwansosStorage.Add(kwanso_behavior);

            //Kwanso kwanso_move = new Kwanso("이동/하다, 위치의 변화");
            //Kwanso kwanso_walk = new Kwanso("걷다.");
            //Kwanso kwanso_leg = new Kwanso("발/다리, not legs");

            //KwansosStorage.Add(kwanso_move);
            //KwansosStorage.Add(kwanso_walk);
            //KwansosStorage.Add(kwanso_leg);

            ///// 이제 여기서 중요한 것은 저 kwanso_walk라는 개념소를 실제로 '걷다'라는 행동을
            ///// 나타내게 하는 것이다. 이것은 '걷다'라는 행동의 필수적인 관계가 들어가야한다고 본다.

            //// 단순연결(mono connect)들의 처리
            //kwanso_entity.AddCompositionKwanso(kwanso_location);
            //kwanso_entity.AddCompositionKwanso(kwanso_behavior);
            //kwanso_entity.AddCompositionKwanso(kwanso_action);
            //kwanso_entity.AddCompositionKwanso(kwanso_leg);

            //// 모든 행동 카테고리에 있는 것들을 행동에 연결 시키는 것이 맞는 것일까?
            //kwanso_behavior.AddCompositionKwanso(kwanso_move);
            //kwanso_behavior.AddCompositionKwanso(kwanso_walk);

            //// 복합연결(composite connect)들의 처리
        }

        /// 본격적으로 복잡해지기 시작했다. 단어를 표현하는 '관소'를 만들기 위해서
        /// 그 개념을 분해하여, 원시적인 '개념소'라는 형태까지 가야하는 것 같다.
        /// 단순히 '변하다'라는 개념(관소)를 나타내기 위해선 이 관소가 두 쌍의 관소를 입력으로
        /// 받아야 한다. 그리고 그 두 쌍의 관소는 주체관소와 주체관소의 구성관소 중 하나인 
        /// 비교관소로 나누어 지는데, 각각의 주체관소와 비교관소는 '동일한' 관소여야 하며, 
        /// 비교관소는 '값'을 가져야한다. 그리고 그 값을 '비교'하여 '달라야'한다.
        /// 이처럼 다시 '변하다'라는 관소를 나타내기 위해서 다시 '비교', '값', '동일/같다'라는
        /// 관소를 또 나타내야 한다. 여기에 관소의 기본적인 성질이 나오는데, 관소는 개념/지식으로서
        /// 하나의 틀일 뿐이고, 그걸 사용하는 인스턴스가 '염소'라고 가정하자.
        /// 그러면 여기서 복잡한 관소를 나타내기 위해선 입력 인스턴스가 필요 할 수 있다.
        /// 즉, 관소는 필요에 따라 '입력염소'를 가질 수 있다.
        /// 그렇게 위에 처럼 계속 그 개념을 분해해서 더 이상 분해 할 수 없는 개념(관소),
        /// '개념소'까지 모두 만들어 내야한다.
        /// 대표적인 개념소로는 '값', '위치(이걸 또 공간과 좌표로 나누나?)'등이 있다.

        /// 조금 생각 해보면 이 관소를 나타내기 위한 연결/관계는 함수라는 것이다.
        /// 입력값, 즉 매개변수도 있고 그 것들로 식을 만들어서 설명하고, 조건도 있다.
        /// 물론, 어디까지나 관소를 표현하고, 나타내기 위한 식이므로, 이런 c언어 스타일의
        /// 함수와는 다른 방식으로 설계해야 할 것이다.
        /// 그리고 가공된 변화들로 그 것의 행/목/의/원을 추론하기 위해서는 좀 더 특별한 방법이
        /// 필요할 것으로 생각된다.

        /// 생각나는 모든 행동(좀 더 집적적으로 동사같이 목적이나 의도가 있고 행하는 행동)을
        /// 관소로 나타내기는 어렵다는 것이다.
        /// '값/같음/다름/not(!)/물체/위치/조건/결과/비교/변화/변하다/이동/이동하다'
        /// 이런 것들을 관소로서 만들고 표현했다고 치자. 뭔가 복잡하고 곧바로 그 내용/뜻 이
        /// 바로 느껴지거나 전해지지는 않지만, 함축적으로 실제 상황/사건/행동등을 나타낸다고 치자.
        /// 문제는 그 다음으로 이제 이동/이동하다 라는 관소(개념/지식, 행/목/의/원을 표현하는 것)
        /// 까지 만들어 냈지만, 그 다음으로 '걸음/걷다/걸어가다'같은 관소를 나타내려고 해보자.
        /// 뭐, 자의적/타의적,자동사/타동사같은 구분을 떠나서 '걷다'라는 행동 자체를 구분하는
        /// 것은 매우 복잡하고, 애매 모호하다는 것이다.
        /// 말이 규칙성/패턴성이지 어떻게 구현할 지도 모르겠고, 누워서 발만 걷는 모션을 취하는
        /// 경우처럼 이게 걷는 건지 뭔지 기준이 명확하지 않다는 것이다.
        /// 다른 예로, '먹다'라는 관소를 만드는 것은 쉽다. 하지만, 이 관소가 실제로 '먹는것
        /// /먹는 행위, 섭취하는것'이라는 행동이라고 표현 할 수 있어야 한다는 것이다.
        /// 그러니깐 단순히 관념적 단어로서가 아닌 심층의식에서 무의식에서 자의식에서 실직적으로
        /// 사용되는 비유적이거나 은유적이지 않은 본질적/본능적 구분가능한 사실이여야 한다.
        /// 그럼 그 본질적/본능적/의식적 표현을 어떻게 만들어 내는냐?
        /// 수 많은 상황을 들어 구분가능한 실질적인 의식내부의 기호같은 걸로 나타내는냐?

        /// 솔직히 모르겠다. 너무 복잡해 보이기도 하고, 불가능해 보이기도하고, 답답하다.
        /// 하나, 깨달은 사실은 내가 만들려는 것은 '현실'이 아니다.
        /// 정해진 규칙과 명확한 기준이 있는 '게임 세상'이 라는 것이다.
        /// 실제 현실처럼 복잡하거나 명확한 기준이나 셀 수없는 변수가 존재하는 것이 아니다.
        /// 뭔가 다른 방법이 있을 것이다. 아니면 너무 과열되게 생각한 것일 수도 있다.

        /// 일단 명확한 기준이 필요하다. '섭취'라는 독립체처럼 확실하게 구분이 가능해야한다.
        /// 1.특정 entity들은(먹을 수 있는 기능이 있는 객체) '소화기관'과 '입'이라는 정해진
        /// 기능이 있는 기관이 있어야만 '섭취'를 할 수 있다.
        /// 2.독립체가(포식자) 독립체를(피식자) 섭취하기 위해선 '섭취조건'을 만족해야 한다.
        /// 예를 들어 크기가 입의 정해진 조건에 만족하지 못하거나, '제압'등의 어떤 수치를
        /// 만족하지 못한다면 섭취를 할 수없다.
        /// 그리고 섭취를 하게 된다면, 피식자 독립체는 월드 상에서 사라지고 포식자 독립체의
        /// 소화기관의 내부 로컬 영역으로 이동하게 된다. 소화방법은 소화기관마다 다를 수 있다.
        /// 이 처럼 조건을 만족한 상태에서 '월드상 피식자 독립체가 포식자 독립체의 소화기관의
        /// 로컬 영역으로 이동'하게 되는 것을 섭취라는 것으로 만든다.
        /// 그럼 '걷는 것'같은 것은 어떻게 나타내는가?
        /// 일단 이 행동?행위?는 자의적인 것이다. 누군가의 명령에 의해서든 외력에 의해서든
        /// 일단 걷다라는 행동의 분류에 들어가기 위해서는 행위자의 발이 움직여 이동을 해야한다.
        /// 한쪽 발이 지면에 붙어있는 상태에서 다른 발로 이동하는 모든 행위가 '걷다'에
        /// 포함 될 것 같은데? 이거 가능해 보이는데? 굳이 패턴/규칙성 안봐도 될 것 같은데?

        /// 그렇다면 여기서 생각난 다른 부분은 행동을 하나의 단어? 개념? 관소?로
        /// 나타낼 수 있는가? 그리고 그렇게 나타내는것이 맞는것인가? 이 부분이다.
        /// 간단하게 한 동물이 사냥 중인것을 관찰하였다고 가정하자.
        /// 그렇다면 그 동물의 행동을 '사냥하다/사냥중이다' 이런식으로 표현 할 수있을 것이다.
        /// 하지만 그렇게 함축적인 표현이나 단어가 실제로 가능하고 올바른 인식인가?
        /// 실제로 사냥 중이라면 동물은 어떤 의도나 목적으로 특정 액션을 취하고 있을 것이다.
        /// 관찰자는 그 것을 보면서 전체적인 동물의 행동을 인식하고 파악한 상태일 것이다.
        /// 사냥한다는 것은 전체적인 상황의 평가이나 상태를 함축적으로 나타내는 표현일 뿐이다.
        /// 생명체가 의식상태에서 다른 물체를 인지/인식 중일때 행동/상황을 그렇게 하나의
        /// 표현으로 해석하거나 압축해서 생각하는지도 알 수 없다.
        /// 어쩌면 전체적인 정보들을 펼쳐서 연결만 시켜놓고, 그 상태가 뭔지라고 물었을 때
        /// 언어적으로 표현하기 위해 단어화시키는 것일 뿐일지도 모른다.

        /// 그래서 현재 만들려고 하는 방식은 물체에 대한 정보들을 펼쳐서 연결만 시키는
        /// 형태의 방식을 사용하려고 한다. 그렇게 펼쳐진 정보들의 연결이 모여서 특정 상태를
        /// 나타 낼 수 있고, 그게 반복적이거나 지식/개념에 있는 관계라면 집합화해서
        /// 표현하는 것이다. 어쩌면 지금 까지와 크게 다르지 않을지도 모르지만, 억지로 상태/
        /// 상황을 해석/압축/이해 하는게 아니라 최대한 있는 그 정보들로 전체적인 상태/상황을
        /// 나타내는게 핵심이라는 것이다.
        /// 그리고 결국 시간의 흐름이 필요한 것 같다. 특별한 무언가나 변화를 감지한 프레임의
        /// 정보를 각 엔티티에 연결해야한다.
        /// 좀 더 정확하게는 '시간을 나타내는 것'과'독립체'는 서로 종속관계가 아니라,
        /// 연관된 관계로 연결된 것이 맞는 표현인 것 같다.
        /// 특정 이미지맵에 뿌려진 정보들을 관계로 연결시키고, 만약 연결들이 모여서 특정
        /// 패턴이나 규칙에 만족하면 그걸 묶어서 함축적으로도 표현 할 수 있을 것이다.
        /// 어디까지나 묶어서 표현 할 수 있다는 것이지, 그게 꼭 해야 한다는 것은 아니다.
        /// 그렇게 각각의 '시간'들과 '독립체'들은 얻어진 정보로서 뿌려지고 연결되어 있다.
        /// 그리고 다시 각 독립체의 구성/연결 성분들은 각 시간 정보 때 마다 얻어진 
        /// 정보 값으로 연결되어 표현되어진다.
        /// 즉, 매 순간마다의 독립체의 구성/연결 정보가 그 순간의 시간정보에 연결되어지는
        /// 것이다.

        // 인위적인 시간에 따른 관소 연결망
        {
            //Kwanso kwanso_entity_rabbit = new Kwanso("entity_rabbit");
            //KwansosStorage.Add(kwanso_entity_rabbit);

            //Kwanso kwanso_time_list = new Kwanso("time_list", kwanso_entity_rabbit);
            //KwansosStorage.Add(kwanso_time_list);

            //Kwanso kwanso_location_list = new Kwanso("location_list", kwanso_entity_rabbit);
            //KwansosStorage.Add(kwanso_location_list);

            //Kwanso kwanso_action_list = new Kwanso("action_list", kwanso_entity_rabbit);
            //KwansosStorage.Add(kwanso_action_list);


            //Kwanso kwanso_time_1 = new Kwanso("time_1", kwanso_time_list);
            //KwansosStorage.Add(kwanso_time_1);

            //Kwanso kwanso_time_2 = new Kwanso("time_2", kwanso_time_list);
            //KwansosStorage.Add(kwanso_time_2);

            //Kwanso kwanso_time_3 = new Kwanso("time_3", kwanso_time_list);
            //KwansosStorage.Add(kwanso_time_3);

            //Kwanso kwanso_time_4 = new Kwanso("time_4", kwanso_time_list);
            //KwansosStorage.Add(kwanso_time_4);

            //Kwanso kwanso_time_current = new Kwanso("time_current", kwanso_time_list);
            //KwansosStorage.Add(kwanso_time_current);


            //Kwanso kwanso_location_1 = new Kwanso("location_1", kwanso_location_list);
            //KwansosStorage.Add(kwanso_location_1);

            //Kwanso kwanso_location_2 = new Kwanso("location_2", kwanso_location_list);
            //KwansosStorage.Add(kwanso_location_2);

            //Kwanso kwanso_location_3 = new Kwanso("location_3", kwanso_location_list);
            //KwansosStorage.Add(kwanso_location_3);

            //Kwanso kwanso_location_4 = new Kwanso("location_4", kwanso_location_list);
            //KwansosStorage.Add(kwanso_location_4);

            //Kwanso kwanso_location_current = new Kwanso("location_current", kwanso_location_list);
            //KwansosStorage.Add(kwanso_location_current);


            //Kwanso kwanso_action_1 = new Kwanso("action_1", kwanso_action_list);
            //KwansosStorage.Add(kwanso_action_1);

            //Kwanso kwanso_action_2 = new Kwanso("action_2", kwanso_action_list);
            //KwansosStorage.Add(kwanso_action_2);

            //Kwanso kwanso_action_3 = new Kwanso("action_3", kwanso_action_list);
            //KwansosStorage.Add(kwanso_action_3);

            //Kwanso kwanso_action_4 = new Kwanso("action_4", kwanso_action_list);
            //KwansosStorage.Add(kwanso_action_4);

            //Kwanso kwanso_action_current = new Kwanso("action_current", kwanso_action_list);
            //KwansosStorage.Add(kwanso_action_current);


            //kwanso_entity_rabbit.AddCompositionKwanso(kwanso_time_list);
            //kwanso_entity_rabbit.AddCompositionKwanso(kwanso_location_list);
            //kwanso_entity_rabbit.AddCompositionKwanso(kwanso_action_list);

            //kwanso_time_list.AddCompositionKwanso(kwanso_time_1);
            //kwanso_time_list.AddCompositionKwanso(kwanso_time_2);
            //kwanso_time_list.AddCompositionKwanso(kwanso_time_3);
            //kwanso_time_list.AddCompositionKwanso(kwanso_time_4);
            //kwanso_time_list.AddCompositionKwanso(kwanso_time_current);

            //kwanso_location_list.AddCompositionKwanso(kwanso_location_1);
            //kwanso_location_list.AddCompositionKwanso(kwanso_location_2);
            //kwanso_location_list.AddCompositionKwanso(kwanso_location_3);
            //kwanso_location_list.AddCompositionKwanso(kwanso_location_4);
            //kwanso_location_list.AddCompositionKwanso(kwanso_location_current);

            //kwanso_action_list.AddCompositionKwanso(kwanso_action_1);
            //kwanso_action_list.AddCompositionKwanso(kwanso_action_2);
            //kwanso_action_list.AddCompositionKwanso(kwanso_action_3);
            //kwanso_action_list.AddCompositionKwanso(kwanso_action_4);
            //kwanso_action_list.AddCompositionKwanso(kwanso_action_current);
        }

        /// 기억의 분류와 관리.
        /// 현재 단순한 개념소들로 연결(단순연결/복합연결)하여, 그 관계로 행/목/의/원을
        /// 나타내려고 하고있다. 그것까지는 좋다 치지만, 몇권의 자료를 찾아보면 실제 뇌의
        /// 기억이 여러가지로 나누어져 관리된다고 한다. 물론, 이게 사람의 뇌지, 컴퓨터가 
        /// 생각하는 방법과는 상관없는 것일 수도 있다.
        /// 하지만 그래도 실제 뇌에서 사용하는 기억들과 사용법을 참고한다면, 그것이 좀 더 
        /// '인간답게' 생각한다고 보여지지 않을까?
        /// 이 부분에 대해서는 일단 현재 생각나는대로 만들어 보고 따지는 것이 좋을 것이다.
    }

    void Thought_Setup2()
    {
        Ye_Action aa = new Ye_Action();
        Ye_Move bb = new Ye_Move();

        Concept concept_walk = new Concept();

        concept_walk.Name = "Concept_Walk";

        Prerequisite_Condition condition_direction = new Prerequisite_Condition();

        condition_direction.ListParameterYeomsoTypeNumber.Add(YeomsoTypeNumber.GetTypeNumber(typeof(Ye_Move)));

        Func<Ye_Entity, Prerequisite_Yeomso[], bool> func = (ye_entity, arrData) =>
        {
            Ye_Move ye_move = (Ye_Move)arrData[0].Ye_object;

            Transform transform = ye_entity.RealEntity.transform;

            // 걷는 방향과 독립체 방향이 30도 보다 크다면
            if (ye_move.IsMove == false || Vector3.Angle(transform.forward, ye_move.DirectionMove) > 30)
            {
                return false;
            }

            return true;
        };

        condition_direction.ConditionFunc = func;

        Prerequisite_Condition condition_action = new Prerequisite_Condition();

        condition_action.ListParameterYeomsoTypeNumber.Add(YeomsoTypeNumber.GetTypeNumber(typeof(Ye_Action)));

        func = (ye_entity, arrData) =>
        {
            Ye_Action ye_action = (Ye_Action)arrData[0].Ye_object;

            return (ye_action.ActionState == EActionState.WALK);
        };

        condition_action.ConditionFunc = func;

        concept_walk.ListPrerequisiteConditions.Add(condition_direction);
        concept_walk.ListPrerequisiteConditions.Add(condition_action);

        concept_walk.SetupPrerequisiteYeomsos();

        // 나중에 리팩토링
        ConceptList conceptList = new ConceptList();
        conceptList.Add(concept_walk);

        ConceptMemory.Add(EActionState.WALK, conceptList);
    }

    // 어차피 행동할게 아니니깐 업데이트가 생각이라고 가정하고 만들자.
    void Update()
    {
        /// 1) 여우의 토끼잡는 상상 -> 이건 지식(본능/경험/기억)을 '어떻게' 활용하는지가 포인트.
        /// 2) 영화를 보며 감상 -> 이건 '견해/판/평'을 통해 지식(경험/정보)를 쌓는지가 포인트.
        /// 얼핏보면 1)번이 저지능 동물이기에 쉬워보이지만, 둘다 단순히 같은 동물을 가정하면
        /// 지식을 쌓는 것 보다 지식을 '어떻게' 활용하는지가 더 어렵다.
        /// 당연히 지식을 활용하기 위해서는 지식이 쌓여있어야하기 때문이기도 하다.
        /// 즉, 지식을 쌓는 문제부터 해결해보자. 굳이 인간이 아니더라도 더 간단한 것을 
        /// 관찰하고 지식을 쌓아도 된다.
        /// 즉, 우선 순위는 관찰을 통한 지식의 축적 -> 행동을 통한 경험의 축적 -> 본능 구성
        /// -> 지식(경험/기억/본능)을 통한 관념선택/행동결정.

        /// 관찰을 통해 지식을 쌓다.
        /// 이게 참 어려운게 지시을 쌓기 위해선 어느정도의 바탕 지식이 필요하다는 것이다.
        /// 그러니깐 여기서는 기초/바탕 지식을 위한 견해나 판/평 이 없는 날 것 그대로 정보를
        /// 지식으로 받아들이는 방법을 사용해볼까 한다.
        /// 쌓여진 지식들로 부터 반복이나 경험을 통해 '통념/상식/본능'을 만들어야 할것이다.

        /// 상황을 가정하자. 관찰자는 음, 나중에 필요하면 정하자.
        /// 고정된 시야(2차원 좌표계)에서 일어난 상황을 관찰하고, 지식으로 만들어야한다.
        /// 상황(시뮬레이션)은 여우(처음보기에 먼지 모름)가 토끼(이것도 모름)를 잡아먹는다.
        /// 그리고 다음에는 토끼가 도망가고, 여우가 쫒지만 잡는데 실패한다.
        /// 다음에는 토끼가 도망가지만 여우가 쫒아가서 잡아먹는다.
        /// 이런식으로 여러번의 상황을 똑같거나 비슷하게 반복해서 보여줘서 지식을 습득하게 한다.
        /// 여기서 얻을 지식은 여우와 토끼라는 객체의 정보와 '여우는 토끼를 잡아먹는다'라는 정보.
        /// '토끼는 도망간다'/'여우는 쫒는다'나 '토끼의 여우 발견'같은 정보도 있고 '먹는다'라는
        /// 기초적인 지식도 쌓아야한다.
        /// 기초적인 지식이라고 해서 말인데, 어디까지 지식이 필요한가도 문제이다.
        /// 좌표계와 객체 위치등은 기본베이스라고 치고, '이동'이라는 개념은 지식인가?
        /// 기본베이스인가? 솔직히 이것도 문제지만, 가장 큰 문제는 이제 관찰과 지식의 구현이다.
        /// 관찰로 모든 객체의 정보(위치,형태,식별코드/이름)를 알았다고 치자.
        /// 이걸로 상황(연속된 관찰정보에 따른 흐름)을 만들어내고, 거기서 지식으로
        /// 만들어 내는 것은 전혀 모르겠다는 것이다.
        /// 일단 위에 글에는 2가지가 필요하다고 적혀있다. '상황의 구현/이해'와 '정보/지식'이다.
        /// 이 두가지는 어떤 연관이 있고, 꼭 필요한 것인가? 어느것이 먼저이고, 중요한가?

        /// 상황은 예를 들자면, '여우가 토끼에게 접근해서 물다'와 같은 것인데,
        /// 이게 문장처럼 압축되서 기호로서 표현되는지 아니면 영상처럼 받아들일지,
        /// 그것도 아니면 다른 방식으로 구현 될지도 정해지지 않았다.
        /// 일단 가장 간단한 영상처럼 관찰된 것을 시간순으로 나열하는 것은 어떤가?
        /// 뭐, 특정기준(이게 무슨기준인지, 지식인지도 문제이지만)으로 키프레임으로 나눌 수있다.
        /// 일단 이 방법은 그 어떤 해석도, 견해도 들어가지 않았다는 것에서 간단하다.
        /// 문제는 이게 의미가 있나 싶기도하다. 하지만, 일단 키프레임으로 압축되어
        /// 보관가능하기에 기억으로서는 오히려 이게 더 괜찮을 지도 모른다.
        /// 그럼 다른 방법은? 위에 처럼 기호로 나타낸다는데, 상황이라는 것은 결국 시간의 흐름이다.
        /// 시간의 순서에 따라 정리/나열 되어야 하는데, 결국 기호로 표현한다쳐도 각 객체를
        /// 키프레임으로 나누어야하지 않겠는가? 거기에 객체정보를 기호로 나타내거나 견해등을
        /// 포함 시킬 수 있을 것이다.
        /// 그 외에 다른 방식은? 문장으로 나타내는 방법? 상황을 이해하고 그것을
        /// 관념적언어(기호같은)로 나타 낼 수 있지 않을까?
        /// '여우가 나타났다.' + '여우가 토끼를 본것 같다.' -> '여우가 토끼에게 몰래 접근한다.'
        /// 이런식으로 말이다. 문제는 역시 이렇게 문장식(꼭 글일 필요는없다)로 나타내려면,
        /// 결국 상황을 받아들이는 순간 이해해서 해석해야 한다는 것이다. 그리고 너무 부정확하다는
        /// 문제도 있지만, 개인이 상황을 이해하는 것은 원래 주관적이고, 정확할 필요는 없다.
        /// 장점은 객체정보들을 키프레임으로 만든것에 비해 압축률이 높다는 것이다.
        /// 하지만, 이건 결국 나중에 상황을 이해해서 문장으로 해석하는 일이 필요할 것이므로 일단
        /// 지금은 좀 더 간단한 시간순 나열방식을 이용하는게 좋을것같다.

        /// 다음은 '정보/지식의 표현과 축적'이다.
        /// 위위 말처럼 이게 상황과 어떤 관련이 있을까? 잘 모르겠다?
        /// 모르겠다면(없다고치고), 지식은 어떤 방식으로 구현/표현되어야 하는가?
        /// 지식은 기호로 된 문장이다?
        /// '여우는 먹는다 토끼를' 이런식으로 문장으로 된 것이 있다.
        /// 저것이 지식/정보 인가? 그럼 '먹다'라는 동사(행동)도 지식/정보 인가?
        /// 동사(먹다)도 지식이고, 명사(객체, 토끼/여우)도 지식이다.
        /// 물론, 형용사(맛있게)등도 지식으로 존재 할 수 있을 것이다.
        /// '여우가 토끼를 맛있게 먹다'라는 문장은 일단 정보이긴 하다. 이게 지식인가?
        /// 위의 문장은 지식이라기에는 뭔가 애매하다. '10초전 여기서'라는 장소와 시간이
        /// 붙는다면 지식이라고 할 수 있을까?
        /// 정보와 지식의 차이가 존재할까? 무엇일까? 
        /// 일단 그 전에, 위에 가정된 상황에서 얻을 수 있는 정보와 지식은 무엇일까?
        /// 간단한 것부터 생각나는대로 모두 나열을 해보자.
        /// '여우(위치, 형태, 행동, 액션)' / '토끼(==)' / '지형(표면재질 등)' /
        /// '먹다-풀(토끼 행동/액션)' / '먹다-토끼(여우 행/액)' / '조심히걷다(여우 행/액)' /
        /// '도망치다(행동)' / '뛰다(행/액)' / '사냥하다(행동)' /
        /// '조금전(시간) 눈앞에서(위치) 여우가 토끼를 잡아먹다.(이건 주관적인 해석)'
        /// 기억⊃지식 , 기억⊃정보, 지식≠정보 일 거라고 생각된다.
        /// 아직 상념이 뭔지 모르겠다. 하지만, 상황을 관찰 한 뒤, 상황을 '이해'->'해석'해서
        /// 기억에 저장하는 것은 가능하지 않을까?
        /// 결국 지금 내가 여기서 지식이든 정보든 고민하고 있는 것은 '상황'을 '이해'하고
        /// '해석'하는 것인데, 그 만들어진 결과물인 지식/정보가 어떤 형태인지를 정하는 것이다.
        /// 모르겠다. 일단 해석되지 않는 상태의 '상황'을 구현해 볼까?(가능하면 키프레임으로된)

        // 상황의 구현 (이해와 해석은 일단 배재한다.)

        /// 매 프레임마다 '상황'은 항상 구현되어있어야한다.
        /// 그러므로 '관찰'을 통한 정보로 바로 상황부터 갱신한다.

        // 생각/뇌 가 가진 객체 Situation.Update(관찰정보);
        //UpdateSituation();

        /// 일단 관찰된 단순한 정보를 가공하여 인식중인 관소 연결망에 연결 시키는 작업이 필요하다.
        /// Trigger2DStay에서 현재 시야에 들어온 정보를 받아온다.


        // 인지 중인 물체에 대한 변화를 감지 했을 경우, 생각/사고의 변화를 구현해보자.

        /// 일단 인지학적 순서를 관념(생각/사고/상념/Thought 를 앞으로 편의상 관념이라 부르자)에
        /// 맞춰서 구현해 보자.
        /// 우선 들어온 물체를 관측단계에서 '단순한 형태'와 '단순한 위치(시야부분에서)'의
        /// 정보로 들어오게 된다고 가정하자. 그러면 관념이 사고의 흐름이라면 저 두 정보를
        /// 염소로서 받아들이게 된다. 즉, 새로운 발견-> 독립체 -> 단순한위치, 단순한형태
        /// 그렇다면 여기서 머리는 관념은 무슨 생각을 하는게 맞을까?
        /// 어떤 생각을 거쳐서 새로운 독립체에 대해 '생각'하게 될까?
        /// 저 독립체가 '무엇인지', '공간상의 위치는 어디인지', '감정적으로 어떻게느껴지는지'
        /// 이런 것들을 서로 다른 부분에서 생각하게 되는게 인지학적 뇌과학의 설명이었다.

        /// '무엇인지?', '무슨행동을하는거지?/왜저러는거지?/목적이뭘까?' 이런 생각 한다고
        /// 예상된다. 그렇다면 어떻게 저런 생각을 어떻게 하는 것일까?
        /// '무엇인지?'는 뭐 의무적/필수 과정이라고 가정해도, 다른 생각들은 어떤 과정을
        /// 어떤 알고리즘을 거쳐서 그런 생각을 어떻게 하는 것일까?
        /// 결국 지금 문제의 핵심은 '어떤 과정'과 '어떻게 그런 생각'이라는 것이다.
        /// 그렇다면 물체에 대한 인식을 할 경우의 수를 나눠서 생각해보자.
        /// 1. 물체 정체를 알고, 어떤 과정(블랙박스)를 거쳐서 '무엇을, 왜'하는지에 대한 문제.
        /// 2. 물체 정체를 모르고(처음봄), ""
        /// 3. 물체 정체를 알고, 어떤 과정을 거쳐서 다음 생각(무엇을,왜)에 대해 생각하는지 문제.
        /// 4. 물체 정체를 모르고, ""

        /// 1. 일단 새로운 물체에 대한 정보/기억이 있다고 가정하자. 그리고 어떤 과정을 거쳤는지는
        /// 모르지만, 그 물체가 다음으로 '뭘하는지', '왜 저러는지'에 대해 생각한다고 가정하자.
        /// 그렇다면, 그런 생각을 어떻게 구현 할 것인가?

        // ThoughtAboutChangedEntity에 대한 구현
        {
            /// 일단 상황을 설명해보자.
            /// 정체를 아는 독립체가 일직선으로 걷고있다.
            /// 그러다가 독립체가 이 프레임에 멈춰서서 특정행동(대기,둘러보기)을 한다.
            /// 그렇다면 이 순간 관찰자는 어떤 과정을 거쳐서 변화를 감지한 독립체에 대해
            /// '뭘 하는건지','왜 저러는건지'에 대해 생각을 한다. 그리고 그 생각이 이 부분이다.
            /// 문제는 지금까지의 상황에 대한 인식부터가 안돼있다.
            /// 상황의 인식/이해가 먼지 모르겠고, 일단 뭐하는 건지라는 궁금증이 생겼다고 치자.
            /// 결국 여기서 처리 할 것은 독립체가 현재 무엇을 하는지, 왜 하는지에 대한 생각이다.
            /// 여기서 현재까지의 독립체의 행동(Action),위치,속도등의 정보들을 이용해서
            /// '뭘 하는지'에 대해 생각을 만는게 목표이다.
            /// 결국 현재 Behavior와 Purpose를 구성해야 한다.

            /// 그럼 Behavior은 어떻게 구성 되어있는가?
            /// 행동이라는 것은 단순한 행위(Action)을 포함하는 목적을 가지고 행하는
            /// 일련의 행위의 연속이라고 할 수 있지 않을까?
            /// 'Entity_A가 일정한 속도로 쭉 걸어간다.' 라는 것은 그 물체의 행동을 묘사한다.
            /// 'A가 B를 때린다.'라는 것도 A의 행동의 묘사라고 할 수 있을것 같다.
            /// 단순히 'Attack'이라는 행위(고유 애니메이션 뼈태+애니메이션+offset)가 있다.
            /// 이것은 목적도 목표도 없는 단순한 행위지만, 여기에 '누가''누구'를 이라는
            /// 행위자와 목표가 정해지면 이건 행동이라고 할 수 있을 것이다.
            /// 그리고 거기에 그 행위가 단순히 공중에 헛스윙을 하던, 아니면 누군가에게 피해를
            /// 주기 위해서던의 목적이 추가되서 '공중에 헛방질을하다', 'B를 공격하다.'라는
            /// 좀 더 구체적인 행동을 나타낸다고 할 수 있다.

            /// Behavior의 틀을 만들어 생각나는 대로 만들어보자.
            /// 우선 행위자는 당연히 있고, 알고 있다. target은 있을 수도 있고, 없을 수도 있다.
            /// purpose를 알아야 할까? '일정하게 걷고있다.'라는 행동이 있다. 여기에
            /// 목적이나, 목표가 존재 하는가? 어디로 가는지 왜 가는지 모를 수도 있다.
            /// 예를 들어 행동(Behavior)이 가지고 있는 기본 속성으로 purpose, target,
            /// cause(원인/이유), actionList등을 가지고 있다고 가정하자.
            /// 그러면 그 것들이 그 행동을 나타낸다고 할 수 있나?
            /// 고민을 해봐도 목적,목표,원인/이유,행위들을 아무리 본다고 해도 그 행동 자체를
            /// 알 수도 없을 뿐더러 묘사한다고 할 수도 없을 것이다.
            /// '걷고 있다'라는 행동이 있다 가정하자. 이것을 풀어서 설명이 가능한가?
            /// 어떤 방향으로 '걷다'라는 행위 카테고리(발이 없는 생물체는 걸을 수 없을 것이고,
            /// 발이 있어도 뛰지 않고 이동하는 action들만 포함, 어떻게 만들어 지는지는 생략)에
            /// 포함된 행위로 이루어진 이동. 즉 '움직이다'라는 행동에 포함되는 하위 행동이다.
            /// '움직이다'⊃'걸어가다' 처럼 행동은 다른 행동에 포함되거나 할 수 있다.
            /// '공연하다'라는 행동에 '춤을 추다'라는 행동이 포함 될 수도 안 될수도 있다.
            /// 단순히 action으로 나눌 수도 없는게, '쫒아가다'라는 행동에는 뛰어서든 걷든
            /// 일단 '이동'해서 목표를 따라가는게 된다.
            /// 즉, 이건 기초 개념부터 쌓아서 만들어 내야하는 것이다.

            /// 결국 이제 핵심은 Behavior의 구현/구성이다.
            /// 이건 단순한게 아니라, 아주 기초 개념부터 쌓아진 지식들이 필요할 것이다.
            /// '걷다'⊂'이동하다'⊂'이동'⊂'위치의 변화'처럼 단순화 시킬 수 있으면 편하지만,
            /// '공연하다'처럼 복합적인 행동은 단순화 시키는게 어렵다.
            /// 그리고 '춤을추다'->'춤??'처럼 행위(Action)를 특정 시키기 어려운 것도 있다.
            /// 솔직히 어디서부터 어떻게 구현해야 할지 감도 잡히지 않는다.

            /// 일단 단순한 '걷다'라는 행동을 나타내는 것을 목표로 하자.
            /// 위에 예시 처럼 '걷다'라는 개념은 '이동하다'에 특정 action들이 합쳐진 개념이다.
            /// 여기서 일단 특정 action이라는 것은 좀 있다 생각하고, '이동하다'라는 것에 대해
            /// 다시 생각해보아야 한다. '이동/이동하다' 라는건 '위치의 변화'이다.
            /// 이 '위치의 변화'라는 것을 어떻게 나타내고, 개념화 시키고 확장 시키는가?
            /// 여기선 '위치'와 '변화'라는 단순하고 기본적인 것 같은 개념이 나왔지만,
            /// '밥을 먹다'같은 행동은 결국 '먹다'라는 뭔가 기본적인 것 같지 않은 개념이 나온다.
            /// 이 더 이상 간단화 시키기 힘든 기본 개념들. 이것들을 어떻게 구현하고,얼마나 많은지,
            /// 어떻게 구할 것인지 그런 것도 문제이다.

            /// 일단 생각나는 모든 행동을 단순화 시키고, 나오는 기본 개념들을 닥치는 대로
            /// 만드는 것이다. 어떻게 구현 할 지는 모르겠지만.
            /// 그리고 만약 그런 기초/기본 개념/지식들이 구현돼 있다면, 관찰을 통해 감지된
            /// 독립체의 변화를 보고 그게 무엇을 하는건지 내가 알고 있는 커다란 개념으로
            /// 나타내는 것이 '생각한다'라는 것이라고 할 수 있지 않을까?
            /// 즉, 독립체의 '위치'의 변화와 '행위'를 보고 저 독립체가 '걸어간다'라는 행동을
            /// 하고 있다는 것을 유추하는 것이 생각 이라고 할 수 있을지도 모른다는 것이다.
            /// 그러니깐 단순한 수치들로부터 '걷다'라는 행동을 나타내는 것 까지를 구해야한다.

            /// 그럼 우선 '위치의 변화'=> '이동/이동하다'라는 것을 개념/지식으로 나타내보자.
            /// '위치'와 '변화'라는 것부터 개념/지식으로 나타내야 할 것이다.
            /// 솔직히 '개념/지식'을 어떻게 나타내야 할지 모르겠다.
            /// 그렇다면 위에 말한대로 기본 수치를 보고 '걷다'라는 것을 추론해 나가는 
            /// 과정을 여기서 구현해 보는 것도 방법일 것이다.

            /// var changedProperties = GetChangedProperty(entityA);
            /// foreach (var property in changedProperties)
            /// {
            ///     property.GetInfo() --> 여기서 'position'과 'changed'라는 정보가 나옴.
            /// 정보/개념/지식을 어떻게 표현하고, 어떻게 연결하고, 저장하고 사용할건데?

            /// '관찰정보' 중에서 '주목할만한(변화가있는, 중요한, 위험한 등등)' 것들을 구한다.
            /// 예를 들어 변화를 판/평해서 '규칙성/패턴성'을 구한 '이동 궤적/정보',
            /// 똑같이 이전과의 변화를 판/평한 'action 정보(뼈대+재생도+재생속도+카테고리)'등
            /// 이런 기본이되는 가공된 정보들을 만든 후(또는 만들었다고 가정한뒤),
            /// 그런 정보로 부터 독립체의 행동/의도/목적/원인 등을 유추하는 것이다.
            /// 물론, 이 과정에서 행/의/목/원을 나타내기 위한 방법을 만들어야 할 것이다.

            /// 첫번째로 생각나는 방법은 정보들로 간단한 행동(behavior)을 추론/형성 하는것.
            /// 두번째는 일단, 염소 그래프 만들듯이 행/의/목/원 을 개념소로 이루어진 형태로
            /// 만들어 내는 것이다.

            /// organizedFeatures = OrganizeFeatureFromEntity(entity);
            /// 가공(이전 상황들과 비교되어 주목 할만한 모든 특징을 규칙성/패턴화를 통해 정리)된
            /// 모든 정보를 얻었다고 가정하자. 여기에는 관찰된 독립체에 대해 생각나는 모든
            /// 특징들이 들어있다.
            /// 여기서 관찰자는 저 독립체가 '걷고있다' 또는 '걷다가 갑자기 멈추다'등의 행동을
            /// 추론하고 만들어 내야한다.(당연히 행동을 정의하고 표현하는 방법도 만들어야한다.)
            /// 

            OrganizedFeatureList organizedFeatures = new OrganizedFeatureList();
            /// 어떤 기준으로 나누어서 수 많은 결과(행동) 중에 하나를 선택 할지 모르겠다.
            /// 결국 이 부분은 임시로 if문 떡칠로 만든 뒤, 나중에 머신런닝으로 해결을 해보자.

            /// 어떻게 추론 할지 모르겠으면 우선, 개념소를 만들어서 그것들을 연결해서 '걷다'라는
            /// 행동을 구현해보자. 그리고 '이동'같은 포괄적인 개념과 연결시켜야 한다.
            /// 
        }


        //ImplementThought2();
        //ImplementThought3();
        ImplementThought4();
    }

    /// <summary>
    ///  2020.05.05   시간 순으로 판/평으로 이루어지는 상념의 구현
    /// </summary>
    void ImplementThought2()
    {
        // Think 부분

        // createMoment() -> 현재 순간을 나타내는 시간을 만들어 낸다.
        Yeomso_Time timeCurrentMoment = new Yeomso_Time(Time.time);

        // 현재 순간을 테이블에 추가하기 전에 이전 프레임과 비교해서 변화를 감지하고, 판평해야한다.
        Yeomso previousTime = null;

        if (ThoughtTimeTable.First != null)
        {
            previousTime = ThoughtTimeTable.First.Value;
        }

        ThoughtTimeTable.AddFirst(timeCurrentMoment);

        // 인지 중이던 객체들에 대한 처리
        foreach (var thoughtObject in ThoughtObjectsTable)
        {
            Entity realEntity = thoughtObject.RealEntity;

            /// 여기가 현재 만들려는 사고 시스템의 핵심부분이다.
            /// 우선 현재 객체의 위치와 행동등의 정보를 업데이트(염소를 만들어 현재 시간에 연결)한다.
            /// 그리고 이전 시간들의 정보들과 판/평으로 부터 현재 순간의 판/평을 실시한다?
            /// 시야에 들어와서 처음 판/평을 실행 할 때, 어떤 기준으로 어떤 순서로 어떻게 해야할까?
            /// 첫번째 프레임에는 단순히 관찰 정보(위치,행동,생김새)등을 시간에 맞게 생성할 뿐이다.
            /// 그 다음 프레임, 이제 그 물체에 대한 판/평을 해야한다.
            /// 그 물체(독립체)에 대해 가진 정보는 이전 프레임과 현재 프레임의 관찰정보 뿐이다.
            /// 여기서 처음에 무엇을 해야 하는가?

            // 처음 판/평을 할 경우
            if (thoughtObject.IsFirstJudgmentEvaluation())
            {
                /// 일단 정체를 알아야 하지 않을까?
                /// 그리고 그 다음에 뭘 하느지를 봐야겠고?
                /// 이게 무조건적인 정해진 순서와 방법(코드)에 의해서 결정되는게 맞는가?
                /// 실제로 한 사람이 제대로 식별 가능한 시야각은 120도정도라고 한다.
                /// 하지만 물체를 인지하는 것은 200도를 넘어서는데, 이 외야 시야각에서는 물체를 인식해도
                /// 그 정체나 행동에 대해 '자세하게' 알 수 없을 것이다.
                /// 즉 시야와 거리 등에 따라 물체에 대한 판/평 수준이 다르다는 것이다.
                /// 거기에 상황이나 경험등에 따라 물체에 대한 판/평에 추측/예견등이 들어 갈 수도 있을것이다.
                /// 물론, 대충 평가한 물체가 엄청 크거나 처음보는등 뭔가 이상하다면 그 물체에 대해
                /// 좀 더 관심을 가지게 될것이고, 그 물체에 대해 더 자세한 판/평을 하게 될 것이다.
                /// 즉, 어떤 물체에 대한 판/평은 단순히 일률적인 방법이 아니라, 물체에 대한
                /// 거리, 시야, 그리고 대충된 판/평으로 인한 중요도(추측/예측의 차이, 크거나 처음보는 등의
                /// 경험에 대한 차이)에 따라 다른 수준으로 판/평이 이루어져야 할 것이다.

                /// 정체를 파악하고(독립체에 대한 정보 갱신), 뭘하는 생각하고(행동 갱신), 왜 그러는지
                /// 생각하는(의도 및 원인 등 갱신) 순서로 한다고 가정하자.

                // 정체 파악 : 독립체에 대한 정보 갱신 CharacterInfoUpdate
                {
                    // 종 파악하기
                    Yeomso_Race yeomso_race = new Yeomso_Race();
                    yeomso_race.Race = realEntity.Race;

                    thoughtObject.Race = yeomso_race;

                    /// 이 독립체가 본적이 있는지 얼마나 친숙한지(비슷한 독립체 검색) 등을 파악(기억/경험 탐색)
                    /// 현재는 기억/경험 등의 시스템도 없고, 완전히 처음봤으므로 생략한다.
                }

                // 행동 파악 : 독립체가 현재 어떤 행동을 하고 있는지에 대해 판단 BehaviourJudgmentUpdate
                {
                    /// 행동을 어떻게 파악할까?
                    /// 일단 알 수 있는 정보는 이전과 현재의 위치, 액션, 형태 밖에 없다.
                    /// 물론, 경험이나 기억에서 얻거나 이전에 판단한 정보가 있을 수도 있다.
                    /// 하지만, 지금은 처음이므로 위치와 액션(애니메이션)정보를 토대로 판단해야한다.

                    // 이동 여부 판단
                    Yeomso_Behavior yeomso_move = new Yeomso_Behavior();

                    yeomso_move.Time = timeCurrentMoment;
                    yeomso_move.Owner = thoughtObject;

                    if (thoughtObject.Pos.PosData == realEntity.transform.position)
                    {
                        yeomso_move.Data = "none_move";
                    }
                    else
                    {
                        yeomso_move.Data = "move";
                    }

                    // 위치 염소를 상념에 부착 : 이걸 여기서 하는게 좀 이상하긴하다.
                    // 리스트 형식을 취하는데, 나만의 규칙으로 작성되므로 순서가 중요하다.
                    Yeomso_Location yeomso_pos = new Yeomso_Location();
                    yeomso_pos.PosData = realEntity.transform.position;
                    yeomso_pos.ConnectYeomso(thoughtObject.Pos);
                    thoughtObject.Pos = yeomso_pos;

                    yeomso_move.InsertYeomso(thoughtObject.Pos);
                    yeomso_move.InsertYeomso(thoughtObject.Pos.ConnetedYeomsos[0]);

                    thoughtObject.InsertYeomso(yeomso_move);

                    // 행위(action)로 부터 정보 판단
                    Yeomso_Behavior yeomso_action = new Yeomso_Behavior();

                    yeomso_action.Time = timeCurrentMoment;
                    yeomso_action.Owner = thoughtObject;
                    yeomso_action.AS = realEntity.AS;

                    // 마찬가지로 행위상태 염소를 부착
                    Yeomso_IntData yeomso_actionState = new Yeomso_IntData(EYeomsoType.ACTION_STATE);
                    yeomso_actionState.Data = (int)realEntity.AS;
                    yeomso_actionState.ConnectYeomso(thoughtObject.AS);

                    thoughtObject.AS = yeomso_actionState;

                    thoughtObject.InsertYeomso(yeomso_actionState);
                }

                // 의도나 원인등은 첫번째 판/평에서는 생략한다고 가정하자.
            }
            // 이전에 판/평을 했을 경우
            else
            {
                /// 이 독립체가 어떤 녀석인지? 나와 무슨관계인지? 무슨 성격인지 등등
                /// 독립체 개인에 대한 정체/정보는 관찰되는 매 순간마다 바뀔 수 있다.
                /// 하지만, 그게 매 프레임마다 정해진 순서로 행해지는 것은 아닌 것 같다.
                /// 매 순간의 관찰자가 판단한 독립체의 행동을 평가하고 그것으로 부터 축적된 정보를
                /// 변화시키거나 쌓아나간다는 것이 올바른 표현이고 방법일 것이다.
                /// 결국 독립체의 정체/정보는 나중에 좀 더 깊이 만들어야 할 것이다.
                /// 단순히 종이나 겉모습만이 아닌, 예측된 성격, 관계, 소지중인 물품,
                /// 그리고 의도와 목표 행동까지 어떻게 보면 이 모든 것이 독립체를 나타내는 정보이자 정체이다.
                /// 그렇다면, 현재 구현하려는 것은 독립체가 매 순간 무엇을, 어떻게, 왜 하냐는 것이다.
                /// 독립체의 행동을 판단하고 평가해서 의도와 목적을 추측, 예측하는 것이다.

                /// 현재 단순하게 생각나는 방법은 판/평된 행동들은 기초적인 정보로 부터 만들어진 정보들로
                /// 이루어진 복잡한 행동까지를 스택처럼 보관하게 된다.
                /// 즉, 다음 순간에서는 그 스택된 행동들을 복잡한 순부터 가장낮은 정보까지 역으로 흩으며
                /// 새로운 정보들과 비교하며 스택하는 방식을 생각하고는 있다.
                /// 

            }
        }

        // 새롭게 관찰된(이전 프레임에 없던) 객체에 대한 처리
        foreach (var newEntity in EnterObservedEntities)
        {
            Yeomso_Object newThoughtObject = new Yeomso_Object(newEntity);

            Yeomso_Location pos = new Yeomso_Location();
            Yeomso_IntData action = new Yeomso_IntData(EYeomsoType.ACTION_STATE);

            pos.Owner = newThoughtObject;
            action.Owner = newThoughtObject;

            pos.Time = timeCurrentMoment;
            action.Time = timeCurrentMoment;

            pos.PosData = newEntity.transform.position;
            action.Data = (int)newEntity.AS;

            newThoughtObject.Pos = pos;
            newThoughtObject.AS = action;

            ThoughtObjectsTable.AddLast(newThoughtObject);
        }

        // 시야에서 사라진 오브젝트에 대한 처리
        foreach (var exitEntity in ExitObservedEntities)
        {

        }

        // 나머지 처리 부분
        EnterObservedEntities.Clear();
        ExitObservedEntities.Clear();
    }

    /// <summary>
    /// 2020.05.27
    /// 기존의 상념 시스템에서 염소 구조를 처음부터 다시 구성해서 만들어야한다.
    /// 살짝 복잡한 상황, 'A가 B를 쫒고 있고 B는 도망치다가 앞에있는 나무에 올라간다.'같은 
    /// 상황을 시간 순으로 어떻게 구성되는지 만들어 봐야한다.
    /// </summary>
    void ImplementThought3()
    {
        // 상념의 기초 현재 순간의 시간을 만들어서 연결, 이전 시간을 마크해둔다.

        Ye_Time ye_timeCurrent = new Ye_Time(Time.time);
        Ye_Time ye_timePrevious = null;

        if (StorageTimeTable.First != null)
        {
            ye_timePrevious = StorageTimeTable.First.Value;
        }

        StorageTimeTable.AddFirst(ye_timeCurrent);

        // 인지 중이던 객체들에 대한 처리
        foreach (var ye_entity in StorageEntitiesTable)
        {
            Entity realEntity = ye_entity.RealEntity;

            DependentYeomsoSetupStruct setupData;

            setupData.owner = ye_entity;
            setupData.time = ye_timeCurrent;

            // 위치 염소를 상념에 부착
            Ye_Position ye_pos = new Ye_Position();
            ye_pos.Setup(setupData);
            ye_pos.Pos = realEntity.transform.position;

            ye_pos.LinkPreviouYeomso(ye_entity.Ye_position);
            ye_entity.Ye_position = ye_pos;

            // 행위 염소를 상념에 부착
            Ye_ActionState ye_actionState = new Ye_ActionState();
            ye_actionState.Setup(setupData);
            ye_actionState.State = realEntity.AS;

            ye_actionState.LinkPreviouYeomso(ye_entity.Ye_actionState);
            ye_entity.Ye_actionState = ye_actionState;

            // 처음 판/평을 할 경우
            if (ye_entity.IsFirstJudgmentEvaluation())
            {
                /// 정체를 파악하고(독립체에 대한 정보 갱신), 뭘하는 생각하고(행동 갱신), 왜 그러는지
                /// 생각하는(의도 및 원인 등 갱신) 순서로 한다고 가정하자.

                // 정체 파악 : 독립체에 대한 정보 갱신 CharacterInfoUpdate
                {
                    // 종 파악하기
                    Ye_Race ye_race = new Ye_Race();
                    ye_race.Setup(setupData);
                    ye_race.Race = realEntity.Race;

                    ye_entity.Race = ye_race;

                    /// 이 독립체가 본적이 있는지 얼마나 친숙한지(비슷한 독립체 검색) 등을 파악(기억/경험 탐색)
                    /// 현재는 기억/경험 등의 시스템도 없고, 완전히 처음봤으므로 생략한다.
                }

                // 행동 파악 : 독립체가 현재 어떤 행동을 하고 있는지에 대해 판단 BehaviourJudgmentUpdate
                {
                    /// 행동을 어떻게 파악할까?
                    /// 일단 알 수 있는 정보는 이전과 현재의 위치, 액션, 형태 밖에 없다.
                    /// 물론, 경험이나 기억에서 얻거나 이전에 판단한 정보가 있을 수도 있다.
                    /// 하지만, 지금은 처음이므로 위치와 액션(애니메이션)정보를 토대로 판단해야한다.

                    // 이동 여부 판단
                    Ye_Move ye_move = new Ye_Move();
                    ye_move.Setup(setupData);

                    ye_move.Ye_focusTime = ye_timeCurrent;
                    ye_move.Ye_previousTime = ye_timePrevious;

                    ye_move.Pr_VariationPos.Ye_FocusData = ye_pos;
                    ye_move.Pr_VariationPos.Ye_previousData = ye_pos.Ye_previous;

                    if (ye_pos.Pos == ye_pos.Ye_previous.Pos)
                    {
                        ye_move.IsMove = false;
                    }
                    else
                    {
                        ye_move.IsMove = true;
                    }

                    // 행위(action) 갱신
                    Ye_Action ye_action = new Ye_Action();
                    ye_action.Setup(setupData);

                    ye_action.Ye_focusTime = ye_timeCurrent;
                    ye_action.Ye_previousTime = ye_timePrevious;

                    ye_action.Pr_VariationAction.Ye_FocusData = ye_actionState;
                    ye_action.Pr_VariationAction.Ye_previousData = ye_actionState.Ye_previous;

                    ye_action.ActionState = ye_actionState.State;
                }

                // 의도나 원인등은 첫번째 판/평에서는 생략한다고 가정하자.
            }
            // 이전에 판/평을 했을 경우
            else
            {
                /// 이 독립체가 어떤 녀석인지? 나와 무슨관계인지? 무슨 성격인지 등등
                /// 독립체 개인에 대한 정체/정보는 관찰되는 매 순간마다 바뀔 수 있다.
                /// 하지만, 그게 매 프레임마다 정해진 순서로 행해지는 것은 아닌 것 같다.
                /// 매 순간의 관찰자가 판단한 독립체의 행동을 평가하고 그것으로 부터 축적된 정보를
                /// 변화시키거나 쌓아나간다는 것이 올바른 표현이고 방법일 것이다.
                /// 결국 독립체의 정체/정보는 나중에 좀 더 깊이 만들어야 할 것이다.
                /// 단순히 종이나 겉모습만이 아닌, 예측된 성격, 관계, 소지중인 물품,
                /// 그리고 의도와 목표 행동까지 어떻게 보면 이 모든 것이 독립체를 나타내는 정보이자 정체이다.
                /// 그렇다면, 현재 구현하려는 것은 독립체가 매 순간 무엇을, 어떻게, 왜 하냐는 것이다.
                /// 독립체의 행동을 판단하고 평가해서 의도와 목적을 추측, 예측하는 것이다.

                /// 현재 단순하게 생각나는 방법은 판/평된 행동들은 기초적인 정보로 부터 만들어진 정보들로
                /// 이루어진 복잡한 행동까지를 스택처럼 보관하게 된다.
                /// 즉, 다음 순간에서는 그 스택된 행동들을 복잡한 순부터 가장낮은 정보까지 역으로 흩으며
                /// 새로운 정보들과 비교하며 스택하는 방식을 생각하고는 있다.

                /// 역스택 방식은 제쳐두고, 다시 생각해보니 각 행동/변화/사건(물리적)에 대해 함축/포괄하는것은
                /// 이전 프레임에 없던 새로운 상황에 대한 것도 있다.
                /// 즉, 역스택 방식은 단순히 연속된 상황에 대해서 유효한 것이지, 행동 전환이나
                /// 갑작스런 변화에 대해서는 별 도움이 되지않는다.
                /// 결국 완전히 기초적인 행동/변화로 부터 함축/포괄을 할 수 있어야 한다는 것인데,
                /// 문제는 현재의 상황이 수 많은 함축/포괄 중에서 어떤 것이지 어떻게 알 수 있냐는 것이다.
                /// 솔직히 아직도 이 문제에 대한 해결책을 찾지 못하겠다.
                /// 그래서 일단 단순히 정해진 상황을 정해진 염소로 함축/포괄하는 식으로 만들면서
                /// 뭔가 특별한 알고리즘이 존재 하는지 찾아보는 방식으로 만들어야 할 것 같다.

                /// 가장 단순하게 '걷고있다'라는 함축/포괄을 나타내보자.
                /// 일단 대략적인 관계도는 변화 'move'의 원인으로 변화 'action:walk'가 있고, 그것들로 부터
                /// 전체적인 행동이 'behavior:walk'라고 결론내리는 것인데, 어디서 부터 시작해야 하는가?
                /// 

                // 우선 이동여부와 이동했다면 그 원인이 무엇인지 부터?
                Ye_Move ye_move = new Ye_Move();
                ye_move.Setup(setupData);

                ye_move.Ye_focusTime = ye_timeCurrent;
                ye_move.Ye_previousTime = ye_timePrevious;

                ye_move.Pr_VariationPos.Ye_FocusData = ye_pos;
                ye_move.Pr_VariationPos.Ye_previousData = ye_pos.Ye_previous;

                if (ye_pos.Pos == ye_pos.Ye_previous.Pos)
                {
                    ye_move.IsMove = false;
                }
                else
                {
                    ye_move.IsMove = true;
                }

                // 행위(action) 갱신
                Ye_Action ye_action = new Ye_Action();
                ye_action.Setup(setupData);

                ye_action.Ye_focusTime = ye_timeCurrent;
                ye_action.Ye_previousTime = ye_timePrevious;

                ye_action.Pr_VariationAction.Ye_FocusData = ye_actionState;
                ye_action.Pr_VariationAction.Ye_previousData = ye_actionState.Ye_previous;

                ye_action.ActionState = ye_actionState.State;

                /// 함축/복합 염소의 기본요소로 크게 '원인/이유', '변화/결과', '목적/의도', '주체'로
                /// 나뉜다고 가정해보자. 근거도 너무 빈약하고, 기준도 애매하며, 왜 저렇게 나눴느지 모르겠지만
                /// 더 근본적이고 논리적인 분류나 방법이 떠오르지 않는다.
                /// 그리고 가장 기초적인 이동여부나 행위같은 염소의 기본요소부터 채워 가는 것이다.
                /// 그리고 그 시간때의 모든 기본요소를 채우고 나서 그것들로 부터 함축을 시켜야 한다.

                /// 일단 전체적인 그림은 낮은부분부터든 높은 부분부터든 재귀적인 형태로 함축이 더 이상
                /// 안될 경우 까지 계속해서 함축을 반복하는것이다.
                /// 여기서 생각해보면 몇가지 문제가 있다.
                /// 첫번째로 위에서 제시한 기본구성요소를 채우는 방식으로 한다고 하는데, 이걸 어떻게
                /// 가능한지가 문제이다. 단순하게 'move'의 '원인/이유'를 구한다고 해도, 이게 쉽자않다.
                /// 이동의 원인은 크게 2가지이다. 힘과 시스템적 위치변경.
                /// 여기서 시스템 위치 변경은 게임 물리법칙을 따르지 않는 이동, 즉 텔레포트같은 것들이다.
                /// 문제는 단거리로 위치 이동을 했을 경우, 어떻게 이걸 일반적 힘에 의한 이동과 구분하는거냐는 것이다.
                /// 지금 당장은 매 순간 연속적인 생각갱신을 하므로, 어느정도의 제약을 걸면 가능할 것이다.
                /// 하지만 그걸 떠나서도 힘에 의한 이동도 이걸 인지하는 관찰자의 입장에서는 다르다는 것이다.
                /// 관찰자는 저지능 생물부터 인간같은 고지능까지 있을 수 있다. 인간이라쳐도 힘에 대한
                /// 지식이 없을 수도 있고 안다고 해도 매 순간 판단에서 독립체의 이동에 판단에 외력계산등을
                /// 하지는 않을 것이다.
                /// 그렇다면 매 순간 이동에 대한 판단을 어떻게 해야 할까? 아니 하는게 맞는가?
                /// 이동은 그저 그게 순간이동인지 연속된(힘에의한)이동인지만 구분해 놓으면 되는것 가인가?
                /// 뭐, 방향같은 이동에 대한 정보도 있을 수 있겠지만, 이동에 원인/이유? 이런게 필요한가?
                /// 다시 생각해보자. '이동'염소에 '원인/이유'를 알아야 할 이유가 뭘까?
                /// 특정 행동(걷다, 도망치다, 춤추다)에 따른 조건인지 혹은 그 반동으로 이동이 발생했는지
                /// 알기 위해서 이지 않을까? 그렇다면, 반대로 그건 그 특정행동의 판단에서 확인해야 하는것이지
                /// '이동'이라는 염소에서 미리 원인을 찾을 필요는 없을 것이다.
                /// 외부적 요인에 의한 이동까지 고려한다면 어떨까? 즉, 현재 이동이 걷는 행동에 의한 것인지
                /// 아니면 외력에 의한 이동인지 판단하기 위해서는 '이동'자체가 어느 원인에서 발생했는지
                /// 알아야 할 것이다.
                /// 그래서 '원인/이유'를 찾아야한다 말인가 아닌가?
                /// 지금 중요 요점은 판단 순간의 '이동'이 특정 행동 때문인지, 아니면 그외 다른 원인에서
                /// 일어난 것인지 판단하기 모호하다는 것이다.
                /// 결국 이건 상황을 봐야 알 수 있는 것 아닌가?
                /// 여기서 상황이란 이전까지의 연속된 염소들의 판/평을 의미하는 것이고, 이전 것들과 현재 염소들을
                /// 하나씩 점검하면서 원인을 파악해야 할 것이다.
                /// 그래서 '이동'의 '이유/원인'을 찾을 필요가 있는가?
                /// 솔직히 모르겠다. 하지만 다른 관점에서 생각해보자.
                /// '원인/이유'의 유무는 결국 특정행동의 판단이나 특정행동을 찾는 것에 관점이 있다.
                /// 즉, 현재 특정 행동을 찾는 방법이나, 특정 행동의 판단 방법이 없는 상황에서는 필요없다는 것이다.

                /// 두번째로 가장 중요한 특정 행동의 결정 방법, 함축 할 염소를 찾는 것이다.
                /// 당장 떠오르는 것은 지식/기억의 활용이다. 모르는 행동에 대해 생각할 수 없다.
                /// 상식/본능 선에서 알고 있는 지식과 기억으로 전체 상황을 함축/묘사 해야 할 것같다.
                /// 여기서 또 다른 문제들이 당장 떠 오르는데, 한가지는 어떻게 수 많은 상식/본능들을
                /// 미리 구현해 놓을 것이며 지능수준에 따라 어떻게 나누어 어느 수준으로 만들것이냐는것이다.
                /// 다른 하나는 그렇다면 완전 처음보는 행동들과 상황에 대해 어떻게 대처할 것이냐는 것이다.
                /// 이건 다른 말로는 어떻게 새로운 지식과 경험을 쌓아가냐나는 것이기도 한데,
                /// 당장 처음보는 상황에 대해 최대한 올바르고 논리적인 판단과 평가를 해야한다는 전제가있다.
                /// 우선 처음보는 새로운 상황/행동은 미뤄두고, 알고 있는 상황/행동들에 대한 판단/결정을 해결하자.
                /// 위에 말했듯이 지식/기억/경험 등을 활용하는 방법이 있을 것이다.
                /// 문제는 어떻게 수 많은 지식/기억/경험 등을 만들 것이며, 그것들 중에서 어떤 것이
                /// 현재 상황/행동에 알맞은 것인지 고르고 선택하는 것이다.

                bool enableImply = true;

                // 더 이상 함축/포괄/판단/묘사가 불가능 할 때까지 계속해서 함축/포괄/판단/묘사를 실행한다.
                while (enableImply)
                {
                    BehaviourOverTime behaviours = null; //= ye_entity.RecentBehaviors;

                    // 최근 행동들이 없는 경우
                    if (behaviours == null | behaviours.Ye_time != ye_timeCurrent | behaviours.Hash_Behaviors == null)
                    {
                        /// action을 위주로 행동 선택?
                        /// 현재 알 수 있는 것은 위치,행위,모습 그리고 이전 행동들이다.
                        /// 이전 행동들은 항상 존재하는게 아니며 행동자체가 갑자기 바뀔 수 있으므로,
                        /// 다른 것들로 부터 우선 행동을 유추해야 한다.
                        /// 결국 남은 것은 위치의 변화, 행위의 변화, 그리고 나머지 정보들(모습, 장비,종족등등)이다.
                        /// 결국 우선 관찰중인 객체 자체에서 하는 자발적인 행동, 즉 현재 행위에서 유추해야한다.
                        ConceptList conceptList = ConceptMemory[ye_action.ActionState];

                        if (conceptList == null)
                        {
                            // 처음 보는 행위에 대한 처리
                            // 새로운 행동 작성?
                        }
                        else
                        {
                            // 현재 행위에 해당하는 개념들중 현재 상황/행동에 알맞는 행동을 찾아야한다.
                            foreach (var concept in conceptList)
                            {
                                // 각 개념에서 조건에 부합하는지를 확인하고 판단한다.

                            }
                        }
                    }
                    // 최근 행동들이 있고, 여기서 함축을 시작하는 경우
                    else
                    {

                    }
                }
            }
        }

        // 새롭게 관찰된 객체에 대한 처리
        foreach (var newEntity in EnterObservedEntities)
        {
            Ye_Entity ye_entityNew = new Ye_Entity(newEntity);

            Ye_Position position = new Ye_Position();
            Ye_ActionState action = new Ye_ActionState();

            position.Owner = ye_entityNew;
            action.Owner = ye_entityNew;

            position.Time = ye_timeCurrent;
            action.Time = ye_timeCurrent;

            position.Pos = newEntity.transform.position;
            action.State = newEntity.AS;

            ye_entityNew.Ye_position = position;
            ye_entityNew.Ye_actionState = action;

            StorageEntitiesTable.AddLast(ye_entityNew);
        }
    }

    /// <summary>
    /// 2020.06.21
    /// 개념을 만들어서 적용하기 위해서 몇가지 수정을 거쳐야 할 것 같다.
    /// 우선 상념(염소들)의 처리 단계를 나누어야 할 것 같다.
    /// 1. 단순하게 관찰정보를 염소로 만들고, 직전 염소들과 비교해서 이동여부와 행위를 판/평 한다.
    /// 2. 판별된 정보(이동여부,행위)와 지금 까지의 정보들을 이용해서 새로운 정보에 대한 원인/이유를 추측한다.
    /// 3. 지금 까지의 정보들로부터 현재의 상황에 맞는 행동을 개념에서 찾아서 확인하고 판/평 한다.
    /// 
    /// 그리고 다른 중요한 것은 동적 개념의 생산과 활용이다.
    /// 처음보는 새로운 상황에 대한 새로운 개념을 만들어서 지식을 쌓는 방법을 만들어야 한다.
    /// 일단은 게임의 시작과 동시에 미리 만들어둔 개념을 개념에 추가하고,
    /// 그것으로 현재 상황을 판/평하는게 우선일 것이다.
    /// </summary>
    void ImplementThought4()
    {
        // 상념의 기초 현재 순간의 시간을 만들어서 연결, 이전 시간을 마크해둔다.

        LinkedListNode<Ye_Time> nodeCurrentTime = StorageTimeTable.AddLast(new Ye_Time(Time.time));

        FirstThoughtUpdate(nodeCurrentTime);
        SecondThoughtUpdate(nodeCurrentTime);
        //ThirdThoughtUpdate(nodeCurrentTime);
        EnterEntitiesProcess(nodeCurrentTime);

        EnterObservedEntities.Clear();
        ExitObservedEntities.Clear();

        foreach (var ye_entity in StorageEntitiesTable)
        {
            if (ye_entity.RecentYeomsos == null)
            {
                continue;
            }

            foreach (var key in ye_entity.RecentYeomsos.Hash_Yeomsos.Keys)
            {
                key.DebugLogType();
            }
        }
    }

    /// <summary>
    /// 새롭게 추가된 독립체들에 대한 판/평하기에는 아직 정보가 부족하다.
    /// 즉, 다음 생각순간부터 처리해야하는데, 이걸 먼저 하면 인지중인 독립체들의 판/평에서
    /// 방해되므로 따로 빼서 기존 인지에 대한 판/평이 끝난 뒤에 실시하도록 하자.
    /// + 하지만 인지된 물체에 대한 판/평을 전혀 안하기에는 또 좀 이상하다.
    /// 이건 나중에 어느정도까지 처리할지를 생각하고 어느 순간에 넣어야 할지도 다시 생각하자.
    /// </summary>
    /// <param name="ye_timeCurrent"></param>
    void EnterEntitiesProcess(LinkedListNode<Ye_Time> nodeCurrentTime)
    {
        foreach (var enterEntity in EnterObservedEntities)
        {
            Ye_Entity ye_entityNew = new Ye_Entity(enterEntity);

            UI_Yeomso ui = UIManager.SpawnUIYeomsoAddedVerticalLayer(Time.time);
            ui.LabelText.text = enterEntity.name;
            ye_entityNew.UIYeomso = ui;

            Ye_Position position = new Ye_Position();
            Ye_ActionState action = new Ye_ActionState();

            position.Owner = ye_entityNew;
            action.Owner = ye_entityNew;

            position.Time = nodeCurrentTime.Value;
            action.Time = nodeCurrentTime.Value;

            position.Pos = enterEntity.transform.position;
            action.State = enterEntity.AS;

            ye_entityNew.Ye_position = position;
            ye_entityNew.Ye_actionState = action;

            StorageEntitiesTable.AddLast(ye_entityNew);
        }
    }

    /// <summary>
    /// 현재 시간에 관찰정보를 기본 정보 염소들로 만들고, 직전 시간의 기본 정보 염소들과
    /// 비교해서 이동여부, 행위 등을 판별한다.
    /// </summary>
    void FirstThoughtUpdate(LinkedListNode<Ye_Time> nodeCurrentTime)
    {
        /// enter, stay, exit 에서 exit => stay => enter 순으로 관찰정보를 처리한다.
        /// 그 이유는 단순하게 stay가 가장 많은 부분을 차지하게 될텐데, 이걸 ObservedEntities에서
        /// 독립체(Entity)마다 처리하려면 현재 관찰자가 가지고 있는 상념에서 각 독립체마다 알맞은
        /// 독립체염소(Ye_Entity)를 찾아서 처리해야한다.
        /// 그러면 귀찮으니깐, 우선 ExitObservedEntities를 처리하면 인지 중인 독립체 염소들만 남은
        /// StorageEntitiesTable에서 각 독립체염소마다 미리 연결된 실제 객체를 처리하면 쉽기 때문이다.
        /// 단순하게 Entity->Ye_Entity를 참조 할 수 없지만, 반대로 Ye_Entity->Entity는 가능하기 때문에
        /// 저런 순서로 처리하게 되었다.
        /// 마지막에 EnterObservedEntities를 처리한것은, 앞서서 새롭게 독립체염소를 추가하면
        /// 추가된 염소는 두번 처리되기 때문에 귀찮아서 뒤로 뺀 것이다.
        /// + 다시 생각 해보니 새롭게 추가된 독립체는 기존 모든 독립체에 대한 행동 판/평이 끝난 뒤에 와야한다.
        /// 따라서 이 메서드에서 enter독립체들에 대한 부분을 지우고 따로 만들어야한다.

        // 인지에서 사라진 독립체들에 대한 처리
        foreach (var exitEntity in ExitObservedEntities)
        {
            // 일단 나중에 구현한다.
            var node = StorageEntitiesTable.Find((n) => n.RealEntity == exitEntity);

            Debug.Log("Remove Yeomso : " + node.Value.RealEntity.name);

            StorageEntitiesTable.Remove(node);
        }


        // 인지 중이던 독립체들에 대한 처리
        foreach (var ye_entity in StorageEntitiesTable)
        {
            Entity realEntity = ye_entity.RealEntity;
            Ye_Time ye_timePrevious = nodeCurrentTime.Previous.Value;

            DependentYeomsoSetupStruct setupData;

            setupData.owner = ye_entity;
            setupData.time = nodeCurrentTime.Value;

            // 위치 염소를 상념에 부착
            Ye_Position ye_pos = new Ye_Position();
            ye_pos.Setup(setupData);
            ye_pos.Pos = realEntity.transform.position;

            ye_pos.LinkPreviouYeomso(ye_entity.Ye_position);
            ye_entity.Ye_position = ye_pos;

            // 행위 염소를 상념에 부착
            Ye_ActionState ye_actionState = new Ye_ActionState();
            ye_actionState.Setup(setupData);
            ye_actionState.State = realEntity.AS;

            ye_actionState.LinkPreviouYeomso(ye_entity.Ye_actionState);
            ye_entity.Ye_actionState = ye_actionState;

            // 이동 여부 판단
            Ye_Move ye_move = new Ye_Move();
            ye_move.Setup(setupData);

            ye_move.Ye_focusTime = nodeCurrentTime.Value;
            ye_move.Ye_previousTime = nodeCurrentTime.Value;

            ye_move.Pr_VariationPos.Ye_FocusData = ye_pos;
            ye_move.Pr_VariationPos.Ye_previousData = ye_pos.Ye_previous;

            if (ye_pos.Pos == ye_pos.Ye_previous.Pos)
            {
                ye_move.IsMove = false;
            }
            else
            {
                ye_move.IsMove = true;
            }

            ye_entity.Ye_move = ye_move;

            // 행위(action) 갱신
            Ye_Action ye_action = new Ye_Action();
            ye_action.Setup(setupData);

            ye_action.Ye_focusTime = nodeCurrentTime.Value;
            ye_action.Ye_previousTime = nodeCurrentTime.Value;

            ye_action.Pr_VariationAction.Ye_FocusData = ye_actionState;
            ye_action.Pr_VariationAction.Ye_previousData = ye_actionState.Ye_previous;

            ye_action.ActionState = ye_actionState.State;

            ye_entity.Ye_action = ye_action;

            // 현재시간의 염소집합체의 생성과 생성된 염소(이동/행위)의 추가
            YeomsosPerTime currenttYeomsosPerTime = new YeomsosPerTime();

            currenttYeomsosPerTime.Add(ye_move);
            currenttYeomsosPerTime.Add(ye_action);

            ye_entity.ListYeomsosPerTime.AddLast(currenttYeomsosPerTime);
        }
    }

    /// <summary>
    /// 첫번째로 판별된 기본 정보 염소들과 이전의 염소들을 이용해서 현재 일어난
    /// 기본 정보 염소의 원인과 기본 관계를 판별한다.
    /// + 정체파악(종,기억 검색 등)을 여기서 해야할까? 한다면 새롭게 인지된 독립체들은?
    /// </summary>
    void SecondThoughtUpdate(LinkedListNode<Ye_Time> nodeCurrentTime)
    {
        /// 사건과 행동들에 그리고 결과에 대한 '인과'와 '개연성/우연성/확실성/필연성'등을
        /// 연결해서 그것들에 대한 '관계'를 연결하자는 것인데, 아직 감이 안 잡힌다.
        /// 솔직히 이걸 어떻게 구현할지, 정말 필요한지 조차도 모르겠다.
        /// 그리고 사건? 
        /// 현재까지는 관찰자는 인지된 독립체들에 대해서만 행동등을 판/평했다.
        /// 그런데 그것 만으로 '상황'이라는 것을 나타 낼 수 있을까? 아니, 그전에
        /// 현재 생각하는 방식으로 각 독립체마다가 아닌 독립체들간의 전체적인 묘사가 가능한가?
        /// '전체적인 묘사, 상황, 사건' 어쩌면 이게 다 같은 말일지도 모른다.
        /// 그리고 아직 여기에 대해 더 생각해봐야한다.
    }

    /// <summary>
    /// 현재 시간에 대해 각 독립체의 염소들을 함축/포괄/묘사를 실시한다.
    /// </summary>
    void ThirdThoughtUpdate(LinkedListNode<Ye_Time> nodeCurrentTime)
    {
        foreach (var ye_entity in StorageEntitiesTable)
        {
            if (ye_entity.IsFirstJudgmentEvaluation())
            {
                continue;
            }

            Debug.Log("ActionState : " + ye_entity.Ye_action.ActionState);

            ConceptList conceptList = ConceptMemory[ye_entity.Ye_action.ActionState];

            if (conceptList != null)
            {
                // foreach (conceptList)
                Ye_Dependent ye_behavior;

                if (conceptList[0].ImpliedYeomso(ye_entity, out ye_behavior) == true)
                {
                    ye_behavior.Time = nodeCurrentTime.Value;
                    ye_entity.RecentYeomsos.Add(ye_behavior);
                }
            }
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        Debug.Log("Enter");

        /// 새롭게 관찰된 항목들의 처리
        /// 새로운 오브젝트가 관찰된다면, 어떤 것들을 해야 할까?
        /// 우선 이해/정보화/판/평의 제외하고 생각한다면 상황(키프레임)에 추가를 해야 할 것이다.

        if (EnterObservedEntities.Count != 0)
        {
            Debug.Log("EnterObservedEntities : 어디선가 이걸 처리하고, 비워줘야한다.");
        }

        SituationObject newObject = new SituationObject();

        Entity observedEntity = collision.GetComponent<Entity>();

        if (observedEntity == null)
        {
            Debug.Log("충돌체의 단일체컴포넌트가 없다면 뭔가 문제가 있다.");
        }

        newObject.InstanceID = observedEntity.GetInstanceID();
        newObject.AddFactor(observedEntity);

        EnterObservedEntities.AddLast(observedEntity);
        SituationObjects.AddLast(newObject);

        /// 상황에 추가 했다. 그 다음은?
        /// 상황에 대한 주관적인 생각없이 있는 그대로의 자료를 기입하는 것은 쉽다.
        /// 하지만, 이건 견해/이해가 없는 빈껍데기일 뿐이다.
        /// 즉, 사견/이해가 들어가야한다는 말이다.
        /// 그렇다면 언제, 어떻게 만들어내냐가 문제이다.
        /// 새롭게 관찰된 물체에 대해 사견/이해 가 필요한가?
        /// 모르겠다. 필요한것 같기는 한데, 어떤 식으로, 그리고 새로운 물체에 대한 검색은 어떻게?
        /// 일단 확실히 생각되는 것은 이미 관찰 중인 물체에 변화가 생겼을 때는
        /// 그 변화를 인지하고, 변환 상황에 대한 새로운 견해/이해가 필요할 것이라는 것이다.
        /// 거기에다가 지금 당장 떠오르지 않는 새로운 물체에 대한 검색등의 문제도 없다.
        /// 우선 관찰 중인 물체의 변화에 대해서 처리하고 오자.
    }

    private void OnTriggerStay2D(Collider2D collision)
    {
        Debug.Log("Stay");

    }

    /// 관찰 중이던 물체에 대한 변화를 감지하고, 갱신한다.
    /// 즉, enter/exit가 새롭게 추가/삭제에 대한 감지 처리라면,
    /// 이 함수는 OnTriggerStay에 대응하는 감지 중이던 물체에 대한 처리이다.
    void UpdateSituation()
    {
        var entityNode = ObservedEntities.First;
        var situationNode = SituationObjects.First;

        Entity observedEntity;
        SituationObject situationObject;

        // 새롭게 추가/삭제 된 오브젝트가 있을 경우 enter/exit에서 잘 처리할 것이므로,
        // 예외가 있지 않는 이상, situationObjects와 observedEntities의 순서는 일치할 것이다.
        while (entityNode != null)
        {
            observedEntity = entityNode.Value;
            situationObject = situationNode.Value;

            if (observedEntity.InstanceID != situationObject.InstanceID)
            {
                Debug.Log("뭔가 잘못된 거임.");
            }

            /// 관찰 중이던 물체의 변화 감지(나중에 따로 메소드로 리팩토링도 고려해볼것.)
            /// 현재는 행동과 속도만 비교하지만, 속도가 아니라 예상위치를 비교하는 것이
            /// 좀 더 정확할 것이다. 또한 변화의 감지에 대한 것은 집중도에 따라 다르므로
            /// 나중에 알고리즘을 만들어 내는 것이 좋은 것이다.
            /// 거기다가 특정 시간(예를들면 0.5초)이상 변화가 없으면, 키프레임을 생성하는 것이
            /// 상황을 기억하고 형성하는데 더 도움이 될 것이다.
            if (observedEntity.AS != situationObject.RecentFactor.AS ||
                 observedEntity.RD2D.velocity != situationObject.RecentFactor.Vel)
            {
                situationObject.AddFactor(observedEntity);

                Debug.Log("변화가 감지된 키프레임수 : " + situationObject.FactorList.Count);
            }

            entityNode = entityNode.Next;
            situationNode = situationNode.Next;

            /// 여기까지가 사견/이해/판/평이 없는 변화의 감지 영역이다.
            /// 아마 저 위의 addFactor메소드 밑에 그 부분이 들어가야할 것이다.(리팩토링 필요)
            /// 변화를 감지한 순간 어떤 생각을 해야 할까?

            /// 생각/사고/상념 의 가장 작은 단위라 할 수 있는 형태소(morpheme)를 만들것이다.
            /// 어디까지나 가장 작은단위라는 뜻에서 형태소이지, 단어의 개념이 아니라 생각/정보를 기호화한 개념이다.
            /// 생각/사고 의 원소, 원자 라는 의미로 이름을 지어도 괜찮을 것 같다. (염소? 염자? 사소? 사자?)
            /// 딱히 찾아보아도 생각을 이루는 개념/정보/지식의 가장 작은 단위를 나타내는 말은 없어보인다.
            /// 다른 뜻과 혼동돼지 않도록 '염소(Yeomso)'라고 부르자.
            /// 하여튼, 이제 부터 염소를 만들 것이다. 그리고 미리 적절하게 생각 중을 구성해 놓아야한다.
            /// 즉, 초기화를 통해 초기 배치를 해놓는게 관건이다.
            /// 예상으로는 Setup의 내용과 염소의 구성을 조절하면, 상념의 기초를 만들 수 있을 거라고 본다.
        }

        if (situationNode != null)
        {
            Debug.Log("뭔가 잘못된 거임.");
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        Debug.Log("Exit");

        if (ExitObservedEntities.Count != 0)
        {
            Debug.Log("ExitObservedEntities : 어디선가 이걸 처리하고, 비워줘야한다.");
        }

        Entity observedEntity = collision.GetComponent<Entity>();

        if (observedEntity == null)
        {
            Debug.Log("충돌체의 단일체컴포넌트가 없다면 뭔가 문제가 있다.");
        }

        ExitObservedEntities.AddLast(observedEntity);
    }
}
