using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI_Yeomso : MonoBehaviour
{
    static private UIManager_Thought uIManager;
    public static UIManager_Thought UIManager { get => uIManager; set => uIManager = value; }

    public enum EUpdateState
    {
        LinerIncrease,
        SideScroll,
        Accumulation
    }

    protected static EUpdateState updateState = EUpdateState.LinerIncrease;
    public static EUpdateState UpdateState { get => updateState; set => updateState = value; }

    public RectTransform rtButton;
    public RectTransform rtLabel;
    public RectTransform rtElapse;
    private Text labelText;
    public Text LabelText { get => labelText; }

    //private List<UI_Yeomso> children;
    private float startTime;
    private float time;
    private float timePos;
    private float top;
    private float left;
    private float height;
    private float labelWidth;

    //public float TimePos { set => timePos = value; }
    public float StartTime { get => startTime; set => startTime = value; }
    public float Time { get => time; set => time = value; }
    public float Top { get => top; set => top = value; }
    public float Left { get => left; set => left = value; }
    public float Height { get => height; set => height = value; }
    public float LabelWidth { get => labelWidth; set => labelWidth = value; }

    protected UI_Yeomso() { }

    private void Awake()
    {
        labelText = rtLabel.GetComponentInChildren<Text>();
    }

    private void Update()
    {
        timePos = uIManager.GetNormalizedTimePosition(time);

        switch (updateState)
        {
            case EUpdateState.LinerIncrease:
                UpdateRectTransform();
                break;
            case EUpdateState.SideScroll:
                float interval = rtButton.anchorMax.x - timePos;
                left -= interval;
                UpdateRectTransform();
                break;
            case EUpdateState.Accumulation:
                left = uIManager.GetNormalizedTimePosition(startTime) - labelWidth;
                UpdateRectTransform();
                break;
        }
    }

    private void UpdateRectTransform()
    {
        float temp = (timePos - left);

        if (temp <= labelWidth)
        {
            left = timePos - labelWidth;
            temp = 1.0f;
        }
        else
        {
            temp = labelWidth / temp;
        }

        rtButton.anchorMax = new Vector2(timePos, top);
        rtButton.anchorMin = new Vector2(left, top - height);

        rtLabel.anchorMax = new Vector2(temp, 1.0f);

        rtElapse.anchorMin = new Vector2(temp, 0.0f);
    }

    //public void SetVerticalPosition(float top, float height)
    //{
    //    Vector2 temp;

    //    // max
    //    temp = rtElapse.anchorMax;
    //    temp.y = top;
    //    rtElapse.anchorMax = temp;

    //    rtButton.anchorMax = temp;

    //    temp.x = rtElapse.anchorMin.x;
    //    rtLabel.anchorMax = temp;

    //    // min
    //    temp = rtElapse.anchorMin;
    //    temp.y = top - height;
    //    rtElapse.anchorMin = temp;

    //    temp.x = rtLabel.anchorMin.x - height;
    //    rtLabel.anchorMin = temp;

    //    rtButton.anchorMin = temp;
    //}
}
