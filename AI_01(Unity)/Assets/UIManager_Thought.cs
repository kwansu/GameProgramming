using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIManager_Thought : MonoBehaviour
{
    // ui 풀링용
    private Queue<UI_Yeomso> queueData;
    public Transform PoolTransform;
    public GameObject PrefabTarget;// { get; set; }

    // 시간 관련
    public UI_Yeomso UI_Time;// { get; set; }
    public TemporaryAI AIProcesser;//{ get; set; }
    public float MaxTimePos;// { get; set; }
    public float TimeMaxRatio;
    private float elapsedTime;

    // layer 배치 관련 : 전부 정규화된 비율 값
    public float Top;
    public float Left;
    public float Height;
    public float LabelWidth;
    public float LayerInterval;
    private int layerCount;

    void Start()
    {
        UI_Yeomso.UIManager = this;
        Initialize(100);
        TimeMaxRatio = MaxTimePos / TimeMaxRatio;

        UI_Time.Top = GetVerticalLayerTop(layerCount++);
        UI_Time.Left = Left;
        UI_Time.Height = Height;
        UI_Time.LabelWidth = LabelWidth;

        UI_Time.LabelText.text = "Time";
    }

    private void Update()
    {
        elapsedTime = Time.time;

        UI_Time.Time = elapsedTime;

        if (UI_Yeomso.UpdateState == UI_Yeomso.EUpdateState.LinerIncrease &&
            Left + elapsedTime * TimeMaxRatio >= MaxTimePos)
        {
            UI_Yeomso.UpdateState = UI_Yeomso.EUpdateState.Accumulation;

            Vector2 temp = UI_Time.rtButton.anchorMax;
            temp.x = GetNormalizedTimePosition(elapsedTime);
            UI_Time.rtButton.anchorMax = temp;
        }

    }

    public float GetVerticalLayerTop(int layerIndex)
    {
        return Top - layerIndex * Height - (layerIndex - 1) * LayerInterval;
    }

    public float GetNormalizedTimePosition(float time)
    {
        float timePos = Left;

        switch (UI_Yeomso.UpdateState)
        {
            case UI_Yeomso.EUpdateState.LinerIncrease:
                timePos += time * TimeMaxRatio;
                break;
            case UI_Yeomso.EUpdateState.SideScroll:
                timePos = MaxTimePos - (elapsedTime - time) * TimeMaxRatio;
                if (timePos < Left)
                {
                    timePos = Left;
                }
                break;
            case UI_Yeomso.EUpdateState.Accumulation:
                timePos += time * ((MaxTimePos - Left) / elapsedTime);
                break;
        }

        return timePos;
    }

    private void Initialize(int count)
    {
        queueData = new Queue<UI_Yeomso>(count);

        for (int i = 0; i < count; ++i)
        {
            queueData.Enqueue(CreateUIYeomso());
        }
    }

    private UI_Yeomso CreateUIYeomso()
    {
        if (PrefabTarget == null)
        {
            Debug.LogError(1);
        }

        GameObject newObject = Instantiate<GameObject>(PrefabTarget);
        newObject.SetActive(false);
        newObject.transform.SetParent(PoolTransform);

        return newObject.GetComponent<UI_Yeomso>();
    }

    public UI_Yeomso SpawnUIYeomso()
    {
        UI_Yeomso result;

        if (queueData.Count == 0)
        {
            Debug.LogWarning(2);

            result = CreateUIYeomso();
        }
        else
        {
            result = queueData.Dequeue();
        }

        result.gameObject.SetActive(true);
        result.transform.SetParent(transform);

        result.rtButton.localPosition = Vector2.zero;
        result.rtButton.sizeDelta = Vector2.zero;
        result.LabelWidth = LabelWidth;

        return result;
    }

    public void ReturnUIYeomso(UI_Yeomso target)
    {
        target.transform.SetParent(PoolTransform);
        target.gameObject.SetActive(false);
        queueData.Enqueue(target);
    }

    public UI_Yeomso SpawnUIYeomsoAddedVerticalLayer(float startTime = 0.0f)
    {
        UI_Yeomso result = SpawnUIYeomso();

        result.StartTime = startTime;
        result.Time = startTime;
        result.Left = GetNormalizedTimePosition(startTime) - LabelWidth;
        result.Top = GetVerticalLayerTop(layerCount++);
        result.Height = Height;

        return result;
    }
}
